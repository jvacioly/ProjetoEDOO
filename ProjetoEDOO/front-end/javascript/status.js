let pedido = document.querySelector(".pedido")
let pedidoConteudo = document.querySelector(".pedidoConteudo")
let condicaoAbrir = false
let abaPedidos = document.getElementById("pedidos")
let andamentobtn = document.querySelector(".andamento")
let historicobtn = document.querySelector(".historico")
let seletorbtn = document.getElementById("seletorbtn")

//Funções
function abrirPedido(pedido){
    condicaoAbrir = !condicaoAbrir
    if (condicaoAbrir == true){
        pedido.style.display = "flex"
    } else {
        pedido.style.display = "none"
    }
    
}
function processarPedidosAndamento(dados) {

    console.log("Pedidos atualizado")
    

    const pedidosArray = Object.keys(dados).map(key => {
        return { id : key, ...dados[key] };
    });

    pedidosArray.sort((a, b) => {
        const horaA = new Date(`1970-01-01T${a.horario_pedido}Z`);
        const horaB = new Date(`1970-01-01T${b.horario_pedido}Z`);
        return horaB - horaA;
    });

    console.log(pedidosArray)
    abaPedidos.innerHTML = ""

    pedidosArray.forEach(pedido => {

        if (pedido.status === "confirmar") {
            pedido.status = "Esperando Confirmação"
        } else if (pedido.status === "preparando") {
            pedido.status = "Pedido Sendo Preparado"
        } else if (pedido.status === "caminho") {
            pedido.status = "Pedido a Caminho"
        } else {
            pedido.status = "Pedido Finalizado"
        }

        const horaformatado = pedido.horario_pedido.substring(0, 5);
        
        if (pedido.status !== "Pedido Finalizado") {
            let divPedido = document.createElement("div")
            divPedido.classList.add("pedido")
            divPedido.innerHTML = `
                <div class="pedidoCabecalho">
                <p>Pedido #${pedido.id} - ${horaformatado}</p>
                <span>${pedido.status}</span>
                </div>
                <div class="pedidoConteudo">
                    <div class="endereco"><h3>Endereço:<p> ${pedido.endereco}, ${pedido.numero}</p></h3> <h3>CEP:<p> ${pedido.CEP}</p></h3></div>
                    <div class="itens">
                        <h3>Itens:</h3>
                        
                    </div>
                    <div class="valor">
                        <h3>Pagamento:<p>${pedido.forma_pagamento}</p></h3> 
                        <h3>Valor Total:<p> R$${pedido.preco_total.toFixed(2)}</p></h3>
                    </div>
                </div>
            `
            let itens = divPedido.querySelector(".itens")
            pedido.itens_do_pedido.forEach(item => {
                let pitem = document.createElement("p")
                pitem.innerHTML = `
                    ${item.prato_nome} ${item.quantidade}x R$${item.preco_unitario}
                `
                itens.append(pitem)
            })
            
            abaPedidos.append(divPedido)

            divPedido.addEventListener("mousedown", () => abrirPedido(divPedido.querySelector(".pedidoConteudo")))
    }
    
})
}
function processarPedidosFinalizados(dados) {

    console.log("Pedidos finalizados atualizado")
    

    const pedidosArray = Object.keys(dados).map(key => {
        return { id : key, ...dados[key] };
    });

    pedidosArray.sort((a, b) => {
        const horaA = new Date(`1970-01-01T${a.horario_pedido}Z`);
        const horaB = new Date(`1970-01-01T${b.horario_pedido}Z`);
        return horaB - horaA;
    });

    console.log(pedidosArray)
    abaPedidos.innerHTML = ""
    pedidosArray.forEach(pedido => {

        if (pedido.status === "confirmar") {
            pedido.status = "Confirmar Pedido"
        } else if (pedido.status === "preparando") {
            pedido.status = "Preparando Pedido"
        } else if (pedido.status === "caminho") {
            pedido.status = "Pedido a Caminho"
        } else if (pedido.status === "finalizado"){
            pedido.status = "Pedido Finalizado"
        } else {
            pedido.status = "Cancelado"
        }

        const horaformatado = pedido.horario_pedido.substring(0, 5);
        
        if (pedido.status === "Pedido Finalizado" || pedido.status === "Cancelado") {
            let divPedido = document.createElement("div")
            divPedido.classList.add("pedido")
            divPedido.innerHTML = `
                <div class="pedidoCabecalho">
                <p>Pedido #${pedido.id} - ${horaformatado}</p>
                <span>${pedido.status}</span>
                </div>
                <div class="pedidoConteudo">
                    <div class="endereco"><h3>Endereço:<p> ${pedido.endereco}, ${pedido.numero}</p></h3> <h3>CEP:<p> ${pedido.CEP}</p></h3></div>
                    <div class="itens">
                        <h3>Itens:</h3>
                        
                    </div>
                    <div class="valor">
                        <h3>Pagamento:<p>${pedido.forma_pagamento}</p></h3> 
                        <h3>Valor Total:<p> R$${pedido.preco_total.toFixed(2)}</p></h3>
                    </div>
                </div>
            `
            let itens = divPedido.querySelector(".itens")
            pedido.itens_do_pedido.forEach(item => {
                let pitem = document.createElement("p")
                pitem.innerHTML = `
                    ${item.prato_nome} ${item.quantidade}x R$${item.preco_unitario}
                `
                itens.append(pitem)
            })
            
            abaPedidos.append(divPedido)

            divPedido.addEventListener("mousedown", () => abrirPedido(divPedido.querySelector(".pedidoConteudo")))
    }
    
})
}

//EventListeners


andamentobtn.addEventListener("click", ()=> {
    if (!historicobtn.classList.contains("inativo")){
        processarPedidosAndamento(window.dados)
    }
    
    seletorbtn.style.transform = "translatex(0px)"
    historicobtn.classList.add("inativo")
    andamentobtn.classList.remove("inativo")
    

})
historicobtn.addEventListener("click", ()=> {
    if (!andamentobtn.classList.contains("inativo")){
        processarPedidosFinalizados(window.dados)
    }
    seletorbtn.style.transform = "translatex(143px)"
    historicobtn.classList.remove("inativo")
    andamentobtn.classList.add("inativo")
    

})
    


//Servidor

// Criando a conexão WebSocket com o servidor C++
const socket = new WebSocket('ws://localhost:8000/ws');

// Função para tratar mensagens recebidas do servidor (JSON com dados do estoque)
socket.onmessage = function(event) {
    // Convertendo a string JSON para um objeto JavaScript
    window.dados = JSON.parse(event.data);

    processarPedidosAndamento(window.dados)
    }



// Função para quando a conexão for aberta
socket.onopen = function() {
    console.log("Conexão WebSocket estabelecida");
    // Não é necessário enviar nada no momento, mas pode ser feito para solicitar dados
    socket.send('Solicitar Pedidos');
};