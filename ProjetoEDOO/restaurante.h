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
    public:
        //Construtor e Destrutor
        Restaurante(const string& nome, const vector<string>& endereco, const string& contato, const string& descricao, const vector<Prato>& menuInicial);
        Restaurante(const string& nome, const vector<Prato>& menuInicial);
        explicit Restaurante(const vector<Prato>& menuInicial);
        ~Restaurante();

        //Get Methods
        [[nodiscard]] string getNome() const {return nome;}
        [[nodiscard]] vector<Prato> getMenu() const { return menu; }

        //Métodos do Estoque
        void carregarEstoque();
        void salvarEstoque() const;
        void addEstoque(const Produto& produto, int quantidade);
        void editEstoque(int codigoProduto, string nome, string categoria, string medida, double quantidade, bool remover=false);
        bool apagarItem(int codigoProduto);
        bool checarEstoque(const Pedido& pedido);
        void mostrarEstoque() const;

        //Métodos dos Pedidos
        void carregarPedidos();
        void salvarPedidos() const;
        void registrarPedido(const Pedido& pedido);
        void prepararPedido(const string& IDpedido);
        void enviarPedido(const string& IDpedido);
        void cancelarPedido(const string& IDpedido);
        void finalizarPedido(const string& IDpedido);

        //Métodos do Fluxo
        void carregarFluxo();
        void salvarFluxo() const;
        void registrarCompra(double valor);
        void registrarVenda(double valor);
        void adicionarCaixa(double valor);

        //Outros Métodos
        void mostrarMenu() const;
};



#endif //RESTAURANTE_H
