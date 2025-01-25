
#include <string>
#include <memory>
#include "json.hpp"
#include "produto.h"
#include "prato.h"
#include "pedido.h"
#include "restaurante.h"
#include "cliente.h"
#include "server.cpp"

using namespace std;

shared_ptr<Restaurante> restaurante = make_shared<Restaurante>(vector<Prato>{});

int main() {
    setup_websocket_server();
    return 0;
}
