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
      int codigo;
      string nome;
      double preco;
    public:
      //Construtor
      Produto(int codigo, const string& nome, double preco);

      //Get Methods
      [[nodiscard]] int getCodigo() const { return codigo; };
      [[nodiscard]] const string& getNome() const { return nome; };
      [[nodiscard]] double getPreco() const { return preco; };

      //Set Methods
      void setNome(const string& nome);
      void setPreco(double preco);

      void print() const;
};



#endif //PRODUTO_H
