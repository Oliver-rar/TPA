#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

struct Aluno {
    char matricula[9];
    char cpf[15];
    char nome[40];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    Aluno *prox;
    Aluno *ante;
};

struct Alunos {
    Aluno *inicio;
    Aluno *fim;
    int quantidade;
};

Alunos v1[1000];
Alunos v2[10000];
Alunos v3[100000];
int duplicados = 0;
int total = 0;

void inicializa(int tam, Alunos vetor[]) {
    for (int i = 0; i < tam; i++) {
        vetor[i].inicio = NULL;
        vetor[i].fim = NULL;
        vetor[i].quantidade = 0;
    }
}

long long extrairCPF(const char* cpf) {
    long long numero = 0;
    for (int i = 0; cpf[i] != '\0'; i++) {
        if (cpf[i] >= '0' && cpf[i] <= '9') {
            numero = numero * 10 + (cpf[i] - '0');
        }
    }
    return numero;
}

Aluno* buscarCPF(const char* cpf, int tam, Alunos vetor[]) {
    long long numero = extrairCPF(cpf);
    int indice = numero % tam;
    Aluno* atual = vetor[indice].inicio;
    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0) {
            return atual;
        }
        atual = atual->prox;
    } 
    return NULL;
}

Aluno* buscarMatricula(const char* matricula, int tam, Alunos vetor[]) {
    for (int i = 0; i < tam; i++) {
        Aluno* atual = vetor[i].inicio;
        while (atual != NULL) {
            if (strcmp(atual->matricula, matricula) == 0) return atual;
            atual = atual->prox;
        } 
    }
    return NULL;
}

void removerAluno(Aluno* alvo, int tam, Alunos vetor[]) {
    if (alvo == NULL) return;
    long long numero = extrairCPF(alvo->cpf);
    int indice = numero % tam;

    if (alvo == vetor[indice].inicio && alvo == vetor[indice].fim) {
        vetor[indice].inicio = NULL;
        vetor[indice].fim = NULL;
    }
    else if (alvo == vetor[indice].inicio) {
        vetor[indice].inicio = alvo->prox;
        if (alvo->prox != NULL) alvo->prox->ante = NULL;
    }
    else if (alvo == vetor[indice].fim) {
        vetor[indice].fim = alvo->ante;
        if (alvo->ante != NULL) alvo->ante->prox = NULL;
    }
    else {
        alvo->ante->prox = alvo->prox;
        alvo->prox->ante = alvo->ante;
    }
    delete alvo;
    vetor[indice].quantidade--;
}

void adicionarAluno(Aluno* novo, int tam, Alunos vetor[]) {
    long long numero = extrairCPF(novo->cpf);
    int indice = numero % tam;

    if (buscarCPF(novo->cpf, tam, vetor) != NULL) {
        if (tam == 1000) duplicados++; // Conta duplicados apenas na primeira tabela para evitar contagem triplicada
        delete novo;
        return;
    }

    if (vetor[indice].inicio == NULL) {
        novo->prox = NULL;
        novo->ante = NULL;
        vetor[indice].inicio = novo;
        vetor[indice].fim = novo;
    }
    else if (strcmp(novo->nome, vetor[indice].inicio->nome) < 0) {
        novo->prox = vetor[indice].inicio;
        novo->ante = NULL;
        vetor[indice].inicio->ante = novo;
        vetor[indice].inicio = novo;
    }
    else {
        Aluno* atual = vetor[indice].inicio->prox;
        while (atual != NULL && strcmp(novo->nome, atual->nome) >= 0) {
            atual = atual->prox;
        }
        if (atual == NULL) {
            vetor[indice].fim->prox = novo;
            novo->ante = vetor[indice].fim;
            vetor[indice].fim = novo;
        } else {
            novo->prox = atual;
            atual->ante->prox = novo;
            novo->ante = atual->ante;
            atual->ante = novo;
        }
    }
    
    vetor[indice].quantidade++;
    if (tam == 1000) total++; // Conta o total baseado na primeira tabela
}

