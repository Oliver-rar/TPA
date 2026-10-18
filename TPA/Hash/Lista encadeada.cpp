#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;
//PARA COMPILAR UTILIZE CTRL+SHIFT+B

struct Aluno{
    char nome[40];
    int matricula;
    Aluno *prox;
    Aluno *ante;
};

struct Alunos{
    Aluno *inicio;
    Aluno *fim;
    int quantidade;
};

Alunos a;



void inserir(Alunos &a){
    Aluno *temp = new Aluno;
    int m;     
    char n[40];
    
    cout << "Digite o nome do aluno: " ;
    cin >> n;
    cout << "Digite a matricula do aluno: "<<endl;
    cin >> m;
    strcpy(temp->nome, n);
    temp->matricula = m;
    temp->prox = NULL;
    temp->ante = NULL;
    
    if (a.inicio == NULL){
        a.inicio = temp;
        a.fim = temp;
        a.quantidade++;
        
    }
    else{

        a.fim->prox = temp;
        temp->ante = a.fim;
        a.fim = temp;
        a.quantidade++;
        
    }
    cout << "Matricula feita com sucesso!" <<endl;
}

void listar(Alunos &a){
    Aluno *temp = a.inicio;

    if (a.inicio == NULL){
        printf("Lista vazia");
    }
    else{
        while (temp != NULL)
        {
            cout << "Aluno: " << temp->nome <<endl; 
            cout << "Matricula: " << temp->matricula <<endl << endl;
            temp = temp->prox;
        }

        cout << "Fim da Lista \n";        
    }
}

void listarAoContrario(Alunos &a){
    Aluno *temp = a.fim;

    if (a.inicio == NULL){
        printf("Lista vazia");
    }
    else{
        while (temp != NULL)
        {
            cout << "Aluno: " << temp->nome <<endl; 
            cout << "Matricula: " << temp->matricula <<endl << endl;
            temp = temp->ante;
        }

        cout << "Fim da Lista"<<endl;        
    }
}
int main(){
    int op;

do {
    cout << "1 - Inserir aluno" << endl;
    cout << "2 - Listar alunos" << endl;
    cout << "3 - Listar alunos ao contrario" << endl;
    cout << "0 - Sair" << endl;
    cout << "Escolha: ";
    cin >> op;

    switch (op){
    case 1:
        inserir(a);
        break;
    case 2:
        listar(a);
        break;
    case 3:
        listarAoContrario(a);
        break;
    case 0:
        break;
    default:
        cout << "Opção inválida!" << endl;
}
} while (op!=0);


}