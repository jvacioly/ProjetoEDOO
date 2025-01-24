
// Popups

//inicializando variaveis
let botaoAdicionar = document.getElementById("adicionarBotao")
let overlayADD = document.querySelector(".overlay.add")
let overlayEDIT = document.querySelector(".overlay.edit")
let adicionarItembtn = document.getElementById("adicionaritemBotao")
let salvaralteracoesbtn = document.getElementById("salvaralteracoesBotao")
let formAdcionar = document.querySelector("#adicionar form")
let formEditar = document.querySelector("#editar form")
let xADD = document.querySelector("#xADD")
let xEDIT = document.querySelector("#xEDIT")
let radioAdd = document.getElementById("radioAdd");
let radioRem = document.getElementById("radioRem");
let campoAdicionar = document.querySelector(".text.campoAdd");
let campoRemover = document.querySelector(".text.campoRem");


//funçoes
function abrirPopupADD() {
    overlayADD.style.display = "flex"

}

function fecharPopupADD() {
    overlayADD.style.display = "none"
    formAdcionar.reset();
}
function abrirPopupEDIT() {
    overlayEDIT.style.display = "flex"
    verificarOpcao()
    

}

function fecharPopupEDIT() {
    overlayEDIT.style.display = "none"
    formEditar.reset();
}

function verificarOpcao() {
    if (radioAdd.checked) {
        campoAdicionar.style.display = "flex";
        campoRemover.style.display = "none";
    } else if (radioRem.checked) {
        campoAdicionar.style.display = "none";
        campoRemover.style.display = "flex";
    } else {
        campoAdicionar.style.display = "none";
        campoRemover.style.display = "none";

    }
}
//Eventlisteners Popups

//popup ADD
botaoAdicionar.addEventListener("click", abrirPopupADD)
overlayADD.addEventListener("click", function (event) {
    if (event.target === overlayADD) { 
        fecharPopupADD()
    }
})
xADD.addEventListener("click", fecharPopupADD)
adicionarItembtn.addEventListener("click", function() {
    if (!formAdcionar.checkValidity()) {
        alert("Preencha todos os campos!");
        return;
    }
    let formData = new FormData(formAdcionar)

    let formObject = Object.fromEntries(formData.entries())


    const elementosP = document.querySelectorAll('.nome');

    const nomes = Array.from(elementosP).map(p => p.textContent);

    console.log(nomes);
    
    const itemEncontrado = nomes.find(item => formObject.nome === item);
    if (itemEncontrado) {
        alert(`Item ${formObject.nome} já existe!`);
        return
    }


    formObject["acao"] = "adicionar"

    console.log(formObject);

    const jsonData = JSON.stringify(formObject)

    socket.send(jsonData)
    console.log("enviado")

    fecharPopupADD()

        
            
    
    

    
})

//popup EDIT

overlayEDIT.addEventListener("click", function (event) {
    if (event.target === overlayEDIT) { 
        fecharPopupEDIT()
    }
})
xEDIT.addEventListener("click", fecharPopupEDIT)
salvaralteracoesbtn.addEventListener("click", function() {
    let formData = new FormData(formEditar)

    console.log(Object.fromEntries(formData.entries()));

    formEditar.reset(); //ou botar funçao de fechar
    
})


//eventos de mudança nos radios
radioAdd.addEventListener("change", verificarOpcao);
radioRem.addEventListener("change", verificarOpcao);


//Script de Recarregar o Estoque e Criar Conexão

// Criando a conexão WebSocket com o servidor C++
const socket = new WebSocket('ws://localhost:8000/ws');

// Função para tratar mensagens recebidas do servidor (JSON com dados do estoque)
socket.onmessage = function(event) {
    // Convertendo a string JSON para um objeto JavaScript
    const dados = JSON.parse(event.data);

    console.log(dados)

    const estoqueArray = Object.keys(dados).map(key => {
        return { nome: key, ...dados[key] };
    });

    console.log(estoqueArray);


    // Selecionando o container para exibir o estoque
    const container = document.querySelector('.itens');
    container.innerHTML = '';  // Limpar o conteúdo existente

    // Iterando sobre os dados e exibindo-os
    estoqueArray.forEach(item => {
            let valorTotal = (parseFloat(item.preco, 10) * parseFloat(item.quantidade, 10))
            const divItem = document.createElement('div');
            divItem.classList.add('item');
            divItem.innerHTML = `
                    <p class="nome">${item.nome}</p>
                    <p class="quant">${item.quantidade} (${item.descricao})</p>
                    <p class="valor">R$ ${item.preco}</p>
                    <p class="categoria">${item.categoria}</p>
                    <p class="saida">R$ ${valorTotal}</p>
                    <p class="balanco">Entrada</p>
                    <p class="categoria">Saida</p>
                    <img src="imagens/settings.svg" alt="" class="ajustes">
                `;
            container.appendChild(divItem);

            let ajustesbtn = divItem.querySelector("img.ajustes")
            ajustesbtn.addEventListener("click", abrirPopupEDIT)

        })

    }



// Função para quando a conexão for aberta
socket.onopen = function() {
    console.log("Conexão WebSocket estabelecida");
    // Não é necessário enviar nada no momento, mas pode ser feito para solicitar dados
    socket.send('Solicitar Estoque');  // Exemplo de uma requisição
};



