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
    vector<Prato> menu = {
        Prato(1010, "Pizza Marguerita", 35.50, "prato principal", {farinha, queijo, tomate}),
        Prato(1011, "Pizza Calabresa", 38.50, "prato principal", {farinha, queijo, calabresa})
    };

    //Inicializar o restaurante e o estoque
    Restaurante restaurante(menu);

    //Adicionar Produtos ao Estoque
    restaurante.addEstoque(farinha, 5);
    /*restaurante.addEstoque(tomate, 30);
    restaurante.addEstoque(queijo, 50);
    restaurante.addEstoque(calabresa, 50);*/

    return 0;
}
