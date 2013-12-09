<?php

	require_once('helperFunctions.php');

	function update_android_registration_id(){
		if(!isset($_POST['mac_ad']) || !isset($_POST['reg_id'])){
			respondToClient(401);
		} else {
			$mac_ad = $_POST['mac_ad'];

			$reg_id = $_POST['reg_id'];
	
			$phone = new phone();
	
			if ($phone -> phUpdateAndroidRegistrationID($mac_ad, $reg_id)) {
				respondToClient(200);
			} else {
				respondToClient(400);
			}
		}
		
		

	}

	update_android_registration_id();

?>