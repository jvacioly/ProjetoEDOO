//
// Created by victo on 03/01/2025.
//

#ifndef PEDIDO_H
#define PEDIDO_H

#include <vector>
#include "prato.h"

using namespace std;

class Pedido {
    private:
        int ID; // ID único do pedido, gerado automaticamente
        vector<pair<Prato, int>> itens; // Lista de itens do pedido, onde cada item é um par (Prato, quantidade)
        string observacao;
        string horarioPedido;
        string tipoEndereco; // Tipo de endereço (ex: casa, trabalho)
        string endereco;
        string numero;
        string CEP;
        string formaPagamento;
        double valorTotal;
        string status="confirmar";
        double atualizarValorTotal();
    public:
        //Construtor
        Pedido(const vector<pair<Prato, int>>& itens, const string& tipoEndereco, const string& endereco, const string& numero, const string& CEP, const string& formaPagamento);

        //Get Methods
        [[nodiscard]] int getID() const {return ID;}
        [[nodiscard]] const vector<pair<Prato, int>>& getItens() const {return itens;}
        [[nodiscard]] double getValorTotal() const {return valorTotal;}
        [[nodiscard]] string getObservacao() const {return observacao;}
        [[nodiscard]] string getHorarioPedido() const {return horarioPedido;}
        [[nodiscard]] string getStatus() const {return status;}
        [[nodiscard]] string getTipoEndereco() const {return tipoEndereco;}
        [[nodiscard]] string getEndereco() const {return endereco;}
        [[nodiscard]] string getNumero() const {return numero;}
        [[nodiscard]] string getCEP() const {return CEP;}
        [[nodiscard]] string getFormaPagamento() const {return formaPagamento;}

        //Set Methods
        void setStatus(const string& status);
        void setObs(const string& observacao);

        //Outros Métodos
        void print() const; // Exibe as informações do pedido
        void addPrato(const Prato& prato, int quantidade); // Adiciona um prato ao pedido com uma quantidade específica
        void removePrato(int codigoProduto); // Remove um prato do pedido com base no código do produto
        void addObservacao(const string& observacao);

};


#endif //PEDIDO_H
