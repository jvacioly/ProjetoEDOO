#include <fstream>
#include <nlohmann/json.hpp>
#include "civetweb.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "globals.h"
#include "pedido.h"
#include "prato.h"

using json = nlohmann::json;
using namespace std;

// Pratos
// Prato bruschetta("Bruschetta", 18.99, "entrada", {});

optional<Prato> encontrarPrato(const vector<Prato>& menu, const string& nomePrato) {
    for (const auto& prato : menu) {
        if (prato.getNome() == nomePrato) {
            return prato;
        }
    }
    return nullopt;
}

// Função que envia os dados de pedidos em formato JSON
void send_pedidos_json(struct mg_connection *conn) {
    string caminho_arquivo = BASE_DIR + "pedidos.json";
    ifstream file(caminho_arquivo);
    json pedidos;
    file >> pedidos;

    string json_data = pedidos.dump();
    mg_websocket_write(conn, MG_WEBSOCKET_OPCODE_TEXT, json_data.c_str(), json_data.size());
}
// Função que envia os dados de fluxo em formato JSON
void send_fluxo_json(struct mg_connection *conn) {
    string caminho_arquivo = BASE_DIR + "fluxo.json";
    ifstream file(caminho_arquivo);
    json fluxo;
    file >> fluxo;

    string json_data = fluxo.dump();
    mg_websocket_write(conn, MG_WEBSOCKET_OPCODE_TEXT, json_data.c_str(), json_data.size());
}

// Função que envia os dados de estoque em formato JSON
void send_estoque_json(struct mg_connection *conn) {
    string caminho_arquivo = BASE_DIR + "estoque.json";
    ifstream file(caminho_arquivo);
    json estoque;
    file >> estoque;

    string json_data = estoque.dump();
    mg_websocket_write(conn, MG_WEBSOCKET_OPCODE_TEXT, json_data.c_str(), json_data.size());
}

// Handler para novas conexões WebSocket
int websocket_connect_handler(const struct mg_connection *conn, void *cbdata) {
    cout << "Nova conexao WebSocket estabelecida" << endl;
    return 0;  // Retorna 0 para aceitar a conexão
}

// Handler para quando a conexão estiver pronta
void websocket_ready_handler(struct mg_connection *conn, void *cbdata) {
    cout << "WebSocket pronto para comunicacao" << endl;
}

