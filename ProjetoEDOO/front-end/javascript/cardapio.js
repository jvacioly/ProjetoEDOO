// Inicializando variaveis
let overlay = document.getElementById("overlayPopup")
let pratos = document.querySelectorAll(".prato")
let x = document.getElementById("x")
let carrinhobtn = document.getElementById("carrinhoIcon")
let carrinho = document.getElementById("carrinho")
let overlayCarrinho = document.getElementById("overlayCarrinho")




// funções
function fecharPopup() {
    overlay.style.display = "none"
    
}

function abrirPopup() {
    overlay.style.display = "flex"
    
}

function fecharCarrinhoFora(event) {
    if (!carrinho.contains(event.target)) {
        overlayCarrinho.style.display = "none";

    }
}


function abrirfecharCarrinho() {
    
    overlayCarrinho.style.display = "flex"
    
    
}








//Eventlisteners Popup
overlay.addEventListener("mousedown", function (event) {
    if (event.target === overlay) { 
        fecharPopup()
    }
})

pratos.forEach(prato => {
    prato.addEventListener("mousedown", abrirPopup)
});

x.addEventListener("mousedown", fecharPopup)

carrinhobtn.addEventListener("mousedown", abrirfecharCarrinho)

overlayCarrinho.addEventListener("click", fecharCarrinhoFora)


