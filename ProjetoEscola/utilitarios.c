#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "use.h"
#include "utilitarios.h"

//Funções Globais..
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

void name_read(char *texto) {
    scanf(" %[^\n]", texto);
}

void caracter_read(char *texto) {
    scanf(" %c%*[^\n]", texto);
}

int invalid_id(int x) {
    if(x < 0){
        printf("Matricula Invalida\n");
        return 0;
    }
    return 1;
}

//Função Para Aluno, pq não serve para todos os casos ? pq eu passo o vetor aluno e não professor.
//========================================================================================================

int Checklist_Aluno(Aluno lista_aluno[], int qtdAluno, int x){
    
    for(int i = 0; i < qtdAluno; i++) {           
        if(lista_aluno[i].matricula == x) {
           return 1; 
        }
    }
    return 0;
}
int search_id(Aluno lista_aluno[], int qtdAluno, int x){
    
    for(int i = 0; i < qtdAluno; i++) {           
        if(lista_aluno[i].matricula == x) {
           return i; 
        }
    }
    return -1;
}

int comparaNomes(char *nome1, char *nome2) {
    int i = 0;
    while(nome1[i] != '\0' && nome2[i] != '\0' && nome1[i] == nome2[i]) {
        i++;
    }
    return nome1[i] - nome2[i];
}

int comparaData(Data data1, Data data2) {
    if(data1.ano != data2.ano) return data1.ano - data2.ano;
    if(data1.mes != data2.mes) return data1.mes - data2.mes;
    return data1.dia - data2.dia;
}

void ordenarAlunosPorNome(Aluno vetor[], int qtdAluno) {
    for(int i = 0; i < qtdAluno - 1; i++) {
        for(int j = 0; j < qtdAluno - 1 - i; j++) {
            if(comparaNomes(vetor[j].name, vetor[j+1].name) > 0) {
                Aluno temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}

void ordenarAlunosPorData(Aluno vetor[], int qtdAluno) {
    for(int i = 0; i < qtdAluno - 1; i++) {
        for(int j = 0; j < qtdAluno - 1 - i; j++) {
            if(comparaData(vetor[j].date_birth, vetor[j+1].date_birth) > 0) {
                Aluno temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}
//==============================================================================================


//Função Professor.
//==============================================================================================
int Checklist_Professor(Professor lista_professor[], int qtdProfessor, int x){
    for(int i = 0; i < qtdProfessor; i++) {
        if(lista_professor[i].matricula == x) {
           return 1;
        }
    }
    return 0;
}

int search_id_professor(Professor lista_professor[], int qtdProfessor, int x){
    for(int i = 0; i < qtdProfessor; i++) {
        if(lista_professor[i].matricula == x) {
           return i;
        }
    }
    return -1;
}

void ordenarProfessoresPorNome(Professor vetor[], int qtdProfessor) {
    for(int i = 0; i < qtdProfessor - 1; i++) {
        for(int j = 0; j < qtdProfessor - 1 - i; j++) {
            if(comparaNomes(vetor[j].name, vetor[j+1].name) > 0) {
                Professor temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}

void ordenarProfessoresPorData(Professor vetor[], int qtdProfessor) {
    for(int i = 0; i < qtdProfessor - 1; i++) {
        for(int j = 0; j < qtdProfessor - 1 - i; j++) {
            if(comparaData(vetor[j].date_birth, vetor[j+1].date_birth) > 0) {
                Professor temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}

//=================================================================================================


//Disciplina
//===================================================================================================
int search_id_disciplina(Disciplina lista_disciplina[], int qtdDisciplina, int x){
    for(int i = 0; i < qtdDisciplina; i++) {
        if(lista_disciplina[i].id == x) {
           return i;
        }
    }
    return -1;
}



//Refazer os search passando parametros de *
//
//
//Verificações Especificas.

int Verify_Date(Data d) {
    int achou = 0;

    if ((d.ano % 4 == 0 && d.ano % 100 != 0) || d.ano % 400 == 0)
        achou = 1;

    if(d.ano < 1900 || d.ano > 2026)
        return 0;
    if(d.mes < 1 || d.mes > 12)
        return 0;

     int day_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
     
     if (achou == 1)
     day_mes[1] = 29;

     if (d.dia < 1 || d.dia > day_mes[d.mes-1])
     return 0;
     else
     return 1;
}

int valid_cpf(char *cpf) {

    int tam = strlen(cpf);

    if(tam != 11) {
        return 0;
    }
    for(int i = 0; cpf[i] != '\0'; i++) {
        if(cpf[i] < '0' || cpf[i] > '9')
        return 0;
    }
        
    return 1; 
}
 
void new_format(char name[]) {
    int tam = strlen(name);
    int maior = 1;

    for(int i = 0; name[i] != '\0'; i++) {

        if(isspace(name[i])) {
            maior = 1;
        } else if(maior) {
            name[i] = toupper(name[i]);
            maior = 0;
        } else {
            name[i] = tolower(name[i]); 
        }
    }
}

char valid_sex() {
    char sexo;
    do {
        printf("Digite seu genero \"M\"ou \"F\": ");
        caracter_read(&sexo);
        sexo = toupper(sexo);
        
        if(sexo != 'M' && sexo != 'F') {
        printf("Caracter invalido. Tente novamente.\n");
        }
    } while(sexo != 'M' && sexo != 'F');

    return sexo;
}
