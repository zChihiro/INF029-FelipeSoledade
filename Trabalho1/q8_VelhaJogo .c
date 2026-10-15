#include <stdio.h>
#include <string.h>

#define MARCA_1 'X'
#define MARCA_2 '0'

void iniciarTabuleiro(char t[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            t[i][j] = ' ';
}

void mostrarTabuleiro(char t[3][3], int jogador)
{
    int i;
    printf("\n     1   2   3\n");
    for (i = 0; i < 3; i++)
    {
        printf("  %c  %c | %c | %c\n", 'A' + i, t[i][0], t[i][1], t[i][2]);
        if (i < 2)
            printf("    ---+---+---\n");
    }
    printf("\nJogador %d, informe sua jogada: ", jogador);
}

int lerCelula(char *s, int *lin, int *col)
{
    char letra;

    if (strlen(s) != 2)
        return 0;

    letra = s[0];
    if (letra >= 'a' && letra <= 'z')
        letra = letra - 32;

    if (letra < 'A' || letra > 'C')
        return 0;
    if (s[1] < '1' || s[1] > '3')
        return 0;

    *lin = letra - 'A';
    *col = s[1] - '1';
    return 1;
}

char verificarGanhador(char t[3][3])
{
    int i;

    for (i = 0; i < 3; i++)
    {

        if (t[i][0] != ' ' && t[i][0] == t[i][1] && t[i][1] == t[i][2])
            return t[i][0];

        if (t[0][i] != ' ' && t[0][i] == t[1][i] && t[1][i] == t[2][i])
            return t[0][i];
    }

    if (t[1][1] != ' ' && t[0][0] == t[1][1] && t[1][1] == t[2][2])
        return t[1][1];
    if (t[1][1] != ' ' && t[0][2] == t[1][1] && t[1][1] == t[2][0])
        return t[1][1];

    return ' ';
}

int main()
{
    char tabuleiro[3][3];
    char entrada[20];
    char ganhador = ' ';
    int jogada, jogador, lin, col, ok;

    iniciarTabuleiro(tabuleiro);

    for (jogada = 0; jogada < 9 && ganhador == ' '; jogada++)
    {
        jogador = (jogada % 2) + 1;

        ok = 0;
        while (!ok)
        {
            mostrarTabuleiro(tabuleiro, jogador);
            scanf("%19s", entrada);

            if (!lerCelula(entrada, &lin, &col))
                printf("\nCelula invalida! Use letra A-C e numero 1-3 (ex: B3).\n");
            else if (tabuleiro[lin][col] != ' ')
                printf("\nEssa celula ja esta ocupada!\n");
            else
                ok = 1;
        }

        if (jogador == 1)
            tabuleiro[lin][col] = MARCA_1;
        else
            tabuleiro[lin][col] = MARCA_2;

        ganhador = verificarGanhador(tabuleiro);
    }

    printf("\n     1   2   3\n");
    for (lin = 0; lin < 3; lin++)
    {
        printf("  %c  %c | %c | %c\n", 'A' + lin, tabuleiro[lin][0], tabuleiro[lin][1], tabuleiro[lin][2]);
        if (lin < 2)
            printf("    ---+---+---\n");
    }

    if (ganhador == MARCA_1)
        printf("\nO Jogador 1 (%c) ganhou!\n", MARCA_1);
    else if (ganhador == MARCA_2)
        printf("\nO Jogador 2 (%c) ganhou!\n", MARCA_2);
    else
        printf("\nNao houve ganhador (deu velha).\n");

    return 0;
}
