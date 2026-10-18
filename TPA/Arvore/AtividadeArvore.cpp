//Exemplo de código para montar a primeira arvore binária
//Neste exemplo também teremos leitura de arquivos CSV e manipulação de strings
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
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

struct NoAluno{
    Aluno *aluno;
    NoAluno *pai;
    NoAluno *dir;
    NoAluno *esq;
    int altura;
    int grau;
    int nivel;
};

struct Arvore{
    NoAluno *raiz;
    int quantidadeElementosDeAlunos;
    int nivelMaximo;

};

Arvore a;

void inicializa(){
    a.raiz = NULL;
    a.quantidadeElementosDeAlunos = 0;
    a.nivelMaximo = 0;
}


// Trocar pra função generica recebendo a lista como
// parametro
void adicionarAluno(Aluno* novo) {
    NoAluno* no = new NoAluno;
    no->aluno = novo;
    no->pai = NULL;
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 0;
    no->grau = 0;
    no->nivel = 0;

    if(a.raiz == NULL){
        a.raiz = no;
        a.quantidadeElementosDeAlunos++;
    }
    else{
        NoAluno* atual = a.raiz;
        NoAluno* pai = NULL;

        while (atual != NULL)
        {
            pai = atual;        
            if (strcmp(novo->nome, atual->aluno->nome) < 0){
                atual=atual->esq;
            }
            else{
                atual=atual->dir;
            }
        }

        if (strcmp(novo->nome, pai->aluno->nome) < 0)
        {
            pai->esq = no;
        }

        else{
            pai->dir = no;
        }

        pai->grau++;
        no->pai = pai;
        no->nivel = pai->nivel+1;

        if (no->nivel > a.nivelMaximo)
        {
            a.nivelMaximo = no->nivel;
        }

        a.quantidadeElementosDeAlunos++;
        
        
        

    }


}

NoAluno* buscarAlunoPorNome(const char* nome){
    NoAluno*atual = a.raiz;
    while (atual != NULL)
    {
            if (strcmp(nome,atual->aluno->nome) == 0)
            {
                return atual;
            }
                   
            if (strcmp(nome, atual->aluno->nome) < 0){
                atual=atual->esq;
            }
            else{
                atual=atual->dir;
            }
    }
    return NULL;    
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
    // Ler cada linha usando fscanf diretamente na struct
    Aluno* novo;
    while ((novo = new Aluno) != NULL) {
        //%N significa que fará a leitura de até N caracteres, evitando overflow
        //O [^caractere] é uma classe de caracteres negativa - significa "qualquer caractere EXCETO o especificado".
        //É muito útil para parar a leitura quando encontrar um delimitador específico (como vírgula ou quebra de linha).
        if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n", 
                   novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7) {
            
            adicionarAluno(novo);
        } else {
            // Se não conseguiu ler todos os campos, liberar memória e sair
            delete novo;
            break;
        }
    }
    
    fclose(arquivo);
    printf("Leitura concluida. Total de alunos: %d\n", a.quantidadeElementosDeAlunos);
}

// Função para exibir todos os alunos
// Função já transformada em generica
//!!! arrumar essa funcao
void exibirAlunosOrdem(NoAluno* no, int* contador) {
    if (no == NULL) {
        return;
    }

    exibirAlunosOrdem(no->esq, contador);

    printf("Aluno %d:\n", *contador);
    printf("  Matricula: %s\n", no->aluno->matricula);
    printf("  CPF: %s\n", no->aluno->cpf);
    printf("  Nome: %s\n", no->aluno->nome);
    printf("  Nota: %.2f\n", no->aluno->nota);
    printf("  Idade: %d\n", no->aluno->idade);
    printf("  Curso: %s\n", no->aluno->curso);
    printf("  Cidade: %s\n", no->aluno->cidade);
    printf("  ---\n");
    (*contador)++;

    exibirAlunosOrdem(no->dir, contador);
}

void exibirAlunos(){
    printf("\n=== LISTA DE ALUNOS ===\n");
    int contador = 1;
    exibirAlunosOrdem(a.raiz, &contador);
    printf("Total: %d alunos\n\n", a.quantidadeElementosDeAlunos);
}



int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");

    clock_t inicioLeitura = clock();
    lerArquivoCSV("alunos_completosV2.csv");
    clock_t fimLeitura = clock();

    // Teste de exibicao em ordem - SO use com CSV pequeno (10-20 linhas)!
    // Com o arquivo grande, comente essa linha.
    exibirAlunos();

    // Teste de busca
    const char* nomeBusca = "Jason Prata Graham"; // troque por um nome real do seu CSV
    clock_t inicioBusca = clock();
    NoAluno* resultado = buscarAlunoPorNome(nomeBusca);
    clock_t fimBusca = clock();

    if (resultado == NULL) {
        printf("\nAluno nao encontrado.\n");
    } else {
        printf("\nEncontrado: %s (CPF: %s)\n", resultado->aluno->nome, resultado->aluno->cpf);
    }

    // ===== Todos os tempos e metricas, juntos, no final =====
    printf("\n=== METRICAS ===\n");
    printf("Tempo de insercao (leitura do CSV): %.4f ms\n",
           (double)(fimLeitura - inicioLeitura) / CLOCKS_PER_SEC * 1000.0);
    printf("Tempo de busca por nome: %.4f ms\n",
           (double)(fimBusca - inicioBusca) / CLOCKS_PER_SEC * 1000.0);
    printf("Altura da arvore (nivel maximo): %d\n", a.nivelMaximo);
    printf("Total de alunos: %d\n", a.quantidadeElementosDeAlunos);

    system("pause");
    return 0;
}