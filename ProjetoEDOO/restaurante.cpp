//
// Created by victo on 13/01/2025.
//

#include <fstream>
#include "restaurante.h"
#include "prato.h"
#include "globals.h"

//Construtor e Destrutor
Restaurante::Restaurante(const string &nome, const vector<string> &endereco, const string &contato, const string &descricao,
    const vector<Prato> &menuInicial)
    : nome(nome), endereco(endereco), contato(contato), descricao(descricao), menu(menuInicial) {
    carregarEstoque();
    carregarPedidos();
    carregarFluxo();
}

Restaurante::Restaurante(const string& nome, const vector<Prato>& menuInicial)
    : Restaurante(nome, {"", "", ""}, "", "", menuInicial) {}

Restaurante::Restaurante(const vector<Prato>& menuInicial)
    : Restaurante("", {"", "", ""}, "", "", menuInicial) {}

Restaurante::~Restaurante() {
    salvarEstoque();
    salvarPedidos();
    salvarFluxo();
}

//Métodos do Estoque
void Restaurante::carregarEstoque() {
    string caminho_estoque = BASE_DIR + "estoque.json";
    ifstream estoqueFile(caminho_estoque);
    estoque = json::object();  // Inicializa como objeto vazio

    if (estoqueFile.is_open()) {
        try {
            estoqueFile >> estoque;
            if (!estoque.is_object()) {
                cout << "Formato inválido no arquivo de estoque. Recriando estoque." << endl;
                estoque = json::object();
            }
            else {
                if (estoque.contains("estoque") && estoque["estoque"].is_array()) {
                    estoque.erase("estoque");
                }
            }
        }
        catch (const json::parse_error& e) {
            cout << "Erro ao carregar o estoque: " << e.what() << ". Criando novo estoque." << endl;
            estoque = json::object();
            salvarEstoque(); // Correção do erro de parse
        }
        estoqueFile.close();
    }
    else {
        cout << "Arquivo estoque.json não encontrado. Criando novo estoque." << endl;
    }
}

void Restaurante::salvarEstoque() const {
    string caminho_estoque = BASE_DIR + "estoque.json";
    ofstream estoqueFile(caminho_estoque);
    if (estoqueFile.is_open()) {
        estoqueFile << estoque.dump(4);  // Grava o conteúdo do JSON com formatação
        estoqueFile.close();
        cout << "Estoque salvo com sucesso." << endl;
    }
    else {
        cout << "Erro ao abrir o arquivo estoque.json para salvar os dados." << endl;
    }
}

void Restaurante::addEstoque(const Produto &produto, int quantidade) {
    const string& nome = produto.getNome();
    int codigo = produto.getCodigo();
    double preco = produto.getPreco();
    const string& categoria = produto.getCategoria();
    const string& medida = produto.getMedida();
    double valorTotal = quantidade * preco;

    if (estoque.contains(nome) && estoque[nome].is_object()) {
        estoque[nome]["quantidade"] = estoque[nome]["quantidade"].get<int>() + quantidade;
    }
    else {
        estoque[nome] = {
            {"codigo", codigo},
            {"quantidade", quantidade},
            {"preco", preco},
            {"categoria", categoria},
            {"medida", medida}
        };
    }

    cout << "Adicionado " << quantidade << " unidade(s) do produto " << nome << " ao estoque." << endl;
    salvarEstoque();
    registrarCompra(valorTotal);
}

void Restaurante::editEstoque(int codigoProduto, string nome, string categoria, string medida, double quantidade, bool remover) {
    for (auto& [produto, dados] : estoque.items()) {
        if (dados["codigo"] == codigoProduto) {
            double quantidadeAtual = dados.value("quantidade", 0.0);
            double preco = dados.value("preco", 0.0);

            if (!nome.empty()) {
                dados["nome"] = nome;
            }
            if (!categoria.empty()) {
                dados["categoria"] = categoria;
            }
            if (!medida.empty()) {
                dados["medida"] = medida;
            }

            if (remover == false) {
                dados["quantidade"] = quantidadeAtual + quantidade;
                fluxo["Despesas"] = fluxo["Despesas"].get<double>() + (preco * quantidade);
                fluxo["Lucro"] = fluxo["Receita"].get<double>() - fluxo["Despesas"].get<double>();
                salvarFluxo();
            }
            else {
                dados["quantidade"] = quantidadeAtual - quantidade;
            }

            salvarEstoque();
            break;
        }
    }
}

