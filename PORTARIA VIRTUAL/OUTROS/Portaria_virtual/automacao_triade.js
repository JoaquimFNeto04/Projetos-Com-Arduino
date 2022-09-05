funcionar AlteraRele1 () {
    var estado = document.getElementById ( "estado") innerHTML.;
    if (estado === "0") {
        . Document.getElementById ( "estado") innerHTML = "1";
        . Document.getElementById ( "rele") innerHTML = "<div class = 'rele1_ligado"> </ div> ";
		document.getElementById ( "botao") innerHTML = "<a href='/?desligar' class='botao'> Desliga </a>.";
    } outro {
        . Document.getElementById ( "estado") innerHTML = "0";
        . Document.getElementById ( "rele") innerHTML = "<div class = 'rele1_desligado"> </ div> ";
        document.getElementById ( "botao") innerHTML = "<a href='/?ligar' class='botao'> Liga </a>.";
    }
}

funcionar AlteraRele2 () {
    var estado_2 = document.getElementById ( "estado_2") innerHTML.;
    Se (estado_2 === "0") {
        . Document.getElementById ( "estado_2") innerHTML = "1";
        . Document.getElementById ( "rele_2") innerHTML = "<div class = 'rele2_ligado"> </ div> ";
		. Document.getElementById ( "botao_2") innerHTML = "<a href='/?2_desligar' class='botao_2'> Desliga </a>";
    } outro {
        . Document.getElementById ( "estado_2") InnerHTML = "0";
        . Document.getElementById ( "rele_2") innerHTML = "<div class = 'rele2_desligado"> </ div> ";
        . Document.getElementById ( "botao_2") innerHTML = "<a href='/?2_ligar' class='botao_2'> Liga </a>";
    }
}
 