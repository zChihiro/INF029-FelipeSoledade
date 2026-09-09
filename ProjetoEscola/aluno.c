#include <stdio.h>
#include "aluno.h"

int menuAluno() {


    printf("======== Módulo Aluno ========\n\n");
    int sairAluno = 0;
    int opcaoAluno;

    printf("0 - Sair\n");
    printf("1 - Cadastrar Aluno\n");
    printf("2 - Listar Alunos\n");
    printf("3 - Alterar Aluno\n");
    printf("4 - Excluir Aluno\n");
    printf("Digite a sua opção: ");
    scanf("%d", &opcaoAluno);

    return opcaoAluno;
}

void cadastrarAluno(Aluno lista_aluno[], int *qtdAluno) {
    

    if  (*qtdAluno >= TAM_ALUNO) {
        printf("Limite de alunos atingido.\n");
        return;
    }

    Aluno novoAluno;
    printf("Digite a matrícula do aluno: ");
    scanf("%d", &novoAluno.matricula);
    printf("Digite o sexo do aluno (M/F): ");
    scanf(" %c", &novoAluno.sexo);
    novoAluno.ativo = 1;

    lista_aluno[*qtdAluno] = novoAluno;
    (*qtdAluno)++;
    printf("Aluno cadastrado com sucesso!\n\n");
}

void listarAlunos(Aluno lista_aluno[], int qtdAluno) {
   
    
}

void alterarAluno(Aluno lista_aluno[], int *qtdAluno) {
    
}

void excluirAluno(Aluno lista_aluno[], int *qtdAluno) {
    
}