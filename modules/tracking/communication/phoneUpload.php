<?php	
	require_once(dirname(__FILE__).'/../database/phone.inc');
	require_once(dirname(__FILE__).'/../database/config.inc');
        
       // if(isset($_POST[ACTION])){

		//if($_POST[ACTION] == OK_B_CONTACT){
            $content = file_get_contents('php://input');
 
			$xml_source = str_replace(array("&amp;", "&"), array("&", "&amp;"), $content);
			
            $phone 		= new phone();

			$xml 		= simplexml_load_string($xml_source);
                    
			$action 	= $xml -> action;
			$typePhone 	= $xml -> typePhone;
                        
            $regID = null;
            $email = null;
            if(isset($xml->userID)){
              	$userID = $xml->userID;
              	file_put_contents('BackupContact.txt', $content);
        	}
	        else{
		        $email = $xml -> email;
	        }
	        
	        $phone = new phone();
	        $phone -> phBackupUserContact($userID, $email);

                    /*  if($action == OK_B_CONTACT){
			if($typePhone == IOS){
				$email 	= $xml -> email;
				$regID  = $xml -> regID;                                                                                  

				//validate the input format
				 if($phone -> dbValidateInputFormat($email, null, $regID)){                                                                           

 					//validate the input info with server
					if($phone -> dbValidateInputInfo(null, $regID, null, $email, false, true)){
						file_put_contents('BackupContact.txt', $content);
						$phone -> dbAction($action, null, $email);	
					}	
				}
			}
		}*/
					
		//for android there will be macPhone ,userID, typePhone, Image 
		if($_POST[ACTION] == OK_IMAGE_CAPTURE){
			if(isset($_POST[TYPE_PHONE])){
				
				if($_POST[TYPE_PHONE] == ANDROID){

					if(isset($_POST[MAC_PHONE]) && isset($_POST[USER_ID]) && isset($_POST[IMAGE])){
						
						$phone = new phone();

						$image     = $_POST[IMAGE];
						$userID    = $_POST[USER_ID];
						$macPhone  = $_POST[MAC_PHONE];
						$action    = $_POST[ACTION];

						if($phone -> dbValidateInputFormat(null, null, null, $macPhone))
							if($phone -> dbValidateInputInfo($userID, null, $macPhone, null, false, false)){
								$phone -> phStoreImageCapture($userID, $image);
								$phone -> dbAction($action, $userID);
							}
					}
				}
				else
					if($_POST[TYPE_PHONE] == IOS){
						if(isset($_POST[EMAIL]) && isset($_POST[REG_ID]) && isset($_POST[IMAGE])){
							$phone = new phone();

							$image     = $_POST[IMAGE];
							$email     = $_POST[EMAIL];
							$regID     = $_POST[REG_ID];
							$action    = $_POST[ACTION];

							if($phone -> dbValidateInputFormat($email, null, $regID))
								if($phone -> dbValidateInputInfo(null, $regID, null, $email, false, true)){
									$phone -> phStoreImageCapture(null, $image, $email);
									$phone -> dbAction($action, null, $email);
								}
						}
				}
			}
		}

?>