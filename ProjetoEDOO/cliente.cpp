//
// Created by victo on 20/01/2025.
//

#include "cliente.h"

#include <iostream>
#include <ostream>
#include <algorithm>

// Construtor
Cliente::Cliente(const string &email, const string &password, const string &CPF,
    const vector<vector<string>> &enderecos)
    : email(email), password(password), CPF(CPF), enderecos(enderecos) {}

Cliente::Cliente(const string &email, const string &password)
    : Cliente(email, password, "", {}) {}

// Outros Métodos
void Cliente::addEndereco(const vector<string> &endereco) {
    if (endereco.size() != 3) {
        cout << "ERRO: Endereco incorreto" << endl;
        return;
    }
    enderecos.push_back(endereco);
    cout << "Endereco adicionado com sucesso!";
}

void Cliente::removeEndereco(const vector<string> &endereco) {
    auto it = find(enderecos.begin(), enderecos.end(), endereco);

    if (it != enderecos.end()) {
        enderecos.erase(it);
        cout << "Endereco removido" << endl;
    }
    else {
        cout << "Endereco nao encontrado" << endl;
    }
}

