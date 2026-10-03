//Exemplo de código para utilizar contagem de tempo em execução de funções ou trechos de código
//Neste exemplo também teremos leitura de arquivos CSV e manipulação de strings
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string.h>

struct Aluno;


//Necessário: Ordem alfabética na inserção, buscar por CPF, buscar por Matrícula, opção pra remover pós busca. Impedir CPF repetido e mostrar quantos repetidos tem.




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
    Aluno *prox;
    Aluno *ante;
};

struct Alunos{
    Aluno *inicio;
    Aluno *fim;
    int quantidade;
};

Alunos v1[100];
Alunos v2[1000];
Alunos v3[1000000];
int duplicados;
int total;

void inicializa(){
    for ( int i = 0; i < 100 ; i++)
    {
        v1[i].inicio = NULL;
        v1[i].fim = NULL;
        v1[i].quantidade = 0;
    }

    for ( int i = 0; i < 1000 ; i++)
    {
        v2[i].inicio = NULL;
        v2[i].fim = NULL;
        v2[i].quantidade = 0;
    }

    for ( int i = 0; i < 1000000 ; i++)
    {
        v3[i].inicio = NULL;
        v3[i].fim = NULL;
        v3[i].quantidade = 0;
    }

    duplicados = 0;
}

int extrairCPF(const char* cpf){
    int digito1= cpf[12] - '0';
    int digito2= cpf[13] - '0';
    int indice = digito1*10+digito2;
    return indice;
}

Aluno* buscarCPF1(const char* cpf){
    int indice = extrairCPF(cpf);
    Aluno* atual = v1[indice].inicio;
    while (atual != NULL){
       if (strcmp(atual->cpf,cpf) == 0)
       {
        return atual;
       }
       else{
        atual = atual->prox;
        }
    }   
return NULL;
}

Aluno* buscarCPF2(const char* cpf){
    int indice = extrairCPF(cpf);
    Aluno* atual = v2[indice].inicio;
    while (atual != NULL){
       if (strcmp(atual->cpf,cpf) == 0)
       {
        return atual;
       }
       else{
        atual = atual->prox;
        }
    }   
return NULL;
}

Aluno* buscarCPF3(const char* cpf){
    int indice = extrairCPF(cpf);
    Aluno* atual = v3[indice].inicio;
    while (atual != NULL){
       if (strcmp(atual->cpf,cpf) == 0)
       {
        return atual;
       }
       else{
        atual = atual->prox;
        }
    }   
return NULL;
}

Aluno* buscarMatricula1(const char* matricula){
    
    for (int i = 0; i < 100; i++)
    {
        Aluno* atual = v1[i].inicio;
        while (atual != NULL)
        {
            if (strcmp(atual->matricula,matricula) == 0) return atual;
            atual = atual->prox;
        
        }  
    }
     return NULL;
}

Aluno* buscarMatricula2(const char* matricula){
    
    for (int i = 0; i < 100; i++)
    {
        Aluno* atual = v2[i].inicio;
        while (atual != NULL)
        {
            if (strcmp(atual->matricula,matricula) == 0) return atual;
            atual = atual->prox;
            
            }  
    }
     return NULL;
}

Aluno* buscarMatricula3(const char* matricula){
    
    for (int i = 0; i < 100; i++)
    {
        Aluno* atual = v3[i].inicio;
        while (atual != NULL)
        {
            if (strcmp(atual->matricula,matricula) == 0) return atual;
            atual = atual->prox;
            
            }  
    }
     return NULL;
}


void removerAluno1(Aluno*alvo){

    if (alvo == NULL) return;
    int indice = extrairCPF(alvo->cpf);

    if(alvo == v1[indice].inicio && alvo == v1[indice].fim){
        v1[indice].inicio = NULL;
        v1[indice].fim = NULL;
    }
    else if (alvo == v1[indice].inicio)
    {
        v1[indice].inicio = alvo->prox;
        alvo->prox->ante = NULL;
    }
    else if (alvo == v1[indice].fim)
    {
        v1[indice].fim = alvo->ante;
        alvo->ante->prox = NULL;
    }
    else{
        alvo->ante->prox = alvo->prox;
        alvo->prox->ante = alvo->ante;
    }
    delete alvo;
    v1[indice].quantidade--;
    
    
}

