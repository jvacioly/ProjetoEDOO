//
// Created by victo on 03/01/2025.
//

#include "pedido.h"


//Construtor
Pedido::Pedido(int id)
    : ID(id), valorTotal(0) {}

//Outros Metodos
void Pedido::atualizarValorTotal() {
    for (const auto& item : itens) {
        valorTotal += item.first.getPreco() * item.second;
    }
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




