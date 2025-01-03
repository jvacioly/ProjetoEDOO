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
        vector<string> ingredientes;
        string categoria; //(Entrada, Principal, Sobremesa)
    public:
        //Construtor e Destrutor
        Prato(int codigo, const string &nome, double preco, const string& categoria, const vector<string> &ingredientes);
        ~Prato();

        //Get Methods
        const vector<string> &getIngredientes() const {return ingredientes;};
        const string &getCategoria() const {return categoria;};

        //Set Methods
        void setIngredientes(const vector<string> &novosIngredientes);
        void setCategoria(const string &novaCategoria);

        //Outros Metodos
        void print() const;

};



#endif //PRATO_H
