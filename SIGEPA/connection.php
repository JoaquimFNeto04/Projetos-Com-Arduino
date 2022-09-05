<?php
	try {
		
		$HOST = "mysql08.redehost.com.br";
		$BANCO = "bdcbtu";
		$USUARIO = "bdgrupo2g";
		$SENHA = "Laercio@160383";
		
		$PDO = new PDO("mysql:host=" . $HOST . ";dbname=" . $BANCO . ";charset=utf8", $USUARIO, $SENHA);
		//echo "Conexão efetuada com sucesso" ;
		
	} catch (PDOException $erro){
		
		//echo "Erro ao conectar com Banco de Dados, Detalhes: " . $erro->getMessage();
		//echo  date()  ;
	}


?>