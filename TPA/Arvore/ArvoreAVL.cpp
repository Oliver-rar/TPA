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

//deverão ser duas arvores, uma por CPF como ordenação e outra como Nome
Arvore a;
Arvore b;

void inicializa(){
    a.raiz = NULL;
    a.quantidadeElementosDeAlunos = 0;
    a.nivelMaximo = 0;

    b.raiz = NULL;
    b.quantidadeElementosDeAlunos = 0;
    b.nivelMaximo = 0;
}

int altura(NoAluno* no){
    if (no == NULL)
    {
        return 0;
    }

    else{
        return no->altura;
    }
    

}

void atualizaAltura(NoAluno *no){
    if (no != NULL){
        int he = altura(no->esq);
        int hd = altura(no->dir);

        no->altura = 1+(he>hd ? he:hd);
    }
}

int fb(NoAluno *no){
    if (no == NULL)
    {
        return 0;
    }
    
    return altura(no->esq) - altura(no->dir);
}

NoAluno* rotacaoSimplesDireita(NoAluno *x) {
    NoAluno *y = x->esq;
    NoAluno *T2 = y->dir;

    // Executa a rotação
    y->dir  = x;
    x->esq = T2;

    // Atualiza alturas
    atualizaAltura(x);
    atualizaAltura(y);

    // Novo nó raiz
    return y;;
}

NoAluno* rotacaoSimplesEsquerda(NoAluno *x) {
    NoAluno *y = x->dir;
    NoAluno *T2 = y->esq;

    // Executa a rotação
    y->esq  = x;
    x->dir = T2;

    // Atualiza alturas
    atualizaAltura(x);
    atualizaAltura(y);

    // Novo nó raiz
    return y;
}

NoAluno* rotacaoDuplaEsquerda(NoAluno *z) { 
    z->dir = rotacaoSimplesDireita(z->dir);
    return rotacaoSimplesEsquerda(z); 
}

NoAluno* rotacaoDuplaDireita(NoAluno *z){
    z->esq = rotacaoSimplesEsquerda(z->esq);
    return rotacaoSimplesDireita(z); 
}



// A função de adicionar aluno na arvore já faz o balancemanento e retorna o novo nó se mudou o mo mesmo nó se nao teve mudança
//Faça uma função de adicinar para cada arvore,
//OU utilize função como passagem por parametro para as comparações de ordenação
NoAluno* adicionarAlunoNome(NoAluno *no, Aluno *novoAluno){
//NoAluno* adicionarAlunoCPF(NoAluno *no, Aluno *novoAluno){    
    if(no == NULL){
        NoAluno* novoNo = new NoAluno;
        novoNo->aluno = novoAluno;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
        novoNo->pai = NULL;
        novoNo->altura = 1;

    return novoNo;
}
    
        

    if(strcmp(no->aluno->nome, novoAluno->nome) < 0){
        no->dir = adicionarAlunoNome(no->dir, novoAluno);
    }
    else{
        no->esq = adicionarAlunoNome(no->esq, novoAluno);
    }

    atualizaAltura(no);

    int balanceamento = fb(no);


    //Como aplicar as rotações?
    //Aplica rotações conforme o caso
    if(balanceamento > 1 && fb(no->esq) >= 0) {
        return rotacaoSimplesDireita(no);
    }
    if(balanceamento < -1 && fb(no->dir) <= 0) {
        return rotacaoSimplesEsquerda(no);            // RR
    }
    if(balanceamento > 1 && fb(no->esq) < 0) {
        return rotacaoDuplaDireita(no);
    }
    if(balanceamento < -1 && fb(no->dir) > 0) {
        return rotacaoDuplaEsquerda(no);
    }

    //Retorna nó (já possivelmente rotacionado)
    return no;
}

NoAluno* adicionarAlunoCPF(NoAluno *no, Aluno *novoAluno){    
        if(no == NULL){
            NoAluno* novoNo = new NoAluno;
            novoNo->aluno = novoAluno;
            novoNo->esq = NULL;
            novoNo->dir = NULL;
            novoNo->pai = NULL;
            novoNo->altura = 1;

            return novoNo;
        }

    
        

    if(strcmp(no->aluno->cpf, novoAluno->cpf) < 0){
        no->dir = adicionarAlunoCPF(no->dir, novoAluno);
    }
    else{
        no->esq = adicionarAlunoCPF(no->esq, novoAluno);
    }

    atualizaAltura(no);

    int balanceamento = fb(no);


    //Como aplicar as rotações?
    //Aplica rotações conforme o caso
    if(balanceamento > 1 && fb(no->esq) >= 0) {
        return rotacaoSimplesDireita(no);
    }
    if(balanceamento < -1 && fb(no->dir) <= 0) {
        return rotacaoSimplesEsquerda(no);            // RR
    }
    if(balanceamento > 1 && fb(no->esq) < 0) {
        return rotacaoDuplaDireita(no);
    }
    if(balanceamento < -1 && fb(no->dir) > 0) {
        return rotacaoDuplaEsquerda(no);
    }

    //Retorna nó (já possivelmente rotacionado)
    return no;
}


NoAluno* buscarAlunoPorNome(NoAluno* raiz, const char* nome){
    if (raiz == NULL) {
        return NULL;
    }
    int cmp = strcmp(nome, raiz->aluno->nome);
    if (cmp == 0) {
        return raiz;
    } else if (cmp < 0) {
        return buscarAlunoPorNome(raiz->esq, nome);
    } else {
        return buscarAlunoPorNome(raiz->dir, nome);
    }
}

