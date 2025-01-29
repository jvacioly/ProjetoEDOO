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
        vector<pair<string, int>> ingredientes;
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
        Prato(const string &nome, double preco, const string& categoria, const vector<pair<string, int>> &ingredientes);
        ~Prato();

        //Get Methods
        [[nodiscard]] vector<pair<string, int>> getIngredientes() const {return ingredientes;};

        //Set Methods
        void setIngredientes(const vector<pair<string, int>> &novosIngredientes);

        //Outros Metodos
        // void print() const;

};



#endif //PRATO_H
