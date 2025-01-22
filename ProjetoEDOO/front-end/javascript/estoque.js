

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