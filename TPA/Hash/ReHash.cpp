//Exemplo de código para utilizar contagem de tempo em execução de funções ou trechos de código
//Neste exemplo também teremos leitura de arquivos CSV e manipulação de strings
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string.h>

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

#define CARGA_MAXIMA 0.6
#define TAMANHO_HASH_INICIAL 1021
struct Alunos{
    Aluno **hash;
    bool *hashOcupada;
    int tamanhoAtual;
    int quantidade;
};

Alunos a;
void expandirHash();
void adicionarAluno(Aluno* novo);

void inicializa(){
    a.tamanhoAtual = TAMANHO_HASH_INICIAL;
    a.quantidade = 0;
    a.hash = new Aluno*[a.tamanhoAtual];
    a.hashOcupada = new bool[a.tamanhoAtual];
    for(int i=0; i<a.tamanhoAtual; i++){
        a.hashOcupada[i] = false;
        a.hash[i] = NULL;
    }
}

bool primo(int n){
    if (n < 2) return false;
    else{
        for (int i = 2; i*i <= n; i++)
        {
            if (n % i == 0) return false;
        }
    }
    return true;
}

int proxPrimo(int n){
    int i = n+1;
    while (primo(i) != true)
    {
        i++;
    }
    return i;
}

int calculoHash(char* nome, int tam){
    int i = 0;
    long long soma = 0;
    while (nome[i] != '\0')
    {
        soma += (long long)nome[i];
        i++;
    }
    long long hashValor = soma * soma;
    return hashValor % tam;
    
}

void expandirHash(){
    Aluno **hashAntigo = a.hash;
    bool *ocupadoAntigo = a.hashOcupada;
    int tamAntigo = a.tamanhoAtual;
    

    int tamNovo = proxPrimo(tamAntigo*2);

    a.tamanhoAtual = tamNovo;
    a.quantidade = 0;
    a.hash = new Aluno*[tamNovo];
    a.hashOcupada = new bool[tamNovo];

    for(int i=0; i<tamNovo; i++){
        a.hashOcupada[i] = false;
        a.hash[i] = NULL;
    }
    

    for (int i = 0; i < tamAntigo; i++)
    {
        if (ocupadoAntigo[i] == true)
        {
            adicionarAluno(hashAntigo[i]);
        }
        
    }
    
    delete[] hashAntigo;
    delete[] ocupadoAntigo;
}


void adicionarAluno(Aluno*novo){
    double cargaAtual = (double)(a.quantidade+1) / a.tamanhoAtual;
    if (cargaAtual > CARGA_MAXIMA) {
        expandirHash();
    }

    int indice = calculoHash(novo->nome, a.tamanhoAtual);

    while (a.hashOcupada[indice] == true)
    {
        indice++;
        if (indice >= a.tamanhoAtual)
        {
            indice = 0;
        }
    }
    
    a.hash[indice] = novo;
    a.hashOcupada[indice] = true;
    a.quantidade++;  
}

Aluno* buscarPorNome(char* nome, int tam){
    int indice = calculoHash(nome, tam);

    while ( a.hashOcupada[indice] == true )
    {
        if ( strcmp(a.hash[indice]->nome, nome) == 0 ){
            return a.hash[indice];
        }
        indice++;
        if (indice > tam-1)
        {
            indice = 0;
        }
        
    }
    return NULL;
}

// Função para ler arquivo CSV
// Função para ler arquivo CSV
// Função para ler arquivo CSV usando leitura segura por linha
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
    
    int linhasLidas = 0;
    // Lê o ficheiro linha por linha de forma segura
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Aluno* novo = new Aluno;
        
        // Remove quebras de linha no final da string caso existam (\r ou \n)
        linha[strcspn(linha, "\r\n")] = '\0';
        
        // Faz o parsing dos dados diretamente da string da linha
        int res = sscanf(linha, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]", 
                         novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade);
        
        if (res >= 6) { // Aceita se conseguir ler os campos principais
            adicionarAluno(novo);
            linhasLidas++;
        } else {
            delete novo; // Liberta a memória se a linha for inválida/vazia
        }
    }
    
    fclose(arquivo);
    printf("Leitura concluida. Total de linhas lidas com sucesso: %d\n", linhasLidas);
    printf("Total final de alunos unicos na hash: %d\n", a.quantidade);
    printf("Tamanho final da tabela hash: %d\n", a.tamanhoAtual);
}

// Função para exibir todos os alunos
void exibirAlunos(int tam) {
    int contador = 1;
    printf("\n=== LISTA DE ALUNOS ===\n");
    for (int i = 0; i < tam; i++)
    {
        if (a.hashOcupada[i] == true)
        {
            printf("Aluno %d:\n", contador);
            printf("  Matricula: %s\n", a.hash[i]->matricula);
            printf("  CPF: %s\n", a.hash[i]->cpf);
            printf("  Nome: %s\n", a.hash[i]->nome);
            printf("  Nota: %.2f\n", a.hash[i]->nota);
            printf("  Idade: %d\n", a.hash[i]->idade);
            printf("  Curso: %s\n", a.hash[i]->curso);
            printf("  Cidade: %s\n", a.hash[i]->cidade);
            printf("  ---\n");
            contador++;
        }
        
    }
    
    printf("Total: %d alunos\n\n", a.quantidade);
}
int main(){
    inicializa();
    printf("=== SISTEMA DE HASH DINAMICA DE ALUNOS ===\n\n");

    clock_t inicio, fim;
    inicio = clock();
    
    // Ler arquivo CSV e inserir na hash dinâmica com expansão automática
    lerArquivoCSV("alunos_completosV2.csv"); // Certifique-se que o nome do ficheiro está correto
    
    fim = clock();

    printf("Tempo de processamento (Leitura + Insercao): %d milissegundos\n\n", (int)(fim - inicio));

    // Exemplo de busca repetida para tirar a média
    char nomeBusca[40] = "Bernardina Preto Padilla"; // Certifique-se que este nome existe no ficheiro
    const int REPETICOES = 100000;

    inicio = clock();
    for (int i = 0; i < REPETICOES; i++) {
        buscarPorNome(nomeBusca, a.tamanhoAtual);
    }
    fim = clock();

    double tempoTotalMs = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;
    double tempoMedioMs = tempoTotalMs / REPETICOES;

    printf("Busca por Nome ('%s') realizada %d vezes.\n", nomeBusca, REPETICOES);
    printf("Tempo total das buscas: %.3f ms\n", tempoTotalMs);
    printf("Tempo medio de busca por Nome: %.6f ms\n\n", tempoMedioMs);

    // Exemplo de teste de busca com resultado e exibição de dados
    Aluno* encontrado = buscarPorNome(nomeBusca, a.tamanhoAtual);
    if (encontrado != NULL) {
        printf("[Busca] Aluno encontrado: %s | Curso: %s | Nota: %.2f\n", encontrado->nome, encontrado->curso, encontrado->nota);
    } else {
        printf("[Busca] Aluno nao encontrado.\n");
    }

    system("pause");
    return 0;
}