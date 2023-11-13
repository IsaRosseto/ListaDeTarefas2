//
// Created by isabe on 19/09/2023.
//

#include "biblioteca.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Função para salvar tarefas em um arquivo binário
void salvarTarefa(struct Tarefa tarefas[], int nTarefas) {
    FILE *arquivo;
    arquivo = fopen("tarefas.bin", "wb");

    if (arquivo != NULL) {
        // Escreve as tarefas no arquivo
        fwrite(tarefas, sizeof(struct Tarefa), nTarefas, arquivo);
        fclose(arquivo);
    } else {
        // Exibe uma mensagem de erro se o arquivo não puder ser aberto
        printf("Erro ao abrir o arquivo.\n");
    }
}

// Função para ler tarefas de um arquivo binário
void lerTarefas(struct Tarefa tarefas[], int *nTarefas) {
    FILE *arquivo;
    arquivo = fopen("tarefas.bin", "rb");

    if (arquivo != NULL) {
        // Determina o tamanho do arquivo para calcular o número de tarefas
        fseek(arquivo, 0, SEEK_END);
        long tamanhoArquivo = ftell(arquivo);
        *nTarefas = tamanhoArquivo / sizeof(struct Tarefa);

        fseek(arquivo, 0, SEEK_SET);
        // Lê as tarefas do arquivo
        fread(tarefas, sizeof(struct Tarefa), *nTarefas, arquivo);
        fclose(arquivo);
    } else {
        // Exibe uma mensagem de erro se o arquivo não puder ser aberto para leitura
        printf("Erro ao abrir o arquivo para leitura.\n");
    }
}

// Função para cadastrar uma nova tarefa
void cadastrarTarefa(struct Tarefa tarefas[], int *nTarefas) {
    if (*nTarefas < MAX_TAREFAS) {
        struct Tarefa novaTarefa;
        printf("Qual a prioridade da tarefa (0-10): ");
        scanf("%d", &novaTarefa.prioridade);
        printf("Descreva a tarefa: ");
        scanf(" %[^\n]", novaTarefa.descricao);
        printf("Informe a categoria da tarefa: ");
        scanf(" %[^\n]", novaTarefa.categoria);

        char estado[15];
        do {
            printf("Informe o estado da tarefa:\n - completo\n - em andamento\n - nao iniciado: ");
            scanf(" %[^\n]", estado);
            if (strcmp(estado, "completo") != 0 && strcmp(estado, "em andamento") != 0 && strcmp(estado, "nao iniciado") != 0) {
                printf("Estado inválido. Tente novamente.\n");
            }
        } while (strcmp(estado, "completo") != 0 && strcmp(estado, "em andamento") != 0 && strcmp(estado, "nao iniciado") != 0);

        strcpy(novaTarefa.estado, estado);

        tarefas[*nTarefas] = novaTarefa;
        (*nTarefas)++;
        salvarTarefa(tarefas, *nTarefas);
        printf("Tarefa cadastrada com sucesso!\n");
    } else {
        printf("A lista de tarefas está cheia. Não é possível cadastrar mais tarefas.\n");
    }
}

// Função para exibir uma lista de tarefas
void listarTarefas(struct Tarefa tarefas[], int nTarefas) {
    printf("Lista de Tarefas:\n");
    for (int i = 0; i < nTarefas; i++) {
        printf("Tarefa %d\n", i + 1);
        printf("Prioridade: %d\n", tarefas[i].prioridade);
        printf("Descricao: %s\n", tarefas[i].descricao);
        printf("Categoria: %s\n", tarefas[i].categoria);
        printf("Estado: %s\n", tarefas[i].estado); // Mostrar o estado da tarefa
        printf("\n");
    }
}

// Função para deletar uma tarefa em um índice especificado
void deletarTarefa(struct Tarefa tarefas[], int *nTarefas, int indice) {
    if (indice >= 0 && indice < *nTarefas) {
        for (int i = indice; i < *nTarefas - 1; i++) {
            tarefas[i] = tarefas[i + 1];
        }
        (*nTarefas)--;
        salvarTarefa(tarefas, *nTarefas); // Salva as tarefas no arquivo após deletar uma
        printf("Tarefa deletada com sucesso!\n");
    } else {
        printf("Índice de tarefa inválido.\n");
    }
}

