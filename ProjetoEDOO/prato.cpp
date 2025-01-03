//
// Created by victo on 03/01/2025.
//

#include "prato.h"

//Construtor e Destrutor
Prato::Prato(int codigo, const string &nome, double preco, const string &categoria,
    const vector<string> &ingredientes)
        : Produto(codigo, nome, preco), ingredientes(ingredientes), categoria(categoria) {}

Prato::~Prato() {
    cout << "Prato " << getNome() << " removido do cardapio" << endl;
}

//Set Methods
void Prato::setIngredientes(const vector<string> &novosIngredientes) {
    ingredientes = novosIngredientes;
}

void Prato::setCategoria(const string &novaCategoria) {
    if (novaCategoria.empty()) {
        cout << "CATEGORIA INVALIDA" << endl;
        return;
    }
    categoria = novaCategoria;
}

//Outros Metodos
void Prato::print() const {
    cout << "Codigo: " << getCodigo() << endl;
    cout << "Produto: " << getNome() << endl;
    cout << "Categoria: " << getCategoria() << endl;
    cout.precision(2);
    cout << "Preco: R$" << fixed << getPreco() << endl;
    cout << "Ingredientes: ";
    for (const auto& ingrediente : ingredientes) {
        cout << ingrediente << ", ";
    }
    cout << endl;
}


