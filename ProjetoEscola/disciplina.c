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
    printf("3 - Listar Disciplina e dados aluno\n"); 
    printf("4 - Listar Disciplina com vagas preenchidas\n");  
    printf("5 - Atualizar Disciplina\n");
    printf("6 - Excluir Disciplina.\n");
    printf("7 - Inserir Aluno na Disciplina\n");
    printf("8 - Excluir Aluno Disciplina\n");
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
    
    if(qtdProfessor == 0) {
        printf("Nao ha professores cadastrados para prosseguir.\n\n");
        return 0;
    }

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
        printf("Lista de disciplinas vazia. Cadastre uma disciplina para testes!\n\n");
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

void listarDisciplina(Disciplina lista_disciplina[], Aluno lista_aluno[], int qtdDisciplina, int qtdAluno) {

    if(qtdDisciplina == 0) {
        printf("Lista de disciplinas vazia. Cadastre uma disciplina para testes!\n\n");
        return;
    }

    int idBusca;
    int ok_id;
    do {
        printf("Digite o ID da disciplina: ");
        ok_id = ler_int(&idBusca);
    } while(!ok_id);

    int idxDisciplina = search_id_disciplina(lista_disciplina, qtdDisciplina, idBusca);

    if(idxDisciplina == -1) {
        printf("Disciplina nao encontrada.\n\n");
        return;
    }

    printf(" ** ID: %d\n ** Nome: %s\n ** Semestre: %d\n ** Professor (matricula): %d\n\n",
            lista_disciplina[idxDisciplina].id,
            lista_disciplina[idxDisciplina].name,
            lista_disciplina[idxDisciplina].semestre,
            lista_disciplina[idxDisciplina].teacher_id);

    if(lista_disciplina[idxDisciplina].studentCount > 0) {
        printf("Alunos matriculados:\n\n");

        for(int i = 0; i < lista_disciplina[idxDisciplina].studentCount; i++) {
            int matriculaAluno = lista_disciplina[idxDisciplina].studentRegistration[i];
            int idxAluno = search_id(lista_aluno, qtdAluno, matriculaAluno);

            if(idxAluno != -1) {
                printf(" ** Matricula: %d\n ** Nome: %s\n\n",
                        lista_aluno[idxAluno].matricula,
                        lista_aluno[idxAluno].name);
            }
        }
    } else {
        printf("Nenhum aluno matriculado nesta disciplina.\n\n");
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

void listarDisciplinasComVagasExtrapoladas(Disciplina lista_disciplina[], Professor lista_professor[], int qtdDisciplina, int qtdProfessor) {

    if(qtdDisciplina == 0) {
        printf("Lista de disciplinas vazia. Cadastre uma disciplina para testes!\n\n");
    } else {
        int encontrouExtrapolada = 0;

        for(int i = 0; i < qtdDisciplina; i++) {
            if(lista_disciplina[i].ativo == 1 && lista_disciplina[i].studentCount > 40) {
                encontrouExtrapolada = 1;

                int idxProfessor = search_id_professor(lista_professor, qtdProfessor, lista_disciplina[i].teacher_id);

                printf(" ** ID: %d\n ** Nome: %s\n ** Semestre: %d\n ** Alunos Matriculados: %d\n ** Professor: %s\n\n",
                        lista_disciplina[i].id,
                        lista_disciplina[i].name,
                        lista_disciplina[i].semestre,
                        lista_disciplina[i].studentCount,
                        (idxProfessor != -1) ? lista_professor[idxProfessor].name : "Professor nao encontrado");
            }
        }

        if(!encontrouExtrapolada) {
            printf("Nenhuma disciplina extrapolou o limite de 40 vagas.\n\n");
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

void atualizarDisciplina(Disciplina lista_disciplina[], Professor lista_professor[], int qtdDisciplina, int qtdProfessor) {
    

    if(qtdDisciplina == 0) {
       printf("Nao ha disciplina matriculadas\n\n");
       return;
    }

    int idBusca;
    int ok;
    do { 
    printf("Digite a ID da disciplina: ");
    ok = ler_int(&idBusca);
    } while(!ok);

    int id = search_id_disciplina(lista_disciplina, qtdDisciplina, idBusca);
    
    if(id != -1) {

    int confirmar = 0;
    int ok_name = 0;

    do {
        printf("Digite o novo nome da materia: ");
        name_read(lista_disciplina[id].name);
        new_format(lista_disciplina[id].name);
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
        ok_semestre = ler_int(&lista_disciplina[id].semestre); 
        if(!ok_semestre || (lista_disciplina[id].semestre < 1 || lista_disciplina[id].semestre > 8)){
            printf("-------------------------------------------------\n");
            printf(" Apenas os digitos de 1 a 8 são permitidos no ID.\n");
            printf("-------------------------------------------------\n");
            ok_semestre = 0;
        }
    } while(!ok_semestre);
    
    int novoTeacherId;
    int ok_teacher;
    do {
    printf("Informe a matricula do professor: ");
    ok_teacher = ler_int(&novoTeacherId);

        if(novoTeacherId < 0) {
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
        if(lista_professor[i].matricula == novoTeacherId){
        achou = 1;
        break;
        }
    }
    //fazer tudo isso em do while dps ao invés de return
    if(!achou) {
        printf("Matricula Inexistente. Realize o cadastro novamente.\n\n");
        return;
    }
    else {
        lista_disciplina[id].teacher_id = novoTeacherId;
        printf("Disciplina atualizada com sucesso!\n");
        return;
    }

    } else {
        printf("Matricula nao encontrada, Tente novamente.\n\n");
        return;
    }

}

int excluirDisciplina(Disciplina lista_disciplina[], int qtdDisciplina) {

    if(qtdDisciplina == 0) {
        printf("Sem alunos cadastrados no sistema\n\n");
        return 0;
    }
    
    int ID;
    int ok_id;
    do {
    printf("Digite a ID da Materia para excluir: ");
    ok_id = ler_int(&ID);
    } while(!ok_id);

    
    int id = search_id_disciplina(lista_disciplina, qtdDisciplina, ID);

    if(id != -1) {
            
        for(int i = id; i < qtdDisciplina-1; i++) {
            lista_disciplina[i] = lista_disciplina[i+1];
        }
        printf("Aluno excluido com sucesso.\n\n");
            return 1;  
    } 
    else {
        printf("Matricula Invalida. Tente novamente\n\n");
        return 0;
    }
}

void inserir_AlunoDisciplina(Disciplina lista_disciplina[], Aluno lista_aluno[], int qtdDisciplina, int qtdAluno){

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

    int id_search_student;
    int id_search_disciplina;
    int ok_id;
    do {
    printf("Digite o ID da disciplina para inserir o Aluno: ");
    ok_id = ler_int(&id_search_disciplina);
        
        if(!ok_id || id_search_disciplina < 0){
            printf("-------------------------------------------------\n");
            printf(" Apenas digitos de 0 a 9 sao permitidos no ID.\n");
            printf("-------------------------------------------------\n");
        } 
    }while(!ok_id);
    
    ok_id = 0;
    
    do {
    printf("Digite a matricula do aluno a ser inserida: ");
    ok_id = ler_int(&id_search_student);
             
        if(!ok_id || id_search_student < 0){
            printf("-------------------------------------------------\n");
            printf(" Apenas digitos de 0 a 9 sao permitidos no ID.\n");
            printf("-------------------------------------------------\n");
        } 
    }while(!ok_id);

    int indice_disciplina;
    int indice_aluno;

    indice_disciplina = search_id_disciplina(lista_disciplina, qtdDisciplina, id_search_disciplina);
    indice_aluno = search_id(lista_aluno, qtdAluno, id_search_student);

    if(indice_disciplina != -1 && indice_aluno != -1) {

        lista_disciplina[indice_disciplina].studentRegistration[lista_disciplina[indice_disciplina].studentCount] = id_search_student;
        lista_disciplina[indice_disciplina].studentCount++;

        printf("Aluno inserido com sucesso.\n");
        return;
    }
    else if(indice_disciplina == -1 && indice_aluno == -1) {
        printf("Aluno e disciplina nao encontrados.\n");
        return;
    } else if(indice_disciplina == -1) {
        printf("Nao ha disciplina com essa ID. Tente novamente.\n");
        return;
    } else {
        printf("Nao ha aluno com essa matricula. Tente novamente.\n");
        return;
    }
}

void excluir_AlunoDisciplina(Disciplina lista_disciplina[], Aluno lista_aluno[], int qtdDisciplina, int qtdAluno) {

    if(qtdAluno == 0 && qtdDisciplina == 0) {
        printf("---------------------------------------------\n");
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

    int id_search_student;
    int id_search_disciplina;
    int ok_id;
    do {
        printf("Digite o ID da disciplina para remover o Aluno: ");
        ok_id = ler_int(&id_search_disciplina);

        if(!ok_id || id_search_disciplina < 0){
            printf("-------------------------------------------------\n");
            printf(" Apenas digitos de 0 a 9 sao permitidos no ID.\n");
            printf("-------------------------------------------------\n");
        }
    } while(!ok_id);

    ok_id = 0;

    do {
        printf("Digite a matricula do aluno a ser removido: ");
        ok_id = ler_int(&id_search_student);

        if(!ok_id || id_search_student < 0){
            printf("-------------------------------------------------\n");
            printf(" Apenas digitos de 0 a 9 sao permitidos no ID.\n");
            printf("-------------------------------------------------\n");
        }
    } while(!ok_id);

    int pos_D = search_id_disciplina(lista_disciplina, qtdDisciplina, id_search_disciplina);
    int pos_A = search_id(lista_aluno, qtdAluno, id_search_student);

    if(pos_D == -1 && pos_A == -1) {
        printf("Aluno e disciplina nao encontrados.\n");
        return;
    } else if(pos_D == -1) {
        printf("Nao ha disciplina com essa ID. Tente novamente.\n");
        return;
    } else if(pos_A == -1) {
        printf("Nao ha aluno com essa matricula. Tente novamente.\n");
        return;
    }

    int pos_aluno_na_disciplina = -1;
    for(int i = 0; i < lista_disciplina[pos_D].studentCount; i++) {
        if(lista_disciplina[pos_D].studentRegistration[i] == id_search_student) {
            pos_aluno_na_disciplina = i;
            break;
        }
    }

    if(pos_aluno_na_disciplina == -1) {
        printf("Esse aluno nao esta matriculado nessa disciplina.\n");
        return;
    }

    for(int i = pos_aluno_na_disciplina; i < lista_disciplina[pos_D].studentCount - 1; i++) {
        lista_disciplina[pos_D].studentRegistration[i] = lista_disciplina[pos_D].studentRegistration[i+1];
    }
    lista_disciplina[pos_D].studentCount--;

    printf("Aluno removido da disciplina com sucesso.\n");
}