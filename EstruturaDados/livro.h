#ifndef LIVRO_H
#define LIVRO_H

#define MAX 100

typedef struct {
    char nome[50];
    float preco;
} Livro;

/* ---------- PARTE ORIGINAL (menu no terminal) ---------- */
void cadastrarLivro();
void listarNomeCrescente();
void listarNomeDecrescente();
void listarPrecoCrescente();
void listarPrecoDecrescente();

/* ---------- PARTE NOVA (ponte com a interface grafica) ---------- */
int  cadastrarLivroInterface(const char *nome, float preco);
void listarParaInterface(int porNome, int crescente);

#endif
