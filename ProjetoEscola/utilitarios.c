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

//Função Para Aluno, pq não serve ? pq eu passo o vetor aluno e não professor.

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

//Função Professor.
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
        
        if(sexo != 'M' && sexo != 'F') 
        printf("Caracter invalido. Tente novamente.\n");
    } while(sexo != 'M' && sexo != 'F');

    return sexo;
}
