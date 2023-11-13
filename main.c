//Gustavo Bertoluzzi Cardoso         RA: 22.123.016-2
//Isabella Vieira Silva Rosseto      RA: 22.222.036-0

//OBS: Os comentarios sobre a implementação das funções e a logica estão em "biblioteca.c"


#include <stdio.h>
#include "Biblioteca.h"

int main() {
    struct Tarefa tarefas[MAX_TAREFAS];
    int numTarefas = 0;

    lerTarefas(tarefas, &numTarefas);

    int opcao;
    while (1) {
        printf("Escolha uma opcao:\n");
        printf("1. Cadastrar tarefa\n");
        printf("2. Listar tarefas\n");
        printf("3. Deletar tarefa\n");
        printf("4. Alterar tarefa\n");
        printf("5. Filtrar por prioridade \n");
        printf("6. Filtrar por estado\n");
        printf("7. Filtrar por categoria\n");
        printf("8. Filtrar por prioridade e categoria\n");
        printf("9. Exportar tarefa por Prioridade\n");
        printf("10. Exportar tarefa por Categoria\n");
        printf("11. Exportar por prioridade e Categoria\n");
        printf("12. Sair\n");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarTarefa(tarefas, &numTarefas);
                break;
            case 2:
                listarTarefas(tarefas, numTarefas);
                break;
            case 3:
                if (numTarefas > 0) {
                    int indice;
                    printf("Informe o id da tarefa a ser deletada: ");
                    scanf("%d", &indice);
                    deletarTarefa(tarefas, &numTarefas, indice - 1);
                } else {
                    printf("Não ha tarefas cadastradas.\n");
                }
                break;
            case 4:
                if (numTarefas > 0) {
                    alterarTarefa(tarefas, numTarefas);
                } else {
                    printf("Não ha tarefas cadastradas.\n");
                }
                break;
            case 5:
                if (numTarefas > 0) {
                    int prioridade;
                    printf("Informe a prioridade para filtrar as tarefas: ");
                    scanf("%d", &prioridade);
                    filtrarPorPrioridade(tarefas, numTarefas, prioridade);
                } else {
                    printf("Nenhuma tarefa cadastrada.\n");
                }
                break;
            case 6:
                if (numTarefas > 0) {
                    char estado[15];
                    printf("Informe o estado para filtrar as tarefas (completo/em andamento/não iniciado): ");
                    scanf(" %[^\n]", estado);
                    filtrarPorEstado(tarefas, numTarefas, estado);
                } else {
                    printf("Nenhuma tarefa cadastrada.\n");
                }
                break;
            case 7:
                if (numTarefas > 0) {
                    char categoria[100];
                    printf("Informe a categoria para filtrar as tarefas: ");
                    scanf(" %[^\n]", categoria);
                    filtrarPorCategoria(tarefas, numTarefas, categoria);
                } else {
                    printf("Nenhuma tarefa cadastrada.\n");
                }
                break;
            case 8:
                if (numTarefas > 0) {
                    int prioridade;
                    char categoria[100];
                    printf("Informe a prioridade para filtrar as tarefas: ");
                    scanf("%d", &prioridade);
                    printf("Informe a categoria para filtrar as tarefas: ");
                    scanf(" %[^\n]", categoria);
                    filtrarPorPrioridadeECategoria(tarefas, numTarefas, prioridade, categoria);
                } else {
                    printf("Nenhuma tarefa cadastrada.\n");
                }
                break;
            case 9:
                if (numTarefas > 0) {
                    int prioridadeExportacao;
                    printf("Informe a prioridade para exportar as tarefas: ");
                    scanf("%d", &prioridadeExportacao);
                    exportarPorPrioridade(tarefas, numTarefas, prioridadeExportacao);
                } else {
                    printf("Nenhuma tarefa cadastrada.\n");
                }
                break;
            case 10:
                if (numTarefas > 0) {
                    char categoriaExportacao[100];
                    printf("Informe a categoria para exportar as tarefas: ");
                    scanf(" %[^\n]", categoriaExportacao);
                    exportarPorCategoria(tarefas, numTarefas, categoriaExportacao);
                } else {
                    printf("Nenhuma tarefa cadastrada.\n");
                }
                break;
            case 11:
                if (numTarefas > 0) {
                    int prioridadeExportacao;
                    char categoriaExportacao[100];
                    printf("Informe a prioridade para exportar as tarefas: ");
                    scanf("%d", &prioridadeExportacao);
                    printf("Informe a categoria para exportar as tarefas: ");
                    scanf(" %[^\n]", categoriaExportacao);
                    exportarPorPrioridadeECategoria(tarefas, numTarefas, prioridadeExportacao, categoriaExportacao);
                } else {
                    printf("Nenhuma tarefa cadastrada.\n");
                }
                break;
            case 12:
                printf("Saindo...");
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
