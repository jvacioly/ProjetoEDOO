#include <iostream>
#include <string>
#include "produto.h"
#include "prato.h"

int main() {
    // Criando um prato
    Prato feijoada(1001, "Feijoada", 25.99, "Prato Principal", {"Arroz", "Feijao", "Carne"});

    // Exibindo informações do prato
    feijoada.print();
    feijoada.setIngredientes({"Carne", "Feijao", "Arroz", "Linguica"});
    feijoada.print();

    return 0;
}