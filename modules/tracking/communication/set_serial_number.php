<?php
	require_once('helperFunctions.php');
	function setProtagSerialNumber(){
		if(!isset($_POST['mac_ad']) || !isset($_POST['value'])){
			respondToClient(400);
		} else {
			$mac_addr = $_POST['mac_ad'];
			$serial_number = $_POST['value'];
			$protag = new protag();
			$result = $protag -> prSetSerialNumber($mac_addr, $serial_number);
			if ($result) {
				respondToClient(200);
			} else {
				respondToClient(400);
			}
		}
	}
	setProtagSerialNumber();
?>