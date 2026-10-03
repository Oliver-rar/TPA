//Exemplo de código para montar a primeira arvore binária
//Neste exemplo também teremos leitura de arquivos CSV e manipulação de strings
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string.h>

//Exemplo do arquivo CSV que será lido
//Matricula,CPF,Nome,Nota,Idade,Curso,Cidade
//A0000000,915.216.859-08,Wallace Sampaio,20.35,23,Direito,Rio de Janeiro

struct Aluno{
    char matricullistaPorCpf[9];
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
    //faça isso
}


// Trocar pra função generica recebendo a lista como
// parametro
void adicionarAluno(Aluno* novo) {
    //insira o aluno na arvore
}

void buscarAlunoPorNome(){
    //fazer
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
            
            //chamar o adicionarAluno
        } else {
            // Se não conseguiu ler todos os campos, liberar memória e sair
            delete novo;
            break;
        }
    }
    
    fclose(arquivo);
    printf("Leitura concluida. Total de alunos: %d\n", listaPorCpf[0].quantidade);
}

// Função para exibir todos os alunos
// Função já transformada em generica
//!!! arrumar essa funcao
void exibirAlunos(ListaAlunos a) {
    printf("\n=== LISTA DE ALUNOS ===\n");
    NoAluno* atual = a.raiz;
    int contador = 1;
    
    while (atual != NULL) {
        printf("Aluno %d:\n", contador);
        printf("  Matricula: %s\n", atual->aluno->matricula);
        printf("  CPF: %s\n", atual->aluno->cpf);
        printf("  Nome: %s\n", atual->aluno->nome);
        printf("  Nota: %.2f\n", atual->aluno->nota);
        printf("  Idade: %d\n", atual->aluno->idade);
        printf("  Curso: %s\n", atual->aluno->curso);
        printf("  Cidade: %s\n", atual->aluno->cidade);
        printf("  ---\n");
        
        atual = atual->prox;
        contador++;
    }
    printf("Total: %d alunos\n\n", a[0].quantidade);
}

int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");
    
    time_t inicio, fim;
    inicio = clock();
    // Ler arquivo CSV (você pode alterar o nome do arquivo) Essa função já cria a lista dinâmica com os alunos
    lerArquivoCSV("alunos.csv");
    fim = clock();
    //se eu quiser pegar como inteiro o valor do tempo

    printf("Tempo de leitura: %d milissegundos\n", (int)fim - inicio);
    //se eu quiser pegar como double o valor do tempo
    // double tempo2 = difftime(fim, inicio);
    // printf("Tempo de leitura: %.2f segundos\n", tempo2);
    // Exibir todos os alunos carregados
    //exibirAlunos();
    
    system("pause");
    return 0;
}