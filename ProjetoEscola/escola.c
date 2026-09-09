#include <stdio.h>
#include "aluno.h"

int menuGeral();

int main(void) {

    Aluno lista_aluno[TAM_ALUNO];
    int opcao;
    int qtdAluno = 0;
    int sair = 0;

    while(!sair){
        
        opcao = menuGeral();
        printf("\n");

        switch(opcao){
            case 0:{
                sair = 1;
                break;
            }

            case 1:{
                int sairAluno = 0;
                int opcaoAluno;
                
                while(!sairAluno){
                    opcaoAluno = menuAluno();
                    printf("\n");

                    switch(opcaoAluno){
                        case 0:{
                            sairAluno = 1;
                            break;
                        }
                        case 1:{
                            cadastrarAluno(lista_aluno, &qtdAluno);
                            break;
                        }
                        case 2:{
                            listarAlunos(lista_aluno, qtdAluno);
                            break;
                        }
                        case 3:{
                            alterarAluno(lista_aluno, &qtdAluno);
                            break;
                        }
                        case 4:{
                            excluirAluno(lista_aluno, &qtdAluno);
                            break;
                        }
                        default:{
                            printf("Opção Inválida\n");
                            break;
                        }
                    }
                }
            }

            case 2:{
                printf("Módulo Professor:\n");
                break;
            }

            case 3:{
                printf("Módulo Disciplina:\n");
                break;
            }

            default:{
                printf("Opção Inválida\n");
                break;
            }
        }

    }
}

int menuGeral(){
    int opcao;
    printf("======== Projeto Escola ========\n\n");
        
        printf("0 - Sair\n");
        printf("1 - Aluno\n");
        printf("2 - Professor\n");
        printf("3 - Discisplina\n");
        printf("Digite a sua opção: ");
        scanf("%d", &opcao);
        
        return opcao;
}