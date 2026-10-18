#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string.h>

struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[40];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
};

struct NoAluno{
    Aluno *aluno;
    NoAluno *prox;
    NoAluno *ante;
};

struct ListaAlunos{
    NoAluno *inicio;
    NoAluno *fim;
    int quantidade;
};

const int MAX_ALUNOS = 1000000;
Aluno lidos[MAX_ALUNOS];
int nLidos = 0;

ListaAlunos listaPorCpf[100]; 
ListaAlunos listaPorNome[100]; 
ListaAlunos listaPorMatricula[100];

void inicializa(){
    for(int i=0; i < 100; i++){
        listaPorCpf[i].inicio = NULL;
        listaPorCpf[i].fim = NULL;
        listaPorCpf[i].quantidade = 0;
    }
    for(int i=0; i < 100; i++){
        listaPorNome[i].inicio = NULL;
        listaPorNome[i].fim = NULL;
        listaPorNome[i].quantidade = 0;
    }
    for(int i=0; i < 100; i++){
        listaPorMatricula[i].inicio = NULL;
        listaPorMatricula[i].fim = NULL;
        listaPorMatricula[i].quantidade = 0;
    }
}

// PROTEÇÃO ADICIONADA: Garantir que o índice fique sempre entre 0 e 99
int hashCPFDigitoVerificador(char *cpf){
    int dezena = cpf[12] - '0';
    int unidade = cpf[13] - '0';
    int digito = dezena * 10 + unidade;
    if (digito < 0 || digito > 99) return 0; // fallback seguro se o formato variar
    return digito;
}

int hashMatricula(char *matricula){
    int total = 0;
    for (int i = 0; i < 8; i++){
        total += matricula[i];
    }
    return total % 100;
}

int hashNome(char *nome){
    int total = 0;
    for (int i = 0; nome[i] != '\0'; i++)
    {
        total += nome[i];
    }
    return total % 100;
}

int compararCPF(Aluno* novo, Aluno* aluno){
    return strcmp(novo->cpf, aluno->cpf);
}

int compararMatricula(Aluno* novo, Aluno* aluno){
    return strcmp(novo->matricula, aluno->matricula); 
}

int compararNome(Aluno* novo, Aluno* aluno){
    return strcmp(novo->nome, aluno->nome); 
}

void adicionarAluno(int (*hash)(char*), char *chave, Aluno* novo, ListaAlunos lista[], int (*comparar)(Aluno*, Aluno*)) {
    int posicao = hash(chave);
    NoAluno *atual = lista[posicao].inicio;

    while (atual != NULL && comparar(novo, atual->aluno) > 0){
        atual = atual->prox;
    }
    
    NoAluno *noNovo = new NoAluno;
    noNovo->aluno = novo;
    noNovo->prox = NULL;
    noNovo->ante = NULL;

    if (lista[posicao].inicio == NULL) {
        lista[posicao].inicio = noNovo;
        lista[posicao].fim = noNovo;
    } 
    else if (atual == lista[posicao].inicio)
    {
        lista[posicao].inicio->ante = noNovo;
        noNovo->ante = NULL;
        noNovo->prox = lista[posicao].inicio;
        lista[posicao].inicio = noNovo;
    }
    else if (atual == NULL)
    {
        lista[posicao].fim->prox = noNovo;
        noNovo->ante = lista[posicao].fim;
        noNovo->prox = NULL;
        lista[posicao].fim = noNovo;
    }
    else{
        atual->ante->prox = noNovo;
        noNovo->ante = atual->ante;
        atual->ante = noNovo;
        noNovo->prox = atual;
    }
    
    lista[posicao].quantidade++;
}

bool conferirCPF(Aluno* a, ListaAlunos lista[]){
    int digito = hashCPFDigitoVerificador(a->cpf);
    NoAluno *atual = lista[digito].inicio;
    while (atual != NULL)
    {
        int cmp = strcmp(a->cpf, atual->aluno->cpf);
        if (cmp == 0) {
            return true;   
        }
        else if (cmp < 0) {
            return false;  
        }
        else{
            atual = atual->prox;
        }
    }
    return false;
}

