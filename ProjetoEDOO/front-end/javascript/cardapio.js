// Inicializando variaveis
let overlay = document.getElementById("overlayPopup")
let pratos = document.querySelectorAll(".prato")
let x = document.getElementById("x")
let carrinhobtn = document.getElementById("carrinhoIcon")
let carrinho = document.querySelector(".carrinho")
let overlayCarrinho = document.getElementById("overlayCarrinho")




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

carrinhobtn.addEventListener("mousedown", abrirCarrinho)

overlayCarrinho.addEventListener("click", fecharCarrinhoFora)


