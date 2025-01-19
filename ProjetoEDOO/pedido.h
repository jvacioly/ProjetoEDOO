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
        double valorTotal;
        bool finalizado = false;
        double atualizarValorTotal();
    public:
        //Construtor
        Pedido(const vector<pair<Prato, int>>& itens, const string& observacao);
        explicit Pedido(const vector<pair<Prato, int>>& itens);

        //Get Methods
        [[nodiscard]] int getID() const {return ID;}
        [[nodiscard]] const vector<pair<Prato, int>>& getItens() const {return itens;}
        [[nodiscard]] double getValorTotal() const {return valorTotal;}
        [[nodiscard]] string getObservacao() const {return observacao;}
        [[nodiscard]] string getHorarioPedido() const {return horarioPedido;}
        [[nodiscard]] string getStatus() const {
            if (finalizado) {
                return "Finalizado";
            };
            return "Nao finalizado";
        }

        //Set Methods
        void setStatus(bool finalizado);

        //Outros Métodos
        void print() const;
        void addPrato(const Prato& prato, int quantidade);
        void removePrato(int codigoProduto);

};



#endif //PEDIDO_H
