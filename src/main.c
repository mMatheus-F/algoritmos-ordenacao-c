#include <stdio.h>

#include <stdlib.h>

#define ARQUIVO_ENTRADA "dados.txt"

#define ARQUIVO_SAIDA "ordenado.txt"

typedef struct {

float *valores;

size_t quantidade;

} Lista;

/* Troca dois valores usando os enderecos recebidos. */

void trocar(float *a, float *b) {

float temporario = *a;

*a = *b;

*b = temporario;

}

void bubbleSort(float v[], size_t n) {

size_t i, j;

for (i = 0; i + 1 < n; i++) {

int trocou = 0;

for (j = 0; j + 1 < n - i; j++) {

if (v[j] > v[j + 1]) {

trocar(&v[j], &v[j + 1]);

trocou = 1;

}

}

if (!trocou) break;

}

}

void insertionSort(float v[], size_t n) {

size_t i;

for (i = 1; i < n; i++) {

float chave = v[i];

size_t j = i;

while (j > 0 && v[j - 1] > chave) {

v[j] = v[j - 1];

j--;

}

v[j] = chave;

}

}

void selectionSort(float v[], size_t n) {

size_t i, j;

for (i = 0; i + 1 < n; i++) {

size_t menor = i;

for (j = i + 1; j < n; j++) {

if (v[j] < v[menor]) menor = j;

}

if (menor != i) trocar(&v[i], &v[menor]);

}

}

void intercala(float v[], float auxiliar[], size_t inicio,

size_t meio, size_t fim) {

size_t i = inicio, j = meio, k = inicio;

while (i < meio && j < fim) {

if (v[i] <= v[j]) auxiliar[k++] = v[i++];

else auxiliar[k++] = v[j++];

}

while (i < meio) auxiliar[k++] = v[i++];

while (j < fim) auxiliar[k++] = v[j++];

for (i = inicio; i < fim; i++) v[i] = auxiliar[i];

}

void mergeSortRecursivo(float v[], float auxiliar[],

size_t inicio, size_t fim) {

if (fim - inicio < 2) return;

size_t meio = inicio + (fim - inicio) / 2;

mergeSortRecursivo(v, auxiliar, inicio, meio);

mergeSortRecursivo(v, auxiliar, meio, fim);

intercala(v, auxiliar, inicio, meio, fim);

}

int mergeSort(float v[], size_t n) {

float *auxiliar;

if (n < 2) return 1;

auxiliar = malloc(n * sizeof(float));

if (auxiliar == NULL) {

printf("Memoria insuficiente para o Merge Sort.\n");

return 0;

}

mergeSortRecursivo(v, auxiliar, 0, n);

free(auxiliar);

return 1;

}

void quickSortRecursivo(float v[], long inicio, long fim) {

long i = inicio, j = fim;

float pivo = v[inicio + (fim - inicio) / 2];

while (i <= j) {

while (v[i] < pivo) i++;

while (v[j] > pivo) j--;

if (i <= j) {

trocar(&v[i], &v[j]);

i++;

j--;

}

}

if (inicio < j) quickSortRecursivo(v, inicio, j);

if (i < fim) quickSortRecursivo(v, i, fim);

}

void quickSort(float v[], size_t n) {

if (n > 1) quickSortRecursivo(v, 0, (long)n - 1);

}

/* Le os numeros do arquivo e aumenta o vetor conforme necessario. */

int lerArquivo(const char *nome, Lista *lista) {

FILE *arquivo = fopen(nome, "r");

size_t capacidade = 0;

float numero;

lista->valores = NULL;

lista->quantidade = 0;

if (arquivo == NULL) return 0;

while (fscanf(arquivo, "%f", &numero) == 1) {

if (lista->quantidade == capacidade) {

size_t novaCapacidade = capacidade == 0 ? 8 : capacidade * 2;

float *novo = realloc(lista->valores,

novaCapacidade * sizeof(float));

if (novo == NULL) {

free(lista->valores);

lista->valores = NULL;

lista->quantidade = 0;

fclose(arquivo);

return -1;

}

lista->valores = novo;

capacidade = novaCapacidade;

}

lista->valores[lista->quantidade++] = numero;

}

fclose(arquivo);

return lista->quantidade > 0 ? 1 : 0;

}

int salvarArquivo(const char *nome, const Lista *lista) {

FILE *arquivo = fopen(nome, "w");

size_t i;

if (arquivo == NULL) return 0;

for (i = 0; i < lista->quantidade; i++) {

if (fprintf(arquivo, "%.9g\n", lista->valores[i]) < 0) {

fclose(arquivo);

return 0;

}

}

return fclose(arquivo) == 0;

}

void mostrarLista(const Lista *lista) {

size_t i;

if (lista->quantidade == 0) {

printf("Nao ha valores carregados.\n");

return;

}

for (i = 0; i < lista->quantidade; i++)

printf("%.9g%s", lista->valores[i],

i + 1 == lista->quantidade ? "\n" : "  ");

}

