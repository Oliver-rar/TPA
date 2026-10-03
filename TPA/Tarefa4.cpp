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


int hashCPFDigitoVerificador(char *cpf){
    int digito;
    int dezena = cpf[12] - '0';
    int unidade = cpf[13] - '0';
    digito = dezena * 10 + unidade;
    return digito;
//  000.000.000-56
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
    int a = strcmp(novo->cpf, aluno->cpf);
    return a;
}

int compararMatricula(Aluno* novo, Aluno* aluno){
    int a = strcmp(novo->matricula, aluno->matricula);
    return a; 
}

int compararNome(Aluno* novo, Aluno* aluno){
    int a = strcmp(novo->nome, aluno->nome);
    return a; 
}


// Trocar pra função generica recebendo a lista como
// parametro
void adicionarAluno(int (*hash)(char*), char *chave, Aluno* novo, ListaAlunos lista[], int (*comparar)(Aluno*, Aluno*)) {
    int posicao = hash(chave);
    NoAluno *atual = lista[posicao].inicio;

    while (atual != NULL && comparar(novo, atual->aluno) < 0){
        atual=atual->prox;
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
        noNovo->ante= atual->ante;
        atual->ante = noNovo;
        noNovo->prox=atual;
    }
    

    lista[posicao].quantidade++;
}

bool conferirCPF(Aluno*a, ListaAlunos lista[]){
    int digito = hashCPFDigitoVerificador(a->cpf);
    NoAluno *atual = lista[digito].inicio;
    while (atual != NULL)
    {
        int cmp = strcmp(a->cpf, atual->aluno->cpf);
        if (cmp == 0) {
            return true;   // achou igual -> é duplicado
        }
        else if (cmp < 0) {
            return false;  // já passou do ponto -> não existe
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
       if (strcmp(atual->aluno->cpf,cpf) == 0)
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
    Aluno *novo;
    int quantidade = 0;
    // Ler cada linha usando fscanf diretamente na struct
    while (( novo = new Aluno) != NULL) {
        //%N significa que fará a leitura de até N caracteres, evitando overflow
        //O [^caractere] é uma classe de caracteres negativa - significa "qualquer caractere EXCETO o especificado".
        //É muito útil para parar a leitura quando encontrar um delimitador específico (como vírgula ou quebra de linha).
        if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n", 
                   novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7) {
            
            // Inicializar ponteiros da lista
            //pega o endereço que deve ser inserido no vetor de alunos
            //TEMOS QUE ADICIONAR O ALUNO EM TRES LISTAS AGORA
            if ( conferirCPF(novo,listaPorCpf) == false){
                adicionarAluno(hashCPFDigitoVerificador, novo->cpf, novo, listaPorCpf,compararCPF);
                adicionarAluno(hashMatricula, novo->matricula, novo, listaPorMatricula, compararMatricula);
                adicionarAluno(hashNome, novo->nome, novo, listaPorNome, compararNome);
                quantidade++;
            }
            else{
                delete novo;
            } //(lembre-se de trocar por funções genéricas)
            //printf("Aluno adicionado: %s - %s\n", novo->matricula, novo->nome);
            // Consumir a quebra de linha restante
            //fgetc(arquivo);
        } else {
            // Se não conseguiu ler todos os campos, liberar memória e sair
            delete novo;
            break;
        }
    }
    
    fclose(arquivo);
    printf("Leitura concluida. Total de alunos: %d\n", quantidade);
}

// Função para exibir todos os alunos
// Função já transformada em generica
void exibirAlunos(ListaAlunos a[]) {
    printf("\n=== LISTA DE ALUNOS ===\n");
    int contador = 1;
    
    for (int i = 0; i < 100; i++)
    {
        NoAluno* atual = a[i].inicio;
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
    }
    
    
    printf("Total: %d alunos\n\n", contador-1);
}

int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");

    clock_t inicio, fim;

    // ---- Tempo de leitura do CSV + insercao nas 3 listas de hash ----
    inicio = clock();
    lerArquivoCSV("alunos_completosV2.csv");
    fim = clock();
    printf("Tempo de leitura/insercao: %.3f ms\n\n", 
           (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC);

    // Descomente se quiser ver os alunos carregados em cada lista
    // exibirAlunos(listaPorCpf);
    // exibirAlunos(listaPorMatricula);
    // exibirAlunos(listaPorNome);

    // ---- Tempo de busca em cada uma das 3 listas ----
    // Troque pelos dados de um aluno que exista de verdade no seu CSV
    char cpfTeste[] = "957.998.119-17";
    char matriculaTeste[] = "A0000000";
    char nomeTeste[] = "Cleonice Leblon Granito";

    const int REPETICOES = 100000;

    inicio = clock();
    for (int i = 0; i < REPETICOES; i++) {
        buscarCPF(cpfTeste, listaPorCpf);
    }
    fim = clock();
    printf("Tempo medio de busca por CPF: %.6f ms\n", 
           ((double)(fim - inicio) * 1000 / CLOCKS_PER_SEC) / REPETICOES);

    inicio = clock();
    for (int i = 0; i < REPETICOES; i++) {
        buscarMatricula(matriculaTeste, listaPorMatricula);
    }
    fim = clock();
    printf("Tempo medio de busca por Matricula: %.6f ms\n", 
           ((double)(fim - inicio) * 1000 / CLOCKS_PER_SEC) / REPETICOES);

    inicio = clock();
    for (int i = 0; i < REPETICOES; i++) {
        buscarNome(nomeTeste, listaPorNome);
    }
    fim = clock();
    printf("Tempo medio de busca por Nome: %.6f ms\n", 
           ((double)(fim - inicio) * 1000 / CLOCKS_PER_SEC) / REPETICOES);

    // Comentario final pedido no enunciado: comparar tempo com atividades anteriores
    // (preencher depois de rodar e comparar com a versao de lista unica)

    system("pause");
    return 0;
}

//Tempo de leitura - 12 minutos e 36 segundos
//Busca por CPF - 0.00000173 segundos
//Busca por Matrícula - 0.00000002
//Busca por Nome - 0.00033035