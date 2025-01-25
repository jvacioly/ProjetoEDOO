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
    caixa = 0;
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
    bool compraPossivel = registrarCompra(valorTotal);
    if (compraPossivel) {
        salvarEstoque();
    }
}

bool Restaurante::removerEstoque(const Produto& produto, int quantidade) {
    const string& nome = produto.getNome();

    if (estoque.contains(nome) && estoque[nome]["quantidade"].get<int>() >= quantidade) {
        estoque[nome]["quantidade"] = estoque[nome]["quantidade"].get<int>() - quantidade;
        /*if (estoque[nome]["quantidade"] == 0) {
            estoque.erase(nome);
        }*/
        cout << "Removido " << quantidade << " unidade(s) do produto " << nome << " retirado do estoque." << endl;
        salvarEstoque();
        return true;
    }
    cout << "ERRO: Produto não encontrado ou quantidade insuficiente no estoque." << endl;
    return false;
}

bool Restaurante::apagarItem(const Produto &produto) {
    const string& nome = produto.getNome();

    if (estoque.contains(nome)) {
        estoque.erase(nome);
        cout << "Produto " << nome << " apagado do estoque." << endl;
        salvarEstoque();
        return true;
    }
    cout << "ERRO: Produto não encontrado no estoque." << endl;
    return false;
}

bool Restaurante::checarEstoque(const Pedido &pedido) {
    vector<pair<Produto, int>> ingredientesTotais;

    for (const auto &itemPedido : pedido.getItens()) {
        const Prato& prato = itemPedido.first;
        int quantidadePratos = itemPedido.second;

        for (const auto &ingredienteItem : prato.getIngredientes()) {
            const Produto& ingrediente = ingredienteItem.first;
            int quantidadeIngredientesPorPrato = ingredienteItem.second;
            int quantidadeIngredientesTotal = quantidadeIngredientesPorPrato * quantidadePratos;

            bool encontrado = false;
            for (auto &itemTotal : ingredientesTotais) {
                if (itemTotal.first.getNome() == ingrediente.getNome()) {
                    itemTotal.second += quantidadeIngredientesTotal;
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                ingredientesTotais.emplace_back(ingrediente, quantidadeIngredientesTotal);
            }
        }
    }

    // Verificar no estoque a lista ingredientesTotais
    for (const auto &ingredienteItem : ingredientesTotais) {
        const Produto& ingrediente = ingredienteItem.first;
        int quantidadeIngredientesTotal = ingredienteItem.second;
        if (!estoque.contains(ingrediente.getNome()) || !estoque[ingrediente.getNome()].is_object()) {
            cout << "Ingrediente " << ingrediente.getNome() << " nao encontrado no estoque." << endl;
            return false;
        }
        int quantidadeDisponivel = estoque[ingrediente.getNome()]["quantidade"];
        if (quantidadeIngredientesTotal > quantidadeDisponivel) {
            cout << "Quantidade insuficiente de " << ingrediente.getNome() << endl;
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
                const Produto& ingrediente = ingredienteItem.first;
                int quantidadeNecessaria = ingredienteItem.second * quantidadePrato;
                removerEstoque(ingrediente, quantidadeNecessaria);
            }
        }
        const json novoPedido = {
            {"itens_do_pedido", itensJSON},
            {"preco total", valorTotal},
            {"horario_pedido", horarioPedido},
            {"observacao", observacao},
            {"status", status}
        };

        pedidos[to_string(ID)] = novoPedido;
        cout << "Adicionado pedido ID" << ID << " ao banco de dados." << endl;
        salvarPedidos();
    }
    else {
        cout << "Pedido não registrado" << endl;
    }
}

void registrarPedido(double pedido);

void Restaurante::finalizarPedido(Pedido &pedido) {
    pedido.setStatus(true);

    const string id = to_string(pedido.getID());
    if (pedidos.contains(id)) {
        pedidos[id]["status"] = "Finalizado";
        salvarPedidos();
        cout << "Pedido ID: " << id << " finalizado com sucesso!" << endl;
        registrarVenda(pedido.getValorTotal());
    }
    else {
        cout << "Pedido ID:" << id << " não encontrado." << endl;
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
                if (!fluxo.contains("Caixa")) {
                    fluxo["Caixa"] = 0.0;
                }
                if (!fluxo.contains("Ranking de Pedidos")) {
                    fluxo["Ranking de Pedidos"] = json::object();
                }
            }
        }
        catch (const json::parse_error& e) {
            cout << "Erro ao carregar os dados de fluxo: " << e.what() << ". Criando novo banco." << endl;
            fluxo = json::object();
            fluxo["Caixa"] = 0.0;
            fluxo["Ranking de Pedidos"] = json::object();
            salvarFluxo(); // Correção do parse error
        }
        fluxoFile.close();
    }
    else {
        cout << "Arquivo fluxo.json não encontrado. Criando novo banco de pedidos." << endl;
        fluxo["Caixa"] = 0.0;
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

bool Restaurante::registrarCompra(double valor) {
    if (fluxo.contains("Caixa") && fluxo["Caixa"].is_number()) {
        double caixaAtual = fluxo["Caixa"].get<double>();
        if (caixaAtual >= valor) {
            fluxo["Caixa"] = caixaAtual - valor;
            cout.precision(2);
            cout << "Compra de R$" << fixed << valor << " registrada." << endl;
            cout << "Caixa atualizado: R$" << fixed << fluxo["Caixa"] << endl;
            salvarFluxo();
            return true;
        }
        cout << "Erro: Saldo insuficiente para a compra." << endl;
        return false;
    }
    cout << "Erro: o campo 'Caixa' nao esta corretamente inicializado no banco de dados." << endl;
    return false;
}

void Restaurante::registrarVenda(double valor) {
    if (fluxo.contains("Caixa") && fluxo["Caixa"].is_number()) {
        double caixaAtual = fluxo["Caixa"].get<double>();
        fluxo["Caixa"] = valor + caixaAtual;
        cout.precision(2);
        cout << "Valor de R$" << fixed << valor << " registrado no caixa." << endl;
        salvarFluxo();
    }
    else {
        cout << "Erro: o campo 'Caixa' nao esta corretamente inicializado no banco de dados." << endl;
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












