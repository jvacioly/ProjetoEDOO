// Inicializando variaveis
let overlay = document.getElementById("overlayPopup")
let pratos = document.querySelectorAll(".prato")
let x = document.getElementById("x")
let carrinhobtn = document.getElementById("carrinhoIcon")
let carrinho = document.querySelector(".carrinho")
let overlayCarrinho = document.getElementById("overlayCarrinho")
let cardapio = document.getElementById("cardapio")
let entradabtn = document.querySelector(".entradas")
let sobremesasbtn = document.querySelector(".sobremesas")
let acompanhamentosbtn = document.querySelector(".acompanhamentos")
let bebidasbtn = document.querySelector(".bebidas")
let pratosPrincipaisbtn = document.querySelector(".pratosPrincipais")





// funções
function fecharPopup() {
    overlay.style.display = "none"
    
}

function abrirPopup() {
    overlay.style.display = "flex"
    
}

function fecharCarrinhoFora(event) {
    console.log(event.target)
    if (!carrinho.contains(event.target)) {
        carrinho.classList.add("fadeout")
        setTimeout(() => {
            overlayCarrinho.style.display = "none"
            carrinho.classList.remove("fadeout")
        }, 400)

        

    }
}


function abrirCarrinho() {
    
    overlayCarrinho.style.display = "flex"
    
    
}

function mudarCardapio(categoria){
    console.log(categoria)
    cardapio.innerHTML = ""
    categoria.forEach(prato =>{
        console.log(prato)
        const divPrato = document.createElement("div")
        divPrato.classList.add("prato")

        divPrato.innerHTML = `
            <div id="textos">
            <h3>${prato.nome}</h3>
            <p>${prato.descricao}</p>
            <p>A partir de R$ ${prato.preco}</p>
            </div>
            <img src="${prato.URL}" alt="Prato">
        `
        cardapio.appendChild(divPrato)

        divPrato.addEventListener("mousedown", abrirPopup)
    })

}








//Eventlisteners Popup
overlay.addEventListener("mousedown", function (event) {
    if (event.target === overlay) { 
        fecharPopup()
    }
})


x.addEventListener("mousedown", fecharPopup)

carrinhobtn.addEventListener("mousedown", abrirCarrinho)

overlayCarrinho.addEventListener("click", fecharCarrinhoFora)

//Eventlisteners nav
entradabtn.addEventListener("click", () =>{mudarCardapio(entradas)})
pratosPrincipaisbtn.addEventListener("click", () =>{mudarCardapio(pratosPrincipais)})
sobremesasbtn.addEventListener("click", () =>{mudarCardapio(sobremesas)})
acompanhamentosbtn.addEventListener("click", () =>{mudarCardapio(acompanhamentos)})
bebidasbtn.addEventListener("click", () =>{mudarCardapio(bebidas)})


//POO Cardápio

const entradas = [
    { id: 1, nome: "Bruschetta", descricao: "Pão italiano crocante com tomate, manjericão e azeite de oliva.", preco: 18.90, URL: "imagens/Pizza.jpg" },
    { id: 2, nome: "Pão de Alho", descricao: "Pão recheado com creme de alho e queijo derretido.", preco: 15.00, URL: "imagens/Pizza.jpg"  },
    { id: 3, nome: "Queijo Coalho", descricao: "Espetinhos de queijo coalho grelhados, servidos com melado de cana.", preco: 22.00, URL: "imagens/Pizza.jpg"  },
    { id: 4, nome: "Bolinho de Bacalhau", descricao: "Bolinho crocante de bacalhau com temperos especiais.", preco: 28.50, URL: "imagens/Pizza.jpg"  },
    { id: 5, nome: "Tábua de Frios", descricao: "Seleção de queijos, presuntos e azeitonas.", preco: 35.00, URL: "imagens/Pizza.jpg"  }
  ];
  
  const pratosPrincipais = [
    { id: 1, nome: "Pizza Margherita", descricao: "Molho de tomate, muçarela, manjericão e azeite.", preco: 49.90, URL: "imagens/Pizza.jpg"  },
    { id: 2, nome: "Pizza Calabresa", descricao: "Calabresa fatiada, cebola e queijo muçarela.", preco: 52.00, URL: "imagens/Pizza.jpg"  },
    { id: 3, nome: "Pizza Quatro Queijos", descricao: "Muçarela, gorgonzola, parmesão e provolone.", preco: 58.00, URL: "imagens/Pizza.jpg"  },
    { id: 4, nome: "Pizza Portuguesa", descricao: "Presunto, ovo, cebola, pimentão e azeitonas.", preco: 55.00, URL: "imagens/Pizza.jpg"  },
    { id: 5, nome: "Pizza Vegetariana", descricao: "Tomate, champignon, pimentão e muçarela.", preco: 50.00, URL: "imagens/Pizza.jpg"  }
  ];
  
  const sobremesas = [
    { id: 1, nome: "Pizza de Chocolate", descricao: "Chocolate derretido com morangos e castanhas.", preco: 39.00, URL: "imagens/Pizza.jpg"  },
    { id: 2, nome: "Tiramisu", descricao: "Camadas de biscoito, café e creme mascarpone.", preco: 30.00, URL: "imagens/Pizza.jpg"  },
    { id: 3, nome: "Pudim de Leite", descricao: "Pudim cremoso com calda de caramelo.", preco: 25.00, URL: "imagens/Pizza.jpg"  },
    { id: 4, nome: "Petit Gateau", descricao: "Bolo de chocolate com recheio cremoso e sorvete.", preco: 33.00, URL: "imagens/Pizza.jpg"  },
    { id: 5, nome: "Brownie", descricao: "Brownie de chocolate com castanhas e sorvete.", preco: 29.00, URL: "imagens/Pizza.jpg"  }
  ];
  
  const acompanhamentos = [
    { id: 1, nome: "Batata Frita", descricao: "Porção de batatas fritas crocantes.", preco: 22.00, URL: "imagens/Pizza.jpg"  },
    { id: 2, nome: "Onion Rings", descricao: "Anéis de cebola empanados e crocantes.", preco: 20.00, URL: "imagens/Pizza.jpg"  },
    { id: 3, nome: "Salada Caesar", descricao: "Alface, frango grelhado, croutons e molho especial.", preco: 28.00, URL: "imagens/Pizza.jpg"  },
    { id: 4, nome: "Palitos de Muçarela", descricao: "Palitos de queijo muçarela empanados e fritos.", preco: 27.00, URL: "imagens/Pizza.jpg"  },
    { id: 5, nome: "Arancini", descricao: "Bolinho de arroz italiano recheado com queijo.", preco: 30.00, URL: "imagens/Pizza.jpg"  }
  ];
  
  const bebidas = [
    { id: 1, nome: "Refrigerante", descricao: "Lata 350ml (Coca-Cola, Guaraná, Fanta).", preco: 7.00, URL: "imagens/Pizza.jpg"  },
    { id: 2, nome: "Suco Natural", descricao: "Sabores: laranja, limão, maracujá.", preco: 10.00, URL: "imagens/Pizza.jpg"  },
    { id: 3, nome: "Água Mineral", descricao: "Com ou sem gás.", preco: 5.00, URL: "imagens/Pizza.jpg" },
    { id: 4, nome: "Cerveja", descricao: "Long neck (Heineken, Budweiser, Stella Artois).", preco: 12.00, URL: "imagens/Pizza.jpg"  },
    { id: 5, nome: "Vinho Tinto", descricao: "Taça de vinho tinto seco ou suave.", preco: 20.00, URL: "imagens/Pizza.jpg"  }
  ];
