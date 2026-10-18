//Exemplo de código para montar a primeira arvore binária
//Neste exemplo também teremos leitura de arquivos CSV e manipulação de strings
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string.h>
#include <cmath>                 // para pow()

const int TAM = 1 << 20;         // volta para 2^20 (o programa que roda)
const int ALTURA_PONTEIROS = 49; // nivel maximo medido na versao com ponteiros (1.000.000 alunos)
const int TOTAL_ALUNOS = 1000000;
//Exemplo do arquivo CSV que será lido
//Matricula,CPF,Nome,Nota,Idade,Curso,Cidade
//A0000000,915.216.859-08,Wallace Sampaio,20.35,23,Direito,Rio de Janeiro



struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[40];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
};

struct Arvore{
    int quantidadeElementosDeAlunos;
    int nivelMaximo;
    int maiorIndice;

};

Arvore a;
Aluno* vetor[TAM];

void inicializa(){
    int i = 0;
    while (i <TAM)
    {
        vetor[i] = NULL;
        i++;
    }
    
    a.maiorIndice = NULL;
    a.quantidadeElementosDeAlunos = NULL;
    a.nivelMaximo = NULL;
}


// Trocar pra função generica recebendo a lista como
// parametro
bool adicionarAluno(Aluno* novo){
    int i = 0;
    int nivel = 0;

    while (i < TAM && vetor[i] != NULL) {
        if (strcmp(novo->nome, vetor[i]->nome) < 0)
            i = 2*i + 1;      // filho esquerdo de i
        else
            i = 2*i + 2;      // filho direito de i
        nivel++;
    }

    if (i >= TAM) return false;   // não coube: estourou o vetor

    vetor[i] = novo;
    a.quantidadeElementosDeAlunos++;
    if (nivel > a.nivelMaximo) a.nivelMaximo = nivel;
    if (i > a.maiorIndice) a.maiorIndice = i;
    return true;
}

int buscarAlunoPorNome(const char* nome){
    int i = 0;
    while (i < TAM && vetor[i] != NULL) {
        int c = strcmp(nome, vetor[i]->nome);
        if (c == 0) return i;          // achei: devolve a posição
        if (c < 0) i = 2*i + 1;
        else       i = 2*i + 2;
    }

    return -1;   
}

// Função para ler arquivo CSV
void lerArquivoCSV(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }
    char linha[300];
    printf("Iniciando leitura do arquivo CSV...\n");

    // Pular a primeira linha (cabeçalho)
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        printf("Arquivo vazio ou erro na leitura\n");
        fclose(arquivo);
        return;
    }

    Aluno* novo;
    while ((novo = new Aluno) != NULL) {
        if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n",
                   novo->matricula, novo->cpf, novo->nome, &novo->nota,
                   &novo->idade, novo->curso, novo->cidade) == 7) {

            if (!adicionarAluno(novo)) {      // não coube no vetor
                delete novo;
                printf("Vetor estourou! Alunos inseridos: %d\n", a.quantidadeElementosDeAlunos);
                break;
            }
        }
        else {                                // fim do arquivo
            delete novo;
            break;
        }
    }                                         // <<< fecha o while aqui

    fclose(arquivo);
    printf("Leitura concluida. Total de alunos: %d\n", a.quantidadeElementosDeAlunos);
}
// Função para exibir todos os alunos
// Função já transformada em generica
//!!! arrumar essa funcao
void exibirAlunosOrdem(int i, int* contador) {
    if (i >= TAM || vetor[i] == NULL) return;

    exibirAlunosOrdem(2*i + 1, contador);

    printf("Aluno %d:\n", *contador);
    printf("  Matricula: %s\n", vetor[i]->matricula);
    printf("  CPF: %s\n", vetor[i]->cpf);
    printf("  Nome: %s\n", vetor[i]->nome);
    printf("  Nota: %.2f\n",vetor[i]-> nota);
    printf("  Idade: %d\n", vetor[i]->idade);
    printf("  Curso: %s\n", vetor[i]->curso);
    printf("  Cidade: %s\n", vetor[i]->cidade);
    printf("  ---\n");
    

    exibirAlunosOrdem(2*i + 2, contador);

}

