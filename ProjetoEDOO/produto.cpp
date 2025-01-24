//
// Created by victo on 03/01/2025.
//

#include "produto.h"

//Construtor
Produto::Produto(int codigo, const string& nome, double preco, const string& categoria, const string& medida)
    : codigo(codigo), nome(nome), preco(preco), categoria(categoria), medida(medida) {}

Produto::Produto(int codigo, const string& nome, double preco)
    : Produto(codigo, nome, preco, "", "") {}

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

void Produto::setCategoria(const string &categoria) {
    if (categoria.empty()) {
        cout << "CATEGORIA INVALIDA" << endl;
        return;
    }
    this->categoria = categoria;
}

void Produto::setMedida(const string &medida) {
    if (medida.empty()) {
        cout << "CATEGORIA INVALIDA" << endl;
        return;
    }
    this->medida = medida;
}

//Outros Metodos
void Produto::print() const {
    cout << "Codigo: " << codigo << endl;
    cout << "Produto: " << nome << endl;
    cout.precision(2);
    cout << "Preco: R$" << fixed << preco << endl;
}


