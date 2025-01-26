
// Popups

//inicializando variaveis
let botaoAdicionar = document.getElementById("adicionarBotao")
let overlayADD = document.querySelector(".overlay.add")
let overlayEDIT = document.querySelector(".overlay.edit")
let adicionarItembtn = document.getElementById("adicionaritemBotao")
let salvaralteracoesbtn = document.getElementById("salvaralteracoesBotao")
let removerbtn = document.getElementById("removerBotao")
let formAdcionar = document.querySelector("#adicionar form")
let formEditar = document.querySelector("#editar form")
let xADD = document.querySelector("#xADD")
let xEDIT = document.querySelector("#xEDIT")
let radioAdd = document.getElementById("radioAdd");
let radioRem = document.getElementById("radioRem");
let campoAdicionar = document.querySelector(".text.campoAdd");
let campoRemover = document.querySelector(".text.campoRem");
let editarPopup = document.querySelector("#editar")
let inputNome = document.querySelector("#editar form #nome")
let inputPreco = document.querySelector("#editar form #preco")
let inputCategoria = document.querySelector("#editar form #categoria")
let inputMedida = document.querySelector("#editar form #medida")


//funçoes
function abrirPopupADD() {
    overlayADD.style.display = "flex"

}

function fecharPopupADD() {
    overlayADD.style.display = "none"
    formAdcionar.reset();
}
function abrirPopupEDIT(codigo, nome, categoria, medida, preco) {
    overlayEDIT.style.display = "flex"
    editarPopup.dataset.id = codigo
    inputNome.placeholder = nome
    inputPreco.placeholder = "R$" + preco
    inputCategoria.value = categoria
    inputMedida.value = medida
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
overlayADD.addEventListener("mousedown", function (event) {
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

    
    const itemEncontrado = nomes.find(item => formObject.nome === item);
    if (itemEncontrado) {
        alert(`Item ${formObject.nome} já existe!`);
        return
    }


    formObject["acao"] = "adicionar"

    const jsonData = JSON.stringify(formObject)

    socket.send(jsonData)
    console.log("add enviado:")
    console.log(formObject);

    fecharPopupADD()
  
    

    
})

//popup EDIT

overlayEDIT.addEventListener("mousedown", function (event) {
    if (event.target === overlayEDIT) { 
        fecharPopupEDIT()
    }
})
xEDIT.addEventListener("click", fecharPopupEDIT)

salvaralteracoesbtn.addEventListener("click", function() {

    if (!inputNome.value) inputNome.value = inputNome.placeholder;
    if (!inputPreco.value) inputPreco.value = inputPreco.placeholder;

    let formData = new FormData(formEditar)

    let formObject = Object.fromEntries(formData.entries())

    formObject["acao"] = "editar"
    formObject["codigo"] = editarPopup.dataset.id

    const jsonData = JSON.stringify(formObject)

    socket.send(jsonData)
    console.log("Edit enviado:")
    console.log(formObject);

    fecharPopupEDIT()
    
})

removerbtn.addEventListener("click", function() {

    if (confirm("Tem certeza que deseja excluir este item do estoque?")) {
        console.log("Usuário confirmou remover.");
        let removerObject = new Object();

        removerObject["acao"] = "remover"
        removerObject["codigo"] = editarPopup.dataset.id

        const jsonData = JSON.stringify(removerObject)

        socket.send(jsonData)
        console.log("Remove enviado:")
        console.log(removerObject)

        fecharPopupEDIT()

    } else {
        console.log("Usuário cancelou remover.");
    }

    
    
})




//eventos de mudança nos radios
radioAdd.addEventListener("change", verificarOpcao);
radioRem.addEventListener("change", verificarOpcao);


//Script de Recarregar o Estoque e Criar Conexão


//Funções

//função estoque
function processarEstoque(dados) {

    console.log("Estoque Atualizado:")
    console.log(dados)

    const estoqueArray = Object.keys(dados).map(key => {
        return { nome: key, ...dados[key] };
    });

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
                    <p class="quant">${item.quantidade} (${item.medida})</p>
                    <p class="valor">R$ ${item.preco.toFixed(2)}</p>
                    <p class="valorTotal">R$ ${valorTotal.toFixed(2)}</p>
                    <p class="categoria">${item.categoria}</p>
                    <img src="imagens/settings.svg" alt="" class="ajustes">
                `;
        container.appendChild(divItem);

        let ajustesbtn = divItem.querySelector("img.ajustes")
        ajustesbtn.addEventListener("click", () => abrirPopupEDIT(item.codigo, item.nome, item.categoria, item.medida, item.preco))

    })

}

//função fluxo
function processarFluxo(dados) {
    console.log("Fluxo Atualizado:")
    console.log(dados)

    document.querySelector("p.valores.receita").innerHTML = "R$" + dados.Receita.toFixed(2)
    document.querySelector("p.valores.custos").innerHTML = "R$" + dados.Despesas.toFixed(2)
    document.querySelector("p.valores.lucros").innerHTML = "R$" + dados.Lucro.toFixed(2)

}



// Criando a conexão WebSocket com o servidor C++
const socket = new WebSocket('ws://localhost:8000/ws');

// Função para tratar mensagens recebidas do servidor (JSON com dados do estoque)
socket.onmessage = function(event) {
    // Convertendo a string JSON para um objeto JavaScript
    const dados = JSON.parse(event.data);

    if (dados.hasOwnProperty("Despesas")) {
        processarFluxo(dados)
    } else {
        processarEstoque(dados)
    }


    }



// Função para quando a conexão for aberta
socket.onopen = function() {
    console.log("Conexão WebSocket estabelecida");
    // Não é necessário enviar nada no momento, mas pode ser feito para solicitar dados
    socket.send('Solicitar Estoque');
    socket.send('Solicitar Fluxo');
};



//Filtros 

function filtrarItens() {
    const checkboxes = document.querySelectorAll('.filtro form input');
    const itens = document.querySelectorAll('.item');

    // Obtendo checkboxes selecionados
    const categoriasSelecionadas = Array.from(checkboxes)
        .filter(checkbox => checkbox.checked)
        .map(checkbox => checkbox.value);

    // Se nenhum checkbox estiver selecionado, mostrar todos os itens
    if (categoriasSelecionadas.length === 0) {
        itens.forEach(item => {
            item.style.display = '';  // Mostrar tudo
        });
        return;  // Sai da função para evitar filtro adicional
    }

    // Iterando pelos elementos e mostrando ou escondendo
    itens.forEach(item => {
        const categoria = item.querySelector("p.categoria");
        if (categoriasSelecionadas.includes(categoria.textContent)) {
            item.style.display = '';  // Mostra o item
        } else {
            item.style.display = 'none';  // Oculta o item
        }
    });
}

// Adicionar event listener a todos os checkboxes para atualizar em tempo real
document.querySelectorAll('.filtro-checkbox').forEach(checkbox => {
    checkbox.addEventListener('change', filtrarItens);
});

// Aplicar filtro ao selecionar

document.querySelector(".filtro form").addEventListener("change", filtrarItens)