void exibirAlunos(){
    printf("\n=== LISTA DE ALUNOS ===\n");
    int contador = 1;
    exibirAlunosOrdem(0, &contador);
    printf("Total: %d alunos\n\n", a.quantidadeElementosDeAlunos);
}



int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");

    clock_t inicioLeitura = clock();
    lerArquivoCSV("alunos_completosV2.csv");
    clock_t fimLeitura = clock();

    // So descomente com CSV pequeno (10-20 linhas)!
    // exibirAlunos();

    const char* nomeBusca = "Alfeu Mitchell Knox";
    clock_t inicioBusca = clock();
    int pos = buscarAlunoPorNome(nomeBusca);
    clock_t fimBusca = clock();

    if (pos == -1) {
        printf("\nAluno nao encontrado.\n");
    } else {
        printf("\nEncontrado na posicao %d: %s (CPF: %s)\n",
               pos, vetor[pos]->nome, vetor[pos]->cpf);
    }

    // ===== Metricas no final =====
    printf("\n=== METRICAS ===\n");
    printf("Tempo de insercao (leitura do CSV): %.4f ms\n",
           (double)(fimLeitura - inicioLeitura) / CLOCKS_PER_SEC * 1000.0);
    printf("Tempo de busca por nome: %.4f ms\n",
           (double)(fimBusca - inicioBusca) / CLOCKS_PER_SEC * 1000.0);
    printf("Alunos inseridos: %d\n", a.quantidadeElementosDeAlunos);
    printf("Altura da arvore (nivel maximo): %d\n", a.nivelMaximo);
    printf("Maior indice usado: %d\n", a.maiorIndice);
    printf("Tamanho do vetor (TAM): %d\n", TAM);
    printf("Memoria do vetor: %.2f MB\n", (double)TAM * sizeof(Aluno*) / (1024.0 * 1024.0));
    printf("Memoria dos alunos: %.2f MB\n",
           (double)a.quantidadeElementosDeAlunos * sizeof(Aluno) / (1024.0 * 1024.0));

        // ===== PARTE 2 e 3: vetor necessario para 1.000.000 de alunos =====
    printf("\n=== VETOR NECESSARIO PARA %d ALUNOS (calculo teorico) ===\n", TOTAL_ALUNOS);

    // altura h => niveis 0..h => ultimo indice possivel = 2^(h+1) - 2
    double posicoes = pow(2.0, ALTURA_PONTEIROS + 1);
    double bytesVetor = posicoes * sizeof(Aluno*);
    double bytesAlunos = (double)TOTAL_ALUNOS * sizeof(Aluno);

    printf("Altura da arvore com ponteiros: %d\n", ALTURA_PONTEIROS);
    printf("Posicoes necessarias (2^%d): %.3e\n", ALTURA_PONTEIROS + 1, posicoes);
    printf("Bytes por ponteiro neste compilador: %d\n", (int)sizeof(Aluno*));
    printf("Memoria do vetor: %.2f GB | %.2f TB | %.2f PB\n",
           bytesVetor / pow(1024.0, 3),
           bytesVetor / pow(1024.0, 4),
           bytesVetor / pow(1024.0, 5));
    printf("Memoria dos alunos: %.2f MB\n", bytesAlunos / (1024.0 * 1024.0));
    printf("Aproveitamento do vetor: %.2e (%.10f%%)\n",
           TOTAL_ALUNOS / posicoes, 100.0 * TOTAL_ALUNOS / posicoes);

    double ramPC = 16.0 * pow(1024.0, 3);   // troque 16 pela RAM do seu PC, em GB
    printf("Vezes maior que 16 GB de RAM: %.0f\n", bytesVetor / ramPC);

    // comparacao com arvore balanceada (2^20 posicoes)
    printf("Vetor balanceado (2^20): %.2f MB\n",
           pow(2.0, 20) * sizeof(Aluno*) / (1024.0 * 1024.0));
    printf("Desperdicio em relacao ao balanceado: %.2e vezes\n", posicoes / pow(2.0, 20));
    system("pause");
    return 0;
}