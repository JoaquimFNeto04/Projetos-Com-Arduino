<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="refresh" content="15">
	
	<meta charset = "utf-8">
	<title>.: GRUPO G2 TECNOLOGIA :.</title>
</head>
<body>
	<form action="" method="POST">
		<input type="date" name="data">
		<input type="submit" name="enviar" value="Buscar"> 
	</form>

	<?php 
		include ('connection.php');

		if($_SERVER['REQUEST_METHOD']=='POST'){
			$dataPesquisa = $_POST['data'];

			$dataArray = explode("-" , $dataPesquisa);
			$dataPesquisa = $dataArray[0] . "-" . $dataArray[1] . "-" . $dataArray[2];

			$sql ="SELECT * FROM tblpassageiros WHERE data_hora LIKE '%" . $dataPesquisa . "%'";
			//echo $dataPesquisa;
		}	else {

			$dataAtual = date('Y-m-d');

			//echo $dataAtual;

			$sql ="SELECT * FROM tblpassageiros WHERE data_hora LIKE '%" . $dataAtual . "%'";

		}

		$stmt = $PDO->prepare($sql);
		$stmt->execute();

		echo "<br>";
		echo "<br>";
		echo "<br>";
		echo "<br>";
		echo "<table border=\"1\">";

		echo "<tr><th> ID PASSAGEIRO </th> <th> QUANTIDADE </th> <th> ESTAÇÃO </th> <th> CATRACA </th> <th> DATA </th></tr> ";

		while ($linha = $stmt->fetch(PDO::FETCH_OBJ)) {

			$timestamp = strtotime($linha->data_hora);
			$dataTabela= date('d/m/Y H:i:s' , $timestamp);

			echo "<tr>";
			echo "<td>" . $linha->idpassageiros . "</td>";
			echo "<td>" . $linha->quantidade . "</td>";
			echo "<td>" . $linha->estacao . "</td>";
			echo "<td>" . $linha->catraca . "</td>";
			echo "<td>" . $dataTabela . "</td>";
			echo "</tr>";
			
		}


		echo "</table>";
	?>

</body>
</html>