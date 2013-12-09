<?php
	/*
		@handle inner action from browser
		@display the data to browser also
	*/
	require_once(dirname(__FILE__).'/../database/browser.inc');
	require_once(dirname(__FILE__).'/../database/protag.inc');
	require_once(dirname(__FILE__).'/../database/config.inc');

	function retrievePhoneList($hashUserID, $email){

		//initiate instance of class browser
		$br = new browser();

		if($br -> brCheckSession($hashUserID, $email)){
			
			$dataRetrieve = array();
			$listReg      = array();

			if($listRegIDAndTypePhone = $br -> brRetrieveRegIDList($hashUserID)){

	            //retrieve the typePhone inside the list and return to user
	            foreach($listRegIDAndTypePhone as $data){
	            	if($data[PHONE_NAME] =='')
	            		$data[PHONE_NAME] = $data[TYPE_PHONE];

	            	array_push($dataRetrieve, array($data[TYPE_PHONE], $data[PHONE_NAME]));
	            	array_push($listReg, $data[REG_ID]); 

	            }        
			}
			//display
	        jsonDisplay(true, $dataRetrieve);
	        $_SESSION[REG_ID] = $listReg;
	        return true;
		}
		jsonDisplay(false);		
		return false;
	}

	function phoneRemove($hashUserID, $email, $message, $regID){
		//initiate instance of class browser
		$br = new browser();

		if(is_numeric($message)){
			if($br -> brRemovePhone($hashUserID, $regID[$message])){
					            	
				jsonDisplay(true);
				return true;
			}
		}

		jsonDisplay(false);
		return false;
	} 

	function retrieveImage($hashUserID, $email){
		
		//initiate instance of class browser
		$br = new browser();
		
		
		if($br -> brCheckSession($hashUserID, $email)){
			
			$br ->  brRetrieveUserImageCapture($hashUserID);	
			
		}
		else
			jsonDisplay(false);
	}

	function retrieveProfile($hashUserID, $email){
		//initiate instance of class browser
		$br = new browser();
		
		
		if($br -> brCheckSession($hashUserID, $email)){
			
			jsonDisplay(true, $email);	
			
		}
		else
			jsonDisplay(false);
	}

	function saveProfile($hashUserID, $email, $message){
		
		$decode    = explode('_', $message);

		//initiate instance of class browser
		$br = new browser();

		if($br -> brCheckSession($hashUserID, $email)){
			
			if(!is_null($decode[0]) && !is_null($decode[1])){

				$oldPass = $decode[0];
				$newPass = $decode[1];

				if($br -> brValidateOldPassword($oldPass, $email)){
					//drupal reset password
					//have to do that because we also login to drupal
					$user     = user_load_by_name($email);
					$uid      = $user->uid;

					$account = user_load($uid);
					$pass    = array('pass' => $newPass);

					user_save($account, $pass);

					$br -> brUpdateNewPassword($newPass, $email);

					jsonDisplay(true);
				}
			}
			else{
				jsonDisplay(false);
			}		
		}
		else
			jsonDisplay(false);
		
	}

	function retrieveProtag($hashUserID, $email){

		//initialize the variables
		$br = new browser();
		$pr = new protag();

		if($br -> brCheckSession($hashUserID, $email)){
			
			$pr -> prRetrieveProtagInformation($hashUserID);
		}
		else
			jsonDisplay(false);
	}

	function retrieveLostReport($mac_ad){
		$br = new browser();
		$pr = new protag();

		if($pr-> prRetrieveProtagLostReport($mac_ad)){
			$pr-> prRetrieveProtagLostReport($mac_ad);
		}
		else
			jsonDisplay(false);
	}

	function savePhoneName($hashUserID, $email, $message, $regIDList){
		$br = new browser();
		if($br -> brCheckSession($hashUserID, $email)){
			$decode    = explode('_', $message);

			$regID     = $regIDList[$decode[0]];
			
			$phoneName = $decode[1];

			//jsonDisplay(true, $phoneName);
			$br -> brUpdatePhoneName($regID, $phoneName);
		}
		else
			jsonDisplay(false);
	}

	function jsonDisplay($success, $data = null){
		$arr = array();
		
		if(!$success)
			$arr = array('status' => array('status' => 'fail', 'code' => '100'));
		else
			if(is_null($data)){
				$arr = array('status' => array('status' => 'success', 'code' => '200'));
			}
		else
			$arr = array('status' => array('status' => 'success', 'code' => '200'), 'data' => $data);

		$json = array();
		$json = json_encode($arr);
		
		header('Content-Type: application/json; charset=utf-8');
		echo $json;
	}
?>