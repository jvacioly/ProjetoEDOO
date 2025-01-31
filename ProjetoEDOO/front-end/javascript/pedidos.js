//Variaveis
let overlayPopup = document.getElementById("overlayPedidos")
let xPopup = document.getElementById("xPopup")
let popupTitulo = document.querySelector("#container1 h2")
let popupTextosInfo = document.querySelector("#textosInfo")
let scrollPedidos = document.querySelector(".scrollPedidos")
let scrollObs = document.querySelector(".scrollObs")
let valorTotal = document.getElementById("valorTotal")
let proxEtapabtn = document.getElementById("proxEtapa")
let cancelarbtn = document.getElementById("cancelar")


//Funções

function abrirPopup(pedido) {
    popupTitulo.innerHTML = `<span>${pedido.status}</span> Id: ${pedido.id}`
    popupTextosInfo.innerHTML =  `
                    <p>Horário do Pedido: ${pedido.horario_pedido}</p>
                    <div id="endereco">
                        <div class="enderecos"><p>Endereço: ${pedido.endereco}</p><p>numero: ${pedido.numero}</p></div>
                        <div class="enderecos"><p>Tipo de Endereço: ${pedido.tipo_endereco}</p><p>CEP: ${pedido.CEP}</p></div>
                    </div>
                    <p>Forma de Pagamento: ${pedido.forma_pagamento}</p>
                    `

    scrollPedidos.innerHTML = ""
    pedido.itens_do_pedido.forEach(item => {
        let card = document.createElement("div")
        card.classList.add("card")
        card.innerHTML = `
                <span id="quant">${item.quantidade}x</span>
                <p>${item.prato_nome}</p>
                <span id="preco">R$${item.preco_unitario}</span>
        `
        scrollPedidos.appendChild(card)
    })
    document.getElementById("obsH2").innerHTML = "Observações"
    scrollObs.innerHTML = ""
    if (pedido.observacao !== "") {
    let obsArray = pedido.observacao.split(" - ")
    obsArray.forEach(Obs => {
        let card = document.createElement("div")
        card.classList.add("card")
        card.innerHTML = `
                <p id="descricao">${Obs}</p>
        `
        scrollObs.appendChild(card)

    })} else {
        document.getElementById("obsH2").innerHTML = ""
    }

    valorTotal.innerHTML = `Valor Total R$${pedido.preco_total.toFixed(2)}`

    if (pedido.status === "Pedido Finalizado") {
        document.getElementById("butoes").style.display = "none"
    } else {
        document.getElementById("butoes").style.display = "flex"
    }


    
    if (pedido.status === "Confirmar Pedido") {
        etapa_seguinte = "preparando"
    } else if (pedido.status === "Preparando Pedido") {
        etapa_seguinte = "caminho"
    } else if (pedido.status === "Pedido a Caminho") {
        etapa_seguinte = "finalizado"
    } else {
        etapa_seguinte = "sem etapas seguintes"
    }

    pedido_id = pedido.id 

    overlayPopup.style.display = "flex"
}


function fecharPopup() {
    overlayPopup.style.display = "none"
}

function processarPedidos(dados) {

    console.log("Pedidos atualizado")
    

    const pedidosArray = Object.keys(dados).map(key => {
        return { id : key, ...dados[key] };
    });

    pedidosArray.sort((a, b) => {
        const horaA = new Date(`1970-01-01T${a.horario_pedido}Z`);
        const horaB = new Date(`1970-01-01T${b.horario_pedido}Z`);
        return horaA - horaB;
    });

    console.log(pedidosArray)

    let nodeList = document.querySelectorAll(".scroll")
    containers = Array.from(nodeList)

    
    
    containers.forEach(container => {
        container.innerHTML = ""
    })

    pedidosArray.forEach(pedido => {
        if (pedido.status === "confirmar") {
            let divPedido = document.createElement("div")
            divPedido.classList.add("pedido")
            const formatado = pedido.horario_pedido.substring(0, 5);
            divPedido.innerHTML = `
                <p>Id: ${pedido.id}</p> <p>${formatado}</p>
            `
            pedido.status = "Confirmar Pedido"

            containers[0].appendChild(divPedido)
            divPedido.addEventListener("mousedown", () => abrirPopup(pedido))
            
        } else if (pedido.status === "preparando") {
            let divPedido = document.createElement("div")
            divPedido.classList.add("pedido")
            const formatado = pedido.horario_pedido.substring(0, 5);
            divPedido.innerHTML = `
                <p>Id: ${pedido.id}</p> <p>${formatado}</p>
            `
            pedido.status = "Preparando Pedido"

            containers[1].appendChild(divPedido)
            divPedido.addEventListener("mousedown", () => abrirPopup(pedido))

        } else if (pedido.status === "caminho") {
            let divPedido = document.createElement("div")
            divPedido.classList.add("pedido")
            const formatado = pedido.horario_pedido.substring(0, 5);
            divPedido.innerHTML = `
                <p>Id: ${pedido.id}</p> <p>${formatado}</p>
            `
            pedido.status = "Pedido a Caminho"

            containers[2].appendChild(divPedido)
            divPedido.addEventListener("mousedown", () => abrirPopup(pedido))

        } else if (pedido.status === "finalizado") {
            let divPedido = document.createElement("div")
            divPedido.classList.add("pedido")
            const formatado = pedido.horario_pedido.substring(0, 5);
            divPedido.innerHTML = `
                <p>Id: ${pedido.id}</p> <p>${formatado}</p>
            `
            pedido.status = "Pedido Finalizado"

            containers[3].appendChild(divPedido)
            divPedido.addEventListener("mousedown", () => abrirPopup(pedido))

        }
    })
}

function proxEtapa(etapa, id) {
    let mensagem = new Object()
    mensagem["acao"] = "alterar_status"
    mensagem["id"] = id
    mensagem["novo_status"] = etapa


    const jsonData = JSON.stringify(mensagem)

    socket.send(jsonData)
    console.log(`Status de pedido Id: ${id} alterado para: ${etapa}`)
    console.log(mensagem)
}

//EventListeners

overlayPopup.addEventListener("mousedown", (event)=>{
    if (event.target === overlayPopup) {
        fecharPopup()
    }
})

xPopup.addEventListener("mousedown", fecharPopup)

let etapa_seguinte = ""
let pedido_id = ""
proxEtapabtn.addEventListener("mousedown", ()=> {
    proxEtapa(etapa_seguinte, pedido_id)
    fecharPopup()
})

cancelarbtn.addEventListener("mousedown", ()=> {
    if (confirm("Tem certeza que deseja cancelar este pedido?")){
       proxEtapa("cancelado", pedido_id)
       fecharPopup() 
    }
    
})

//Servidor

// Criando a conexão WebSocket com o servidor C++
const socket = new WebSocket('ws://localhost:8000/ws');

// Função para tratar mensagens recebidas do servidor (JSON com dados do estoque)
socket.onmessage = function(event) {
    // Convertendo a string JSON para um objeto JavaScript
    const dados = JSON.parse(event.data);

    processarPedidos(dados)
    }



// Função para quando a conexão for aberta
socket.onopen = function() {
    console.log("Conexão WebSocket estabelecida");
    // Não é necessário enviar nada no momento, mas pode ser feito para solicitar dados
    socket.send('Solicitar Pedidos');
};