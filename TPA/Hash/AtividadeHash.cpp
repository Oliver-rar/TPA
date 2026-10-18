//Exemplo de código para utilizar contagem de tempo em execução de funções ou trechos de código
//Neste exemplo também teremos leitura de arquivos CSV e manipulação de strings
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string.h>

struct Aluno;
Aluno* buscarCPF(const char* cpf);
Aluno* bucarMatricula(const char* matricula);
void removerAluno(Aluno* alvo);
int extrairCPF(const char* cpf);

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

Alunos v[100];
int duplicados;
int total;

void inicializa(){
    for ( int i = 0; i < 100 ; i++)
    {
        v[i].inicio = NULL;
        v[i].fim = NULL;
        v[i].quantidade = 0;
    }

    duplicados = 0;
}

Aluno* buscarCPF(const char* cpf){
    int indice = extrairCPF(cpf);
    Aluno* atual = v[indice].inicio;
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

Aluno* buscarMatricula(const char* matricula){
    
    for (int i = 0; i < 100; i++)
    {
        Aluno* atual = v[i].inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->matricula,matricula) == 0) return atual;
        atual = atual->prox;
        
        }  
    }
     return NULL;
}


void removerAluno(Aluno*alvo){

    if (alvo == NULL) return;
    int indice = extrairCPF(alvo->cpf);

    if(alvo == v[indice].inicio && alvo == v[indice].fim){
        v[indice].inicio = NULL;
        v[indice].fim = NULL;
    }
    else if (alvo == v[indice].inicio)
    {
        v[indice].inicio = alvo->prox;
        alvo->prox->ante = NULL;
    }
    else if (alvo == v[indice].fim)
    {
        v[indice].fim = alvo->ante;
        alvo->ante->prox = NULL;
    }
    else{
        alvo->ante->prox = alvo->prox;
        alvo->prox->ante = alvo->ante;
    }
    delete alvo;
    v[indice].quantidade--;
    
    
}


int extrairCPF(const char* cpf){
    int digito1= cpf[12] - '0';
    int digito2= cpf[13] - '0';
    int indice = digito1*10+digito2;
    return indice;
}


// Função para adicionar aluno na lista
void adicionarAluno(Aluno* novo) {
    int indice = extrairCPF(novo->cpf);

    if (buscarCPF(novo->cpf) != NULL){
        duplicados++;
        delete novo;
        return;
    }

    if (v[indice].inicio == NULL) {
        novo->prox = NULL;
        novo->ante = NULL;
        v[indice].inicio = novo;
        v[indice].fim = novo;
    }
    else if (strcmp(novo->nome, v[indice].inicio->nome) < 0){
            novo->prox = v[indice].inicio;
            novo->ante = NULL;
            v[indice].inicio->ante = novo;
            v[indice].inicio = novo;
        }
    else{
        Aluno* atual = v[indice].inicio->prox;
        while (atual != NULL && strcmp(novo->nome, atual->nome )>= 0)
        {
            atual = atual->prox;
        }
        if (atual == NULL)
        {
            v[indice].fim->prox = novo;
            novo->ante = v[indice].fim;
            v[indice].fim = novo;
        } else{
            novo->prox = atual;
            atual->ante->prox=novo;
            novo->ante = atual->ante;
            atual->ante = novo;
        }
                

        
    }
    
    v[indice].quantidade++;
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

            adicionarAluno(novo);
            printf("%s\n", novo->matricula);
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
void exibirAlunos() {
    printf("\n=== LISTA DE ALUNOS ===\n");
    int contador = 1;
    int total = 0;

    for (int i = 0; i < 100; i++)
    {
        Aluno* atual = v[i].inicio;
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
    
    time_t inicio, fim;
    inicio = time(NULL);
    // Ler arquivo CSV (você pode alterar o nome do arquivo) Essa função já cria a lista dinâmica com os alunos
    lerArquivoCSV("alunos_completosV2.csv");
    fim = time(NULL);
    //se eu quiser pegar como inteiro o valor do tempo
    // time_t tempo;
    // tempo = fim - inicio;
    // printf("Tempo de leitura: %d segundos\n", (int)tempo);
    //se eu quiser pegar como double o valor do tempo
    double tempo = difftime(fim, inicio);
    printf("Tempo de leitura: %.2f segundos\n", tempo);
    int op;
    do{
         printf("\n=== MENU ===\n");
        printf("1 - Buscar por CPF\n");
        printf("2 - Buscar por Matricula\n");
        printf("3 - Mostrar quantidade de CPFs duplicados bloqueados\n");
        printf("4 - Exibir todos os alunos\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        switch (op) {
            case 1: {
                char cpfBusca[15];
                printf("Digite o CPF: ");
                scanf(" %14[^\n]", cpfBusca);

                Aluno* encontrado = buscarCPF(cpfBusca);

                if (encontrado == NULL) {
                printf("CPF nao encontrado.\n");
                } else {
                printf("Aluno encontrado: %s (Matricula: %s)\n", encontrado->nome, encontrado->matricula);

                int resposta;
                printf("Remover este aluno? (1-Sim / 0-Nao): ");
                scanf("%d", &resposta);

                if (resposta == 1) {
                    removerAluno(encontrado);
                    printf("Aluno removido.\n");
                        }
                    }
                    break;
                }
            case 2: {
                char matriculaBusca[9];
                printf("Digite a Matricula: ");
                scanf(" %8[^\n]", matriculaBusca);

                Aluno* encontrado = buscarMatricula(matriculaBusca);

                if (encontrado == NULL) {
                    printf("Matricula nao encontrada.\n");
                } else {
                    printf("Aluno encontrado: %s (CPF: %s)\n", encontrado->nome, encontrado->cpf);

                    int resposta;
                    printf("Remover este aluno? (1-Sim / 0-Nao): ");
                    scanf("%d", &resposta);

                    if (resposta == 1) {
                        removerAluno(encontrado);
                        printf("Aluno removido.\n");
                    }
                }
                break;
            }
            case 3: {
                printf("CPFs duplicados bloqueados: %d\n", duplicados);
                break;
            }
            case 4: {
                exibirAlunos();
                break;
            }
            case 0: {
                printf("Encerrando...\n");
                break;
            }
            default: {
                printf("Opcao invalida.\n");
            }
        }
    } while (op!= 0);
    
    // Exibir todos os alunos carregados
    //exibirAlunos();
    
    system("pause");
    return 0;
}

// Tempo total gasto: 32 minutos