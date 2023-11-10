//
// Created by isabe on 19/09/2023.
//

#ifndef PROJETO1_BIBLIOTECA_H
#define PROJETO1_BIBLIOTECA_H

#define MAX_TAREFAS 100

struct Tarefa {
    int prioridade;
    char descricao[300];
    char categoria[100];
};

void salvarTarefa(struct Tarefa tarefas[], int nTarefas);
void lerTarefas(struct Tarefa tarefas[], int *nTarefas);
void cadastrarTarefa(struct Tarefa tarefas[], int *nTarefas);
void listarTarefas(struct Tarefa tarefas[], int nTarefas);
void deletarTarefa(struct Tarefa tarefas[], int *nTarefas, int indice);

#endif //PROJETO1_BIBLIOTECA_H