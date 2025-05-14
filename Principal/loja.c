// loja.c - Implementações das funções relacionadas à loja
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:/Users/joaov/Desktop/Sistema_Doceria/Header/loja.h"
#include "C:/Users/joaov/Desktop/Sistema_Doceria/Header/utils.h"

#define MAX_LINHA 100

// Lista todos os usuários cadastrados (do arquivo usuarios.csv)
void listarUsuarios() {
    printf("\n=== LISTA DE USUÁRIOS ===\n");
    FILE *f = fopen("usuarios.csv", "r");
    if (!f) {
        printf("Erro ao abrir arquivo de usuários.\n");
        return;
    }
    char linha[MAX_LINHA];
    int count = 0;
    while (fgets(linha, sizeof(linha), f)) {
        char nome[MAX_NOME], senha[MAX_SENHA];
        sscanf(linha, " %[^,],%[^\n]", nome, senha);
        printf("%d. %s (senha: %s)\n", ++count, nome, senha);
    }
    if (count == 0) {
        printf("Nenhum usu�rio cadastrado.\n");
    }
    fclose(f);
}

// Lista todos os produtos do cardápio (arquivo cardapio.csv)
void listarProdutos() {
    printf("\n=== LISTA DE PRODUTOS (CARD�PIO) ===\n");
    FILE *f = fopen("cardapio.csv", "r");
    if (!f) {
        printf("Erro ao abrir card�pio.\n");
        return;
    }
    char linha[MAX_LINHA];
    int count = 0;
    while (fgets(linha, sizeof(linha), f)) {
        char produto[MAX_PRODUTO];
        int qtd;
        sscanf(linha, " %[^,],%d", produto, &qtd);
        printf("%d. %s (quantidade: %d)\n", ++count, produto, qtd);
    }
    if (count == 0) {
        printf("Nenhum produto cadastrado.\n");
    }
    fclose(f);
}

// Adiciona um novo produto ao cardápio (anexa em cardapio.csv)
void adicionarProduto() {
    char nomeProduto[MAX_PRODUTO];
    int quantidade;
    printf("\n=== ADICIONAR PRODUTO AO CARD�PIO ===\n");
    printf("Digite o nome do produto: ");
    scanf(" %49[^\n]", nomeProduto);
    printf("Digite a quantidade dispon�vel: ");
    scanf("%d", &quantidade);

    FILE *f = fopen("cardapio.csv", "a");
    if (!f) {
        printf("Erro ao abrir card�pio.\n");
        return;
    }
    fprintf(f, "%s,%d\n", nomeProduto, quantidade);
    fclose(f);
    printf("Produto adicionado com sucesso!\n");
}

// Atualiza a quantidade de um produto existente no cardápio
void atualizarProduto() {
    printf("\n=== ATUALIZAR QUANTIDADE DE PRODUTO ===\n");
    listarProdutos();
    int codigo, novaQtd;
    printf("Digite o c�digo do produto para alterar a quantidade: ");
    scanf("%d", &codigo);

    FILE *f = fopen("cardapio.csv", "r");
    if (!f) {
        printf("Erro ao abrir card�pio.\n");
        return;
    }
    FILE *temp = fopen("temp.csv", "w");
    if (!temp) {
        fclose(f);
        printf("Erro ao criar arquivo tempor�rio.\n");
        return;
    }
    char linha[MAX_LINHA];
    int atual = 1;
    bool encontrado = false;
    while (fgets(linha, sizeof(linha), f)) {
        char produto[MAX_PRODUTO];
        int qtd;
        sscanf(linha, " %[^,],%d", produto, &qtd);
        if (atual == codigo) {
            printf("Digite nova quantidade para %s: ", produto);
            scanf("%d", &novaQtd);
            fprintf(temp, "%s,%d\n", produto, novaQtd);
            encontrado = true;
        } else {
            fprintf(temp, "%s,%d\n", produto, qtd);
        }
        atual++;
    }
    fclose(f);
    fclose(temp);

    if (encontrado) {
        remove("cardapio.csv");
        rename("temp.csv", "cardapio.csv");
        printf("Quantidade atualizada com sucesso!\n");
    } else {
        remove("temp.csv");
        printf("Produto n�o encontrado.\n");
    }
}

