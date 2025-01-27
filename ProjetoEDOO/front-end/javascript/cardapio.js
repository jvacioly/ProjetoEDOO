// Inicializando variaveis
let overlay = document.getElementById("overlayPopup")
let pratos = document.querySelectorAll(".prato")
let x = document.getElementById("x")




// funções
function fecharPopup() {
    overlay.style.display = "none"
    
}

function abrirPopup() {
    overlay.style.display = "flex"
    
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
