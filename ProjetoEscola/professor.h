#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "use.h"


typedef struct { 
    int matricula;
    char name[TAM_NAME];
    char cpf[TAM_CPF];
    Data date_birth;
    char sexo;
    int ativo;
} Professor;

int menuProfessor();
int cadastrarProfessor(Professor lista_professor[], int qtdProfessor);
void listarProfessores(Professor lista_professor[], int qtdProfessor);
void listarProfessoresSexo(Professor lista_professor[], int qtdProfessor);
void listarProfessoresName(Professor *lista_professor, int qtdProfessor);
void listarProfessoresData(Professor *lista_professor, int qtdProfessor);
void atualizarProfessor(Professor lista_professor[], int qtdProfessor);
int excluirProfessor(Professor lista_professor[], int qtdProfessor);

#endif // PROFESSOR_H