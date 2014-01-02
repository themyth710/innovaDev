<?php
	require_once('helperFunctions.php');
	function deleteProtag(){
		if(!isset($_POST['mac_ad'])){
			respondToClient(400);
		} else {
			$mac_addr = $_POST['mac_ad'];
			$protag = new protag();
			$result = $protag -> prDeleteProtag($mac_addr);
			if ($result) {
				respondToClient(200);
			} else {
				respondToClient(400);
			}
		}
	}
	deleteProtag();
?>