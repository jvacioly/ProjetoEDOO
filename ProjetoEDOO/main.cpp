
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

// Entradas
Prato bruschetta("Bruschetta", 18.99, "entradas", {});
Prato paoDeAlho("Pão de Alho", 15.99, "entradas", {});
Prato queijoCoalho("Queijo Qualho", 22.99, "entradas", {});
Prato bolinhoDeBacalhau("Bolinho de Bacalhau", 28.99, "entradas", {});
Prato tabuaFrios("Tábua de Frios", 35.99, "entradas", {});

// Pratos Principais
Prato pizzaMargherita("Pizza Margherita", 49.99, "pratos principais", {});
Prato pizzaCalabresa("Pizza Calabresa", 52.99, "pratos principais", {});
Prato pizzaQuatroQueijos("Pizza Quatro Queijos", 58.99, "pratos principais", {});
Prato pizzaPortuguesa("Pizza Portuguesa", 55.99, "pratos principais", {});
Prato pizzaVegetariana("Pizza Vegetariana", 50.99, "pratos principais", {});

// Sobremesas
Prato pizzaChocolate("Pizza de Chocolate", 39.99, "sobremesas", {});
Prato tiramisu("Tiramisu", 30.99, "sobremesas", {});
Prato pudimDeLeite("Pudim de Leite", 25.99, "sobremesas", {});
Prato petitGateau("Petit Gateau", 33.99, "sobremesas", {});
Prato brownie("Brownie", 29.99, "sobremesas", {});

// Acompanhamentos
Prato batataFrita("Batata Frita", 22.99, "acompanhamentos", {});
Prato onionRings("Onion Rings", 20.99, "acompanhamentos", {});
Prato saladaCaesar("Salada Caesar", 28.99, "acompanhamentos", {});
Prato palitosDeMucarela("Palitos de Muçarela", 27.99, "acompanhamentos", {});
Prato arancini("Arancini", 30.99, "acompanhamentos", {});

// Bebidas


shared_ptr<Restaurante> restaurante = make_shared<Restaurante>(vector<Prato>{bruschetta});

int main() {
    setup_websocket_server();
    return 0;
}
