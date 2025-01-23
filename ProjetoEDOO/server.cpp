#include <fstream>
#include <nlohmann/json.hpp>
#include "civetweb.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using json = nlohmann::json;

// Função que envia os dados de estoque em formato JSON
void send_estoque_json(struct mg_connection *conn) {
    std::ifstream file("C:/Users/kddu4/ProjetoEDOO/ProjetoEDOO/banco_de_dados/estoque.json");
    json estoque;
    file >> estoque;

    std::string json_data = estoque.dump();
    mg_websocket_write(conn, MG_WEBSOCKET_OPCODE_TEXT, json_data.c_str(), json_data.size());
}

// Handler para novas conexões WebSocket
int websocket_connect_handler(const struct mg_connection *conn, void *cbdata) {
    std::cout << "Nova conexao WebSocket estabelecida" << std::endl;
    return 0;  // Retorna 0 para aceitar a conexão
}

// Handler para quando a conexão estiver pronta
void websocket_ready_handler(struct mg_connection *conn, void *cbdata) {
    std::cout << "WebSocket pronto para comunicacao" << std::endl;
}

// Handler para mensagens recebidas via WebSocket
int websocket_data_handler(struct mg_connection *conn, int bits, char *data, size_t data_len, void *cbdata) {
    if (data && data_len > 0) {
        std::string request(data, data_len);
        if (request == "Solicitar Estoque") {
            // Envia os dados do estoque para o cliente
            send_estoque_json(conn);
        } else if (request.find("acao") != std::string::npos) {

        }
    }
    return 1;  // Retorna 1 para continuar a comunicação
}

// Handler para fechamento de conexão WebSocket
void websocket_close_handler(const struct mg_connection *conn, void *cbdata) {
    std::cout << "Conexao WebSocket fechada" << std::endl;
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
        std::cerr << "Falha ao iniciar o servidor" << std::endl;
        return;
    }

    // Configurando a rota WebSocket para "/ws"
    mg_set_websocket_handler(ctx, "/ws",
        websocket_connect_handler,  // Quando conecta
        websocket_ready_handler,    // Quando pronto
        websocket_data_handler,     // Quando recebe dados
        websocket_close_handler,    // Quando desconecta
        nullptr);

    std::cout << "Servidor rodando em http://localhost:8000" << std::endl;
    std::cout << "WebSocket disponivel em ws://localhost:8000/ws" << std::endl;

    // Mantém o servidor rodando
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    mg_stop(ctx);
}