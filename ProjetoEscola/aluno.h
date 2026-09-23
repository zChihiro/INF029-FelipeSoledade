#ifndef ALUNO_H
#define ALUNO_H
#include "use.h"


typedef struct Aluno {
    int matricula;
    char name[TAM_NAME];
    char cpf[TAM_CPF];
    Data date_birth;
    char sexo;
    int ativo;
} Aluno;

int menuAluno();
int cadastrarAluno(Aluno lista_aluno[], int qtdAluno);
void listarAlunos(Aluno lista_aluno[], int qtdAluno);
void listarAlunosSexo(Aluno lista_aluno[], int qtdAluno);
void listarAlunosName(Aluno *lista_aluno, int qtdAluno);
void listarAlunosData(Aluno *lista_aluno, int qtdAluno);
void atualizarAluno(Aluno lista_aluno[], int qtdAluno);
int excluirAluno(Aluno lista_aluno[], int qtdAluno);
#endif