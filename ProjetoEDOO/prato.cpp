//
// Created by victo on 03/01/2025.
//

#include "prato.h"

//Construtor e Destrutor
Prato::Prato(const string &nome, double preco, const string &categoria, const vector<pair<Produto, int>> &ingredientes)
    : Produto(nome, preco), ingredientes(ingredientes), categoria(categoria) {}

Prato::~Prato() {
    //cout << "Prato " << getNome() << " removido do cardapio" << endl;
}

//Set Methods
void Prato::setIngredientes(const vector<pair<Produto, int>> &novosIngredientes) {
    ingredientes = novosIngredientes;
}

//Outros Metodos
void Prato::print() const {
    cout << "Codigo: " << getCodigo() << endl;
    cout << "Produto: " << getNome() << endl;
    cout << "Categoria: " << getCategoria() << endl;
    cout.precision(2);
    cout << "Preco: R$" << fixed << getPreco() << endl;
    cout << "Ingredientes: ";
    for (size_t i = 0; i < ingredientes.size(); ++i) {
        cout << ingredientes[i].first.getNome() << ": " << ingredientes[i].second;
        if (i != ingredientes.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}