// Função para alterar uma tarefa
void alterarTarefa(struct Tarefa tarefas[], int nTarefas) {
    int indice;
    printf("Informe o índice da tarefa a ser alterada: ");
    scanf("%d", &indice);

    if (indice >= 1 && indice <= nTarefas) {
        int opcao;
        printf("Escolha qual campo deseja alterar:\n");
        printf("1. Prioridade\n");
        printf("2. Descrição\n");
        printf("3. Categoria\n");
        printf("4. Estado\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Qual a nova prioridade da tarefa (0-10): ");
                scanf("%d", &tarefas[indice - 1].prioridade); // O índice - 1 é porque o primeiro índice do array é igual a 0
                break;
            case 2:
                printf("Qual a nova descrição da tarefa: ");
                scanf(" %[^\n]", tarefas[indice - 1].descricao);
                break;
            case 3:
                printf("Qual a nova categoria da tarefa: ");
                scanf(" %[^\n]", tarefas[indice - 1].categoria);
                break;
            case 4: {
                char estado[15];
                do {
                    printf("Informe o novo estado da tarefa (completo/em andamento/não iniciado): ");
                    scanf(" %[^\n]", estado);
                    if (strcmp(estado, "completo") != 0 && strcmp(estado, "em andamento") != 0 && strcmp(estado, "nao iniciado") != 0) {
                        printf("Estado inválido. Tente novamente.\n");
                    }
                } while (strcmp(estado, "completo") != 0 && strcmp(estado, "em andamento") != 0 && strcmp(estado, "nao iniciado") != 0);
                strcpy(tarefas[indice - 1].estado, estado);
                break;
            }
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
        salvarTarefa(tarefas, nTarefas);
        printf("Tarefa alterada com sucesso!\n");
    } else {
        printf("Índice de tarefa inválido.\n");
    }
}

