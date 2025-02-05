//
// Created by victo on 03/01/2025.
//

#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include <iostream>

using namespace std;

class Produto {
    private:
        int codigo; // inicializado automaticamente
        string nome;
        double preco;
        string categoria;
        string medida;
    public:
        //Construtor
        Produto(const string& nome, double preco, const string& categoria, const string& medida);
        Produto(const string& nome, double preco);

        //Get Methods
        [[nodiscard]] int getCodigo() const { return codigo; };
        [[nodiscard]] const string& getNome() const { return nome; };
        [[nodiscard]] double getPreco() const { return preco; };
        [[nodiscard]] const string& getCategoria() const { return categoria; };
        [[nodiscard]] const string& getMedida() const { return medida; };

        //Set Methods
        void setNome(const string& nome);
        void setPreco(double preco);
        void setCategoria(const string& categoria);
        void setMedida(const string& medida);

        void print() const;
};



#endif //PRODUTO_H
