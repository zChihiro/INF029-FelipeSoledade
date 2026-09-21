#ifndef DISCIPLINA_H
#define DISCIPLINA_H
#include "use.h"
#include "aluno.h"
#include "professor.h"

typedef struct {
    int id;
    char name[TAM_NAME];
    int semestre;
    int teacher_id;
    int ativo;
    int studentRegistration[MAX_ALUNO];
    int studentCount;
} Disciplina;


int menuDisciplina();
int cadastrarDisciplina(Disciplina lista_disciplina[], Professor lista_professor[], int qtdDisciplina, int qtdProfessor);
void listarDisciplinas(Disciplina lista_disciplina[], int qtdDisciplina);
#endif