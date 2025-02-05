//
// Created by victo on 03/01/2025.
//

#include "prato.h"

//Construtor e Destrutor
Prato::Prato(const string &nome, double preco, const string &categoria, const vector<pair<string, int>> &ingredientes)
    : Produto(nome, preco), ingredientes(ingredientes), categoria(categoria) {}

//Set Methods
void Prato::setIngredientes(const vector<pair<string, int>> &novosIngredientes) {
    ingredientes = novosIngredientes;
}