bool Restaurante::apagarItem(int codigoProduto) {
    for (auto& [produto, dados] : estoque.items()) {
        if (dados["codigo"] == codigoProduto) {
            string nomeProduto = dados["nome"];
            estoque.erase(nomeProduto);
            salvarEstoque();

            return true;
        }
    }
    return false;
}

bool Restaurante::checarEstoque(const Pedido &pedido) {
    unordered_map<string, int> ingredientesTotais;

    for (const auto &itemPedido : pedido.getItens()) {
        Prato prato = itemPedido.first;
        int quantidadePratos = itemPedido.second;

        const vector<pair<string, int>>& ingredientes = prato.getIngredientes();

        for (const auto &ingredienteItem : ingredientes) {
            const string& nomeIngrediente = ingredienteItem.first;
            int quantidadeIngredientesPorPrato = ingredienteItem.second;
            int quantidadeIngredientesTotal = quantidadeIngredientesPorPrato * quantidadePratos;

            ingredientesTotais[nomeIngrediente] += quantidadeIngredientesTotal;
        }
    }

    // Verificar no estoque se os ingredientes necessários estão disponíveis
    for (const auto &ingredienteItem : ingredientesTotais) {
        const string& nomeIngrediente = ingredienteItem.first;
        int quantidadeIngredientesTotal = ingredienteItem.second;

        // Verifica se o ingrediente existe no estoque
        if (!estoque.contains(nomeIngrediente) || !estoque[nomeIngrediente].is_object()) {
            cout << "Ingrediente " << nomeIngrediente << " não encontrado no estoque." << endl;
            return false;
        }

        // Obtém a quantidade disponível no estoque
        int quantidadeDisponivel = estoque[nomeIngrediente]["quantidade"];

        // Verifica se há quantidade suficiente
        if (quantidadeIngredientesTotal > quantidadeDisponivel) {
            cout << "Quantidade insuficiente de " << nomeIngrediente << endl;
            return false;
        }
    }
    return true;
}

void Restaurante::mostrarEstoque() const {
    cout << "Estoque atual:" << endl;
    for (const auto& [nome, info] : estoque.items()) {
        cout << "- " << nome << ": " << info["quantidade"] << " unidades R$" << info["preco"] << " cada" << endl;
    }
}

void Restaurante::carregarPedidos() {
    string caminho_arquivo = BASE_DIR + "pedidos.json";
    ifstream pedidosFile(caminho_arquivo);
    pedidos = json::object();  // Inicializa como objeto vazio

    if (pedidosFile.is_open()) {
        try {
            pedidosFile >> pedidos;
            if (!pedidos.is_object()) {
                cout << "Formato inválido no arquivo de pedidos. Recriando banco de pedidos." << endl;
                pedidos = json::object();
            }
            else {
                if (pedidos.contains("pedidos") && pedidos["pedidos"].is_array()) {
                    pedidos.erase("pedidos");
                }
            }
        }
        catch (const json::parse_error& e) {
            cout << "Erro ao carregar o banco de pedidos: " << e.what() << ". Criando novo banco." << endl;
            pedidos = json::object();
            salvarPedidos(); // Correção do parse error
        }
        pedidosFile.close();
    }
    else {
        cout << "Arquivo pedidos.json não encontrado. Criando novo banco de pedidos." << endl;
    }
}

