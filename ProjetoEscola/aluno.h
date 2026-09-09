#ifndef ALUNO_H
#define ALUNO_H

#define TAM_ALUNO 3

typedef struct Aluno {
    int matricula;
    char sexo;
    int ativo;
} Aluno;

int menuAluno();
void cadastrarAluno(Aluno lista_aluno[], int *qtdAluno);
void listarAlunos(Aluno lista_aluno[], int qtdAluno);
void alterarAluno(Aluno lista_aluno[], int *qtdAluno);
void excluirAluno(Aluno lista_aluno[], int *qtdAluno);

#endif