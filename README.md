# Segurança Computacional - Lista de Exercícios 1

Repositório para implementação e análise das cifras clássicas de César e Transposição, desenvolvido para disciplina CIC0201 - Segurança Computacional.

## Funcionalidades Implementadas

### Cifra de César
- Codificação/decodificação com deslocamento fixo
- Ataque por força bruta testando todas as 26 chaves possíveis
- Ataque por análise de distribuição de frequência de letras

### Cifra de Transposição
- Codificação/decodificação colunar com permutação de colunas
- Ataque por força bruta testando permutações de colunas
- Ataque por análise de frequência de digramas e trigramas  |

## Como Compilar e Executar

g++ menu_cifra_cesar.cpp -o run_cesar.out
g++ menu_cifra_transposicao.cpp -o run_transposicao.out

2. Execute os programas:
./run_cesar.out
./run_transposicao.out

## Dependências
- Compilador C++ (g++ recomendado)