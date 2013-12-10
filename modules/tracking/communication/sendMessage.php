<?php
	/*===========================================================
		@this file is only used to send request from server to phone
		@for android side only
		@also updathe notification for user for both android and ios
	=============================================================*/

	require_once(dirname(__FILE__).'/../database/browser.inc');
	require_once(dirname(__FILE__).'/../database/config.inc');

	function sendMessage($action, $message, $hashUserID, $email, $regIDList){
		$browser       = new browser();

		if($browser -> brCheckSession($hashUserID, $email)){
			
			$decode = explode('_', $message);
			$regID  = null;
			$typePhone = null;

			if(is_numeric($decode[0])){
				$regID = $regIDList[$decode[0]];
				$typePhone = $decode[1];
			}

			$userID = $browser -> brRetrieveUserID($hashUserID);

			$messageSend        = $userID.'_'.$action;
			
			if($action == LOCK){
				$password       = $decode[2];
				$stringRemove   = $decode[0].'_'.$decode[1].'_'.$decode[2].'_';
				$messageToUser  = str_replace($stringRemove,'', $message);

				$messageSend   .= '_'.$password.'_'.$messageToUser;
			}else if($action == IMAGE_CAPTURE){
				$imgNum         = $decode[2];

				if($typePhone==ANDROID){
					$messageSend   .= '_'.$imgNum;
				}else if($typePhone==IOS){
					$messageSend = $decode[3];
				}

				$browser -> brUpdateImageNum($userID, $imgNum);
			}else if($action == TEST_TRACK && $typePhone == IOS){
				$messageSend = MSG_IOS_TEST_TRACK;
			}   
			        
			$browser -> brSendMessage($typePhone, $messageSend, $regID, $userID, $action);
		}
		
	}

	function json($success, $data = null){
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
		
		header('Content-Type: application/json');
		echo $json;
	}

?>