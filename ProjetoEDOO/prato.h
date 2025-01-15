//
// Created by victo on 03/01/2025.
//

#ifndef PRATO_H
#define PRATO_H

#include "produto.h"
#include <vector>

using namespace std;

class Prato : public Produto {
    private:
        vector<Produto> ingredientes;
        string categoria;
        //Dados herdados de produto
        /*
         *int codigo
         *string nome
         *double preco

         *string descricao
        */
    public:
        //Construtor e Destrutor
        Prato(int codigo, const string &nome, double preco, const string& categoria, const vector<Produto> &ingredientes);
        ~Prato();

        //Get Methods
        [[nodiscard]] vector<Produto> getIngredientes() const {return ingredientes;};

        //Set Methods
        void setIngredientes(const vector<Produto> &novosIngredientes);

        //Outros Metodos
        void print() const;

};



#endif //PRATO_H