int criarArquivoDados(void) {

FILE *arquivo;

size_t quantidade, i;

float valor;

printf("Quantos numeros deseja gravar? ");

if (scanf("%zu", &quantidade) != 1 || quantidade == 0) {

printf("Informe uma quantidade inteira maior que zero.\n");

return 0;

}

arquivo = fopen(ARQUIVO_ENTRADA, "w");

if (arquivo == NULL) {

printf("Erro ao criar %s.\n", ARQUIVO_ENTRADA);

return 0;

}

for (i = 0; i < quantidade; i++) {

printf("Numero %zu: ", i + 1);

if (scanf("%f", &valor) != 1) {

printf("Entrada invalida. O arquivo pode estar incompleto.\n");

fclose(arquivo);

return 0;

}

if (fprintf(arquivo, "%.9g\n", valor) < 0) {

printf("Erro ao gravar os dados.\n");

fclose(arquivo);

return 0;

}

}

if (fclose(arquivo) != 0) {

printf("Erro ao finalizar a gravacao.\n");

return 0;

}

printf("Valores gravados em %s.\n", ARQUIVO_ENTRADA);

return 1;

}

int escolherOrdenacao(void) {

int opcao;

printf("\nEscolha o algoritmo:\n");

printf("1 - Bubble Sort\n");

printf("2 - Insertion Sort\n");

printf("3 - Selection Sort\n");

printf("4 - Merge Sort\n");

printf("5 - Quick Sort\n");

printf("Opcao: ");

if (scanf("%d", &opcao) != 1) return 0;

return opcao;

}

void ordenarEGravar(void) {

Lista lista;

int leitura = lerArquivo(ARQUIVO_ENTRADA, &lista);

int algoritmo;

if (leitura == 0) {

printf("Nao foi possivel ler valores. Crie primeiro o arquivo %s.\n",

ARQUIVO_ENTRADA);

return;

}

if (leitura < 0) {

printf("Memoria insuficiente para ler os valores.\n");

return;

}

printf("Valores lidos de %s: ", ARQUIVO_ENTRADA);

mostrarLista(&lista);

algoritmo = escolherOrdenacao();

switch (algoritmo) {

case 1: bubbleSort(lista.valores, lista.quantidade); break;

case 2: insertionSort(lista.valores, lista.quantidade); break;

case 3: selectionSort(lista.valores, lista.quantidade); break;

case 4:

if (!mergeSort(lista.valores, lista.quantidade)) {

free(lista.valores);

return;

}

break;

case 5: quickSort(lista.valores, lista.quantidade); break;

default:

printf("Opcao de ordenacao invalida.\n");

free(lista.valores);

return;

}

printf("Resultado em ordem crescente: ");

mostrarLista(&lista);

if (salvarArquivo(ARQUIVO_SAIDA, &lista))

printf("Resultado salvo em %s.\n", ARQUIVO_SAIDA);

else

printf("Erro ao salvar %s.\n", ARQUIVO_SAIDA);

free(lista.valores);

}

void alterarValorEReordenar(void) {

Lista lista;

int leitura = lerArquivo(ARQUIVO_ENTRADA, &lista);

size_t posicao;

float novoValor;

if (leitura == 0) {

printf("Crie primeiro o arquivo %s.\n", ARQUIVO_ENTRADA);

return;

}

if (leitura < 0) {

printf("Memoria insuficiente para ler os valores.\n");

return;

}

printf("Valores atuais (posicoes comecam em 1):\n");

for (size_t i = 0; i < lista.quantidade; i++)

printf("%zu: %.9g\n", i + 1, lista.valores[i]);

printf("Qual posicao deseja alterar? ");

if (scanf("%zu", &posicao) != 1 || posicao < 1 ||

posicao > lista.quantidade) {

printf("Posicao invalida.\n");

free(lista.valores);

return;

}

printf("Novo valor: ");

if (scanf("%f", &novoValor) != 1) {

printf("Valor invalido.\n");

free(lista.valores);

return;

}

lista.valores[posicao - 1] = novoValor;

if (!salvarArquivo(ARQUIVO_ENTRADA, &lista)) {

printf("Erro ao atualizar %s.\n", ARQUIVO_ENTRADA);

free(lista.valores);

return;

}

printf("%s atualizado. Escolha como ordenar novamente.\n",

ARQUIVO_ENTRADA);

free(lista.valores);

ordenarEGravar();

}

int main(void) {

int opcao;

do {

printf("\n=== ORDENACAO E ARQUIVOS ===\n");

printf("1 - Criar/gravar os valores desordenados em dados.txt\n");

printf("2 - Ler e ordenar os valores de dados.txt\n");

printf("3 - Alterar um valor em dados.txt e reordenar\n");

printf("0 - Sair\n");

printf("Opcao: ");

if (scanf("%d", &opcao) != 1) {

printf("Entrada invalida. Encerrando.\n");

break;

}

switch (opcao) {

case 1: criarArquivoDados(); break;

case 2: ordenarEGravar(); break;

case 3: alterarValorEReordenar(); break;

case 0: printf("Programa encerrado.\n"); break;

default: printf("Opcao invalida. Tente novamente.\n"); break;

}

} while (opcao != 0);

return 0;

}
