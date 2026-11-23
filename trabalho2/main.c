#include <stdio.h>
#include <stdlib.h>

#include "trabalho2.h"

//Nome de funções Só utilitárias.
int menu();
int ler_int(int *n);
void limpar_buffer();
void imprimir_vetor(int vetor[], int tam);
void erro_numero();
void retornar_listar();


//Nome Funções em si

void inserir_elemento();
void listar_numeros(int decidir);
void listar_todos_numeros(int decidir);
void excluir_numero();
void aumentar();

//Aqui tá tudo embaralhado. 

void retornar_listar() {
int retorno = 0;
        do{
        printf("Digite 1 para retornar: ");
        ler_int(&retorno);
        if(retorno != 1){
            printf("Digito invalido. Tente novamente!\n");
            retorno = 0;
        }
    } while(!retorno);
}

void erro_numero() {
    printf("----------------------------------\n");
    printf("    Apenas numeros permitidos\n");
    printf("----------------------------------\n\n");
}

void limpar_buffer() {
    int c = getchar();

    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int ler_int(int *n) {
    if (scanf("%d", n) != 1) {
        limpar_buffer();
        return 0;
    }

    if (getchar() != '\n') {
        limpar_buffer();
        return 0;
    }

    return 1;
}

void imprimir_vetor(int vetor[], int tam) {

    for(int i = 0; i < tam- 1; i++) {
        printf("%d, ", vetor[i]);
    }
    printf("%d ", vetor[tam-1]);
}

int menu()
{
    int op = 0;
    printf("------------------------\n");
    printf("         MENU \n");
    printf("------------------------\n");
    printf("1 - InserirElemento.\n");
    printf("2 - Listar os numeros de todas estruturas por posicao.\n");
    printf("3 - Listar os numeros ordenados para cada estrutura por posicao.\n");
    printf("4 - Listar todos os numeros de forma ordernada.\n");
    printf("5 - Excluir elemento da estrutura.\n");
    printf("6 - Aumentar tamanho de uma estrutura\n");
    printf("7 - Sair.\n");
    if(!ler_int(&op)) {
        erro_numero();
    }
    return op;
}



void inserir_elemento() {   
    int posicao;
    
    printf("Digite a posicao da estrutura a inserir: ");
    if(!ler_int(&posicao)) {
        erro_numero();
        return;
    }

    int ret = getQuantidadeElementosEstruturaAuxiliar(posicao);

    if(ret == POSICAO_INVALIDA) {
        printf("Posicao invalida, apenas numeros de 1 a 10.\n");
        return;
    } else if(ret == SEM_ESTRUTURA_AUXILIAR) {
        printf("\nSem estrutuda alocada na posicao.\n");
        printf("Digite o tamanho da estrutura auxiliar.\n");
        
        int tamanho = 0;
        if(!ler_int(&tamanho)) {
        erro_numero();
        return;
        }

        int ret2 = criarEstruturaAuxiliar(posicao, tamanho);
        if(ret2 == TAMANHO_INVALIDO) {
            printf("tamanho invalido, apenas numeros >= (1).\n");
            return;
        }
        else if(ret2 == SEM_ESPACO_DE_MEMORIA) {
            printf("Nao foi possivel alocar a estrutura no tamanho pedido.\n");
            return;
        } else {
            
            printf("Estrutura criada com sucesso.\n");
            printf("Tamanho: %d\n", tamanho);

            printf("Digite o valor a ser inserido: ");
            int valor;
            if(!ler_int(&valor)) {
            erro_numero();
            return;
            }  

            inserirNumeroEmEstrutura(posicao, valor);

            printf("Numero inserido com sucesso.\n");
            printf("Quantidade: %d\n", getQuantidadeElementosEstruturaAuxiliar(posicao));

        }

    } else {

        printf("Digite o valor a ser inserido: ");
        int valor;
        if(!ler_int(&valor)) {
            erro_numero();
            return;
        }
        
        int retorno = inserirNumeroEmEstrutura(posicao, valor);

        if(retorno == SEM_ESPACO) {
            printf("Tamanho maximo da estrutura preenchido.\n");
            return;
        }
        if(retorno == SUCESSO) {
            printf("Numero Inserido com Sucesso.\n");
            printf("Quantidade: %d\n", getQuantidadeElementosEstruturaAuxiliar(posicao));
            return;
        }
    }

}

void lista_numeros(int decidir) {

    int *Vetor;

    for(int i = 1; i <= 10; i++) { // na função eu faço i - 1 por isso começa em 1 e vai até 10.
        int n = getQuantidadeElementosEstruturaAuxiliar(i);
        
        if(n ==  SEM_ESTRUTURA_AUXILIAR) {
            printf("Nenhuma Estrutura na posicao %d\n", i);
        }
        else if(n == ESTRUTURA_AUXILIAR_VAZIA) {
            printf("Estrutura Auxiliar Vazia na posicao %d\n", i);
        }
        else {
            Vetor = malloc(n * sizeof(int));
            if(Vetor == NULL) {
                printf("NAO FOI POSSIVEL ALOCAR.\n");
                return;
            }
            
            if(decidir) 
            getDadosOrdenadosEstruturaAuxiliar(i, Vetor); 
            else 
            getDadosEstruturaAuxiliar(i, Vetor);

            printf("Posicao %d - ",i);
            imprimir_vetor(Vetor, n);
            free(Vetor);
            printf("\n");

        }
    }

    retornar_listar();
    return;

}

void listar_todos_numeros(int decidir) {

    int total = 0;
    for(int posicao = 1; posicao <= 10; posicao++) {

        int n = getQuantidadeElementosEstruturaAuxiliar(posicao);
        if(n > 0)
            total += n;
    }

    if(total == 0) {
        printf("Todas estruturas vazias.\n");
        return;
    }

    int *vetor = malloc (total * sizeof(int));
    if(vetor == NULL) {
        printf("Sem espaço disponivel para alocar.\n");
        return;
    }

    if(decidir) 
    getDadosOrdenadosDeTodasEstruturasAuxiliares(vetor);
    else 
    getDadosDeTodasEstruturasAuxiliares(vetor);

    imprimir_vetor(vetor, total);
    free(vetor);

    printf("\n");
    retornar_listar();
    return;

}

void excluir_numero() {

    int posicao;

    printf("Digite a posicao da estrutura a excluir: ");
    if(!ler_int(&posicao)) {
        erro_numero();
        return;
    }
    int valor;
    printf("Digite o valor da estrutura a excluir: ");
    if(!ler_int(&valor)) {
        erro_numero();
        return;
    }

    int antes = getQuantidadeElementosEstruturaAuxiliar(posicao);
    int exclusao = excluirNumeroEspecificoDeEstrutura(posicao, valor);

    if(exclusao == POSICAO_INVALIDA ) {
        printf("Posicao invalida, apenas numeros de 1 a 10.\n");
        
    } else if( exclusao == SEM_ESTRUTURA_AUXILIAR) {
        printf("Nao ha estrutura criada nessa posicao.\n");
        
    } else if( exclusao == ESTRUTURA_AUXILIAR_VAZIA) {
        printf("Nao ha numeros inseridos nessa estrutura.\n");
       
    } else if( exclusao == NUMERO_INEXISTENTE) {
        printf("O Valor a ser apagado nao foi encontrado.\n");

        
    } else{
        printf("Numero excluido com sucesso:\n");
        printf("Numero de elementos antes: %d\n", antes);
        printf("Numero de elementos após: %d\n", antes - 1);       
    }

}

void aumentar() {
    
    int posicao;
    printf("Digite a posicao da estrutura a aumentar: ");
    if(!ler_int(&posicao)) {
        erro_numero();
        return;
    }
    int tamanho;
    printf("Digite o valor da estrutura a aumentar: ");
    if(!ler_int(&tamanho)) {
        erro_numero();
        return;
    }

    if(tamanho < 1) {
        printf("Apenas valores maior do que 1.\n");
        return;
    }

    int novo_tam = modificarTamanhoEstruturaAuxiliar(posicao, tamanho);

    if(novo_tam == POSICAO_INVALIDA ) {
        printf("Posicao invalida, apenas numeros de 1 a 10.\n");
        
    } else if( novo_tam == SEM_ESTRUTURA_AUXILIAR) {
        printf("Nao ha estrutura criada nessa posicao.\n");
    } else if( novo_tam == SEM_ESPACO_DE_MEMORIA) {
        printf("Nao foi possivel alocar o novo tamanho.\n");
    } else {
        printf("Sucesso na alteração do tamanho da estrutura.\n");
    }    
}

int main()
{
    inicializar();
    int op;
    int sair = 0;
    while (!sair)
    {
        op = menu();
        switch (op)
        {
        case 1:
        { //inserir
            //TODO
            inserir_elemento();
            break;
        }

        case 2:
        {   
            lista_numeros(0);
            break;
        }
        case 3:
        {
            lista_numeros(1);
            break;
        }

        case 4:
        { //recuperar dados estrutura auxiliar        
            listar_todos_numeros(1);
            break;
        }
        case 5:
        {
            excluir_numero();
            break;
        }
        case 6:
        {
            aumentar();
            break;
        }
        case 7:
        {
            sair = 1;
            break;
        }
        /*case 10:
        { //dobrar
            //ler um numero
            int valor;
            scanf("%i", &valor);

            dobrar(&valor);

            //passar para um funcao (void dobrar(...)) que recebe o numero e dobra (EstruturaVetores.c)

            printf("%i", valor);

            break;
        }*/

        default:
        {
            printf("opcao inválida\n");
        }
        }

    }
    finalizar();

    return 0;
}