void removerAluno2(Aluno*alvo){

    if (alvo == NULL) return;
    int indice = extrairCPF(alvo->cpf);

    if(alvo == v2[indice].inicio && alvo == v2[indice].fim){
        v2[indice].inicio = NULL;
        v2[indice].fim = NULL;
    }
    else if (alvo == v2[indice].inicio)
    {
        v2[indice].inicio = alvo->prox;
        alvo->prox->ante = NULL;
    }
    else if (alvo == v2[indice].fim)
    {
        v2[indice].fim = alvo->ante;
        alvo->ante->prox = NULL;
    }
    else{
        alvo->ante->prox = alvo->prox;
        alvo->prox->ante = alvo->ante;
    }
    delete alvo;
    v2[indice].quantidade--;
    
    
}

void removerAluno3(Aluno*alvo){

    if (alvo == NULL) return;
    int indice = extrairCPF(alvo->cpf);

    if(alvo == v3[indice].inicio && alvo == v3[indice].fim){
        v3[indice].inicio = NULL;
        v3[indice].fim = NULL;
    }
    else if (alvo == v3[indice].inicio)
    {
        v3[indice].inicio = alvo->prox;
        alvo->prox->ante = NULL;
    }
    else if (alvo == v3[indice].fim)
    {
        v3[indice].fim = alvo->ante;
        alvo->ante->prox = NULL;
    }
    else{
        alvo->ante->prox = alvo->prox;
        alvo->prox->ante = alvo->ante;
    }
    delete alvo;
    v3[indice].quantidade--;
    
    
}


// Função para adicionar aluno na lista
void adicionarAluno1(Aluno* novo) {
    int indice = extrairCPF(novo->cpf);

    if (buscarCPF1(novo->cpf) != NULL){
        duplicados++;
        delete novo;
        return;
    }

    if (v1[indice].inicio == NULL) {
        novo->prox = NULL;
        novo->ante = NULL;
        v1[indice].inicio = novo;
        v1[indice].fim = novo;
    }
    else if (strcmp(novo->nome, v1[indice].inicio->nome) < 0){
            novo->prox = v1[indice].inicio;
            novo->ante = NULL;
            v1[indice].inicio->ante = novo;
            v1[indice].inicio = novo;
        }
    else{
        Aluno* atual = v1[indice].inicio->prox;
        while (atual != NULL && strcmp(novo->nome, atual->nome )>= 0)
        {
            atual = atual->prox;
        }
        if (atual == NULL)
        {
            v1[indice].fim->prox = novo;
            novo->ante = v1[indice].fim;
            v1[indice].fim = novo;
        } else{
            novo->prox = atual;
            atual->ante->prox=novo;
            novo->ante = atual->ante;
            atual->ante = novo;
        }
                

        
    }
    
    v1[indice].quantidade++;
    total++;
}

void adicionarAluno2(Aluno* novo) {
    int indice = extrairCPF(novo->cpf);
    int index = indice % 1000;
    if (buscarCPF2(novo->cpf) != NULL){
        duplicados++;
        delete novo;
        return;
    }

    if (v2[index].inicio == NULL) {
        novo->prox = NULL;
        novo->ante = NULL;
        v2[index].inicio = novo;
        v2[index].fim = novo;
    }
    else if (strcmp(novo->nome, v2[index].inicio->nome) < 0){
            novo->prox = v2[index].inicio;
            novo->ante = NULL;
            v2[index].inicio->ante = novo;
            v2[index].inicio = novo;
        }
    else{
        Aluno* atual = v2[index].inicio->prox;
        while (atual != NULL && strcmp(novo->nome, atual->nome )>= 0)
        {
            atual = atual->prox;
        }
        if (atual == NULL)
        {
            v2[index].fim->prox = novo;
            novo->ante = v2[index].fim;
            v2[index].fim = novo;
        } else{
            novo->prox = atual;
            atual->ante->prox=novo;
            novo->ante = atual->ante;
            atual->ante = novo;
        }
                

        
    }
    
    v2[index].quantidade++;
    total++;
}