void Restaurante::salvarPedidos() const {
    string caminho_arquivo = BASE_DIR + "pedidos.json";
    ofstream pedidosFile(caminho_arquivo);
    if (pedidosFile.is_open()) {
        pedidosFile << pedidos.dump(4);  // Grava o conteúdo do JSON com formatação
        pedidosFile.close();
        cout << "Pedidos salvos com sucesso." << endl;
    }
    else {
        cout << "Erro ao abrir o arquivo pedidos.json para salvar os dados." << endl;
    }
}

//Métodos dos Pedidos
void Restaurante::registrarPedido(const Pedido &pedido) {
    if (checarEstoque(pedido)) {
        const int ID = pedido.getID();
        const string& observacao = pedido.getObservacao();
        const string& horarioPedido = pedido.getHorarioPedido();
        const string& tipoEndereco = pedido.getTipoEndereco();
        const string& endereco = pedido.getEndereco();
        const string& numero = pedido.getNumero();
        const string& CEP = pedido.getCEP();
        const string& formaPagamento = pedido.getFormaPagamento();
        double valorTotal = pedido.getValorTotal();
        string status = pedido.getStatus();

        json itensJSON = json::array();
        for (const auto& item : pedido.getItens()) {
            const Prato& prato = item.first;
            int quantidadePrato = item.second;
            itensJSON.push_back({
                {"prato_nome", prato.getNome()},
                {"quantidade", quantidadePrato},
                {"preco_unitario", prato.getPreco()}
            });
            // Removendo os ingredientes do estoque
            for (const auto& ingredienteItem : prato.getIngredientes()) {
                int codigoIngrediente = 0;
                const string ingrediente = ingredienteItem.first;
                int quantidadeNecessaria = ingredienteItem.second * quantidadePrato;

                for (const auto& produto : estoque) {
                    if (produto["nome"] == ingrediente) {
                        codigoIngrediente = produto["codigo"];
                        break;
                    }
                }
                editEstoque(codigoIngrediente, "", "", "", quantidadeNecessaria, true); // Alterar para edit estoque
            }
        }
        const json novoPedido = {
            {"itens_do_pedido", itensJSON},
            {"preco_total", valorTotal},
            {"horario_pedido", horarioPedido},
            {"observacao", observacao},
            {"status", status},
            {"tipo_endereco", tipoEndereco},
            {"endereco", endereco},
            {"numero", numero},
            {"CEP", CEP},
            {"forma_pagamento", formaPagamento}
        };

        pedidos[to_string(ID)] = novoPedido;
        cout << "Adicionado pedido ID" << ID << " ao banco de dados." << endl;
        salvarPedidos();
    }
    else {
        cout << "Pedido não registrado" << endl;
    }
}

void Restaurante::prepararPedido(const string &IDpedido) {
    for (const auto& pedido : pedidos) {
        if (IDpedido == pedido.begin().key()) {
            pedidos[IDpedido]["status"] = "preparando";
            salvarPedidos();
            break;
        }
    }
}

void Restaurante::enviarPedido(const string &IDpedido) {
    for (const auto& pedido : pedidos) {
        if (IDpedido == pedido.begin().key()) {
            pedidos[IDpedido]["status"] = "caminho";
            salvarPedidos();
            break;
        }
    }
}

void Restaurante::cancelarPedido(const string &IDpedido) {
    for (const auto& pedido : pedidos) {
        if (IDpedido == pedido.begin().key()) {
            pedidos[IDpedido]["status"] = "cancelado";
            salvarPedidos();
            break;
        }
    }
}

void Restaurante::finalizarPedido(const string& IDpedido) {
    for (const auto& pedido : pedidos) {
        if (IDpedido == pedido.begin().key()) {
            pedidos[IDpedido]["status"] = "finalizado";
            salvarPedidos();
            registrarVenda(pedido["preco_total"]);
            break;
        }
    }
}

