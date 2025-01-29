//
// Created by victo on 03/01/2025.
//

#include "pedido.h"
#include <chrono>
#include <fstream>
#include <random>
#include "json.hpp"
#include "globals.h"

using json = nlohmann::json;

//Construtor
Pedido::Pedido(const vector<pair<Prato, int>> &itens, const string &tipoEndereco, const string &endereco,
    const string &numero, const string &CEP, const string &formaPagamento)
    : itens(itens), tipoEndereco(tipoEndereco), endereco(endereco), numero(numero), CEP(CEP), formaPagamento(formaPagamento), valorTotal(atualizarValorTotal()) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(10000000, 99999999);

    int novoID;
    bool IDUnico = false;

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
        novoID = distrib(gen);
        IDUnico = true;
        for (const auto& pedido : pedidosExistentes) {
            if (pedido.contains("ID") && pedido["ID"] == novoID) {
                IDUnico = false;
                break;
            }
        }
    }while (!IDUnico);

    ID = distrib(gen);

    // Horário do Pedido
    auto agora = chrono::system_clock::now();
    time_t horaAtual = chrono::system_clock::to_time_t(agora);

    tm horaLocal = *localtime(&horaAtual);
    ostringstream oss;
    oss << put_time(&horaLocal, "%H:%M:%S");

    horarioPedido = oss.str();
}
/*Pedido::Pedido(const vector<pair<Prato, int>> &itens, const string& observacao)
    : itens(itens), observacao(observacao), valorTotal(atualizarValorTotal()){
    // Gerar ID do pedido
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(10000000, 99999999);

    int novoID;
    bool IDUnico = false;

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
        novoID = distrib(gen);
        IDUnico = true;
        for (const auto& pedido : pedidosExistentes) {
            if (pedido.contains("ID") && pedido["ID"] == novoID) {
                IDUnico = false;
                break;
            }
        }
    }while (!IDUnico);

    ID = distrib(gen);

    // Horário do Pedido
    auto agora = chrono::system_clock::now();
    time_t horaAtual = chrono::system_clock::to_time_t(agora);

    tm horaLocal = *localtime(&horaAtual);
    ostringstream oss;
    oss << put_time(&horaLocal, "%H:%M:%S");

    horarioPedido = oss.str();
}

Pedido::Pedido(const vector<pair<Prato, int>>& itens)
    : Pedido(itens, "") {}*/

//Set Methods
void Pedido::setStatus(const string& status) {
    this->status = status;
}

void Pedido::setObs(const string &observacao) {
    if (!observacao.empty()) {
        this->observacao = observacao;
    }
}

//Outros Metodos
double Pedido::atualizarValorTotal() {
    for (const auto& item : itens) {
        valorTotal += item.first.getPreco() * item.second;
    }
    return valorTotal;
}

void Pedido::print() const {
    cout << "------------------------------------------" << endl;
    cout << "Pedido: " << ID << endl;
    cout.precision(2);
    cout << "Valor: R$" << fixed << valorTotal << endl;
    for (const auto& item : itens) {
        cout << item.first.getNome() << ": " << item.second << " - R$" << fixed << item.first.getPreco()  << endl;
    }
    cout << "Total: R$" << fixed << valorTotal << endl;
    cout << "------------------------------------------" << endl;
}

void Pedido::addPrato(const Prato& prato, int quantidade) {
    if (quantidade <= 0) {
        cout << "QUANTIDADE INVALIDA!" << endl;
        return;
    }
    for (auto& item : itens) {
        if (item.first.getCodigo() == prato.getCodigo()) {
            item.second += quantidade;
            atualizarValorTotal();
            return;
        }
    }
    itens.emplace_back(prato, quantidade);
    atualizarValorTotal();
}

void Pedido::removePrato(int codigoPrato) {
    for (auto it = itens.begin(); it != itens.end(); ++it) {
        if (it->first.getCodigo() == codigoPrato) {
            itens.erase(it);
            atualizarValorTotal();
            return;
        }
    }
    cout << "PRATO NAO ENCONTRADO NO PEDIDO" << endl;
}

void Pedido::addObservacao(const string &observacao) {
    if (this->observacao.empty()) {
        this->observacao = observacao;
    }
    else {
        this->observacao = this->observacao + " - " + observacao;
    }
}