void adicionarAluno3(Aluno* novo) {
    int indice = extrairCPF(novo->cpf);
    int index = indice % 1000000;
    if (buscarCPF3(novo->cpf) != NULL){
        duplicados++;
        delete novo;
        return;
    }

    if (v3[index].inicio == NULL) {
        novo->prox = NULL;
        novo->ante = NULL;
        v3[index].inicio = novo;
        v3[index].fim = novo;
    }
    else if (strcmp(novo->nome, v3[index].inicio->nome) < 0){
            novo->prox = v3[index].inicio;
            novo->ante = NULL;
            v3[index].inicio->ante = novo;
            v3[index].inicio = novo;
        }
    else{
        Aluno* atual = v3[index].inicio->prox;
        while (atual != NULL && strcmp(novo->nome, atual->nome )>= 0)
        {
            atual = atual->prox;
        }
        if (atual == NULL)
        {
            v3[index].fim->prox = novo;
            novo->ante = v3[index].fim;
            v3[index].fim = novo;
        } else{
            novo->prox = atual;
            atual->ante->prox=novo;
            novo->ante = atual->ante;
            atual->ante = novo;
        }
                

        
    }
    
    v3[index].quantidade++;
    total++;
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
            
            // Inicializar ponteiros da lista
            novo->prox = NULL;
            novo->ante = NULL;

            
            Aluno* novo1 = new Aluno(*novo);
            Aluno* novo2 = new Aluno(*novo);
            Aluno* novo3 = new Aluno(*novo);
            delete novo;

            adicionarAluno1(novo1);
            adicionarAluno2(novo2);
            adicionarAluno3(novo3);
            printf("%s\n", novo1->matricula);
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
    printf("Leitura concluida. Total de alunos: %d\n", total);
}

// Função para exibir todos os alunos
void exibirAlunos1() {
    printf("\n=== LISTA DE ALUNOS ===\n");
    int contador = 1;
    int total = 0;

    for (int i = 0; i < 100; i++)
    {
        Aluno* atual = v1[i].inicio;
        while (atual != NULL)
        {

        printf("Aluno %d:\n", contador);
        printf("  Matricula: %s\n", atual->matricula);
        printf("  CPF: %s\n", atual->cpf);
        printf("  Nome: %s\n", atual->nome);
        printf("  Nota: %.2f\n", atual->nota);
        printf("  Idade: %d\n", atual->idade);
        printf("  Curso: %s\n", atual->curso);
        printf("  Cidade: %s\n", atual->cidade);
        printf("  ---\n");
        
        atual = atual->prox;
        contador++;
        total++;
        }
    }
    printf("Total: %d alunos\n\n", total);
}

void exibirAlunos2() {
    printf("\n=== LISTA DE ALUNOS ===\n");
    int contador = 1;
    int total = 0;

    for (int i = 0; i < 100; i++)
    {
        Aluno* atual = v2[i].inicio;
        while (atual != NULL)
        {

        printf("Aluno %d:\n", contador);
        printf("  Matricula: %s\n", atual->matricula);
        printf("  CPF: %s\n", atual->cpf);
        printf("  Nome: %s\n", atual->nome);
        printf("  Nota: %.2f\n", atual->nota);
        printf("  Idade: %d\n", atual->idade);
        printf("  Curso: %s\n", atual->curso);
        printf("  Cidade: %s\n", atual->cidade);
        printf("  ---\n");
        
        atual = atual->prox;
        contador++;
        total++;
        }
    }
    printf("Total: %d alunos\n\n", total);
}

