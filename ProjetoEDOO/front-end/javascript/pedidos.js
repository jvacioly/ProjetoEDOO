//Variaveis
let overlayPopup = document.getElementById("overlayPedidos")
let xPopup = document.getElementById("xPopup")



//Funções

function abrirPopup() {
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
    console.log(pedidosArray)

    let nodeList = document.querySelectorAll("scroll")
    containers = Array.from(nodeList)
    
    containers.forEach(container => {
        container.innerHTML = ""
    })

    pedidosArray.forEach(pedido => {
        if (pedido.status ===)
    })
}

//EventListeners

overlayPopup.addEventListener("mousedown", (event)=>{
    if (event.target === overlayPopup) {
        fecharPopup()
    }
})

xPopup.addEventListener("mousedown", fecharPopup)


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