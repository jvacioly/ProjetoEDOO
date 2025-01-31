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
let navBotoes = document.querySelectorAll("#nav button")
let addCarrinhobtn = document.getElementById("addCarrinhobtn")
let popupForm = document.getElementById("textosPopup")
let carrinhoScroll = document.getElementById("scroll")
let pedirbtn = document.getElementById("pedir")
let formCarrinho = document.getElementById("formCarrinho")
let overlayConfirmacao = document.getElementById("overlayConfirmacao")
let confirmacao = document.getElementById("confirmacao")
let xConfirmacao = document.getElementById("xConfirmacao")



// funções
function adicionarCarrinho(prato, preco) {
    let formData = new FormData(popupForm)
    let formObject = Object.fromEntries(formData.entries())
    formObject["nome"] = prato
    formObject["preco"] = preco
    console.log("Item adicionado no carrinho:")
    console.log(formObject)
    fecharPopup()

    // criação dos cards no carrinho
    let nodeList = document.querySelectorAll(".cardPrato p")
    let arrayCardPrato = Array.from(nodeList)
    let arrayPrato = arrayCardPrato.map((p) => p.textContent)
    
    let index = arrayPrato.indexOf(formObject.nome)
    
    if (index !== -1) {
        let divCardAdd = carrinhoScroll.children[index]
        let num =  divCardAdd.children[0].textContent
        let sum = parseInt(num) + parseFloat(formObject.quantidade)
        divCardAdd.children[0].textContent = sum + "x"
        sumValorTotal = sum * parseFloat(divCardAdd.dataset.preco)
        divCardAdd.dataset.precototal = sumValorTotal

    } else {

        const divCard = document.createElement("div")
        divCard.classList.add("cardPrato")
        let sumValorTotal = parseFloat(formObject.preco) * parseFloat(formObject.quantidade)
        divCard.dataset.observacao = formObject.observacao
        divCard.dataset.preco = formObject.preco
        divCard.dataset.precototal = sumValorTotal

        divCard.innerHTML = `
            <span class="cardQuant">${formObject.quantidade}x</span>
            <p>${formObject.nome}</p>
            <img src="imagens/xwhite.svg" alt="">
        `
        carrinhoScroll.appendChild(divCard)

        let xCard = divCard.children[2]

        xCard.addEventListener("mousedown", ()=>{
            divCard.remove()
            console.log(`${prato} removido do carrinho`)
            carregarValorTotal()
        })
    }

    carregarValorTotal()
    abrirCarrinho()
}

function carregarValorTotal() {
    let nodeList = document.querySelectorAll(".cardPrato")
    let arrayCardPrato = Array.from(nodeList)
    let valorTotal = 0
    let valorTotalCampo = document.querySelector("#valorTotal p")

    arrayCardPrato.forEach(card => {
        let valorTotalCard = parseFloat(card.dataset.precototal)
        valorTotal += valorTotalCard

    })

    valorTotalCampo.innerHTML = `R$${valorTotal.toFixed(2)}`

}

function fecharPopup() {
    overlay.style.display = "none"
    popupForm.reset()
    
}



function abrirPopup(prato) {

    
    
    document.querySelector("#textosPopup h3").innerHTML = prato.nome
    document.querySelector("#textosPopup p").innerHTML = prato.descricao
    document.querySelector("#adicionar p").innerHTML = "A partir de R$ " + prato.preco
    document.getElementById("pratoPopupImg").src = prato.URL

    prato_nome = prato.nome
    prato_preco = prato.preco

    overlay.style.display = "flex" 
    
}

