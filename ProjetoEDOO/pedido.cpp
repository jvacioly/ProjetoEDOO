//
// Created by victo on 03/01/2025.
//

#include "pedido.h"
#include <chrono>


//Construtor
Pedido::Pedido(const vector<pair<Prato, int>> &itens, const string& observacao)
    : ID(0), itens(itens), observacao(observacao), valorTotal(atualizarValorTotal()){
    auto agora = chrono::system_clock::now();
    time_t horaAtual = chrono::system_clock::to_time_t(agora);

    tm horaLocal = *localtime(&horaAtual);
    ostringstream oss;
    oss << put_time(&horaLocal, "%H:%M:%S");

    horarioPedido = oss.str();

    //Cálculo do valor total

}

Pedido::Pedido(const vector<pair<Prato, int>>& itens)
    : Pedido(itens, "") {}

//Set Methods
void Pedido::setStatus(bool finalizado) {
    if (finalizado) {
        this->finalizado = true;
    }
    else {
        this->finalizado = false;
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
    cout << "Pedido: " << ID << endl;
    cout.precision(2);
    cout << "Valor: R$" << fixed << valorTotal << endl;
    for (const auto& item : itens) {
        cout << item.first.getNome() << ": " << item.second << " - R$" << fixed << item.first.getPreco()  << endl;
    }
    cout << "Total: R$" << fixed << valorTotal << endl;
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




