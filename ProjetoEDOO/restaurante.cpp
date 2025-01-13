//
// Created by victo on 13/01/2025.
//

#include "restaurante.h"
#include <fstream>
#include "prato.h"

//Construtor e Destrutor
Restaurante::Restaurante(const unordered_map<string, float>& menuInicial, float caixa)
    : menu(menuInicial), caixa(caixa) {
    carregarDados();
}

Restaurante::Restaurante(const unordered_map<string, float> &menuInicial)
    : Restaurante(menuInicial, 0) {}

Restaurante::~Restaurante() {
    salvarDados();
}

// Métodos para carregar dados do JSON
void Restaurante::salvarDados() const {
    ofstream estoqueFile("estoque.json");
    estoqueFile << estoque.dump(4);
    estoqueFile.close();

    ofstream pedidosFile("pedidos.json");
    pedidosFile << pedidos.dump(4);
    pedidosFile.close();

    cout << "Dados salvos nos arquivos JSON." << endl;
}

void Restaurante::carregarDados() {
    ifstream estoqueFile("estoque.json");
    if (estoqueFile.is_open()) {
        estoqueFile >> estoque;
        estoqueFile.close();
    }

    ifstream pedidosFile("pedidos.json");
    if (pedidosFile.is_open()) {
        pedidosFile >> pedidos;
        pedidosFile.close();
    }

    cout << "Dados carregados nos arquivos JSON." << endl;
}

//Métodos do Estoque
void Restaurante::addEstoque(const Produto &produto, int quantidade) {
    string nome = produto.getNome();
    if (estoque.contains(nome)) {
        estoque[nome] += quantidade;
    }
    else {
        estoque[nome] = quantidade;
    }
    cout << "Adicionado " << quantidade << " unidades do produto " << nome << " ao estoque." << endl;
}

bool Restaurante::removerEstoque(const string &nomeProduto, int quantidade) {
    if (estoque.contains(nomeProduto) && estoque[nomeProduto]["quantidade"].get<int>() >= quantidade) {
        estoque[nomeProduto]["quantidade"] = estoque[nomeProduto]["quantidade"].get<int>() - quantidade;
        if (estoque[nomeProduto]["quantidade"] == 0) {
            estoque.erase(nomeProduto);
        }
        cout << "Produto " << nomeProduto << " retirado do estoque." << endl;
        return true;
    }
    cout << "ERRO: Produto não encontrado ou quantidade insuficiente no estoque." << endl;
    return false;
}

void Restaurante::mostrarEstoque() const {
    cout << "Estoque atual:" << endl;
    for (const auto& [nome, info] : estoque.items()) {
        cout << "- " << nome << ": " << info["quantidade"] << " unidades R$" << info["preco"] << " cada" << endl;
    }
}

//Métodos dos Pedidos (EM DESENVOLVIMENTO)
bool Restaurante::registrarPedido(const Pedido &pedido) {
    float totalPedido = 0;

    //Verificar se todos os pratos estão no menu
    for (const auto& [prato, quantidade] : pedido.getItens()) {
        if (menu.find(prato.getNome()) == menu.end()) {
            cout << "ERRO: o prato '" << prato.getNome() << "' não está no menu do restaurante." << endl;
            return false;
        }
    }

    //Verificar estoque e calcular total
    for (const auto& [prato, quantidade] : pedido.getItens()) {
        if (!estoque.contains(prato.getNome()) || estoque[prato.getNome()].get<int>() < quantidade) {
            cout << "ERRO: Estoque insuficiente para o prato '" << prato.getNome() << "'." << endl;
            return false;
        }
        totalPedido += menu[prato.getNome()] * quantidade;
    }

    //Atualizar estoque e registrar pedido
    for (const auto& [prato, quantidade] : pedido.getItens()) {
        estoque[prato.getNome()] = estoque[prato.getNome()].get<int>() - quantidade;
    }

    //Atualizar valor total do pedido e registrar no histórico
    json novoPedido = {
        {"id", pedido.getID()},
        { "itens", json::array()},
        {"valor_total", totalPedido}
    };

    for (const auto& [prato, quantidade] : pedido.getItens()) {
        novoPedido["itens"].push_back({
            {"prato", prato.getNome()},
            {"quantidade", quantidade}
        });
    }
    pedidos.push_back(novoPedido);
    caixa += totalPedido;

    cout << "Pedido registrado com sucesso! Total R$" << totalPedido << endl;
    return true;
}










