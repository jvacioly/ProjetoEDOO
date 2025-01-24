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
        json fluxo;
        string nome;
        vector<string> endereco; // {"rua", "numero", "cep"}
        string contato;
        string descricao;
        vector<Prato> menu;
        float caixa;
    public:
        //Construtor e Destrutor
        Restaurante(const string& nome, const vector<string>& endereco, const string& contato, const string& descricao, const vector<Prato>& menuInicial, float caixa);
        Restaurante(const string& nome, const vector<Prato>& menuInicial);
        explicit Restaurante(const vector<Prato>& menuInicial);
        ~Restaurante();

        //Get Methods
        [[nodiscard]] string getNome() const {return nome;}

        //Métodos do Estoque
        void carregarEstoque();
        void salvarEstoque() const;
        void addEstoque(const Produto& produto, int quantidade);
        bool removerEstoque(const Produto& produto, int quantidade);
        bool apagarItem(const Produto& produto);
        bool checarEstoque(const Pedido& pedido);
        void mostrarEstoque() const;

        //Métodos dos Pedidos (EM DESENVOLVIMENTO)
        void carregarPedidos();
        void salvarPedidos() const;
        void registrarPedido(const Pedido& pedido);
        // bool removerPedido();
        void finalizarPedido(Pedido& pedido);
        // void mostrarPedidos() const;

        //Métodos do Fluxo
        void carregarFluxo();
        void salvarFluxo() const;
        bool registrarCompra(double valor);
        void registrarVenda(double valor);
        // void mostrarRanking() const;

        //Outros Métodos
        void mostrarMenu() const;


};



#endif //RESTAURANTE_H
