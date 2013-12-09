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
				trackingRespond(200);
			} else {
				trackingRespond(400);
			}
		}
	}
	deleteProtag();
?>