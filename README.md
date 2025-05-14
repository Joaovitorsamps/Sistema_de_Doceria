# 🍰 Sistema de Doceria - CRUD em C com Manipulação de CSV

Este projeto foi desenvolvido como parte da disciplina **Estrutura de Dados I**, com o objetivo de aplicar os conceitos aprendidos através da criação de um sistema completo em linguagem **C**. O projeto simula o gerenciamento de uma doceria, oferecendo funcionalidades para **clientes** e para a **loja**, com persistência de dados em arquivos `.csv`.

## 📋 Descrição Geral

O **Sistema de Doceria** é um programa em C com interface via terminal que permite:

- Login e cadastro de usuários.
- Realização de pedidos de clientes.
- Gerenciamento do cardápio pela loja (adicionar e remover produtos).
- Armazenamento dos dados em arquivos `.csv`.

A estrutura do programa é organizada em múltiplos arquivos `.c` e `.h`, utilizando `locale.h` para configuração regional e promovendo a modularização com funções específicas para cada área do sistema.

---

## 🛠️ Funcionalidades

### 👤 Área do Cliente
- Login com autenticação simples.
- Criação de novo usuário.
- Escolha de itens do cardápio.
- Geração e registro de pedidos no arquivo `pedidos.csv`.

### 🏪 Área da Loja
- Acesso ao menu administrativo.
- Adição de novos produtos ao `cardapio.csv`.
- Remoção de produtos existentes do cardápio.

### 📂 Estrutura de Arquivos CSV
- `usuarios.csv`: Registra usuários e senhas.
- `cardapio.csv`: Armazena os produtos disponíveis e seus preços.
- `pedidos.csv`: Contém o histórico dos pedidos realizados pelos clientes.

---

## 📁 Organização do Projeto

Sistema_de_Doceria/
├── main.c # Menu principal e lógica de execução
├── Principal/
│ ├── cliente.c # Lógica da área do cliente
│ ├── loja.c # Lógica da área da loja
│ ├── utils.c # Funções utilitárias comuns
│ └── *.h # Headers correspondentes
| └── cliente.h
| └── loja.h
| └── utils.h
├── output/
│ └── main.exe # Executável final
| └── pedidos.csv
| └── usuarios.csv
| └── cardapio.csv
└── README.md # Este arquivo


---

## 💻 Compilação

Para compilar o projeto manualmente com `gcc`:

```bash
gcc -Wall -Wextra -g3 main.c Principal/cliente.c Principal/loja.c Principal/utils.c -IHeader -o output/main.exe

🌐 Tecnologias Utilizadas
Linguagem C (C99)

Manipulação de arquivos .csv

Biblioteca: locale.h para suporte à acentuação/idioma

Terminal/Console como interface principal

🎓 Autor
Este projeto foi desenvolvido por (João Vitor Sampaio/Letícia Melo/Luana Kellen), estudantes do curso de Sistemas de Informação, para a matéria de Estrutura de Dados I, com o intuito de consolidar os conhecimentos em:

Estruturas condicionais e de repetição

Funções e modularização

Manipulação de arquivos

Estrutura de dados básica (vetores, structs)