function fecharCarrinhoFora(event) {
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

function mudarCardapio(categoria, botao){
    cardapio.innerHTML = ""
    categoria.forEach(prato =>{
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

        divPrato.addEventListener("mousedown", ()=> abrirPopup(prato))
    })
    navBotoes.forEach(nav =>{
        if (nav.classList.contains("ativo")){
            nav.classList.remove("ativo")
        }
    })
    botao.classList.add("ativo")



}

function fecharPopupConfirmacao() {
    overlayConfirmacao.style.display = "none"
    
}
function abrirPopupConfirmacao() {
    overlayConfirmacao.style.display = "flex"
    
}







//Eventlisteners Popup
overlay.addEventListener("mousedown", function (event) {
    if (event.target === overlay) { 
        fecharPopup()
    }
})


x.addEventListener("mousedown", fecharPopup)

overlayConfirmacao.addEventListener("mousedown", function (event) {
    if (event.target === overlayConfirmacao) { 
        fecharPopupConfirmacao()
    }
})
//botao popup
let prato_nome = ""
let prato_preco = ""

addCarrinhobtn.addEventListener("mousedown", function addCarrinho() { 
    adicionarCarrinho(prato_nome, prato_preco)})

xConfirmacao.addEventListener("mousedown", fecharPopupConfirmacao)

carrinhobtn.addEventListener("mousedown", abrirCarrinho)

overlayCarrinho.addEventListener("click", fecharCarrinhoFora)

//Eventlisteners nav
entradabtn.addEventListener("click", () =>{mudarCardapio(entradas, entradabtn)})
pratosPrincipaisbtn.addEventListener("click", () =>{mudarCardapio(pratosPrincipais, pratosPrincipaisbtn)})
sobremesasbtn.addEventListener("click", () =>{mudarCardapio(sobremesas, sobremesasbtn)})
acompanhamentosbtn.addEventListener("click", () =>{mudarCardapio(acompanhamentos, acompanhamentosbtn)})
bebidasbtn.addEventListener("click", () =>{mudarCardapio(bebidas, bebidasbtn)})

//Eventlistener Carrinho Pedir
pedirbtn.addEventListener("mousedown", () =>{
    if (!formCarrinho.checkValidity()) {
        alert("Preencha todos os campos corretamente!");
        return;
    }
    if (carrinhoScroll.childElementCount === 0) {
        alert("Não há itens adicionados ao carrinho!");
        return;
    }
    let formData = new FormData(formCarrinho)

    let formObject = Object.fromEntries(formData.entries())

    let nodeList = document.querySelectorAll(".cardPrato")
    let cardsPratos = Array.from(nodeList)

    let itens = []

    cardsPratos.forEach(card => {
        let pedidoIndividual = new Object()
        pedidoIndividual["nome"] = card.children[1].textContent
        pedidoIndividual["quantidade"] = parseInt(card.children[0].textContent)
        pedidoIndividual["observacao"] = card.dataset.observacao
        itens.push(pedidoIndividual)
    })

    formObject["itens"] = itens
    formObject["acao"] = "pedido"
    

    formCarrinho.reset()
    carrinhoScroll.innerHTML = ""
    carregarValorTotal()

    //Enviando pro servidor
    const jsonData = JSON.stringify(formObject)
    

    socket.send(jsonData)
    console.log("Pedido enviado:")
    console.log(formObject)

    //fechando aba de carrinho
    carrinho.classList.add("fadeout")
        setTimeout(() => {
            overlayCarrinho.style.display = "none"
            carrinho.classList.remove("fadeout")
        }, 400)

    //abrindo confirmação
    abrirPopupConfirmacao()
    
    

    
})

//POO Cardápio

const entradas = [
    { id: 1, nome: "Bruschetta", descricao: "Fatias de pão italiano crocantes, cobertas com tomate fresco, manjericão e azeite de oliva, criando uma combinação leve e deliciosa para abrir o apetite.", preco: 18.99, URL: "imagens/cardapio/Bruschetta.jpg" },
    { id: 2, nome: "Pão de Alho", descricao: "Pão macio recheado com um creme saboroso de alho e queijo derretido, assado até atingir a perfeição dourada.", preco: 15.99, URL: "imagens/cardapio/Pão de Alho.jpg"  },
    { id: 3, nome: "Queijo Coalho", descricao: "Espetinhos de queijo coalho grelhados até ficarem dourados, servidos com um toque doce de melado de cana.", preco: 22.99, URL: "imagens/cardapio/Queijo Coalho.jpg"  },
    { id: 4, nome: "Bolinho de Bacalhau", descricao: "Crocantes por fora e macios por dentro, esses bolinhos são feitos com bacalhau de qualidade e temperos especiais.", preco: 28.99, URL: "imagens/cardapio/Bolinho de Bacalhau.jpg"  },
    { id: 5, nome: "Tábua de Frios", descricao: "Uma seleção refinada de queijos, presuntos, azeitonas e acompanhamentos, perfeita para compartilhar.", preco: 35.99, URL: "imagens/cardapio/Tábua de Frios.jpg"  }
  ];
  
  const pratosPrincipais = [
    { id: 1, nome: "Pizza Margherita", descricao: "Clássica e saborosa, com molho de tomate, queijo muçarela, manjericão fresco e um toque de azeite de oliva.", preco: 49.99, URL: "imagens/cardapio/Pizza Margherita.jpg"  },
    { id: 2, nome: "Pizza Calabresa", descricao: "Coberta com fatias de calabresa, cebola e queijo muçarela derretido, oferecendo um sabor marcante.", preco: 52.99, URL: "imagens/Pizza.jpg"  },
    { id: 3, nome: "Pizza Quatro Queijos", descricao: "Uma combinação cremosa e intensa de muçarela, gorgonzola, parmesão e provolone.", preco: 58.99, URL: "imagens/cardapio/Pizza Quatro Queijos.jpg"  },
    { id: 4, nome: "Pizza Portuguesa", descricao: "Uma explosão de sabores com presunto, ovo, cebola, pimentão e azeitonas sobre uma base de queijo.", preco: 55.99, URL: "imagens/cardapio/Pizza Portuguesa.jpg"  },
    { id: 5, nome: "Pizza Vegetariana", descricao: "Deliciosa mistura de tomate, champignon, pimentão e muçarela, ideal para quem busca uma opção leve.", preco: 50.99, URL: "imagens/cardapio/Pizza Vegetariana.jpg"  }
  ];
  
  const sobremesas = [
    { id: 1, nome: "Pizza de Chocolate", descricao: "Massa fina coberta com chocolate derretido, pedaços de morango e castanhas crocantes.", preco: 39.99, URL: "imagens/Pizza.jpg"  },
    { id: 2, nome: "Tiramisu", descricao: "Camadas delicadas de biscoito embebido em café, intercaladas com um creme suave de mascarpone.", preco: 30.99, URL: "imagens/Pizza.jpg"  },
    { id: 3, nome: "Pudim de Leite", descricao: "Pudim tradicional, cremoso e envolto em uma calda dourada e irresistível de caramelo.", preco: 25.99, URL: "imagens/Pizza.jpg"  },
    { id: 4, nome: "Petit Gateau", descricao: "Pequeno bolo de chocolate com recheio cremoso, acompanhado de uma bola de sorvete de creme.", preco: 33.99, URL: "imagens/Pizza.jpg"  },
    { id: 5, nome: "Brownie", descricao: "Brownie úmido com pedaços de castanha e servido com uma bola de sorvete para completar o sabor.", preco: 29.99, URL: "imagens/Pizza.jpg"  }
  ];
  
  const acompanhamentos = [
    { id: 1, nome: "Batata Frita", descricao: "Porção generosa de batatas fritas crocantes, salgadas na medida certa.", preco: 22.99, URL: "imagens/Pizza.jpg"  },
    { id: 2, nome: "Onion Rings", descricao: "AAnéis de cebola empanados e fritos até ficarem dourados e crocantes.", preco: 20.99, URL: "imagens/Pizza.jpg"  },
    { id: 3, nome: "Salada Caesar", descricao: "Alface fresca com frango grelhado, croutons crocantes e molho Caesar caseiro.", preco: 28.99, URL: "imagens/Pizza.jpg"  },
    { id: 4, nome: "Palitos de Muçarela", descricao: "Queijo muçarela empanado e frito até atingir uma crocância irresistível.", preco: 27.99, URL: "imagens/Pizza.jpg"  },
    { id: 5, nome: "Arancini", descricao: "Bolinhos de arroz italiano recheados com queijo, fritos até ficarem dourados.", preco: 30.99, URL: "imagens/Pizza.jpg"  }
  ];
  
  const bebidas = [
    { id: 1, nome: "Refrigerante", descricao: "Lata de 350ml disponível em sabores clássicos como Coca-Cola, Guaraná e Fanta.", preco: 7.99, URL: "imagens/Pizza.jpg"  },
    { id: 2, nome: "Suco Natural", descricao: "Suco fresco e saboroso disponível nos sabores laranja, limão e maracujá.", preco: 10.99, URL: "imagens/Pizza.jpg"  },
    { id: 3, nome: "Água Mineral", descricao: " Opção de água com ou sem gás, ideal para refrescar e hidratar.", preco: 5.99, URL: "imagens/Pizza.jpg" },
    { id: 4, nome: "Cerveja", descricao: "Long necks geladas das marcas Heineken, Budweiser e Stella Artois.", preco: 12.99, URL: "imagens/Pizza.jpg"  },
    { id: 5, nome: "Vinho Tinto", descricao: "Taça de vinho tinto seco ou suave, perfeito para acompanhar pratos mais elaborados.", preco: 20.99, URL: "imagens/Pizza.jpg"  }
  ];


  mudarCardapio(entradas, entradabtn)


  // Criando a conexão WebSocket com o servidor C++
const socket = new WebSocket('ws://localhost:8000/ws');

// Função para quando a conexão for aberta
socket.onopen = function() {
    console.log("Conexão WebSocket estabelecida");
    
};
