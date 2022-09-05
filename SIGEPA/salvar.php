<?php
	
	include('connection.php');
	
	$reg_quantidade = $_GET['quantidade'];
	$reg_estacao = $_GET['estacao'];
	$reg_catraca = $_GET['catraca'];
	
	$sql = "INSERT INTO tblpassageiros (quantidade, estacao, catraca) VALUES (:quantidade, :estacao, :catraca)";
	//$sql = "INSERT INTO tblpassageiros (quantidade, estacao, catraca) VALUES (:quantidade, :estacao, :catraca)";
	
	$stmt = $PDO->prepare($sql);
	
	$stmt->bindParam(':quantidade' , $reg_quantidade);
	$stmt->bindParam(':estacao' , $reg_estacao);
	$stmt->bindParam(':catraca' , $reg_catraca);
	
	if($stmt->execute()) {
		//echo "200 OK \n";
	} else{
		//echo "Erro ao salvar dados \n";
		
		
	}
	


?>