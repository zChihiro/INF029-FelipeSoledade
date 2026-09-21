#include <stdio.h>
#include "use.h"
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"
#include "utilitarios.h"

int menuGeral();

int main(void) {

    Aluno lista_aluno[TAM_ALUNO];
    Professor lista_professor[TAM_PROFESSOR];
    Disciplina lista_disciplina[TAM_DISCIPLINA];

    int opcao;
    int qtdAluno = 0;
    int qtdProfessor = 0;
    int qtdDisciplina = 0;
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
                            if(cadastrarAluno(lista_aluno, qtdAluno))
                                qtdAluno++;     
                            break;
                        }
                        case 2:{
                            listarAlunos(lista_aluno, qtdAluno);
                            break;
                        }
                        case 3:{
                            atualizarAluno(lista_aluno, qtdAluno);
                            break;
                        }
                        case 4:{
                            if(excluirAluno(lista_aluno, qtdAluno))
                                qtdAluno--;
                            break; 
                        }
                        default:{
                            printf("Opção Inválida\n");
                            break;
                        }
                    }
                }
                break;
            }

            case 2:{
                int sairProfessor = 0;
                int opcaoProfessor = 0;

                while(!sairProfessor) {
                    opcaoProfessor = menuProfessor();
                    printf("\n");
                    switch(opcaoProfessor) {
                        case 0:{
                            sairProfessor = 1;
                            break;
                        }
                        case 1:{
                            if(cadastrarProfessor(lista_professor, qtdProfessor))
                            qtdProfessor++;
                            break;
                        }
                        case 2:{
                            listarProfessores(lista_professor, qtdProfessor);
                            break;
                        }
                        case 3:{
                            atualizarProfessor(lista_professor, qtdProfessor);
                            break;
                        }
                        case 4:{
                            if(excluirProfessor(lista_professor, qtdProfessor))
                            qtdProfessor--;
                            break;
                        }
                        default:{
                            printf("Opcao Invalida");
                            break;
                        }
                    }
                }
                break;
            }

            case 3:{
                int sairDisciplina = 0;
                int opcaoDisciplina = 0;

                while(!sairDisciplina) {
                    opcaoDisciplina = menuDisciplina();

                    switch(opcaoDisciplina) {
                        case 0: {
                            sairDisciplina = 1;
                            break;
                        }
                        case 1: {
                            if(cadastrarDisciplina(lista_disciplina, lista_professor, qtdDisciplina, qtdProfessor))
                            qtdDisciplina++;
                            break;
                        }
                        case 2: {
                            listarDisciplinas(lista_disciplina, qtdDisciplina);
                            break;
                        }
                    }
                }
                break;
            }

            default:{
                printf("Opção Inválida\n");
                break;
            }
        }

    }
}


//Função única do escola.c Menu Geral!

int menuGeral(){
    int opcao;
    printf("======== Projeto Escola ========\n\n");
        
        printf("0 - Sair\n");
        printf("1 - Aluno\n");
        printf("2 - Professor\n");
        printf("3 - Discisplina\n");
        printf("Digite a sua opcao: ");
        scanf("%d", &opcao);
        
        return opcao;
}
