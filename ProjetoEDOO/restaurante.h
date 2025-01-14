//
// Created by victo on 13/01/2025.
//

#ifndef RESTAURANTE_H
#define RESTAURANTE_H
#include "json.hpp"
#include "produto.h"
#include "prato.h"
#include "pedido.h"

using namespace std;
using json = nlohmann::json;

class Restaurante {
    private:
        json estoque;
        json pedidos;
        vector<Prato> menu;
        float caixa;
    public:
        //Construtor e Destrutor
        Restaurante(const vector<Prato>& menuInicial, float caixa);
        explicit Restaurante(const vector<Prato>& menuInicial);
        ~Restaurante();

        //Métodos do Estoque
        void carregarEstoque();
        void salvarEstoque() const;
        void addEstoque(const Produto& produto, int quantidade);
        bool removerEstoque(const string& nomeProduto, int quantidade);
        void mostrarEstoque() const;


        //Métodos dos Pedidos (EM DESENVOLVIMENTO)
        //bool registrarPedido(const Pedido& pedido);
        /*bool removerPedido();
        void finalizarPedido();
        void mostrarPedidos() const;

        //Outros Métodos
        void mostrarMenu() const;*/


};



#endif //RESTAURANTE_H
