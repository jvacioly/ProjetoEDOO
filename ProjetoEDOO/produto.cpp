//
// Created by victo on 03/01/2025.
//

#include "produto.h"

//Construtor
Produto::Produto(int codigo, const string& nome, double preco)
    : codigo(codigo), nome(nome), preco(preco) {}

void Produto::setNome(const string &nome) {
    if (nome.empty()) {
            cout << "NOME INVALIDO!" << endl;
        return;
    }
    this->nome = nome;
}

//Set Methods
void Produto::setPreco(double preco) {
    if (preco <= 0) {
        cout << "VALOR INVALIDO!" << endl;
        return;
    }
    this->preco = preco;
}

//Outros Metodos
void Produto::print() const {
    cout << "Codigo: " << codigo << endl;
    cout << "Produto: " << nome << endl;
    cout.precision(2);
    cout << "Preco: R$" << fixed << preco << endl;
}


