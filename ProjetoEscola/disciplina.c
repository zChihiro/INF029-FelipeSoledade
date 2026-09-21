#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "use.h"
#include "disciplina.h"
#include "utilitarios.h"


int menuDisciplina(void) {

    int option;
    printf("========= Modulo Disciplina ========\n\n");
    printf("0 - Sair\n");
    printf("1 - Cadastrar Disciplina\n");  
    printf("2 - Listar Disciplinas\n");  
    printf("Digite sua opcao: ");
    scanf("%d", &option);
    printf("\n");
    return option;
}

int cadastrarDisciplina(Disciplina lista_disciplina[], Professor lista_professor[], int qtdDisciplina, int qtdProfessor) {

    if(qtdDisciplina == TAM_DISCIPLINA) {
        printf("Lista de disciplina Cheia");
        return 0;
    }
    
    Disciplina key = {0};
    int ok_disciplina = 0;
    do {
        printf("Digite o ID da disciplina: ");     
        ok_disciplina = ler_int(&key.id);

        if(key.id < 0) {
            printf("Opcao Invalida, Tente novamente.\n");
            ok_disciplina = 0;
        }else if(!ok_disciplina) {
            printf("-------------------------------------------------\n");
            printf(" Apenas conjuntos de 0 a 9 sao permitidos no ID.\n");
            printf("-------------------------------------------------\n");
        }
    } while(!ok_disciplina);

    int confirmar = 0;
    int ok_name = 0;

    do {
        printf("Digite o nome da materia: ");
        name_read(key.name);
        new_format(key.name);
        confirmar = 0;
        do {
            printf("\n-----Confimar nome------\n");
            printf("Digite 1 - *SIM*\nDigite 2 - *NAO*\n");
            printf("Digito----: ");   
            ok_name = ler_int(&confirmar);
            
            if(!ok_name){
                printf("-------------------------------------------------\n");
                printf(" Apenas os digitos 1 e 2 permitidos no ID.\n");
                printf("-------------------------------------------------\n");
            } else if (confirmar < 1 || confirmar > 2) {
                printf("Opcao Invalida. Digite apenas 1 ou 2.");
            }

        } while(!ok_name || confirmar < 1 || confirmar > 2);

    } while(confirmar == 2);
   
    int ok_semestre = 0;
    do
    {
        printf("Digite o semestre: ");
        ok_semestre = ler_int(&key.semestre); 
        if(!ok_semestre || (key.semestre < 1 || key.semestre > 8)){
            printf("-------------------------------------------------\n");
            printf(" Apenas os digitos de 1 a 8 são permitidos no ID.\n");
            printf("-------------------------------------------------\n");
            ok_semestre = 0;
        }
    } while(!ok_semestre);
    
    //if(qtdProfessor == 0) {
        // printf("Nao ha professores cadastrados para prosseguir.\n\n");
        //return 0;
        //}

    int ok_teacher = 0;
    do {
    printf("Informe a matricula do professor: ");
    ok_teacher = ler_int(&key.teacher_id);

        if(key.teacher_id < 0) {
        printf("Opcao de matricula invalida. Tente novamente\n");
        ok_teacher = 0;
        }else if(!ok_teacher) {
            
            printf("-------------------------------------------------\n");
            printf("          Caracteres não são permitidos.\n");
            printf("-------------------------------------------------\n");
        }
    } while(!ok_teacher);    

    int achou = 0;

    for(int i = 0; i < qtdProfessor; i++) {
        if(lista_professor[i].matricula == key.teacher_id){
        achou = 1;
        break;
        }
    }
    //fazer tudo isso em do while dps ao invés de return
    if(!achou) {
        printf("Matricula Inexistente. Realize o cadastro novamente.\n\n");
        return 0;
    }

    key.ativo = 1;
    lista_disciplina[qtdDisciplina] = key;

    printf("Cadastro realizado com sucesso.\n\n");
    return 1;
            
} 

void listarDisciplinas(Disciplina lista_disciplina[], int qtdDisciplina) {

    if(qtdDisciplina== 0){
        printf("Lista de disciplinas vazia. Cadastre uma disciplina para testes!\n");
    }else {
        for(int i = 0; i < qtdDisciplina; i++) {
            if (lista_disciplina[i].ativo == 1) {
                printf(" ** ID: %d\n ** Nome: %s\n ** Semestre: %d\n\n",
                        lista_disciplina[i].id,
                        lista_disciplina[i].name,
                        lista_disciplina[i].semestre);
            }
        }
        int retorno;
        do{
        printf("Digite 1 para retornar: ");
        scanf("%d", &retorno);
        if(retorno != 1){
            printf("Numero inválido.\n\n");
            retorno = 0;
        }
        } while(!retorno);
            return;
    }
}