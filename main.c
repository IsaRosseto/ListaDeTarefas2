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
        printf("4. Sair\n");
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
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
