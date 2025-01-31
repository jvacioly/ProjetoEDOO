let pedido = document.querySelector(".pedido")
let pedidoConteudo = document.querySelector(".pedidoConteudo")


//Funções
function abrirPedido(){
    pedidoConteudo.style.display = "flex"
}

//EventListeners
pedido.addEventListener("click", abrirPedido)

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