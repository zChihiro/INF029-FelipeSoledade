#include <stdio.h>
#define TAM_ALUNO 3

typedef struct alu{
    int matricula;
    char sexo;
    int ativo;
} Aluno;

int main(void) {

    Aluno lista_aluno[TAM_ALUNO];
    int opcao;
    int qtdAluno = 0;
    int sair = 0;

    while(!sair){
        printf("======== Projeto Escola ========\n\n");
        
        printf("0 - Sair\n");
        printf("1 - Aluno\n");
        printf("2 - Professor\n");
        printf("3 - Discisplina\n\n");

        printf("Digite a sua opção: ");
        scanf("%d", &opcao);
        printf("\n");

        switch(opcao){
            case 0:{
                sair = 1;
                break;
            }

            case 1:{
                
                printf("======== Módulo Aluno ========"); 
                int sairAluno = 0;
                int opcaoAluno;
                printf("\n"); 
                
                while(!sairAluno){

                    printf("\n");
                    printf("0 - Sair\n");
                    printf("1 - Cadastrar Aluno\n");
                    printf("2 - Listar Aluno\n");
                    printf("3 - Atualizar Aluno\n");
                    printf("4 - Excluir Aluno\n\n");

                    printf("Digite a sua opção: ");
                    scanf("%d", &opcaoAluno);
                    printf("\n");
                    
                    
                    
                    switch(opcaoAluno){
                        case 0:{
                            sairAluno = 1;
                            break;
                        }                      
                        case 1:{
                            printf("--Cadastrar Aluno--\n");
                            printf("Digite a matrícula: ");
                            int matricula;
                            scanf("%d", &matricula);
                            
                            if(matricula < 0){
                                printf("Matrícula Inválida:\n");   
                            }

                            else{
                                if(qtdAluno == TAM_ALUNO){
                                    printf("Lista de Alunos cheia:\n");
                                }
                                else{
                                   lista_aluno[qtdAluno].matricula = matricula;
                                   lista_aluno[qtdAluno].ativo = 1;
                                   qtdAluno++;
                                   printf("Aluno Cadastrado com Sucesso!\n"); 
                                }
                             }
                            

                           break;
                        }
                        case 2:{
                           printf("--Listar Aluno--\n");
                           
                           if(qtdAluno == 0){
                            printf("Não há alunos matriculados");
                           }
                           
                           else{
                            for(int i = 0; i < qtdAluno; i++){
                             
                                if(lista_aluno[i].ativo)
                                printf("Matriculas ativa no momento: %d\n", lista_aluno[i].matricula);                            
                            }

                           }
                           
                           break; 
                        }
                        case 3:{
                           printf("--Atualizar Aluno--\n");
                           
                           printf("Digite a matricula: ");
                           int matricula;
                           scanf("%d", &matricula);

                           int achou = 0;

                           if(matricula < 0)
                           printf("Matrícula Inválida\n");

                           else{
                            for(int i = 0; i < qtdAluno; i++){

                                if(matricula == lista_aluno[i].matricula && lista_aluno[i].ativo){
                                    printf("Digite a nova matricula: ");
                                    int nova_matricula;
                                    scanf("%d", &nova_matricula);
                                
                                    achou = 1;
                                    lista_aluno[i].matricula = nova_matricula;
                                
                                    break;
                                }
                            
                            }

                            if(achou)
                                printf("Aluno atualizado com sucesso\n");
                            else
                                printf("Matrícula Inexistente\n");
                            }

                           break; 
                        }
                        case 4:{
                           printf("--Excluir Aluno--\n");
                           printf("Digite a matrícula: ");                         
                           int matricula;
                           scanf("%d", &matricula);
                           int achou = 0;

                           if(matricula < 0){
                            printf("Matrícula Inválida:\n");
                           }
                           else{
                            for(int i = 0; i < qtdAluno; i++){
                               
                                if(matricula == lista_aluno[i].matricula){
                                    lista_aluno[i].ativo = -1;
                                    achou = 1;

                                    for(int j = i; j <qtdAluno - 1; j++){
                                        lista_aluno[j].matricula = lista_aluno[j+1].matricula; 
                                        lista_aluno[j].sexo = lista_aluno[j+1].sexo; 
                                        lista_aluno[j].ativo = lista_aluno[j+1].ativo; 
                                    }

                                    qtdAluno--;
                                    break;
                                } 
                            }
                            
                            if(achou)
                                printf("Aluno excluido com sucesso:\n");
                            
                            else
                                printf("Matrícula Inexistente:\n");
                            
                           }
                        
                           break; 
                        }

                    }
                }

                break;
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