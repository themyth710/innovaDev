<?php
	require_once(dirname(__FILE__).'/../database/phone.inc');
	require_once(dirname(__FILE__).'/../database/config.inc');
	file_put_contents('test2.txt', 'go here');
	if(isset($_POST[ACTION])){
		
		$phone = new phone();

		if($_POST[ACTION] == REGISTER){

			if(isset($_POST[EMAIL]) &&
			   isset($_POST[PASSWORD]) &&
			   isset($_POST[DATE_CREATE])){

				$email     = $_POST[EMAIL];
				$password  = $_POST[PASSWORD];
				$dateCreate= $_POST[DATE_CREATE];

				//validate the input format
				if($phone -> dbValidateInputFormat($email, $password, null, null, $dateCreate)){
					$phone -> phPhoneRegister($email, $password, $dateCreate);
				}
			}
		}
		else if($_POST[ACTION] == LOGIN){
			if(isset($_POST[TYPE_PHONE]) &&
			   isset($_POST[EMAIL]) &&
			   isset($_POST[PASSWORD])){
			   
			   	$typePhone = $_POST[TYPE_PHONE];
			   	$email     = $_POST[EMAIL];
				$password  = $_POST[PASSWORD];
			   
				//check the input format
				if($phone -> dbValidateInputFormat($email, $password)){
					$phone -> phPhoneLogin($email, $password, null, null, null, $typePhone);
				}
			}
		}

		else if($_POST[ACTION] == SEND_REGID){
			if(isset($_POST[TYPE_PHONE])){
				$typePhone = $_POST[TYPE_PHONE];
				
				if(isset($_POST[USER_ID]) &&
				isset($_POST[REG_ID]) &&
				($typePhone == IOS || isset($_POST[MAC_PHONE])) &&
				isset($_POST[DATE_CREATE])){
					$userID    = $_POST[USER_ID];
					$regID 	   = $_POST[REG_ID];
					//Only Android requires macPhone;
					$macPhone  = null;
					if($typePhone == ANDROID){
						$macPhone  = $_POST[MAC_PHONE];
					}
					$dateCreate = $_POST[DATE_CREATE];
				
					//check the input format
					if($phone -> dbValidateInputFormat(null ,null, $regID, $macPhone, $dateCreate)){
						$phone -> phPhoneLogin(null, null, $regID , $macPhone , $dateCreate , $typePhone , $userID);
					}
				}
			}
		}

		else if($_POST[ACTION] == OK_TRACK || $_POST[ACTION] == OK_LOCK || $_POST[ACTION] == OK_B_CONTACT){
			if(isset($_POST[TYPE_PHONE])){
				if($_POST[TYPE_PHONE] == IOS){
					if(isset($_POST[EMAIL]) && isset($_POST[REG_ID])){

						$action = $_POST[ACTION];
						$email  = $_POST[EMAIL];
						$regID  = $_POST[REG_ID];
						
						//validate the input format
						if($phone -> dbValidateInputFormat($email, null, $regID)){
							//validate the input info with server
							if($phone -> dbValidateInputInfo(null, $regID, null, $email, false, true))
								$phone -> dbAction($action, null, $email);
								
						}
					}
				}
				else if($_POST[TYPE_PHONE] == ANDROID){
					if(isset($_POST[USER_ID]) && isset($_POST[MAC_PHONE])){
						
						$action   = $_POST[ACTION];
						$macPhone = $_POST[MAC_PHONE];
						$userID   = $_POST[USER_ID];

						//validate the input format
						if($phone -> dbValidateInputFormat(null, null, null, $macPhone)){
							//validate the input info with server
							if($phone -> dbValidateInputInfo($userID, null, $macPhone, null, false, false)){
								$phone -> dbAction($action, $userID);
							}
						}
					}
				}
				else
					exit(ACCESS_DENIED);
			}
		}

		else if($_POST[ACTION] == SEND_TRACK_DATA){
			if(isset($_POST[TYPE_PHONE])){
				if($_POST[TYPE_PHONE] == IOS){
					if(isset($_POST[EMAIL])  && 
					   isset($_POST[REG_ID]) &&
					   isset($_POST[LAT])    &&
					   isset($_POST[LONG])   &&
					   isset($_POST[ACC])    &&
					   isset($_POST[BAT])	 &&
					   isset($_POST[DATE_CREATE])){
					   
						$action 	= $_POST[ACTION];
						$email      = $_POST[EMAIL];
						$regID 	    = $_POST[REG_ID];
						$dateCreate = $_POST[DATE_CREATE];
						$lat        = $_POST[LAT];
						$long       = $_POST[LONG];
						$acc        = $_POST[ACC];
						$bat        = $_POST[BAT]; 

						if($phone -> dbValidateInputFormat($email, null, $regID, null, $dateCreate, $lat, $long, $bat, $acc)){
							if($phone -> dbValidateInputInfo(null, $regID, null, $email, false, true)){
								
								$phone -> dbAction($action, null, $email);
								$phone -> phUpdatePhoneLocation(null, $regID, $lat, $long, $acc, $bat, $dateCreate);
							}
						}
						
						
					}
					
				}
				else if($_POST[TYPE_PHONE] == ANDROID){
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
								$phone -> dbAction($action, $userID);
								$phone -> phUpdatePhoneLocation($macPhone, null, $lat, $long, $acc, $bat);
							}
						}
					}
				}
				else
					exit(ACCESS_DENIED);
			}
		}
		else if($_POST[ACTION] == SEND_IOS_NOTI_TOKEN){
			if(isset($_POST[REG_ID])	&&
			   isset($_POST[IOS_NOTI_TOKEN])){
			   
			   	$regID = $_POST[REG_ID];
			   	$token = $_POST[IOS_NOTI_TOKEN];
			   	
			   	if($phone -> dbValidateInputFormat(null, null, $regID, null, null, null, null, null, null)){
			   		$phone -> phUpdateNotificationTokenForiOS($regID, $token);
			   	}			   
			}
		}
		else if($_POST[ACTION] == LAST_FLARE){
			if(isset($_POST[TYPE_PHONE])){
				if($_POST[TYPE_PHONE] == ANDROID){
					if(isset($_POST[USER_ID])  && 
					   isset($_POST[MAC_PHONE]) &&
					   isset($_POST[LAT])    &&
					   isset($_POST[LONG])   &&
					   isset($_POST[ACC])    &&
					   isset($_POST[BAT])	 &&
					   isset($_POST[DATE_CREATE])){
					   	
						$action 	= $_POST[ACTION];
						$userID     = $_POST[USER_ID];
						$macPhone 	= $_POST[MAC_PHONE];
						$dateCreate = $_POST[DATE_CREATE];
						$lat        = $_POST[LAT];
						$long       = $_POST[LONG];
						$acc        = $_POST[ACC];
						$bat        = $_POST[BAT]; 
						file_put_contents('test2.txt', $lat);
						$phone -> phLastFlareAction($userID, $lat, $long, $acc, $dateCreate);
					}
				}
			}
		}
	}
?>