NoAluno* buscarAlunoPorCPF(NoAluno* raiz, const char* cpf){
    if (raiz == NULL) {
        return NULL;
    }
    int cmp = strcmp(cpf, raiz->aluno->cpf);
    if (cmp == 0) {
        return raiz;
    } else if (cmp < 0) {
        return buscarAlunoPorCPF(raiz->esq, cpf);
    } else {
        return buscarAlunoPorCPF(raiz->dir, cpf);
    }
}

NoAluno* minimoNo(NoAluno* no) {
    NoAluno* atual = no;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

NoAluno* apagarNoArvoreNome(NoAluno* raiz, const char* nome) {
    if (raiz == NULL) return NULL;

    int cmp = strcmp(nome, raiz->aluno->nome);
    if (cmp < 0) {
        raiz->esq = apagarNoArvoreNome(raiz->esq, nome);
    } else if (cmp > 0) {
        raiz->dir = apagarNoArvoreNome(raiz->dir, nome);
    } else {
        // Nó com apenas um filho ou nenhum filho
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            NoAluno *temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL) { // Sem filhos
                temp = raiz;
                raiz = NULL;
                delete temp; // Remove apenas o nó da árvore (o Aluno é mantido para a outra árvore)
            } else { // Um filho
                *raiz = *temp; 
                delete temp;
            }
        } else {
            // Nó com dois filhos: obtém o sucessor em ordem (menor da direita)
            NoAluno* temp = minimoNo(raiz->dir);
            raiz->aluno = temp->aluno;
            raiz->dir = apagarNoArvoreNome(raiz->dir, temp->aluno->nome);
        }
    }

    if (raiz == NULL) return NULL;

    atualizaAltura(raiz);
    int balanceamento = fb(raiz);

    // Rotações de reequilíbrio pós-remoção
    if (balanceamento > 1 && fb(raiz->esq) >= 0)
        return rotacaoSimplesDireita(raiz);
    if (balanceamento > 1 && fb(raiz->esq) < 0)
        return rotacaoDuplaDireita(raiz);
    if (balanceamento < -1 && fb(raiz->dir) <= 0)
        return rotacaoSimplesEsquerda(raiz);
    if (balanceamento < -1 && fb(raiz->dir) > 0)
        return rotacaoDuplaEsquerda(raiz);

    return raiz;
}

NoAluno* apagarNoArvoreCPF(NoAluno* raiz, const char* cpf) {
    if (raiz == NULL) return NULL;

    int cmp = strcmp(cpf, b.raiz->aluno->cpf);
    if (cmp < 0) {
        raiz->esq = apagarNoArvoreCPF(raiz->esq, cpf);
    } else if (cmp > 0) {
        raiz->dir = apagarNoArvoreCPF(raiz->dir, cpf);
    } else {
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            NoAluno *temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
                delete temp;
            } else {
                *raiz = *temp;
                delete temp;
            }
        } else {
            NoAluno* temp = minimoNo(raiz->dir);
            raiz->aluno = temp->aluno;
            raiz->dir = apagarNoArvoreCPF(raiz->dir, temp->aluno->cpf);
        }
    }

    if (raiz == NULL) return NULL;

    atualizaAltura(raiz);
    int balanceamento = fb(raiz);

    if (balanceamento > 1 && fb(raiz->esq) >= 0)
        return rotacaoSimplesDireita(raiz);
    if (balanceamento > 1 && fb(raiz->esq) < 0)
        return rotacaoDuplaDireita(raiz);
    if (balanceamento < -1 && fb(raiz->dir) <= 0)
        return rotacaoSimplesEsquerda(raiz);
    if (balanceamento < -1 && fb(raiz->dir) > 0)
        return rotacaoDuplaEsquerda(raiz);

    return raiz;
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
            
            a.raiz = adicionarAlunoNome(a.raiz, novo);
            b.raiz = adicionarAlunoCPF(b.raiz, novo);
            
            // Incrementa o contador para não ficar zerado nas métricas
            a.quantidadeElementosDeAlunos++;
            b.quantidadeElementosDeAlunos++;
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
int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV (AVL) ===\n\n");

    clock_t inicioLeitura = clock();
    lerArquivoCSV("alunos_completosV2.csv");
    clock_t fimLeitura = clock();
    printf("Leitura concluida!");

    // Teste de busca
    const char* nomeBusca = "Jason Prata Graham"; 
    clock_t inicioBusca = clock();
    NoAluno* resultado = buscarAlunoPorNome(a.raiz, nomeBusca);
    clock_t fimBusca = clock();

    if (resultado == NULL) {
        printf("\nAluno nao encontrado.\n");
    } else {
        printf("\nEncontrado: %s (CPF: %s)\n", resultado->aluno->nome, resultado->aluno->cpf);
    }

    // ===== Métricas e Relatório Final =====
    printf("\n=== METRICAS ===\n");
    printf("Tempo de insercao (leitura do ficheiro): %.4f ms\n",
           (double)(fimLeitura - inicioLeitura) / CLOCKS_PER_SEC * 1000.0);
    printf("Tempo de busca por nome: %.4f ms\n",
           (double)(fimBusca - inicioBusca) / CLOCKS_PER_SEC * 1000.0);
    printf("Altura da arvore A (Nome): %d\n", altura(a.raiz));
    printf("Altura da arvore B (CPF): %d\n", altura(b.raiz));
    printf("Total de alunos: %d\n", a.quantidadeElementosDeAlunos);

    printf("\n=== CONCLUSAO DA COMPARACAO ===\n");
    printf("Comparando com a altura 49 de uma ABB desbalanceada da atividade anterior,\n");
    printf("a arvore AVL mantem uma altura logistica extremamente baixa e otimizada,\n");
    printf("garantindo buscas com complexidade O(log n) garantida.\n");

    system("pause");
    return 0;
}