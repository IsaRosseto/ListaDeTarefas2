//
// Created by isabe on 19/09/2023.
//

#include "Biblioteca.h"
#include <stdio.h>

void salvarTarefa(struct Tarefa tarefas[], int nTarefas) {
    FILE *arquivo;
    arquivo = fopen("tarefas.bin", "wb");

    if (arquivo != NULL) {
        fwrite(tarefas, sizeof(struct Tarefa), nTarefas, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo .\n");
    }
}
// na função SALVAR-TAREFA abre o arquivo "tarefas.bin" em modo de escrita binária ,escreve as tarefas no arquivo usando fwrite e fecha o arquivo.
// Se o arquivo não puder ser aberto, uma mensagem de erro é exibida.



void lerTarefas(struct Tarefa tarefas[], int *nTarefas) {
    FILE *arquivo;
    arquivo = fopen("tarefas.bin", "rb");

    if (arquivo != NULL) {
        fseek(arquivo, 0, SEEK_END);
        long tamanhoArquivo = ftell(arquivo);
        *nTarefas = tamanhoArquivo / sizeof(struct Tarefa);

        fseek(arquivo, 0, SEEK_SET);
        fread(tarefas, sizeof(struct Tarefa), *nTarefas, arquivo); // Lê os dados do arquivo
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo para leitura.\n");
    }
}
//A função "lerTarefas" abre o arquivo "tarefas.bin", olha para as tarefas dentro dele,
// lê cada uma das tarefas dentro do arquivo
// ele move o indicador de posição do arquivo para determinar seu tamanho,
// divide pelo tamanho da "struct Tarefa" para obter o número de tarefas,
// lendo essas tarefas no array "tarefas" e, finalmente, fechando o arquivo.



void cadastrarTarefa(struct Tarefa tarefas[], int *nTarefas) {
    if (*nTarefas < MAX_TAREFAS) {
        struct Tarefa novaTarefa;
        printf("Qual a prioridade da tarefa (0-10): ");
        scanf("%d", &novaTarefa.prioridade);
        printf("Descreva a tarefa: ");
        scanf(" %[^\n]", novaTarefa.descricao);
        printf("Informe a categoria da tarefa: ");
        scanf(" %[^\n]", novaTarefa.categoria);
        printf("Informe o estado da tarefa (completo/em andamento/não iniciado): ");
        scanf(" %[^\n]", novaTarefa.estado);

        tarefas[*nTarefas] = novaTarefa;
        (*nTarefas)++;
        salvarTarefa(tarefas, *nTarefas);
        printf("Tarefa cadastrada com sucesso!\n");
    } else {
        printf("A lista de tarefas está cheia. Não é possível cadastrar mais tarefas.\n");
    }
}

//A função verifica se a lista de tarefas não está cheia (MAX_TAREFAS).
// Se houver espaço disponível salvamos uma nova tarefa aumentamndo o contador de tarefas em 1 para saber que temos mais uma tarefa na lista.



void listarTarefas(struct Tarefa tarefas[], int nTarefas) {
    printf("Lista de Tarefas:\n");
    for (int i = 0; i < nTarefas; i++) {
        printf("Tarefa %d\n", i + 1);
        printf("Prioridade: %d\n", tarefas[i].prioridade);
        printf("Descricao: %s\n", tarefas[i].descricao);
        printf("Categoria: %s\n", tarefas[i].categoria);
        printf("\n");
    }
}
//Essa função mostra uma lista de tarefas. Ela imprime cada tarefa na tela, uma por uma.
// Para cada tarefa, mostra a prioridade, a descrição e a categoria.



void deletarTarefa(struct Tarefa tarefas[], int *nTarefas, int indice) {
    if (indice >= 0 && indice < *nTarefas) {
        for (int i = indice; i < *nTarefas - 1; i++) {
            tarefas[i] = tarefas[i + 1];
        }
        (*nTarefas)-- ;
        salvarTarefa(tarefas, *nTarefas); // Salva as tarefas no arquivo após deletar uma
        printf("Tarefa deletada com sucesso!\n");
    } else {
        printf("Índice de tarefa inválido.\n");
    }
}
//Primeiro ela verifica se o número que você escolheu para a tarefa está dentro dos limites da lista.
// Se estiver, ela remove a tarefa, deslocando todas as outras tarefas uma posição para trás, preenchendo o espaço vazio.
// Em seguida, ela diminui o contador de tarefas em 1 para refletir a exclusão e salva a lista atualizada no arquivo
