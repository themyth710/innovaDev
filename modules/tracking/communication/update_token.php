<?php
	require_once('helperFunctions.php');
	function update_ios_notification_token(){		if(!isset($_POST['reg_id']) || !isset($_POST['device_token'])){			$reg_id = $_POST['reg_id'];			$token = $_POST['device_token'];				$phone = new phone();				if ($phone -> phUpdateiOSNotificationToken($reg_id, $token)) {				respondToClient(200);			} else {				respondToClient(400);			}		} else {			respondToClient(400);		}
	}
	update_ios_notification_token();
?>