// Remove um produto do cardápio
void removerProduto() {
    printf("\n=== REMOVER PRODUTO DO CARD�PIO ===\n");
    listarProdutos();
    int codigo;
    printf("Digite o c�digo do produto para remover: ");
    scanf("%d", &codigo);

    FILE *f = fopen("cardapio.csv", "r");
    if (!f) {
        printf("Erro ao abrir card�pio.\n");
        return;
    }
    FILE *temp = fopen("temp.csv", "w");
    if (!temp) {
        fclose(f);
        printf("Erro ao criar arquivo tempor�rio.\n");
        return;
    }
    char linha[MAX_LINHA];
    int atual = 1;
    bool encontrado = false;
    while (fgets(linha, sizeof(linha), f)) {
        char produto[MAX_PRODUTO];
        int qtd;
        sscanf(linha, " %[^,],%d", produto, &qtd);
        if (atual == codigo) {
            encontrado = true;
            printf("Produto %s removido.\n", produto);
            // N�o escreve no temp (omite a linha removida)
        } else {
            fprintf(temp, "%s,%d\n", produto, qtd);
        }
        atual++;
    }
    fclose(f);
    fclose(temp);

    if (encontrado) {
        remove("cardapio.csv");
        rename("temp.csv", "cardapio.csv");
    } else {
        remove("temp.csv");
        printf("Produto n�o encontrado.\n");
    }
}

// Exibe todos os pedidos com status "EM ESPERA" e permite processar um deles
void processarPedidos() {
    printf("\n=== PROCESSAR PEDIDOS ===\n");
    FILE *f = fopen("pedidos.csv", "r");
    if (!f) {
        printf("Erro ao abrir arquivo de pedidos.\n");
        return;
    }
    char linha[MAX_LINHA];
    int count = 0;
    // Lista pedidos pendentes
    while (fgets(linha, sizeof(linha), f)) {
        char cliente[MAX_NOME], produto[MAX_PRODUTO], status[MAX_STATUS];
        int qtd;
        sscanf(linha, " %[^,],%[^,],%d,%19[^\n]", cliente, produto, &qtd, status);
        if (strcmp(status, "EM ESPERA") == 0) {
            printf("%d. Cliente: %-10s | Produto: %-12s | Quantidade: %2d | Status: %s\n",
                   ++count, cliente, produto, qtd, status);
        }
    }
    fclose(f);
    if (count == 0) {
        printf("Não há pedidos em espera.\n");
        return;
    }
    int escolha;
    printf("Digite o número do pedido para processar (0 para voltar): ");
    scanf("%d", &escolha);
    if (escolha == 0) {
        return;
    }
    // Reescreve pedidos, atualizando o escolhido
    f = fopen("pedidos.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!temp) {
        if (f) fclose(f);
        printf("Erro ao criar arquivo tempor�rio.\n");
        return;
    }
    int atual = 0;
    bool encontrado = false;
    while (fgets(linha, sizeof(linha), f)) {
        char cliente[MAX_NOME], produto[MAX_PRODUTO], status[MAX_STATUS];
        int qtd;
        sscanf(linha, " %[^,],%[^,],%d,%19[^\n]", cliente, produto, &qtd, status);
        if (strcmp(status, "EM ESPERA") == 0) {
            atual++;
            if (atual == escolha) {
                char novaStatus[MAX_STATUS];
                printf("Digite novo status para este pedido (CONFIRMADO/RECUSADO): ");
                scanf(" %19[^\n]", novaStatus);
                fprintf(temp, "%s,%s,%d,%s\n", cliente, produto, qtd, novaStatus);
                encontrado = true;
            } else {
                fprintf(temp, "%s,%s,%d,%s\n", cliente, produto, qtd, status);
            }
        } else {
            // Já processados permanecem inalterados
            fprintf(temp, "%s,%s,%d,%s\n", cliente, produto, qtd, status);
        }
    }
    fclose(f);
    fclose(temp);

    if (encontrado) {
        remove("pedidos.csv");
        rename("temp.csv", "pedidos.csv");
        printf("Pedido atualizado com sucesso!\n");
    } else {
        remove("temp.csv");
        printf("Pedido n�o encontrado ou n�o estava em espera.\n");
    }
}

// Menu de opções da área da loja (administração)
void lojaMenu() {
    int opc;
    do {
        printf("\n--- MENU LOJA ---\n");
        printf("1. Listar usu�rios cadastrados\n");
        printf("2. Listar produtos\n");
        printf("3. Adicionar produto\n");
        printf("4. Atualizar produto\n");
        printf("5. Remover produto\n");
        printf("6. Processar pedidos\n");
        printf("0. Voltar\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                listarUsuarios();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                adicionarProduto();
                break;
            case 4:
                atualizarProduto();
                break;
            case 5:
                removerProduto();
                break;
            case 6:
                processarPedidos();
                break;
            case 0:
                // volta ao menu principal
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opc != 0);
}