/////////////////////////////////////////////////////
// Handler para mensagens recebidas via WebSocket //
///////////////////////////////////////////////////
/////////////////////////////////////////////////////
// Trata os dados e devolve o necessário ao front //
///////////////////////////////////////////////////
int websocket_data_handler(mg_connection *conn, int bits, char *data, size_t data_len, void *cbdata) {
    if (data && data_len > 0) {
        string request(data, data_len);

        // AÇÕES DE ESTOQUE
        if (request == "Solicitar Estoque") {
            // Envia os dados do estoque para o cliente
            send_estoque_json(conn);
        }
        else if (request == "Solicitar Fluxo") {
            // Envia os dados do fluxo para o cliente
            send_fluxo_json(conn);
        }
        else if (request == "Solicitar Pedidos") {
            // Envia os dados do fluxo para o cliente
            send_pedidos_json(conn);
        }
        else if (request.find("editar") != string::npos) {
            // Editar características e remover/adicionar quantidades de produto ao estoque
            json jsonInfos = json::parse(request);
            string nome = jsonInfos.value("nome", "");
            string categoria = jsonInfos.value("categoria", "");
            string medida = jsonInfos.value("medida", "");
            int codigoProduto = jsonInfos.contains("codigo") ? stoi(jsonInfos["codigo"].get<string>()) : 0;
            string acao;
            try {
                acao = jsonInfos.value("add/rem", "");
            } catch (const json::exception &e) {
                acao = "";
            }
            if (acao == "adicionar") {
                double quantidade =  jsonInfos.contains("quantAdicionada") ? stod(jsonInfos["quantAdicionada"].get<string>()) : 0.0;
                restaurante->editEstoque(codigoProduto, nome, categoria, medida, quantidade, false);
            }
            else if (acao == "remover") {
                double quantidade =  jsonInfos.contains("quantRemover") ? stod(jsonInfos["quantRemover"].get<string>()) : 0.0;
                restaurante->editEstoque(codigoProduto, nome, categoria, medida, quantidade, true);
            }
            else {
                restaurante->editEstoque(codigoProduto, nome, categoria, medida, 0);
            }
            send_estoque_json(conn);
            send_fluxo_json(conn);
        }
        else if (request.find("adicionar") != string::npos) {
            // Adicionar e inicializar produto no estoque
            json jsonInfos = json::parse(request);
            string nome = jsonInfos.value("nome", "");
            string categoria = jsonInfos.value("categoria", "");
            string medida = jsonInfos.value("medida", "");
            double preco = jsonInfos.contains("preco") ? stod(jsonInfos["preco"].get<string>()) : 0.0;
            int quantidade = jsonInfos.contains("quantM") ? stoi(jsonInfos["quantM"].get<string>()) : 0;

            if (nome.empty() || categoria.empty() || medida.empty() || preco <= 0 || quantidade <= 0) {
                cerr << "Erro: Dados inválidos recebidos." << endl;
                return 0;
            }

            Produto produto(nome, preco, categoria, medida);
            restaurante->addEstoque(produto, quantidade);
            send_estoque_json(conn);
            send_fluxo_json(conn);
        }
        else if (request.find("remover") != string::npos) {
            // Remover item do estoque
            json jsonInfos = json::parse(request);
            int codigoProduto = 0;
            string codigoTemp = jsonInfos.value("codigo", "");

            codigoProduto = stoi(codigoTemp);

            restaurante->apagarItem(codigoProduto);
            send_estoque_json(conn);
        }

        // AÇÕES DE PEDIDO
        else if (request.find("pedido") != std::string::npos) {
            // Adicionar pedido
            json jsonInfos = json::parse(request);
            string formaPagamento = jsonInfos.value("pagamento", "");
            string endereco = jsonInfos.value("endereco", "");
            string numero = jsonInfos.value("numero", "");
            string CEP = jsonInfos.value("CEP", "");
            string tipoEndereco = jsonInfos.value("local", "");

            Pedido pedido({}, tipoEndereco, endereco, numero, CEP, formaPagamento);
            for (const auto &prato : jsonInfos["itens"].items()) {
                const json &dados = prato.value();

                string nome = dados["nome"].get<string>();
                int  quantidade = dados["quantidade"].get<int>();
                string pratoObs = dados["observacao"].get<string>();

                optional<Prato> pratoOpt = encontrarPrato(restaurante->getMenu(), nome);
                if (pratoOpt) {
                    const Prato &dadosPrato = pratoOpt.value();
                    pedido.addPrato(dadosPrato, quantidade);
                }
                if (!pratoObs.empty()) {
                    pratoObs = nome + ": " + pratoObs;
                    pedido.addObservacao(pratoObs);
                }

            }
            restaurante->registrarPedido(pedido);
            send_pedidos_json(conn);
        }
        else if (request.find("alterar_status") != string::npos) {
            // Editar status do pedido
            json jsonInfos = json::parse(request);
            string novoStatus = jsonInfos.value("novo_status", "");
            string IDpedido = jsonInfos.value("id", "");
            if (novoStatus == "preparando") {
                restaurante->prepararPedido(IDpedido);
            }
            else if (novoStatus == "caminho") {
                restaurante->enviarPedido(IDpedido);
            }
            else if (novoStatus == "cancelado") {
                restaurante->cancelarPedido(IDpedido);
            }
            else if (novoStatus == "finalizado") {
                restaurante->finalizarPedido(IDpedido);
            }
            send_pedidos_json(conn);
        }
    }
    return 1;  // Retorna 1 para continuar a comunicação
}

// Handler para fechamento de conexão WebSocket
void websocket_close_handler(const struct mg_connection *conn, void *cbdata) {
    cout << "Conexao WebSocket fechada" << endl;
}

// Função para configurar e iniciar o servidor WebSocket
void setup_websocket_server() {
    const char *options[] = {
        "listening_ports", "8000",
        nullptr
    };

    struct mg_callbacks callbacks;
    memset(&callbacks, 0, sizeof(callbacks));

    struct mg_context *ctx = mg_start(&callbacks, nullptr, options);
    if (!ctx) {
        cerr << "Falha ao iniciar o servidor" << endl;
        return;
    }

    // Configurando a rota WebSocket para "/ws"
    mg_set_websocket_handler(ctx, "/ws",
        websocket_connect_handler,  // Quando conecta
        websocket_ready_handler,    // Quando pronto
        websocket_data_handler,     // Quando recebe dados
        websocket_close_handler,    // Quando desconecta
        nullptr);

    cout << "Servidor rodando em http://localhost:8000" << endl;
    cout << "WebSocket disponivel em ws://localhost:8000/ws" << endl;

    // Mantém o servidor rodando
    while (true) {
        this_thread::sleep_for(chrono::seconds(1));
    }

    mg_stop(ctx);
}