"""
ponte_c.py - a "ponte" entre o Python e o programa em C.

Aqui NAO tem janela. Este arquivo so abre o programa C (catalogo) e troca
mensagens de texto com ele:

    Python manda:  CADASTRAR;Dom Casmurro;29.90
    C responde:    OK;1

    Python manda:  ORDENAR;preco;crescente
    C responde:    Iracema;19.50
                   Dom Casmurro;29.90
                   FIM
"""
import subprocess


class ProgramaC:
    def __init__(self, caminho_executavel):
        # Abre o C em "modo interface" e guarda os canais de conversa:
        #   stdin  = o que o Python ENVIA para o C
        #   stdout = o que o C RESPONDE para o Python
        self.processo = subprocess.Popen(
            [caminho_executavel, "--interface"],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            text=True,
            encoding="utf-8",
            errors="replace",
            bufsize=1,
        )

    def _enviar(self, comando):
        self.processo.stdin.write(comando + "\n")
        self.processo.stdin.flush()

    def cadastrar(self, nome, preco):
        """Cadastra um livro no C. Devolve o total de livros cadastrados."""
        self._enviar(f"CADASTRAR;{nome};{preco:.2f}")
        resposta = self.processo.stdout.readline().strip()

        if resposta.startswith("OK;"):
            return int(resposta.split(";")[1])
        raise RuntimeError(resposta or "o programa C nao respondeu")

    def ordenar(self, criterio, ordem):
        """
        criterio: "nome" ou "preco"
        ordem:    "crescente" ou "decrescente"
        Devolve uma lista de (nome, preco) JA ORDENADA pelo C.
        """
        self._enviar(f"ORDENAR;{criterio};{ordem}")

        livros = []
        erro = None
        while True:
            linha = self.processo.stdout.readline().strip()
            if linha == "FIM" or linha == "":
                break
            if linha.startswith("ERRO;"):
                erro = linha
                continue
            nome, preco = linha.rsplit(";", 1)   # o ultimo ';' separa o preco
            livros.append((nome, float(preco)))

        if erro:
            raise RuntimeError(erro)
        return livros

    def fechar(self):
        try:
            self._enviar("SAIR")
            self.processo.wait(timeout=2)
        except Exception:
            self.processo.kill()
