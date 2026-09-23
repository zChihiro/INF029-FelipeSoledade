#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "use.h"
#include "relatorios.h"


int menuRelatorios(void) {
    int opcao;
    printf("======== Modulo Relatorios ========\n\n");
    printf("0 - Sair\n");
    printf("1 - Buscar Aluno por Nome\n");
    printf("2 - Buscar Professor por Nome\n");
    printf("3 - Busca Aluno com menos de 3 disciplina\n");
    printf("4 - Aniversariante do mes atual aluno\n");
    printf("5 - Aniversariante do mes atual professor\n");
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);
    printf("\n");
    return opcao;
}

void buscarAlunoPorNome(Aluno lista_aluno[], int qtdAluno) {

    if(qtdAluno == 0) {
        printf("Nao ha alunos matriculados\n\n");
        return;
    }

    char textoBuscado[TAM_NAME];
    int tam;

    do {
        printf("Digite no minimo 3 letras para buscar: ");
        name_read(textoBuscado);
        tam = strlen(textoBuscado);

        if(tam < 3) {
            printf("Digite no minimo 3 letras.\n");
        }
    } while(tam < 3);

    int encontrou = 0;

    for(int i = 0; i < qtdAluno; i++) {
        if(strstr(lista_aluno[i].name, textoBuscado) != NULL) {
            encontrou = 1;
            printf(" ** Matricula: %d\n ** Nome: %s\n\n",
                    lista_aluno[i].matricula,
                    lista_aluno[i].name);
        }
    }

    if(!encontrou) {
        printf("Nenhum aluno encontrado com esse texto.\n\n");
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
}

void buscarProfessorPorNome(Professor lista_professor[], int qtdProfessor) {

    if(qtdProfessor == 0) {
        printf("Nao ha professores cadastrados\n\n");
        return;
    }

    char textoBuscado[TAM_NAME];
    int tam;

    do {
        printf("Digite no minimo 3 letras para buscar: ");
        name_read(textoBuscado);
        tam = strlen(textoBuscado);

        if(tam < 3) {
            printf("Digite no minimo 3 letras.\n");
        }
    } while(tam < 3);

    int encontrou = 0;

    for(int i = 0; i < qtdProfessor; i++) {
        if(strstr(lista_professor[i].name, textoBuscado) != NULL) {
            encontrou = 1;
            printf(" ** Matricula: %d\n ** Nome: %s\n\n",
                    lista_professor[i].matricula,
                    lista_professor[i].name);
        }
    }

    if(!encontrou) {
        printf("Nenhum professor encontrado com esse texto.\n\n");
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
}

void listarAlunosMenosDe3Disciplinas(Aluno lista_aluno[], int qtdAluno, Disciplina lista_disciplina[], int qtdDisciplina) {

    if(qtdAluno == 0 && qtdDisciplina == 0) {
        printf("\n---------------------------------------------\n");
        printf("  Nao ha alunos nem disciplina cadastrados.\n");
        printf("---------------------------------------------\n\n");
        return;
    } else if(qtdDisciplina == 0) {
        printf("\n---------------------------------------------\n");
        printf("     Nenhuma disciplina cadastrada.\n");
        printf("---------------------------------------------\n\n");
        return;
    } else if(qtdAluno == 0) {
        printf("\n---------------------------------------------\n");
        printf("       Nenhum Aluno cadastrado.\n");
        printf("---------------------------------------------\n\n");
        return;
    }

    for(int i = 0; i < qtdAluno; i++) {
        int contador = 0;
        for(int j = 0; j < qtdDisciplina; j++) {
            for(int k = 0; k < lista_disciplina[j].studentCount; k++) {
                if(lista_disciplina[j].studentRegistration[k] == lista_aluno[i].matricula) {
                    contador++;
                }
            }
        }
        if(contador < 3){
            printf(" **Name: %s\n **Matricula: %d\n\n", lista_aluno[i].name, lista_aluno[i].matricula);
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
}

void aniversariantesAluno(Aluno lista_aluno[], int qtdAluno) {

    if(qtdAluno == 0) {
        printf("Nao ha alunos matriculados\n\n");
        return;
    }

    time_t agora = time(NULL);
    struct tm *dataAtual = localtime(&agora);
    int mesAtual = dataAtual->tm_mon + 1;

    int encontrou = 0;

    for(int i = 0; i < qtdAluno; i++) {
        if(lista_aluno[i].date_birth.mes == mesAtual) {
            encontrou = 1;
            printf(" ** Nome: %s\n ** Data: %02d/%02d/%d\n\n",
                    lista_aluno[i].name,
                    lista_aluno[i].date_birth.dia,
                    lista_aluno[i].date_birth.mes,
                    lista_aluno[i].date_birth.ano);
        }
    }

    if(!encontrou) {
        printf("Nenhum aluno faz aniversario esse mes.\n\n");
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
}

void aniversariantesProfessor(Professor lista_professor[], int qtdProfessor) {

    if(qtdProfessor == 0) {
        printf("Nao ha professores cadastrados\n\n");
        return;
    }

    time_t agora = time(NULL);
    struct tm *dataAtual = localtime(&agora);
    int mesAtual = dataAtual->tm_mon + 1;

    int encontrou = 0;

    for(int i = 0; i < qtdProfessor; i++) {
        if(lista_professor[i].date_birth.mes == mesAtual) {
            encontrou = 1;
            printf(" ** Nome: %s\n ** Data: %02d/%02d/%d\n\n",
                    lista_professor[i].name,
                    lista_professor[i].date_birth.dia,
                    lista_professor[i].date_birth.mes,
                    lista_professor[i].date_birth.ano);
        }
    }

    if(!encontrou) {
        printf("Nenhum professor faz aniversario esse mes.\n\n");
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
}