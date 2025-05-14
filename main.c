// main.c
// Arquivo principal com o menu de escolha entre Cliente ou Loja
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "./Principal/cliente.h"
#include "./Principal/loja.h"
#include "./Principal/utils.h"



int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcao;
    do {
        printf("\n==== DOCERIA - MENU PRINCIPAL ===\n");
        printf("1. Área do Cliente\n");
        printf("2. Área da Loja\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                clienteMenu(); // Chama o menu de operações do cliente
                break;
            case 2:
                lojaMenu();    // Chama o menu de operações da loja (admin)
                break;
            case 0:
                printf("Saindo do sistema. Obrigado!\n");
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