void lerArquivoCSV(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }
    
    char linha[300];
    printf("Iniciando leitura do arquivo CSV...\n");
    
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        printf("Arquivo vazio ou erro na leitura\n");
        fclose(arquivo);
        return;
    }
    
    while (true) {
        Aluno* novo = new Aluno;
        if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n", 
                   novo->matricula, novo->cpf, novo->nome, &novo->nota,
                   &novo->idade, novo->curso, novo->cidade) == 7) {
            
            novo->prox = NULL;
            novo->ante = NULL;

            Aluno* novo2 = new Aluno(*novo);
            Aluno* novo3 = new Aluno(*novo);

            adicionarAluno(novo, 1000, v1);
            adicionarAluno(novo2, 10000, v2);
            adicionarAluno(novo3, 100000, v3);
        } else {
            delete novo;
            break;
        }
    }
    
    fclose(arquivo);
    printf("Leitura concluida. Total de alunos: %d\n", total);
}

int main() {
    inicializa(1000, v1);
    inicializa(10000, v2);
    inicializa(100000, v3);
    
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");

    clock_t inicioLeitura = clock();
    lerArquivoCSV("alunos_completosV2.csv");
    clock_t fimLeitura = clock();

    double tempoLeitura = (double)(fimLeitura - inicioLeitura) / CLOCKS_PER_SEC * 1000.0;
    printf("Tempo total de leitura + insercao (3 tabelas juntas): %.4f ms\n", tempoLeitura);
    printf("Total de alunos inseridos: %d\n", total);
    printf("CPFs duplicados bloqueados: %d\n\n", duplicados);

    const char* cpfTeste = "915.216.859-08";
    const int REPETICOES = 100000;

    clock_t c1i = clock();
    for (int i = 0; i < REPETICOES; i++) buscarCPF(cpfTeste, 1000, v1);
    clock_t c1f = clock();
    printf("Busca CPF x%d (tabela 1000):     %.4f ms\n", REPETICOES, (double)(c1f - c1i) / CLOCKS_PER_SEC * 1000.0);

    clock_t c2i = clock();
    for (int i = 0; i < REPETICOES; i++) buscarCPF(cpfTeste, 10000, v2);
    clock_t c2f = clock();
    printf("Busca CPF x%d (tabela 10000):    %.4f ms\n", REPETICOES, (double)(c2f - c2i) / CLOCKS_PER_SEC * 1000.0);

    clock_t c3i = clock();
    for (int i = 0; i < REPETICOES; i++) buscarCPF(cpfTeste, 100000, v3);
    clock_t c3f = clock();
    printf("Busca CPF x%d (tabela 100000):   %.4f ms\n\n", REPETICOES, (double)(c3f - c3i) / CLOCKS_PER_SEC * 1000.0);

    const char* matriculaTeste = "A0000000";

    clock_t m1i = clock();
    for (int i = 0; i < REPETICOES; i++) buscarMatricula(matriculaTeste, 1000, v1);
    clock_t m1f = clock();
    printf("Busca Matricula x%d (tabela 1000):   %.4f ms\n", REPETICOES, (double)(m1f - m1i) / CLOCKS_PER_SEC * 1000.0);

    clock_t m2i = clock();
    for (int i = 0; i < REPETICOES; i++) buscarMatricula(matriculaTeste, 10000, v2);
    clock_t m2f = clock();
    printf("Busca Matricula x%d (tabela 10000):  %.4f ms\n", REPETICOES, (double)(m2f - m2i) / CLOCKS_PER_SEC * 1000.0);

    clock_t m3i = clock();
    for (int i = 0; i < REPETICOES; i++) buscarMatricula(matriculaTeste, 100000, v3);
    clock_t m3f = clock();
    printf("Busca Matricula x%d (tabela 100000): %.4f ms\n\n", REPETICOES, (double)(m3f - m3i) / CLOCKS_PER_SEC * 1000.0);

    return 0;
}