Aluno* buscarCPF(char* cpf, ListaAlunos *a){
    int digito = hashCPFDigitoVerificador(cpf);
    NoAluno* atual = a[digito].inicio;
    while (atual != NULL){
       if (strcmp(atual->aluno->cpf, cpf) == 0)
       {
        return atual->aluno;
       }
       else{
        atual = atual->prox;
        }
    }   
    return NULL;
}

Aluno* buscarMatricula(char* matricula, ListaAlunos *a){
    int digito = hashMatricula(matricula);
    NoAluno* atual = a[digito].inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->aluno->matricula, matricula) == 0)
        {
            return atual->aluno;
        }
        else{
            atual = atual->prox;
        }
    }
    return NULL;
}

Aluno* buscarNome(char* nome, ListaAlunos *a){
    int digito = hashNome(nome);
    NoAluno* atual = a[digito].inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->aluno->nome, nome) == 0)
        {
            return atual->aluno;
        }
        else{
            atual = atual->prox;
        }
    }
    return NULL;
}

void lerArquivoCSV(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }
    char linha[300];
    
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        printf("Arquivo vazio ou erro na leitura\n");
        fclose(arquivo);
        return;
    }
    
    nLidos = 0;
    while (nLidos < MAX_ALUNOS) {
        if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n", 
                   lidos[nLidos].matricula, lidos[nLidos].cpf, lidos[nLidos].nome, 
                   &lidos[nLidos].nota, &lidos[nLidos].idade, lidos[nLidos].curso, lidos[nLidos].cidade) == 7) {
            nLidos++;
        } else {
            break;
        }
    }
    fclose(arquivo);
}

int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");

    clock_t inicio, fim;

    inicio = clock();
    lerArquivoCSV("alunos_completosV2.csv");
    fim = clock();
    printf("Tempo de leitura do CSV (Disco -> Memoria): %.3f ms\n", 
           (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC);
    printf("Registros carregados na memoria: %d\n\n", nLidos);
    
    printf("Adicionando Alunos \n");
    inicio = clock();
    int quantidade = 0;
    for (int i = 0; i < nLidos; i++) {
        if (conferirCPF(&lidos[i], listaPorCpf) == false){
            printf("Aluno n - %d \n", quantidade);
            adicionarAluno(hashCPFDigitoVerificador, lidos[i].cpf, &lidos[i], listaPorCpf, compararCPF);
            adicionarAluno(hashMatricula, lidos[i].matricula, &lidos[i], listaPorMatricula, compararMatricula);
            adicionarAluno(hashNome, lidos[i].nome, &lidos[i], listaPorNome, compararNome);
            quantidade++;
        }
    }
    fim = clock();
    printf("Tempo de insercao nas 3 tabelas Hash: %.3f ms\n", 
           (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC);
    printf("Total de alunos unicos inseridos: %d\n\n", quantidade);

    char cpfTeste[] = "957.998.119-17";
    char matriculaTeste[] = "A0000000";
    char nomeTeste[] = "Cleonice Leblon Granito";

    const int REPETICOES = 100000;

    printf("Testando CPF \n");
    inicio = clock();
    for (int i = 0; i < REPETICOES; i++) {
        buscarCPF(cpfTeste, listaPorCpf);
    }
    fim = clock();
    printf("Tempo medio de busca por CPF: %.6f ms\n", 
           ((double)(fim - inicio) * 1000 / CLOCKS_PER_SEC) / REPETICOES);

    printf("Testando Matricula \n");
    inicio = clock();
    for (int i = 0; i < REPETICOES; i++) {
        buscarMatricula(matriculaTeste, listaPorMatricula);
    }
    fim = clock();
    printf("Tempo medio de busca por Matricula: %.6f ms\n", 
           ((double)(fim - inicio) * 1000 / CLOCKS_PER_SEC) / REPETICOES);
    
    printf("Testando Nome \n");
    inicio = clock();
    for (int i = 0; i < REPETICOES; i++) {
        buscarNome(nomeTeste, listaPorNome);
    }
    fim = clock();
    printf("Tempo medio de busca por Nome: %.6f ms\n", 
           ((double)(fim - inicio) * 1000 / CLOCKS_PER_SEC) / REPETICOES);

    system("pause");
    return 0;
}