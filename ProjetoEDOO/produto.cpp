//
// Created by victo on 03/01/2025.
//

#include "produto.h"
#include <random>
#include <fstream>
#include "globals.h"
#include "json.hpp"

using json = nlohmann::json;

//Construtor
Produto::Produto(const string& nome, double preco, const string& categoria, const string& medida)
    : nome(nome), preco(preco), categoria(categoria), medida(medida) {
    // Gerar codigo único do pedido
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1000, 9999);

    int novoCodigo;
    bool codigoUnico = false;

    json pedidosExistentes;
    string caminhoArquivo = BASE_DIR + "estoque.json";
    ifstream pedidosFile(caminhoArquivo);
    if (pedidosFile.is_open()) {
        pedidosFile >> pedidosExistentes;
        pedidosFile.close();
    }
    else {
        pedidosExistentes = json::array();
    }
    do {
        novoCodigo = distrib(gen);
        codigoUnico = true;
        for (const auto& pedido : pedidosExistentes) {
            if (pedido.contains("ID") && pedido["ID"] == novoCodigo) {
                codigoUnico = false;
                break;
            }
        }
    }while (!codigoUnico);

    codigo = distrib(gen);
}

Produto::Produto(const string& nome, double preco)
    : Produto(nome, preco, "", "") {}

//Set Methods
void Produto::setNome(const string &nome) {
    if (nome.empty()) {
            cout << "NOME INVALIDO!" << endl;
        return;
    }
    this->nome = nome;
}

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


