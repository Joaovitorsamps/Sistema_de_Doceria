// cliente.c - Implementa��es das fun��es relacionadas ao cliente
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./cliente.h"
#include "./utils.h"

#define MAX_LINHA 100

// Função de cadastro de novo usuário
void cadastrarUsuario() {
    char nome[MAX_NOME], senha[MAX_SENHA];
    printf("\n=== CADASTRO DE USUÁRIO ===\n");
    printf("Digite o nome do usuário: ");
    scanf(" %49[^\n]", nome); // l� linha at� o fim, incluindo espa�os
    toUpperCase(nome);        // padroniza para mai�sculas
    
    // Verifica se usu�rio já existe em usuarios.csv
    if (nomeExists("usuarios.csv", nome)) {
        printf("Usu�rio j� existe!\n");
        return;
    }

    printf("Digite a senha: ");
    scanf(" %19[^\n]", senha);
    FILE *f = fopen("usuarios.csv", "a");
    if (f == NULL) {
        printf("Erro ao abrir arquivo de usu�rios.\n");
        return;
    }
    fprintf(f, "%s,%s\n", nome, senha); // formata CSV: nome,senha
    fclose(f);
    printf("Cadastro realizado com sucesso!\n");
}

// Função de login do usuário; retorna 1 em sucesso, 0 caso contrário
int loginUsuario(char nomeLogado[]) {
    char nome[MAX_NOME], senha[MAX_SENHA];
    printf("\n=== LOGIN DO USU�RIO ===\n");
    printf("Digite o nome do usu�rio: ");
    scanf(" %49[^\n]", nome);
    toUpperCase(nome);

printf("Digite a senha: ");
    scanf(" %19[^\n]", senha);

    FILE *f = fopen("usuarios.csv", "r");
    if (f == NULL) {
        printf("Erro ao abrir arquivo de usu�rios.\n");
        return 0;
    }
    char linha[MAX_LINHA];
    while (fgets(linha, sizeof(linha), f)) {
        // Extrai nome e senha separados por v�rgula
        char *tokNome = strtok(linha, ",");
        char *tokSenha = strtok(NULL, "\n");
        if (tokNome && tokSenha && strcmp(tokNome, nome) == 0 && strcmp(tokSenha, senha) == 0) {
            strcpy(nomeLogado, nome);
            fclose(f);
            return 1; // login correto
        }
    }
    fclose(f);
    printf("Nome ou senha incorretos.\n");
    return 0;
}

// Função para exibir cardápio e realizar pedido
void fazerPedido(const char nomeUsuario[]) {
    printf("\n=== FAZER PEDIDO ===\n");
    FILE *f = fopen("cardapio.csv", "r");
    if (!f) {
        printf("Erro ao abrir card�pio.\n");
        return;
    }
    char linha[MAX_LINHA];
    int index = 1;
    printf("C�digo | Produto      | Quantidade dispon�vel\n");
    while (fgets(linha, sizeof(linha), f)) {
        char produto[MAX_PRODUTO];
        int qtd;
        sscanf(linha, " %49[^,],%d", produto, &qtd); // l� "produto" at� v�rgula e quantidade
        printf("%6d | %-12s | %d\n", index, produto, qtd);
        index++;
    }
    fclose(f);

    int opcao, qtdPedido;
    printf("Digite o c�digo do produto desejado (0 para cancelar): ");
    scanf("%d", &opcao);
    if (opcao == 0) {
        return; // cancelado
    }
    printf("Digite a quantidade desejada: ");
    scanf("%d", &qtdPedido);

    // Reabre card�pio para verificar disponibilidade do item escolhido
    f = fopen("cardapio.csv", "r");
    if (!f) {
        printf("Erro ao abrir card�pio.\n");
        return;
    }
    int atual = 1;
    char produtoEscolhido[MAX_PRODUTO];
    int qtdDisponivel;
    bool encontrado = false;
    while (fgets(linha, sizeof(linha), f)) {
        char produto[MAX_PRODUTO];
        int qtd;
        sscanf(linha, " %49[^,],%d", produto, &qtd);
        if (atual == opcao) {
            strcpy(produtoEscolhido, produto);
            qtdDisponivel = qtd;
            encontrado = true;
            break;
        }
        atual++;
    }
    fclose(f);

    if (!encontrado) {
        printf("Produto inv�lido.\n");
        return;
    }
    if (qtdPedido <= 0 || qtdPedido > qtdDisponivel) {
        printf("Quantidade inv�lida.\n");
        return;
    }

    // Grava o pedido em pedidos.csv com status "EM ESPERA"
    FILE *fp = fopen("pedidos.csv", "a");
    if (!fp) {
        printf("Erro ao abrir arquivo de pedidos.\n");
        return;
    }
    fprintf(fp, "%s,%s,%d,EM ESPERA\n", nomeUsuario, produtoEscolhido, qtdPedido);
    fclose(fp);
    printf("Pedido realizado com sucesso!\n");
}

// Função para visualizar pedidos do usuário logado
void verPedidos(const char nomeUsuario[]) {
    printf("\n=== MEUS PEDIDOS ===\n");
    FILE *f = fopen("pedidos.csv", "r");
    if (!f) {
        printf("Erro ao abrir arquivo de pedidos.\n");
        return;
    }
    char linha[MAX_LINHA];
    int count = 0;
    while (fgets(linha, sizeof(linha), f)) {
        char cliente[MAX_NOME], produto[MAX_PRODUTO], status[MAX_STATUS];
        int qtd;
        sscanf(linha, " %[^,],%[^,],%d,%19[^\n]", cliente, produto, &qtd, status);
        if (strcmp(cliente, nomeUsuario) == 0) {
            printf("Produto: %-12s | Quantidade: %2d | Status: %s\n", produto, qtd, status);
            count++;
        }
    }
    if (count == 0) {
        printf("Nenhum pedido encontrado para %s.\n", nomeUsuario);
    }
    fclose(f);
}

// Menu de opções da área do cliente (cadastro, login e após login)
void clienteMenu() {
    int opc;
    char nomeLogado[MAX_NOME];
    do {
        printf("\n--- MENU CLIENTE ---\n");
        printf("1. Cadastro de usu�rio\n");
        printf("2. Login\n");
        printf("0. Voltar\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                if (loginUsuario(nomeLogado)) {
                    // Após login, exibe menu de pedidos
                    int escolha;
                    do {
                        printf("\nUsuário %s logado. Escolha:\n", nomeLogado);
                        printf("1. Fazer pedido\n");
                        printf("2. Ver meus pedidos\n");
                        printf("0. Logout\n");
                        scanf("%d", &escolha);
                        switch (escolha) {
                            case 1:
                                fazerPedido(nomeLogado);
                                break;
                            case 2:
                                verPedidos(nomeLogado);
                                break;
                            case 0:
                                printf("Logout realizado.\n");
                                break;
                            default:
                                printf("Op��o inv�lida.\n");
                        }
                    } while (escolha != 0);
                }
                break;
            case 0:
                // volta ao menu principal
                break;
            default:
                printf("Op��o inv�lida!\n");
        }
    } while (opc != 0);
}