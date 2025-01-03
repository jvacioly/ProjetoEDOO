//
// Created by victo on 03/01/2025.
//

#include "produto.h"

//Construtor
Produto::Produto(int codigo, const string& nome, double preco, int qtd)
    : codigo(codigo), nome(nome), preco(preco), qtdEstoque(qtd) {}

Produto::Produto(int codigo, const string& nome, double preco)
    : Produto(codigo, nome, preco, 0) {}

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

void Produto::setQtdEstoque(int qtd) {
    if (qtd <= 0) {
        cout << "VALOR INVALIDO" << endl;
        return;
    }
    this->qtdEstoque = qtd;
}

//Outros Metodos
void Produto::reduzirEstoque(int quantidade) {
    int qtdAtual = qtdEstoque;
    if (quantidade >= qtdAtual) {
        cout << "ERRO! Estoque negativo" << endl;
        return;
    }
    qtdAtual -= quantidade;
    qtdEstoque = qtdAtual;
}

void Produto::addEstoque(int quantidade) {
    qtdEstoque += quantidade;
}

void Produto::print() const {
    cout << "Codigo: " << codigo << endl;
    cout << "Produto: " << nome << endl;
    cout << "Quantidade: " << qtdEstoque << endl;
    cout.precision(2);
    cout << "Preco: R$" << fixed << preco << endl;
}


