# Comparação de Algoritmos de Ordenação em C

Projeto acadêmico em linguagem C que lê números de um arquivo, permite ordená-los com cinco algoritmos diferentes e grava o resultado em outro arquivo. O programa também permite alterar um valor da lista e executar uma nova ordenação.

## Objetivos do projeto

- Praticar vetores dinâmicos e alocação de memória em C.
- Ler e gravar dados em arquivos de texto.
- Implementar e comparar algoritmos clássicos de ordenação.
- Organizar um programa interativo com funções e validação básica de entradas.

## Funcionalidades

1. Criar `dados.txt` informando quantos números deseja armazenar.
2. Ler os números e escolher um algoritmo de ordenação.
3. Gravar o resultado em `ordenado.txt`.
4. Alterar um número pela posição na lista, atualizar `dados.txt` e ordenar novamente.

Os números são ordenados em ordem crescente. A posição exibida para alteração começa em 1.

## Algoritmos implementados

| Algoritmo | Como funciona | Tempo típico/pior caso | Memória adicional |
|---|---|---:|---:|
| Bubble Sort | Compara elementos vizinhos e troca os que estão fora de ordem. Para quando uma passagem não faz trocas. | O(n²) / O(n²) | O(1) |
| Insertion Sort | Insere cada elemento na posição correta dentro da parte já percorrida. | O(n²) / O(n²) | O(1) |
| Selection Sort | Procura o menor elemento restante e o coloca na próxima posição. | O(n²) / O(n²) | O(1) |
| Merge Sort | Divide a lista, ordena as partes recursivamente e intercala os resultados. | O(n log n) / O(n log n) | O(n) |
| Quick Sort | Particiona a lista em torno de um pivô e ordena as partes recursivamente. | O(n log n) / O(n²) | Recursão; até O(n) no pior caso |

O tempo do Quick Sort depende da escolha do pivô e da distribuição dos valores. Neste programa, o pivô é o elemento do meio da faixa atual.

## Organização dos arquivos

```text
algoritmos-ordenacao-c/
├── src/
│   └── main.c
├── .gitignore
├── Makefile
└── README.md
```

`dados.txt` e `ordenado.txt` são arquivos de execução, criados na pasta de onde o programa é iniciado. Eles são ignorados pelo Git para evitar publicar dados de uso local.

## Compilar

É necessário ter GCC ou Clang instalado.

Com `make`:

```sh
make
```

Ou diretamente com GCC:

```sh
gcc -std=c11 -Wall -Wextra -pedantic src/main.c -o ordenacao
```

No Windows com MinGW GCC:

```powershell
gcc -std=c11 -Wall -Wextra -pedantic src/main.c -o ordenacao.exe
```

## Executar

Linux/macOS:

```sh
./ordenacao
```

Windows:

```powershell
.\ordenacao.exe
```

Escolha a opção 1 para criar o arquivo de entrada. Depois use a opção 2 para ordenar ou a opção 3 para alterar um valor e ordenar novamente.

## Exemplo de uso

1. Execute o programa e escolha `1`.
2. Informe quantos valores deseja gravar e digite os números.
3. Escolha `2` e selecione um algoritmo entre 1 e 5.
4. Confira os valores ordenados no terminal e no arquivo `ordenado.txt`.

## Observações

- Digite números usando ponto como separador decimal, por exemplo `3.14`.
- O arquivo de entrada deve conter números que possam ser lidos como `float`.
- O programa usa `scanf` para ler as opções. Entradas que não correspondam ao tipo esperado podem interromper uma operação.
- Este projeto tem finalidade acadêmica e demonstra implementações didáticas dos algoritmos; não é uma biblioteca de ordenação para uso de produção.
