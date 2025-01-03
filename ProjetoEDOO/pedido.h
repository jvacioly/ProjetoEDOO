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
        double valorTotal;
        void atualizarValorTotal();
    public:
        //Construtor
        explicit Pedido(int id);

        //Get Methods
        int getID() const {return ID;}
        double getValorTotal() const {return valorTotal;}

        //Outros Metodos
        void print() const;
        void addPrato(const Prato& prato, int quantidade);
        void removePrato(int codigoProduto);

};



#endif //PEDIDO_H
