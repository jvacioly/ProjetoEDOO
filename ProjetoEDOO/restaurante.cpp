//
// Created by victo on 13/01/2025.
//

#include "restaurante.h"
#include <fstream>
#include "prato.h"

//Construtor e Destrutor
Restaurante::Restaurante(const vector<Prato>& menuInicial, float caixa)
    : menu(menuInicial), caixa(caixa) {
    carregarEstoque();
}

Restaurante::Restaurante(const vector<Prato>& menuInicial)
    : Restaurante(menuInicial, 0) {}

Restaurante::~Restaurante() {
    salvarEstoque();
}

//Métodos do Estoque
void Restaurante::carregarEstoque() {
    ifstream estoqueFile("D:/Victor/Faculdade/Projetos/ProjetoEDOO/banco_de_dados/estoque.json"); //COLOCAR O CAMINHO INTEIRO DO ARQUIVO
    estoque = json::object();  // Inicializa como objeto vazio

    if (estoqueFile.is_open()) {
        try {
            estoqueFile >> estoque;
            if (!estoque.is_object()) {
                cout << "Formato inválido no arquivo de estoque. Recriando estoque." << endl;
                estoque = json::object();
            } else {
                if (estoque.contains("estoque") && estoque["estoque"].is_array()) {
                    estoque.erase("estoque");
                }
            }
        } catch (const json::parse_error& e) {
            cout << "Erro ao carregar o estoque: " << e.what() << ". Criando novo estoque." << endl;
            estoque = json::object();
        }
        estoqueFile.close();
    } else {
        cout << "Arquivo estoque.json não encontrado. Criando novo estoque." << endl;
    }
}

void Restaurante::salvarEstoque() const {
    ofstream estoqueFile("D:/Victor/Faculdade/Projetos/ProjetoEDOO/banco_de_dados/estoque.json");  // COLOCAR O CAMINHO INTEIRO DO ARQUIVO
    if (estoqueFile.is_open()) {
        estoqueFile << estoque.dump(4);  // Grava o conteúdo do JSON com formatação
        estoqueFile.close();
        cout << "Estoque salvo com sucesso." << endl;
    } else {
        cout << "Erro ao abrir o arquivo estoque.json para salvar os dados." << endl;
    }
}

void Restaurante::addEstoque(const Produto &produto, int quantidade) {
    const string& nome = produto.getNome();
    int codigo = produto.getCodigo();
    double preco = produto.getPreco();

    if (estoque.contains(nome) && estoque[nome].is_object()) {
        estoque[nome]["quantidade"] = estoque[nome]["quantidade"].get<int>() + quantidade;
    }
    else {
        estoque[nome] = {
            {"codigo", codigo},
            {"ingrediente_nome", nome},
            {"quantidade", quantidade},
            {"preco", preco}
        };
    }

    cout << "Adicionado " << quantidade << " unidades do produto " << nome << " ao estoque." << endl;
    salvarEstoque();
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
/*
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
*/









