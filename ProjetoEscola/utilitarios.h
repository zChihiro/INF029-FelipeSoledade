#ifndef UTILITARIOS_H
#define UTILITARIOS_H
#include "use.h"
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"

//Aluno....................................................................................
int Checklist_Aluno(Aluno lista_aluno[], int qtdAluno, int x);
int search_id(Aluno lista_aluno[], int qtdAluno, int x);
void ordenarAlunosPorNome(Aluno vetor[], int qtdAluno);
void ordenarAlunosPorData(Aluno vetor[], int qtdAluno);

//Professor....................................................................................
int Checklist_Professor(Professor lista_professor[], int qtdProfessor, int x);
int search_id_professor(Professor lista_professor[], int qtdProfessor, int x);
void ordenarProfessoresPorNome(Professor vetor[], int qtdProfessor);
void ordenarProfessoresPorData(Professor vetor[], int qtdProfessor);
//Disciplina.....................................................................................
int search_id_disciplina(Disciplina lista_disciplina[], int qtdDisciplina, int x);


//Global
int comparaNomes(char *nome1, char *nome2);
int comparaData(Data data1, Data data2) ;
int Verify_Date(Data d); 
int valid_cpf(char *cpf);
int invalid_id(int x);
char valid_sex();
void name_read(char *texto);
void caracter_read(char *texto);
void new_format(char name[]);
void limpar_buffer();
int ler_int(int *n);

#endif