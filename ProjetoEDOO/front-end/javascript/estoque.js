

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
let ajustesbtn = document.querySelectorAll("img.ajustes")
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
//Eventlisteners

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

    console.log(Object.fromEntries(formData.entries()));

    fecharPopupADD()
})

//popup EDIT
ajustesbtn.forEach(element => {element.addEventListener("click", abrirPopupEDIT)
    
});

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


//script de recarregar o estoque

// Criando a conexão WebSocket com o servidor C++
const socket = new WebSocket('ws://localhost:8000/ws');

// Função para tratar mensagens recebidas do servidor (JSON com dados do estoque)
socket.onmessage = function(event) {
    // Convertendo a string JSON para um objeto JavaScript
    const dados = JSON.parse(event.data);

    console.log(dados)

    /*
    // Selecionando o container para exibir o estoque
    const container = document.querySelector('.itens');
    container.innerHTML = '';  // Limpar o conteúdo existente

    // Iterando sobre os dados e exibindo-os
    dados.forEach(produto => {
        const divProduto = document.createElement('div');
        divProduto.classList.add('item');
        divProduto.innerHTML = `
                    <p class="nome">Nome</p>
                    <p class="quant">Quant</p>
                    <p class="status">Status</p>
                    <p class="entrada">Entrada</p>
                    <p class="saida">Saída</p>
                    <p class="balanco">Balanço</p>
                    <p class="categoria">Categoria</p>
                    <img src="imagens/settings.svg" alt="" class="ajustes">
                `;
        container.appendChild(divProduto);
    }); */
};

// Função para quando a conexão for aberta
socket.onopen = function() {
    console.log("Conexão WebSocket estabelecida");
    // Não é necessário enviar nada no momento, mas pode ser feito para solicitar dados
    socket.send('Solicitar Estoque');  // Exemplo de uma requisição
};