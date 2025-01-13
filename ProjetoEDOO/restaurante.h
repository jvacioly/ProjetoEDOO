//
// Created by victo on 13/01/2025.
//

#ifndef RESTAURANTE_H
#define RESTAURANTE_H
#include "json.hpp"
#include "pedido.h"
#include "produto.h"

using namespace std;
using json = nlohmann::json;

class Restaurante {
    private:
        json estoque;
        json pedidos;
        unordered_map<string, float> menu;
        float caixa;
    public:
        //Construtor e Destrutor
        Restaurante(const unordered_map<string, float>& menuInicial, float caixa);
        Restaurante(const unordered_map<string, float>& menuInicial);
        ~Restaurante();

        // Métodos para carregar dados do JSON
        void salvarDados() const;
        void carregarDados();

        //Métodos do Estoque
        void addEstoque(const Produto& produto, int quantidade);
        bool removerEstoque(const string& nomeProduto, int quantidade);
        void mostrarEstoque() const;


        //Métodos dos Pedidos (EM DESENVOLVIMENTO)
        bool registrarPedido(const Pedido& pedido);
        /*bool removerPedido();
        void finalizarPedido();
        void mostrarPedidos() const;

        //Outros Métodos
        void mostrarMenu() const;*/


};



#endif //RESTAURANTE_H
