# Nome do executável (inclui .exe para Windows)
EXEC = doceria.exe

# Compilador
CC = gcc

# Diretórios (fonte e cabeçalhos)
SRC = Principal
INC = Header

# Arquivos fonte
SRCS = main.c $(SRC)/cliente.c $(SRC)/loja.c $(SRC)/utils.c

# Flags de compilação (-g para debug, -I para incluir diretório de headers)
CFLAGS = -I$(INC) -Wall -g

# Regra principal (constrói o executável)
all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

# Limpa o executável gerado
clean:
	del $(EXEC)