void exibirAlunos3() {
    printf("\n=== LISTA DE ALUNOS ===\n");
    int contador = 1;
    int total = 0;

    for (int i = 0; i < 100; i++)
    {
        Aluno* atual = v3[i].inicio;
        while (atual != NULL)
        {

        printf("Aluno %d:\n", contador);
        printf("  Matricula: %s\n", atual->matricula);
        printf("  CPF: %s\n", atual->cpf);
        printf("  Nome: %s\n", atual->nome);
        printf("  Nota: %.2f\n", atual->nota);
        printf("  Idade: %d\n", atual->idade);
        printf("  Curso: %s\n", atual->curso);
        printf("  Cidade: %s\n", atual->cidade);
        printf("  ---\n");
        
        atual = atual->prox;
        contador++;
        total++;
        }
    }
    printf("Total: %d alunos\n\n", total);
}

int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");

    clock_t inicioLeitura = clock();
    lerArquivoCSV("alunos_completosV2.csv");
    clock_t fimLeitura = clock();

    double tempoLeitura = (double)(fimLeitura - inicioLeitura) / CLOCKS_PER_SEC * 1000.0;
    printf("Tempo total de leitura + insercao (3 tabelas juntas): %.4f ms\n", tempoLeitura);
    printf("Total de alunos inseridos: %d\n", total);
    printf("CPFs duplicados bloqueados: %d\n\n", duplicados);

    // ===== Comparacao de tempo de BUSCA por CPF nas 3 tabelas =====
    // Troque pelo CPF de um aluno que exista no seu CSV
    const char* cpfTeste = "915.216.859-08";
    const int REPETICOES = 1000; // repete a busca N vezes para dar tempo mensuravel

    clock_t c1i = clock();
    for (int i = 0; i < REPETICOES; i++) buscarCPF1(cpfTeste);
    clock_t c1f = clock();
    printf("Busca CPF x%d (tabela 100):     %.4f ms\n",
           REPETICOES, (double)(c1f - c1i) / CLOCKS_PER_SEC * 1000.0);

    clock_t c2i = clock();
    for (int i = 0; i < REPETICOES; i++) buscarCPF2(cpfTeste);
    clock_t c2f = clock();
    printf("Busca CPF x%d (tabela 1000):    %.4f ms\n",
           REPETICOES, (double)(c2f - c2i) / CLOCKS_PER_SEC * 1000.0);

    clock_t c3i = clock();
    for (int i = 0; i < REPETICOES; i++) buscarCPF3(cpfTeste);
    clock_t c3f = clock();
    printf("Busca CPF x%d (tabela 1000000): %.4f ms\n\n",
           REPETICOES, (double)(c3f - c3i) / CLOCKS_PER_SEC * 1000.0);

    // ===== Comparacao de tempo de BUSCA por Matricula nas 3 tabelas =====
    // Troque pela matricula de um aluno que exista no seu CSV
    const char* matriculaTeste = "A0000000";

    clock_t m1i = clock();
    for (int i = 0; i < REPETICOES; i++) buscarMatricula1(matriculaTeste);
    clock_t m1f = clock();
    printf("Busca Matricula x%d (tabela 100):     %.4f ms\n",
           REPETICOES, (double)(m1f - m1i) / CLOCKS_PER_SEC * 1000.0);

    clock_t m2i = clock();
    for (int i = 0; i < REPETICOES; i++) buscarMatricula2(matriculaTeste);
    clock_t m2f = clock();
    printf("Busca Matricula x%d (tabela 1000):    %.4f ms\n",
           REPETICOES, (double)(m2f - m2i) / CLOCKS_PER_SEC * 1000.0);

    clock_t m3i = clock();
    for (int i = 0; i < REPETICOES; i++) buscarMatricula3(matriculaTeste);
    clock_t m3f = clock();
    printf("Busca Matricula x%d (tabela 1000000): %.4f ms\n\n",
           REPETICOES, (double)(m3f - m3i) / CLOCKS_PER_SEC * 1000.0);

    system("pause");
    return 0;
}