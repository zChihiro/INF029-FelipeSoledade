"""
servidor.py - servidor da versao WEB do catalogo de livros.

Ele faz o papel de "garcom" entre o navegador e o programa em C:

    Navegador (index.html)  <-->  servidor.py  <-->  ponte_c.py  <-->  catalogo (C)

O servidor NAO ordena nada: ele repassa o pedido para o C (pela mesma
ponte_c.py da versao Tkinter) e devolve a resposta ao navegador.

Para rodar (depois de compilar o C):
    python3 servidor.py          (no Windows: python servidor.py)
Depois abra o endereco mostrado: http://localhost:8000
"""
import json
import math
import os
import sys
import threading
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from urllib.parse import urlparse, parse_qs

from ponte_c import ProgramaC

PASTA = os.path.dirname(os.path.abspath(__file__))
NOME_EXE = "catalogo.exe" if os.name == "nt" else "catalogo"
CAMINHO_EXE = os.path.join(PASTA, NOME_EXE)
CAMINHO_PAGINA = os.path.join(PASTA, "index.html")

CRITERIOS = ("nome", "preco")
ORDENS = ("crescente", "decrescente")

programa_c = None              # o programa em C, aberto uma unica vez
trava = threading.Lock()       # garante que so um pedido fala com o C por vez


def limpar_nome(nome):
    """Prepara o nome para o C: sem ';' e sem quebra de linha, e no maximo
    49 bytes (o C guarda o nome em char[50])."""
    nome = nome.replace(";", ",").replace("\r", " ").replace("\n", " ").strip()
    return nome.encode("utf-8")[:49].decode("utf-8", "ignore")


class Handler(BaseHTTPRequestHandler):

    def log_message(self, formato, *args):
        pass   # deixa o terminal limpo (sem uma linha por pedido)

    def _responder_json(self, codigo, dados):
        corpo = json.dumps(dados, ensure_ascii=False).encode("utf-8")
        self.send_response(codigo)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(corpo)))
        self.end_headers()
        self.wfile.write(corpo)

    def _enviar_pagina(self):
        with open(CAMINHO_PAGINA, "rb") as arquivo:
            corpo = arquivo.read()
        self.send_response(200)
        self.send_header("Content-Type", "text/html; charset=utf-8")
        self.send_header("Content-Length", str(len(corpo)))
        self.end_headers()
        self.wfile.write(corpo)

    # ---------------------------------------------------------- GET
    def do_GET(self):
        url = urlparse(self.path)

        if url.path == "/":
            self._enviar_pagina()

        elif url.path == "/api/ordenar":
            consulta = parse_qs(url.query)
            criterio = consulta.get("criterio", [""])[0]
            ordem = consulta.get("ordem", [""])[0]

            if criterio not in CRITERIOS or ordem not in ORDENS:
                self._responder_json(400, {"erro": "critério ou ordem inválidos"})
                return
            try:
                with trava:
                    livros = programa_c.ordenar(criterio, ordem)   # <-- quem ordena e o C
            except (RuntimeError, OSError) as erro:
                self._responder_json(500, {"erro": str(erro)})
                return

            self._responder_json(200, {
                "livros": [{"nome": n, "preco": p} for n, p in livros]})

        else:
            self._responder_json(404, {"erro": "não encontrado"})

    # ---------------------------------------------------------- POST
    def do_POST(self):
        if urlparse(self.path).path != "/api/cadastrar":
            self._responder_json(404, {"erro": "não encontrado"})
            return

        try:
            tamanho = int(self.headers.get("Content-Length", 0))
            dados = json.loads(self.rfile.read(tamanho).decode("utf-8"))
            nome = limpar_nome(str(dados.get("nome", "")))
            preco = float(dados.get("preco"))
        except (ValueError, TypeError, AttributeError):
            self._responder_json(400, {"erro": "dados inválidos"})
            return

        if not nome or not math.isfinite(preco):
            self._responder_json(400, {"erro": "informe um nome e um preço válidos"})
            return

        try:
            with trava:
                total = programa_c.cadastrar(nome, preco)          # <-- quem guarda e o C
        except (RuntimeError, OSError) as erro:
            self._responder_json(500, {"erro": str(erro)})
            return

        self._responder_json(200, {"total": total})


def main():
    global programa_c

    porta = int(sys.argv[1]) if len(sys.argv) > 1 else 8000

    if not os.path.exists(CAMINHO_EXE):
        print(f"Não achei '{NOME_EXE}'. Compile antes, nesta pasta:")
        print("    gcc main.c livro.c -o catalogo")
        sys.exit(1)

    programa_c = ProgramaC(CAMINHO_EXE)
    servidor = ThreadingHTTPServer(("127.0.0.1", porta), Handler)

    print(f"Servidor rodando em http://localhost:{porta}")
    print("Para encerrar: Ctrl + C")
    try:
        servidor.serve_forever()
    except KeyboardInterrupt:
        print("\nEncerrando...")
    finally:
        servidor.server_close()
        programa_c.fechar()


if __name__ == "__main__":
    main()
