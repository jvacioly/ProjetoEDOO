//
// Created by victo on 20/01/2025.
//

#ifndef CLIENTE_H
#define CLIENTE_H
#include <string>
#include <vector>

using namespace std;

class Cliente {
    private:
        string email;
        string password;
        string CPF;
        vector<vector<string>> enderecos;
    public:
        //Construtor
        Cliente(const string &email, const string &password,
            const string &CPF, const vector<vector<string>> &enderecos);
        Cliente(const string &email, const string &password);

        //Get Methods
        string getEmail() const {return email;}
        string getPassword() const {return password;}
        string getCPF() const {return CPF;}
        vector<vector<string>> getEnderecos() const {return enderecos;}

        //Outros Métodos
        void addEndereco(const vector<string> &endereco);
        void removeEndereco(const vector<string> &endereco);
 };



#endif //CLIENTE_H