//Métodos do Fluxo
void Restaurante::carregarFluxo() {
    string caminho_arquivo = BASE_DIR + "fluxo.json";
    ifstream fluxoFile(caminho_arquivo);
    fluxo = json::object();  // Inicializa como objeto vazio

    if (fluxoFile.is_open()) {
        try {
            fluxoFile >> fluxo;
            if (!fluxo.is_object()) {
                cout << "Formato inválido no arquivo de fluxo. Recriando banco de fluxo." << endl;
                fluxo = json::object();
            }
            else { // ALTERAR
                if (!fluxo.contains("Despesas")) {
                    fluxo["Despesas"] = 0.0;
                }
                if (!fluxo.contains("Receita")) {
                    fluxo["Receita"] = 0.0;
                }
                if (!fluxo.contains("Lucro")) {
                    fluxo["Lucro"] = 0.0;
                }
                if (!fluxo.contains("Ranking de Pedidos")) {
                    fluxo["Ranking de Pedidos"] = json::object();
                }
            }
        }
        catch (const json::parse_error& e) {
            cout << "Erro ao carregar os dados de fluxo: " << e.what() << ". Criando novo banco." << endl;
            fluxo = json::object();
            fluxo["Despesas"] = 0.0;
            fluxo["Receita"] = 0.0;
            fluxo["Lucro"] = 0.0;
            fluxo["Ranking de Pedidos"] = json::object();
            salvarFluxo(); // Correção do parse error
        }
        fluxoFile.close();
    }
    else {
        cout << "Arquivo fluxo.json não encontrado. Criando novo banco de pedidos." << endl;
        fluxo["Despesas"] = 0.0;
        fluxo["Receita"] = 0.0;
        fluxo["Lucro"] = 0.0;
        fluxo["Ranking de Pedidos"] = json::object();
    }
}

void Restaurante::salvarFluxo() const {
    string caminho_arquivo = BASE_DIR + "fluxo.json";
    ofstream fluxoFile(caminho_arquivo);
    if (fluxoFile.is_open()) {
        fluxoFile << fluxo.dump(4);  // Grava o conteúdo do JSON com formatação
        fluxoFile.close();
        cout << "Dados de fluxo salvos com sucesso." << endl;
    }
    else {
        cout << "Erro ao abrir o arquivo fluxo.json para salvar os dados." << endl;
    }
}

void Restaurante::registrarCompra(double valor) {
    if (fluxo.contains("Despesas") && fluxo["Despesas"].is_number()) {
        double despesasAtual = fluxo["Despesas"].get<double>();

        fluxo["Despesas"] = despesasAtual + valor;
        fluxo["Lucro"] = fluxo["Receita"].get<double>() - fluxo["Despesas"].get<double>();
        cout.precision(2);
        cout << "Compra de R$" << fixed << valor << " registrada." << endl;
        cout << "Valor de despesas atualizado: R$" << fixed << fluxo["Despesas"] << endl;
        salvarFluxo();
    }
    cout << "Erro: o campo 'Despesas' nao esta corretamente inicializado no banco de dados." << endl;
}

void Restaurante::registrarVenda(double valor) {
    if (fluxo.contains("Receita") && fluxo["Receita"].is_number()) {
        double receitaAtual = fluxo["Receita"].get<double>();
        fluxo["Receita"] = valor + receitaAtual;
        fluxo["Lucro"] = fluxo["Receita"].get<double>() - fluxo["Despesas"].get<double>();
        cout.precision(2);
        cout << "Valor de receita atualizado: R$" << fixed << fluxo["Receita"] << endl;
        salvarFluxo();
    }
    else {
        cout << "Erro: o campo 'Receita' nao esta corretamente inicializado no banco de dados." << endl;
    }
}

void Restaurante::adicionarCaixa(double valor) {
    if (!fluxo.contains("Caixa") || !fluxo["Caixa"].is_number()) {
        fluxo["Caixa"] = valor;
    }
    else {
        fluxo["Caixa"] = fluxo["Caixa"].get<double>() + valor;
    }
    salvarFluxo();
}

//Outros Métodos
void Restaurante::mostrarMenu() const {
    cout << "----------------------------" << endl;
    cout << "MENU:" << endl;
    for (const auto& item : menu) {
        cout << item.getNome() << ": " << item.getPreco() << endl;
    }
    cout << "----------------------------" << endl;
}
