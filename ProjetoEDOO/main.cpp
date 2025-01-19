#include <string>
#include "json.hpp"
#include "produto.h"
#include "prato.h"
#include "pedido.h"
#include "restaurante.h"

using namespace std;

int main() {
    //Criando ingredientes
    Produto farinha(1, "Farinha", 5);
    Produto queijo(2, "Queijo", 10);
    Produto tomate(3, "Tomate", 5.50);
    Produto calabresa(4, "Calabresa", 15);


    //Criando menu e pratos
    Prato pizzaMarguerita(1010, "Pizza Marguerita", 35.50, "prato principal", {{farinha, 2}, {queijo, 4}, {tomate, 1}});
    Prato pizzaCalabresa(1011, "Pizza Calabresa", 38.50, "prato principal", {{farinha, 2}, {queijo, 4}, {calabresa, 1}});
    vector<Prato> menu = {
        pizzaMarguerita, pizzaCalabresa
    };

    //Inicializar o restaurante e o estoque
    Restaurante restaurante(menu);

    //Adicionar Produtos ao Estoque
    restaurante.addEstoque(farinha, 5);
    restaurante.addEstoque(tomate, 10);
    restaurante.addEstoque(queijo, 50);
    restaurante.addEstoque(calabresa, 50);

    //Remover Produtos do Estoque
    //restaurante.removerEstoque(tomate, 30);
    //restaurante.apagarItem(farinha);

    //Fazendo um Pedido
    Pedido pedido1({{pizzaCalabresa, 1}}, "embalado para viagem");
    restaurante.registrarPedido(pedido1);
    restaurante.finalizarPedido(pedido1);

    return 0;
}
