// utils.h - Declarações de funções e constantes auxiliares
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Limites de tamanho para strings
#define MAX_NOME 50
#define MAX_SENHA 20
#define MAX_PRODUTO 50
#define MAX_STATUS 20

void toUpperCase(char *str); // converte string para maiúsculas
bool nomeExists(const char *filename, const char *nome); // verifica se nome existe em arquivo

#endif
