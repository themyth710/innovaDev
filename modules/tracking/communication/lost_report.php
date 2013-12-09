<?php
	require_once('helperFunctions.php');
	function createLostReport(){
		if(!isset($_POST['message']) || !isset($_POST['mac_ad']) || !isset($_POST['contact_name']) || !isset($_POST['contact_number']) || !isset($_POST['description'])){
			respondToClient(400);
			echo "parameter incorrect!";
		} else {
			
			$message = $_POST['message'];
			$location = $_POST['location'];
			if(!isset($_POST['will_notify'])){
				$will_notify = FALSE;
			} else if($_POST['will_notify']){
				$will_notify = true;
			} else {
				$will_notify = false;
			}
			$mac_addr = $_POST['mac_ad'];
			$contact_name = $_POST['contact_name'];
			$contact_number = $_POST['contact_number'];
			$description = $_POST['description'];
			$protag = new protag();
			
			$result = $protag -> prReportLost($location, $message, $will_notify, $mac_addr, $contact_name, $contact_number, $description);
			if ($result) {
				trackingRespond(200);
			} else {
				respondToClient(400,array('reason' => mysql_error()));
			}
		}
	}
	createLostReport();
?>