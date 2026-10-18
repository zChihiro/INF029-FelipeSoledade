"""
interface.py - a janela (frontend) do catalogo de livros.

Esta janela NAO ordena nada. Ela so:
  1) pega o que o usuario digitou,
  2) manda para o programa em C (pela ponte_c.py),
  3) mostra na tabela o que o C devolveu ja ordenado.

Para rodar:  python interface.py   (antes, compile o C - veja o README)
"""
import os
import tkinter as tk
from tkinter import ttk, messagebox

from ponte_c import ProgramaC

PASTA = os.path.dirname(os.path.abspath(__file__))
NOME_EXE = "catalogo.exe" if os.name == "nt" else "catalogo"
CAMINHO_EXE = os.path.join(PASTA, NOME_EXE)


def cortar_nome(nome, limite=49):
    """O C guarda o nome em char[50]: no maximo 49 bytes + o '\\0'."""
    return nome.encode("utf-8")[:limite].decode("utf-8", "ignore")


class Janela(tk.Tk):
    def __init__(self, programa_c):
        super().__init__()
        self.c = programa_c
        self.title("Catálogo de Livros")
        self.geometry("520x470")
        self.minsize(460, 420)

        self.var_nome = tk.StringVar()
        self.var_preco = tk.StringVar()
        self.var_criterio = tk.StringVar(value="nome")
        self.var_ordem = tk.StringVar(value="crescente")
        self.var_status = tk.StringVar(value="Cadastre alguns livros e clique em Ordenar.")

        self._montar_tela()

    # ------------------------------------------------------------ visual
    def _montar_tela(self):
        # --- bloco 1: cadastrar ---
        quadro_cad = ttk.LabelFrame(self, text="Cadastrar livro", padding=10)
        quadro_cad.pack(fill="x", padx=12, pady=(12, 6))

        ttk.Label(quadro_cad, text="Nome:").grid(row=0, column=0, sticky="w")
        self.entrada_nome = ttk.Entry(quadro_cad, textvariable=self.var_nome, width=32)
        self.entrada_nome.grid(row=0, column=1, padx=6, pady=3, sticky="we")

        ttk.Label(quadro_cad, text="Preço (R$):").grid(row=1, column=0, sticky="w")
        entrada_preco = ttk.Entry(quadro_cad, textvariable=self.var_preco, width=12)
        entrada_preco.grid(row=1, column=1, padx=6, pady=3, sticky="w")
        entrada_preco.bind("<Return>", lambda e: self.cadastrar())

        ttk.Button(quadro_cad, text="Cadastrar", command=self.cadastrar).grid(
            row=1, column=2, padx=6)
        quadro_cad.columnconfigure(1, weight=1)

        # --- bloco 2: ordenar ---
        quadro_ord = ttk.LabelFrame(self, text="Ordenar catálogo", padding=10)
        quadro_ord.pack(fill="x", padx=12, pady=6)

        ttk.Label(quadro_ord, text="Critério:").grid(row=0, column=0, sticky="w")
        ttk.Radiobutton(quadro_ord, text="Nome", value="nome",
                        variable=self.var_criterio).grid(row=0, column=1, padx=6)
        ttk.Radiobutton(quadro_ord, text="Preço", value="preco",
                        variable=self.var_criterio).grid(row=0, column=2, padx=6)

        ttk.Label(quadro_ord, text="Ordem:").grid(row=1, column=0, sticky="w")
        ttk.Radiobutton(quadro_ord, text="Crescente", value="crescente",
                        variable=self.var_ordem).grid(row=1, column=1, padx=6)
        ttk.Radiobutton(quadro_ord, text="Decrescente", value="decrescente",
                        variable=self.var_ordem).grid(row=1, column=2, padx=6)

        ttk.Button(quadro_ord, text="Ordenar", command=self.ordenar).grid(
            row=0, column=3, rowspan=2, padx=16, sticky="ns")

        # --- bloco 3: tabela com o resultado ---
        quadro_tab = ttk.Frame(self)
        quadro_tab.pack(fill="both", expand=True, padx=12, pady=6)

        self.tabela = ttk.Treeview(quadro_tab, columns=("nome", "preco"),
                                   show="headings", height=8)
        self.tabela.heading("nome", text="Nome")
        self.tabela.heading("preco", text="Preço")
        self.tabela.column("nome", width=300)
        self.tabela.column("preco", width=100, anchor="e")

        barra = ttk.Scrollbar(quadro_tab, orient="vertical", command=self.tabela.yview)
        self.tabela.configure(yscrollcommand=barra.set)
        self.tabela.pack(side="left", fill="both", expand=True)
        barra.pack(side="right", fill="y")

        ttk.Label(self, textvariable=self.var_status).pack(
            anchor="w", padx=12, pady=(0, 10))

        self.entrada_nome.focus()

    # ------------------------------------------------------------ acoes
    def cadastrar(self):
        nome = cortar_nome(self.var_nome.get().replace(";", ",").strip())
        texto_preco = self.var_preco.get().replace(",", ".").strip()

        if not nome:
            messagebox.showwarning("Atenção", "Digite o nome do livro.")
            return
        try:
            preco = float(texto_preco)
        except ValueError:
            messagebox.showwarning("Atenção", "Digite um preço válido (ex.: 29,90).")
            return

        try:
            total = self.c.cadastrar(nome, preco)       # <-- quem guarda e o C
        except RuntimeError as erro:
            messagebox.showerror("Erro no programa em C", str(erro))
            return

        self.var_nome.set("")
        self.var_preco.set("")
        self.var_status.set(f"Livro cadastrado! Total no catálogo: {total}")
        self.entrada_nome.focus()

    def ordenar(self):
        try:
            livros = self.c.ordenar(self.var_criterio.get(),    # <-- quem ordena e o C
                                    self.var_ordem.get())
        except RuntimeError as erro:
            messagebox.showerror("Erro no programa em C", str(erro))
            return

        self.tabela.delete(*self.tabela.get_children())
        for nome, preco in livros:
            preco_txt = f"R$ {preco:.2f}".replace(".", ",")
            self.tabela.insert("", "end", values=(nome, preco_txt))

        criterio = "nome" if self.var_criterio.get() == "nome" else "preço"
        self.var_status.set(
            f"{len(livros)} livro(s) ordenado(s) por {criterio} ({self.var_ordem.get()}).")

    def fechar(self):
        self.c.fechar()
        self.destroy()


def main():
    if not os.path.exists(CAMINHO_EXE):
        raiz = tk.Tk()
        raiz.withdraw()
        messagebox.showerror(
            "Programa em C não encontrado",
            f"Não achei '{NOME_EXE}'.\n\nCompile antes, na pasta do projeto:\n"
            "gcc main.c livro.c -o catalogo")
        return

    janela = Janela(ProgramaC(CAMINHO_EXE))
    janela.protocol("WM_DELETE_WINDOW", janela.fechar)
    janela.mainloop()


if __name__ == "__main__":
    main()
