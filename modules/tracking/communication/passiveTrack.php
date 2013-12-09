<?php
	require_once(dirname(__FILE__).'/../database/phone.inc');
	require_once(dirname(__FILE__).'/../database/config.inc');

	if(isset($_POST[ACTION])){
		
		$phone = new phone();
		if($_POST[ACTION] == PASSIVE_TRACK){
			if(isset($_POST[TYPE_PHONE])){
				if($_POST[TYPE_PHONE] == ANDROID){
					if(isset($_POST[USER_ID])   && 
					   isset($_POST[MAC_PHONE]) &&
					   isset($_POST[LAT])       &&
					   isset($_POST[LONG])      &&
					   isset($_POST[ACC])       &&
					   isset($_POST[BAT])		&&
					   isset($_POST[DATE_CREATE])){
						
						$userID     = $_POST[USER_ID];
						$macPhone 	= $_POST[MAC_PHONE];
						$dateCreate = $_POST[DATE_CREATE];
						$lat        = $_POST[LAT];
						$long       = $_POST[LONG];
						$acc        = $_POST[ACC];
						$bat        = $_POST[BAT]; 
						$action 	= $_POST[ACTION];

						if($phone -> dbValidateInputFormat(null, null, null, $macPhone, $dateCreate, $lat, $long, $bat, $acc)){
							if($phone -> dbValidateInputInfo($userID, null, $macPhone, null, false, false)){
								
								$phone -> phPassiveTrackAction($macPhone, $regID, $dateCreate, $lat, $long, $bat, $acc, $userID);
							}
						}
					}
				}
			}
		}

		if($_POST[ACTION] == UPLOAD_IMAGE_PASSIVE_TRACK){ 
			if(isset($_POST[TYPE_PHONE])){
				if($_POST[TYPE_PHONE] == ANDROID){
					if(isset($_POST[USER_ID]) &&
					   isset($_POST[MAC_PHONE]) &&
					   isset($_POST[IMAGE1]) &&
					   isset($_POST[IMAGE2])){
					   	
					   	$macPhone = $_POST[MAC_PHONE];
					    $userID   = $_POST[USER_ID];
					    $image1   = $_POST[IMAGE1];
					    $image2   = $_POST[IMAGE2];

						if($phone -> dbValidateInputFormat(null, null, null, $macPhone)){
							if($phone -> dbValidateInputInfo($userID, null, $macPhone, null, false, false)){
								file_put_contents('test.txt', 'go here');
								$phone -> phUploadPassiveTrackImageAction($userID, $image1, $image2);
							}
						}
					}
				}
			}
		}
	}
?>