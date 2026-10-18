#include <stdio.h>
#include <string.h>
#include "livro.h"

Livro livros[MAX];
int qtd = 0;

/* =====================================================================
   PARTE ORIGINAL - nada aqui foi alterado
   ===================================================================== */

void cadastrarLivro() {
    printf("Nome: ");
    scanf(" %49[^\n]", livros[qtd].nome);

    printf("Preco: ");
    scanf("%f", &livros[qtd].preco);

    qtd++;
    printf("Livro cadastrado!\n");
}

void mostrarLivro(Livro l) {
    printf("%s - R$ %.2f\n", l.nome, l.preco);
}

void ordenarPorNome(Livro copia[]) {
    for (int i = 0; i < qtd; i++)
        copia[i] = livros[i];

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - 1 - i; j++) {
            if (strcmp(copia[j].nome, copia[j + 1].nome) > 0) {
                Livro aux = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = aux;
            }
        }
    }
}

void ordenarPorPreco(Livro copia[]) {
    for (int i = 0; i < qtd; i++)
        copia[i] = livros[i];

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - 1 - i; j++) {
            if (copia[j].preco > copia[j + 1].preco) {
                Livro aux = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = aux;
            }
        }
    }
}

void listarNomeCrescente() {
    Livro copia[MAX];
    ordenarPorNome(copia);
    printf("\n--- Nome crescente (A-Z) ---\n");
    for (int i = 0; i < qtd; i++)
        mostrarLivro(copia[i]);
}

void listarNomeDecrescente() {
    Livro copia[MAX];
    ordenarPorNome(copia);
    printf("\n--- Nome decrescente (Z-A) ---\n");
    for (int i = qtd - 1; i >= 0; i--)
        mostrarLivro(copia[i]);
}

void listarPrecoCrescente() {
    Livro copia[MAX];
    ordenarPorPreco(copia);
    printf("\n--- Preco crescente (menor -> maior) ---\n");
    for (int i = 0; i < qtd; i++)
        mostrarLivro(copia[i]);
}

void listarPrecoDecrescente() {
    Livro copia[MAX];
    ordenarPorPreco(copia);
    printf("\n--- Preco decrescente (maior -> menor) ---\n");
    for (int i = qtd - 1; i >= 0; i--)
        mostrarLivro(copia[i]);
}

/* =====================================================================
   PARTE NOVA - ponte com a interface grafica
   A interface nao usa scanf: ela manda o nome e o preco ja prontos.
   E em vez de "Nome - R$ preco", o C responde "nome;preco", que e mais
   facil da interface ler.
   ===================================================================== */

/* Cadastra um livro sem pedir nada ao usuario.
   Devolve quantos livros existem agora, ou -1 se a lista estiver cheia. */
int cadastrarLivroInterface(const char *nome, float preco) {
    if (qtd >= MAX)
        return -1;

    strncpy(livros[qtd].nome, nome, sizeof(livros[qtd].nome) - 1);
    livros[qtd].nome[sizeof(livros[qtd].nome) - 1] = '\0';
    livros[qtd].preco = preco;

    qtd++;
    return qtd;
}

/* Mesma ideia dos seus listar...(): ordena a copia e imprime.
   porNome = 1 -> ordena por nome   | 0 -> ordena por preco
   crescente = 1 -> do menor pro maior | 0 -> do maior pro menor
   O algoritmo de ordenacao e o SEU (ordenarPorNome / ordenarPorPreco). */
void listarParaInterface(int porNome, int crescente) {
    Livro copia[MAX];

    if (porNome)
        ordenarPorNome(copia);
    else
        ordenarPorPreco(copia);

    if (crescente) {
        for (int i = 0; i < qtd; i++)
            printf("%s;%.2f\n", copia[i].nome, copia[i].preco);
    } else {
        for (int i = qtd - 1; i >= 0; i--)
            printf("%s;%.2f\n", copia[i].nome, copia[i].preco);
    }
}
