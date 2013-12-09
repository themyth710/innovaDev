<?php
	require_once('helperFunctions.php');
	function protagFound(){
		if(!isset($_POST['mac_ad'])){
			trackingRespond(400);
		} else {
			$mac_addr = $_POST['mac_ad'];
			$protag = new protag();
			if ($protag -> prProtagFound($mac_addr)) {
				respondToClient(200);
			} else {
				respondToClient(400);
			}
		}
	}
	protagFound();
?>