#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

/* ---------- MODO TERMINAL: o seu menu original, sem mudancas ---------- */
void modoTerminal() {
    int opcao;

    do {
        printf("\n=== SISTEMA DE LIVROS ===\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Listar por nome (crescente)\n");
        printf("3 - Listar por nome (decrescente)\n");
        printf("4 - Listar por preco (crescente)\n");
        printf("5 - Listar por preco (decrescente)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarLivro(); break;
            case 2: listarNomeCrescente(); break;
            case 3: listarNomeDecrescente(); break;
            case 4: listarPrecoCrescente(); break;
            case 5: listarPrecoDecrescente(); break;
        }
    } while (opcao != 0);
}

/* ---------- MODO INTERFACE: fica lendo comandos da janela ----------
   A janela (Python) manda uma linha de texto e o C responde:

   CADASTRAR;nome;preco        ->  OK;total   (ou ERRO;...)
   ORDENAR;nome|preco;crescente|decrescente
                               ->  uma linha "nome;preco" por livro, e FIM
   SAIR                        ->  encerra
*/
void modoInterface() {
    char linha[256];

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        linha[strcspn(linha, "\r\n")] = '\0';   /* tira o Enter do fim */

        if (strncmp(linha, "CADASTRAR;", 10) == 0) {
            char *resto = linha + 10;           /* "nome;preco" */
            char *sep = strrchr(resto, ';');    /* ultimo ';' separa o preco */

            if (sep == NULL) {
                printf("ERRO;formato invalido\n");
            } else {
                *sep = '\0';                    /* resto agora e so o nome */
                float preco = (float) atof(sep + 1);
                int total = cadastrarLivroInterface(resto, preco);

                if (total < 0)
                    printf("ERRO;lista cheia\n");
                else
                    printf("OK;%d\n", total);
            }
        }
        else if (strncmp(linha, "ORDENAR;", 8) == 0) {
            char criterio[20], ordem[20];

            if (sscanf(linha + 8, "%19[^;];%19s", criterio, ordem) == 2) {
                int porNome   = (strcmp(criterio, "nome") == 0);
                int crescente = (strcmp(ordem, "crescente") == 0);
                listarParaInterface(porNome, crescente);
            } else {
                printf("ERRO;formato invalido\n");
            }
            printf("FIM\n");                    /* avisa que acabou a lista */
        }
        else if (strcmp(linha, "SAIR") == 0) {
            break;
        }
        else {
            printf("ERRO;comando desconhecido\n");
        }

        fflush(stdout);   /* manda a resposta agora, sem esperar encher o buffer */
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--interface") == 0)
        modoInterface();
    else
        modoTerminal();

    return 0;
}
