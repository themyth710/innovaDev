<?php
	/*
		@this file is used for IOS only
	*/

	require_once(dirname(__FILE__).'/../database/phone.inc');	
	require_once(dirname(__FILE__).'/../database/config.inc');

	if(isset($_POST[EMAIL]) && isset($_POST[REG_ID])){
		
		$phone    = new phone();
		
		$email = $_POST[EMAIL];
		$regID = $_POST[REG_ID];
		
		//validate input format
		if($phone -> dbValidateInputFormat($email, null, $regID)){
			//validate input info
			if($phone -> dbValidateInputInfo(null, $regID, null, $email, false, true))//$userID, $regID, $macPhone, $email ,$isHash, $isIOS
				$phone -> phIOSDataChecking($email, $regID);
		}		
	}
?>