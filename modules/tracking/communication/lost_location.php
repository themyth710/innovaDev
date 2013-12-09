<?php
	require_once('helperFunctions.php');
	function reportLostProtagLocation(){
		//echo "post data is ".print_r($_POST, TRUE);
		//echo "post data length ist: ". sizeof($_POST);
		//$devices = $_POST['devices'];
		//echo "devices length ist: ".sizeof($devices);
		//echo "devices 0 length ist: ".$devices[0];
		$data= json_decode(file_get_contents("php://input"),TRUE);
		//echo "data is ".print_r($dataarray, TRUE);
		//respondToClient(400);
		if(!isset($data['devices'])){
			respondToClient(400);
		} else {
			$devices = $data['devices'];
			//$devices = array();
			//array_push($devices, $_POST);
			$final_result = TRUE;
			foreach ($devices as $device) {
				$mac_addr = $device['mac_ad'];
				$latitude = $device['latitude'];
				$longitude = $device['longitude'];
				$protag = new protag();
				$phone = new phone();
				$result = $protag -> prUpdateProtagLocation($mac_addr, $latitude, $longitude);
				if ($result) {
					//send_email_notification($mac_addr, 0);
					$owner_id = $protag -> prRetrieveProtagOwnerId($mac_addr);
					if($owner_id){
						$ios_tokens = $phone -> phRetrieveiOSNotificationTokenViaUserId($owner_id);
						$android_tokens = $phone -> phRetrieveAndroidRegistrationIdsViaUserId($owner_id);
						$protag_name = $protag -> prRetrieveProtagName($mac_addr);
						$message = "Your lost protag ". $protag_name ."'s location has been updated!";
						foreach ($ios_tokens as $token) {
							ios_push_notification($token, $message);
						}
						//android_push_notification($android_tokens, $message);
					}
				} else {
					$final_result = FALSE;
				}
			}
			
			if($final_result){
				respondToClient(200);
			} else {
				respondToClient(400);
			}
		}
	}
	
	reportLostProtagLocation();
?>