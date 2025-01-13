#include <iostream>
#include <string>
#include "json.hpp"
#include "produto.h"
#include "prato.h"
#include "pedido.h"
#include "restaurante.h"

using namespace std;
/*
int main() {
    // Criando um prato
    Prato feijoada(1001, "Feijoada", 25.99, "Prato Principal", {"Arroz", "Feijao", "Carne"});

    // Exibindo informações do prato
    feijoada.print();
    feijoada.setIngredientes({"Carne", "Feijao", "Arroz", "Linguica"});
    feijoada.print();

    return 0;
}
*/

int main() {
    // Criar menu inicial
    unordered_map<std::string, float> menuInicial = {
        {"Pizza", 35.50},
        {"Hamburguer", 20.00},
        {"Refrigerante", 5.50}
    };

    Restaurante restaurante(menuInicial);

    // Criar pratos
    Prato pizza(1, "Pizza", 35.50, "prato principal", {"Tomate", "Queijo", "Farinha"});
    Prato hamburguer(2, "Hamburguer", 20.00, "prato principal", {"Pao", "Tomate", "Queijo", "Alface", "Carne"});

    // Adicionar itens ao estoque
    restaurante.addEstoque(pizza, 10);
    restaurante.addEstoque(hamburguer, 15);

    // Criar pedido
    Pedido pedido(1);
    pedido.addPrato(pizza, 2);
    pedido.addPrato(hamburguer, 1);

    // Registrar pedido
    restaurante.registrarPedido(pedido);

    // Mostrar estoque atualizado
    restaurante.mostrarEstoque();

    return 0;
}
