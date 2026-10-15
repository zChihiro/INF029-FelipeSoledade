#include <stdio.h>
#include <string.h>

#define NUM_NAVIOS 5
#define TAM 10

#define MAR ' '
#define NAVIO 'N'
#define ACERTO '0'
#define ERRO 'X'

int tamanhoDoNavio(int i)
{
    if (i == 0)
        return 4;
    if (i == 1)
        return 3;
    if (i >= 2 && i <= 4)
        return 1;
    return 2;
}

int totalDeCasas()
{
    int i, total = 0;
    for (i = 0; i < NUM_NAVIOS; i++)
        total = total + tamanhoDoNavio(i);
    return total;
}

void iniciarTabuleiro(char t[TAM][TAM])
{
    int i, j;
    for (i = 0; i < TAM; i++)
        for (j = 0; j < TAM; j++)
            t[i][j] = MAR;
}

void limparTela()
{
    int i;
    for (i = 0; i < 40; i++)
        printf("\n");
}

int lerCelula(char *s, int *lin, int *col)
{
    char letra = s[0];
    int tam = strlen(s);

    if (tam < 2 || tam > 3)
        return 0;

    if (letra >= 'a' && letra <= 'z')
        letra = letra - 32;
    if (letra < 'A' || letra > 'J')
        return 0;

    if (s[1] < '0' || s[1] > '9')
        return 0;

    if (tam == 2)
    {
        if (s[1] == '0')
            return 0;
        *col = s[1] - '1';
    }
    else
    {
        if (s[1] != '1' || s[2] != '0')
            return 0;
        *col = 9;
    }

    *lin = letra - 'A';
    return 1;
}

void mostrarTabuleiro(char t[TAM][TAM], int esconder)
{
    int i, j;
    char c;

    printf("\n   ");
    for (j = 1; j <= TAM; j++)
        printf("%2d ", j);
    printf("\n");

    for (i = 0; i < TAM; i++)
    {
        printf("%c  ", 'A' + i);
        for (j = 0; j < TAM; j++)
        {
            c = t[i][j];
            if (esconder && c == NAVIO)
                c = MAR;
            printf("[%c]", c);
        }
        printf("\n");
    }
}

int podePosicionar(char t[TAM][TAM], int lin, int col, char dir, int tam)
{
    int k;

    if (dir == 'H' && col + tam > TAM)
        return 0;
    if (dir == 'V' && lin + tam > TAM)
        return 0;

    for (k = 0; k < tam; k++)
    {
        if (dir == 'H' && t[lin][col + k] != MAR)
            return 0;
        if (dir == 'V' && t[lin + k][col] != MAR)
            return 0;
    }
    return 1;
}

void posicionar(char t[TAM][TAM], int lin, int col, char dir, int tam)
{
    int k;
    for (k = 0; k < tam; k++)
    {
        if (dir == 'H')
            t[lin][col + k] = NAVIO;
        else
            t[lin + k][col] = NAVIO;
    }
}

void posicionarNavios(char t[TAM][TAM], int jogador)
{
    char entrada[10];
    char dir;
    int i, tam, lin, col, ok;

    for (i = 0; i < NUM_NAVIOS; i++)
    {
        tam = tamanhoDoNavio(i);
        ok = 0;

        while (!ok)
        {
            printf("\nJogador %d - seu tabuleiro:", jogador);
            mostrarTabuleiro(t, 0);
            printf("\nNavio %d de %d (tamanho %d)\n", i + 1, NUM_NAVIOS, tam);
            printf("Celula inicial (ex: B3): ");
            scanf("%9s", entrada);

            if (!lerCelula(entrada, &lin, &col))
            {
                printf("\nCelula invalida! Use letra A-J e numero 1-10.\n");
                continue;
            }

            dir = 'H';
            if (tam > 1)
            {
                printf("Direcao (H = horizontal, V = vertical): ");
                scanf(" %c", &dir);
                if (dir == 'h')
                    dir = 'H';
                if (dir == 'v')
                    dir = 'V';
                if (dir != 'H' && dir != 'V')
                {
                    printf("\nDirecao invalida!\n");
                    continue;
                }
            }

            if (!podePosicionar(t, lin, col, dir, tam))
            {
                printf("\nNao cabe ai ou esta em cima de outro navio!\n");
                continue;
            }

            posicionar(t, lin, col, dir, tam);
            ok = 1;
        }
    }

    printf("\nJogador %d - navios posicionados:", jogador);
    mostrarTabuleiro(t, 0);
}

int atirar(char adv[TAM][TAM], int lin, int col)
{
    if (adv[lin][col] == ACERTO || adv[lin][col] == ERRO)
        return -1;

    if (adv[lin][col] == NAVIO)
    {
        adv[lin][col] = ACERTO;
        return 1;
    }

    adv[lin][col] = ERRO;
    return 0;
}

void turno(char meu[TAM][TAM], char adv[TAM][TAM], int jogador, int *restantesAdv)
{
    char entrada[10];
    int lin, col, r;
    int atirou = 0;

    while (!atirou)
    {
        printf("\n===== Vez do Jogador %d =====\n", jogador);
        printf("1 - Listar tabuleiros\n");
        printf("2 - Atirar\n");
        printf("Opcao: ");
        scanf("%9s", entrada);

        if (entrada[0] == '1')
        {
            printf("\nSEU TABULEIRO:");
            mostrarTabuleiro(meu, 0);
            printf("\nTABULEIRO DO ADVERSARIO:");
            mostrarTabuleiro(adv, 1);
        }
        else if (entrada[0] == '2')
        {
            printf("Celula do tiro (ex: B3): ");
            scanf("%9s", entrada);

            if (!lerCelula(entrada, &lin, &col))
            {
                printf("\nCelula invalida!\n");
                continue;
            }

            r = atirar(adv, lin, col);
            if (r == -1)
                printf("\nVoce ja atirou nessa celula! Escolha outra.\n");
            else if (r == 1)
            {
                printf("\nACERTOU um navio!\n");
                *restantesAdv = *restantesAdv - 1;
                atirou = 1;
            }
            else
            {
                printf("\nAgua... errou.\n");
                atirou = 1;
            }
        }
        else
            printf("\nOpcao invalida!\n");
    }
}

int main()
{
    char tab[2][TAM][TAM];
    char entrada[10];
    int restantes[2];
    int p, adv;

    for (p = 0; p < 2; p++)
    {
        iniciarTabuleiro(tab[p]);
        restantes[p] = totalDeCasas();
    }

    for (p = 0; p < 2; p++)
    {
        printf("\nJogador %d vai posicionar os navios. O outro jogador nao deve olhar!\n", p + 1);
        posicionarNavios(tab[p], p + 1);
        printf("\nDigite qualquer letra e ENTER para continuar: ");
        scanf("%9s", entrada);
        limparTela();
    }

    p = 0;
    while (restantes[0] > 0 && restantes[1] > 0)
    {
        adv = 1 - p;

        turno(tab[p], tab[adv], p + 1, &restantes[adv]);

        if (restantes[adv] > 0)
        {
            printf("\nDigite qualquer letra e ENTER para passar a vez: ");
            scanf("%9s", entrada);
            limparTela();
            p = adv;
        }
    }

    printf("\n***** O Jogador %d venceu! *****\n", p + 1);
    return 0;
}
