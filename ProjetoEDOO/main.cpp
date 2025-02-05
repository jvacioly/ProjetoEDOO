#include <string>
#include <memory>
#include <cstdlib>
#include "json.hpp"
#include "prato.h"
#include "restaurante.h"
#include "server.cpp"

using namespace std;

// Entradas
Prato bruschetta("Bruschetta", 18.99, "entradas", {{"Pão", 1}, {"Tomate", 1}, {"Manjericão", 1}, {"Azeite", 0.5}});
Prato paoDeAlho("Pão de Alho", 15.99, "entradas", {{"Pão", 2}, {"Alho", 4}, {"Queijo", 250}});
Prato queijoCoalho("Queijo Coalho", 22.99, "entradas", {{"Queijo Coalho", 500}});
Prato bolinhoDeBacalhau("Bolinho de Bacalhau", 28.99, "entradas", {{"Farinha de Trigo", 500}, {"Bacalhau", 250}, {"Manteiga", 250}});
Prato tabuaFrios("Tábua de Frios", 35.99, "entradas", {{"Queijo", 100}, {"Presunto", 100}, {"Azeitona", 6}});

// Pratos Principais
Prato pizzaMargherita("Pizza Margherita", 49.99, "pratos principais", {{"Farinha de Trigo", 1000}, {"Tomate", 4}, {"Queijo", 500}, {"Manjericão", 1}, {"Azeite", 0.25}});
Prato pizzaCalabresa("Pizza Calabresa", 52.99, "pratos principais", {{"Farinha de Trigo", 1000}, {"Tomate", 2}, {"Queijo", 400}, {"Calabresa", 1}, {"Cebola", 0.5}});
Prato pizzaQuatroQueijos("Pizza Quatro Queijos", 58.99, "pratos principais", {{"Farinha de Trigo", 1000}, {"Queijo", 600}});
Prato pizzaPortuguesa("Pizza Portuguesa", 55.99, "pratos principais", {{"Farinha de Trigo", 1000}, {"Tomate", 1}, {"Queijo", 400}, {"Ovo", 2}, {"Presunto", 200}, {"Cabola", 0.25}, {"Pimentão", 0.5}, {"Azeitona", 8}});
Prato pizzaVegetariana("Pizza Vegetariana", 50.99, "pratos principais", {{"Farinha de Trigo", 1000}, {"Tomate", 4}, {"Queijo", 400}, {"Champignon", 16}, {"Pimentão", 0.5}, {"Azeite", 0.25}});

// Sobremesas
Prato pizzaChocolate("Pizza de Chocolate", 39.99, "sobremesas", {{"Farinha de Trigo", 1000}, {"Chocolate", 400}, {"Morango", 10}, {"Castanha", 300}});
Prato tiramisu("Tiramisu", 30.99, "sobremesas", {{"Queijo", 50}, {"Biscoito", 2}, {"Leite", 50}, {"Chocolate", 50}, {"Café", 10}});
Prato pudimDeLeite("Pudim de Leite", 25.99, "sobremesas", {{"Leite", 250}, {"Ovo", 1}});
Prato petitGateau("Petit Gateau", 33.99, "sobremesas", {{"Chocolate", 50}, {"Manteiga", 25}, {"Farinha de Trigo", 100}, {"Ovo", 1}});
Prato brownie("Brownie", 29.99, "sobremesas", {{"Farinha de Trigo", 50}, {"Ovo", 1}, {"Manteiga", 50}, {"Chocolate", 50}});

// Acompanhamentos
Prato batataFrita("Batata Frita", 22.99, "acompanhamentos", {{"Batata", 10}});
Prato onionRings("Onion Rings", 20.99, "acompanhamentos", {{"Cebola", 4}});
Prato saladaCaesar("Salada Caesar", 28.99, "acompanhamentos", {{"Alface", 250}, {"Frango", 0.2}});
Prato palitosDeMucarela("Palitos de Muçarela", 27.99, "acompanhamentos", {{"Queijo", 250}});
Prato arancini("Arancini", 30.99, "acompanhamentos", {{"Arroz", 400}, {"Queijo", 250}});

// Bebidas
Prato refrigerante("Refrigerante", 7.99, "bebidas", {{"Refrigerante", 1}});
Prato sucoNatural("Suco Natural", 10.99, "bebidas", {{"Suco Natural", 1}});
Prato aguaMineral("Água Mineral", 5.99, "bebidas", {{"Água Mineral", 1}});
Prato cerveja("Cerveja", 12.99, "bebidas", {{"Cerveja", 1}});
Prato vinhoTinto("Vinho Tinto", 20.99, "bebidas", {{"Vinho Tinto", 1}});

// Inicializando o restaurante
shared_ptr<Restaurante> restaurante = make_shared<Restaurante>(vector<Prato>{
    bruschetta, paoDeAlho,queijoCoalho, bolinhoDeBacalhau, tabuaFrios,
    pizzaMargherita, pizzaCalabresa, pizzaQuatroQueijos, pizzaPortuguesa, pizzaVegetariana,
    pizzaChocolate, tiramisu, pudimDeLeite, petitGateau, brownie,
    batataFrita, onionRings, saladaCaesar, palitosDeMucarela, arancini,
    refrigerante, sucoNatural, aguaMineral, cerveja, vinhoTinto});

int main() {
    //////////////////////////////////////////////////////////////////
    // Escreva o caminho absoluto do arquivo /front-end/login.html //
    /////////////////////////////////////////////////////////////////
    const char* htmlPath = "C:/Eu/Faculdade/ProjetoEDOO/ProjetoEDOO/ProjetoEDOO/front-end/login.html";

    ////////////////////////////////////////
    // Escolha o seu sistema operacional //
    //////////////////////////////////////

    string command = "start " + string(htmlPath); // Windows
    // string command = "xdg-open " + string(htmlPath); // Linux
    // string command = "open " + string(htmlPath); // Mac

    system(command.c_str());

    setup_websocket_server();

    return 0;
}
