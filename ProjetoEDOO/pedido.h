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
        int ID; //ID único do pedido
        vector<pair<Prato, int>> itens;
        string observacao;
        string horarioPedido;
        string tipoEndereco;
        string endereco;
        string numero;
        string CEP;
        string formaPagamento;
        double valorTotal;
        string status="preparando";
        double atualizarValorTotal();
    public:
        //Construtor
        Pedido(const vector<pair<Prato, int>>& itens, const string& tipoEndereco, const string& endereco, const string& numero, const string& CEP, const string& formaPagamento);
        /*Pedido(const vector<pair<Prato, int>>& itens, const string& observacao);
        explicit Pedido(const vector<pair<Prato, int>>& itens);*/

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
        void print() const;
        void addPrato(const Prato& prato, int quantidade);
        void removePrato(int codigoProduto);
        void addObservacao(const string& observacao);

};


#endif //PEDIDO_H
