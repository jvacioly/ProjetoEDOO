#include <string>
#include "json.hpp"
#include "produto.h"
#include "prato.h"
#include "pedido.h"
#include "restaurante.h"
#include "cliente.h"

using namespace std;

optional<Prato> encontrarPrato(const vector<Prato>& menu, const string& nomePrato) {
    for (const auto& prato : menu) {
        if (prato.getNome() == nomePrato) {
            return prato;
        }
    }
    return nullopt;
}

int main() {
    //Criando ingredientes
    Produto farinha(1, "Farinha", 5);
    Produto queijo(2, "Queijo", 10);
    Produto tomate(3, "Tomate", 5.50);
    Produto oregano(4, "Oregano", 10);
    Produto calabresa(5, "Calabresa", 15);
    Produto cebola(6, "Cebola", 15);
    Produto frango(7, "Frango", 15);
    Produto azeitona(8, "Azeitona", 15);
    Produto catupiry(9, "Catupiry", 15);

    //Criando menu e pratos
    Prato pizzaMarguerita(1000, "Pizza Marguerita", 56.90, "prato principal", {{farinha, 1}, {queijo, 4}, {tomate, 1}, {oregano, 1}});
    Prato pizzaMussarela(1001, "Pizza Mussarela", 56.90, "prato principal", {{farinha, 1}, {queijo, 8}, {oregano, 1}});
    Prato pizzaCalabresa(1002, "Pizza de Calabresa", 60.90, "prato principal", {{farinha, 1}, {queijo, 4}, {calabresa, 1}, {cebola, 1}, {oregano, 1}});
    Prato pizzaFrango(1003, "Pizza de Frango", 62.90, "prato principal", {{farinha, 1}, {queijo, 4}, {frango, 1}, {oregano, 1}, {azeitona, 1}});
    Prato pizzaFrangoCatupiry(1004, "Pizza de Frango com Catupiry", 69.90, "prato principal", {{farinha, 1}, {queijo, 4}, {frango, 1}, {catupiry, 1}, {oregano, 1}, {azeitona, 1}});
    vector<Prato> menu = {
        pizzaMarguerita, pizzaMussarela, pizzaCalabresa, pizzaFrango, pizzaFrangoCatupiry,
    };

    //Inicializar o restaurante e o estoque
    Restaurante restaurante(menu);

    //Adicionar Produtos ao Estoque
    restaurante.addEstoque(farinha, 50);
    restaurante.addEstoque(queijo, 50);
    restaurante.addEstoque(tomate, 50);
    restaurante.addEstoque(oregano, 50);
    restaurante.addEstoque(calabresa, 50);
    restaurante.addEstoque(cebola, 50);
    restaurante.addEstoque(frango, 50);
    restaurante.addEstoque(azeitona, 50);
    restaurante.addEstoque(catupiry, 50);

    //Remover Produtos do Estoque
    //restaurante.removerEstoque(tomate, 30);
    //restaurante.apagarItem(farinha);

    // LOOP PARA TESTAR TODAS AS AÇÕES
    string login;
    string senha;
    char input;
    Pedido pedidoCliente({}, "");

    cout << "__________ BEM VINDO AO RESTAURANTE " << restaurante.getNome() << " __________" << endl;
    cout << "Log in (email):"; cin >> login;
    cout << "Senha: "; cin >> senha;
    cout << "Deseja registrar mais dados? (CPF e Endereco) (s/n): "; cin >> input;
    if (input == 's') {
        string cpf;
        vector<string> endereco;
        string itemEndereco;
        cout << "CPF: "; cin >> cpf;
        for (int i=0; i < 3; i ++) {
            if (i == 0) {
                cout << "Endereco: (sem o numero)";
                cin.ignore();
                getline(cin, itemEndereco);
            }
            if (i == 1) {
                cout << "Numero: "; cin >> itemEndereco;
            }
            if (i == 2) {
                cout << "CEP: "; cin >> itemEndereco;
            }
            endereco.push_back(itemEndereco);
        }
        Cliente cliente(login, senha, cpf, {endereco});
    }
    else {
        Cliente cliente(login, senha);
    }
    while (true) {
        cout << "--------------------------------------" << endl;
        cout << "[1] Mostrar MENU" << endl;
        cout << "[2] Fazer Pedido" << endl;
        cout << "[3] Sair" << endl;
        cout << "Escolha a opcao:"; cin >> input;
        cout << "-------------------------------------" << endl;
        if (input == '3') {
            restaurante.registrarPedido(pedidoCliente);
            break;
        }
        else if (input == '1') {
            restaurante.mostrarMenu();
        }
        else if (input == '2') {
            string nomePrato;
            int quantidade;
            cout << "O que gostaria de pedir?" << endl;
            cout << "Prato: ";
            cin.ignore();
            getline(cin, nomePrato);
            cout << "Quantidade: "; cin >> quantidade;
            optional<Prato> pratoOpt = encontrarPrato(menu, nomePrato);
            if (pratoOpt) {
                const Prato& prato = pratoOpt.value();
                string observacao;

                cout << "Alguma observacao? (s/n): "; cin >> input;
                if (input == 's') {
                    cout << "Observacao: "; cin >> observacao;
                }
                else {
                    observacao = "Sem observacao";
                }
                pedidoCliente.addPrato(prato, quantidade);
                pedidoCliente.setObs(observacao);
            }
            else {
                cout << "Prato nao encontrado. Tente novamente." << endl;
            }
            while (true) {
                cout << "-------------------------------------" << endl;
                cout << "[1] Adicionar Item" << endl;
                cout << "[2] Remover Item" << endl;
                cout << "[3] Mostrar Pedido" << endl;
                cout << "[4] Finalizar Pedido" << endl;
                cout << "Escolha a opcao: "; cin >> input;
                cout << "-------------------------------------" << endl;

                if (cin.fail()) {
                    cin.clear(); // Limpa o estado de erro do cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora a entrada inválida
                    cout << "Entrada invalida! Tente novamente." << endl;
                    continue; // Retorna ao início do loop
                }

                if (input == '4') {
                    break;
                }
                else if (input == '3') {
                    pedidoCliente.print();
                }
                else if (input == '1') {
                    cout << "O que gostaria de pedir?" << endl;
                    cout << "Prato: ";
                    cin.ignore();
                    getline(cin, nomePrato);
                    cout << "Quantidade: "; cin >> quantidade;
                    optional<Prato> pratoOpt2 = encontrarPrato(menu, nomePrato);
                    if (pratoOpt2) {
                        const Prato& prato = pratoOpt2.value();
                        string observacao;

                        cout << "Alguma observacao? (s/n): "; cin >> input;
                        if (input == 's') {
                            cout << "Observacao: "; cin >> observacao;
                            pedidoCliente.addObservacao(observacao);
                        }
                        pedidoCliente.addPrato(prato, quantidade);
                    }
                }
                else if (input == '2') {
                    cout << "Que item gostaria de remover? "; cin >> nomePrato;
                    for (const auto& prato : pedidoCliente.getItens()) {
                        if (prato.first.getNome() == nomePrato) {
                            pedidoCliente.removePrato(prato.first.getCodigo());
                            break;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
