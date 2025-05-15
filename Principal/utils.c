// utils.c - Implementa��es de fun��es auxiliares
#include "./utils.h"

// Converte cada caractere da string para mai�sculo
void toUpperCase(char *str) 
{
    while (*str) 
    {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

// Verifica se um nome já existe em um arquivo CSV (usuários)
bool nomeExists(const char *filename, const char *nome) 
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        return false;
    }
    char linha[256];
    while (fgets(linha, sizeof(linha), f)) 
    {
        // Extrai a primeira coluna (nome) antes da virgula
        char *token = strtok(linha, ",");
        if (token && strcmp(token, nome) == 0) 
        {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}