// Função para filtrar tarefas por prioridade
void filtrarPorPrioridade(struct Tarefa tarefas[], int nTarefas, int prioridade) {
    printf("Tarefas com prioridade %d:\n", prioridade);
    int encontrou = 0;
    for (int i = 0; i < nTarefas; i++) {
        if (tarefas[i].prioridade == prioridade) {
            printf("Tarefa %d\n", i + 1);
            printf("Descrição: %s\n", tarefas[i].descricao);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Estado: %s\n", tarefas[i].estado);
            printf("\n");
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com a prioridade %d.\n", prioridade);
    }
}

// Função para filtrar tarefas por estado
void filtrarPorEstado(struct Tarefa tarefas[], int nTarefas, const char *estadoFiltrado) {
    printf("Tarefas com estado %s:\n", estadoFiltrado);
    int encontrou = 0;
    for (int i = 0; i < nTarefas; i++) {
        if (strcmp(tarefas[i].estado, estadoFiltrado) == 0) {
            printf("Tarefa %d\n", i + 1);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Descrição: %s\n", tarefas[i].descricao);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("\n");
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com o estado %s.\n", estadoFiltrado);
    }
}

// Função de comparação para qsort
int compararPrioridadeDecrescente(const void *tarefaA, const void *tarefaB) {
    const struct Tarefa *tarefa1 = (const struct Tarefa *)tarefaA;
    const struct Tarefa *tarefa2 = (const struct Tarefa *)tarefaB;
    if (tarefa1->prioridade < tarefa2->prioridade) {
        return 1;
    } else if (tarefa1->prioridade > tarefa2->prioridade) {
        return -1;
    }
    return 0;
}

// Função para filtrar tarefas por categoria
void filtrarPorCategoria(struct Tarefa tarefas[], int nTarefas, const char *categoriaFiltrada) {
    printf("Tarefas na categoria %s, ordenadas por prioridade:\n", categoriaFiltrada);
    struct Tarefa tarefasFiltradas[MAX_TAREFAS];
    int numTarefasFiltradas = 0;

    // Filtrar tarefas pela categoria
    for (int i = 0; i < nTarefas; i++) {
        if (strcmp(tarefas[i].categoria, categoriaFiltrada) == 0) {
            tarefasFiltradas[numTarefasFiltradas] = tarefas[i];
            numTarefasFiltradas++;
        }
    }

    // Ordenar tarefas pela prioridade
    qsort(tarefasFiltradas, numTarefasFiltradas, sizeof(struct Tarefa), compararPrioridadeDecrescente);

    // Exibir tarefas ordenadas
    for (int i = 0; i < numTarefasFiltradas; i++) {
        printf("Tarefa %d\n", i + 1);
        printf("Prioridade: %d\n", tarefasFiltradas[i].prioridade);
        printf("Descrição: %s\n", tarefasFiltradas[i].descricao);
        printf("Estado: %s\n", tarefasFiltradas[i].estado);
        printf("\n");
    }

    if (numTarefasFiltradas == 0) {
        printf("Nenhuma tarefa encontrada na categoria %s.\n", categoriaFiltrada);
    }
}

// Função para filtrar tarefas por prioridade e categoria
void filtrarPorPrioridadeECategoria(struct Tarefa tarefas[], int nTarefas, int prioridade, const char *categoria) {
    printf("Tarefas com prioridade %d e na categoria %s:\n", prioridade, categoria);
    int encontrou = 0;
    for (int i = 0; i < nTarefas; i++) {
        if (tarefas[i].prioridade == prioridade && strcmp(tarefas[i].categoria, categoria) == 0) {
            printf("Tarefa %d\n", i + 1);
            printf("Descricao: %s\n", tarefas[i].descricao);
            printf("Estado: %s\n", tarefas[i].estado);
            printf("\n");
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com a prioridade %d e na categoria %s.\n", prioridade, categoria);
    }
}

// Função para Exportar arquivo pela PRIORIDADE
void exportarPorPrioridade(struct Tarefa tarefas[], int nTarefas, int prioridade) {
    char nomeArquivo[50];
    sprintf(nomeArquivo, "tarefas_por_prioridade_%d.txt", prioridade);
    FILE *arquivoExportado;
    arquivoExportado = fopen(nomeArquivo, "w");

    if (arquivoExportado != NULL) {
        fprintf(arquivoExportado, "Prioridade | Categoria | Estado | Descricao\n");
        for (int i = 0; i < nTarefas; i++) {
            if (tarefas[i].prioridade == prioridade) {
                fprintf(arquivoExportado, "%-10d | %-9s | %-11s | %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
            }
        }
        fclose(arquivoExportado);
        printf("Tarefas com prioridade %d exportadas com sucesso para o arquivo '%s'.\n", prioridade, nomeArquivo);
    } else {
        printf("Erro ao criar o arquivo de exportacao.\n");
    }
}

// Função de comparação para qsort
int compararPrioridade(const void *tarefaA, const void *tarefaB) {
    const struct Tarefa *tarefa1 = (const struct Tarefa *)tarefaA;
    const struct Tarefa *tarefa2 = (const struct Tarefa *)tarefaB;
    if (tarefa1->prioridade < tarefa2->prioridade) {
        return 1;
    } else if (tarefa1->prioridade > tarefa2->prioridade) {
        return -1;
    }
    return 0;
}

// Função para Exportar arquivo pela CATEGORIA
void exportarPorCategoria(struct Tarefa tarefas[], int nTarefas, const char *categoria) {
    char nomeArquivo[50];
    sprintf(nomeArquivo, "tarefas_por_categoria_%s.txt", categoria);
    FILE *arquivoExportado;
    arquivoExportado = fopen(nomeArquivo, "w");

    if (arquivoExportado != NULL) {
        fprintf(arquivoExportado, "Prioridade | Categoria | Estado | Descricao\n");

        // Filtrar tarefas pela categoria
        struct Tarefa tarefasFiltradas[MAX_TAREFAS];
        int numTarefasFiltradas = 0;
        for (int i = 0; i < nTarefas; i++) {
            if (strcmp(tarefas[i].categoria, categoria) == 0) {
                tarefasFiltradas[numTarefasFiltradas] = tarefas[i];
                numTarefasFiltradas++;
            }
        }

        // Ordenar tarefas pela prioridade
        qsort(tarefasFiltradas, numTarefasFiltradas, sizeof(struct Tarefa), compararPrioridade);

        // Exportar tarefas ordenadas
        for (int i = 0; i < numTarefasFiltradas; i++) {
            fprintf(arquivoExportado, "%-10d | %-9s | %-11s | %s\n", tarefasFiltradas[i].prioridade, tarefasFiltradas[i].categoria, tarefasFiltradas[i].estado, tarefasFiltradas[i].descricao);
        }
        fclose(arquivoExportado);
        printf("Tarefas na categoria %s exportadas com sucesso para o arquivo '%s'.\n", categoria, nomeArquivo);
    } else {
        printf("Erro ao criar o arquivo de exportacao.\n");
    }
}

// Função para Exportar arquivo pela CATEGORIA e PRIORIDADE
void exportarPorPrioridadeECategoria(struct Tarefa tarefas[], int nTarefas, int prioridade, const char *categoria) {
    int tarefasEncontradas = 0;

    // Verificar se existem tarefas com a prioridade e a categoria especificadas
    for (int i = 0; i < nTarefas; i++) {
        if (tarefas[i].prioridade == prioridade && strcmp(tarefas[i].categoria, categoria) == 0) {
            tarefasEncontradas = 1;
            break;
        }
    }

    if (tarefasEncontradas) {
        char nomeArquivo[50];
        sprintf(nomeArquivo, "tarefas_por_prioridade_%d_e_categoria_%s.txt", prioridade, categoria);
        FILE *arquivoExportado;
        arquivoExportado = fopen(nomeArquivo, "w");

        if (arquivoExportado != NULL) {
            fprintf(arquivoExportado, "Prioridade | Categoria | Estado | Descricao\n");
            for (int i = 0; i < nTarefas; i++) {
                if (tarefas[i].prioridade == prioridade && strcmp(tarefas[i].categoria, categoria) == 0) {
                    fprintf(arquivoExportado, "%-10d | %-9s | %-11s | %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
                }
            }
            fclose(arquivoExportado);
            printf("Tarefas com prioridade %d e na categoria %s exportadas com sucesso para o arquivo '%s'.\n", prioridade, categoria, nomeArquivo);
        } else {
            printf("Erro ao criar o arquivo de exportacao.\n");
        }
    } else {
        printf("Nenhuma tarefa encontrada com a prioridade %d e na categoria %s. Nenhum arquivo foi exportado.\n", prioridade, categoria);
    }
}
