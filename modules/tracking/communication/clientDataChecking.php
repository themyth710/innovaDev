<?php
	require_once(dirname(__FILE__).'/../database/browser.inc');
	require_once(dirname(__FILE__).'/../database/config.inc');

	function retrievePhoneData($action, $userID, $email, $regIDList, $message){

		$browser = new browser();

		//default variables
		$g_iosTimeRestart = 3;
		$g_andrTrackRestart = 3;
		$g_andrRestart = 3;
		$g_timeOut = 10;

		$decode    = explode('_', $message);
		$regID     = null;
		$typePhone = null;
		$curPic    = null;

		if(count($decode) >= 2){
			if(is_numeric($decode[0])){
				$regID     = $regIDList[$decode[0]];
				$typePhone = $decode[1];

				if(!is_null($decode[2]))
					$curPic= $decode[2];
			}
			else{
				jsDisplay(false);
				return false;
			}
		}
		else{
			jsDisplay(false);
			return false;
		} 

		if($browser -> brCheckSession($userID, $email)){
			if($action == TRACK || $action == LOCK || $action == BACKUP_CONTACT || $action == TEST_TRACK){
				if($typePhone == IOS)
					$browser -> brNotificationClientCheck($action, $userID, $typePhone, $regID, $g_timeOut, $g_iosTimeRestart);
				if($typePhone == ANDROID)
					$browser -> brNotificationClientCheck($action, $userID, $typePhone, $regID, $g_timeOut, $g_andrRestart);
			}
			else 
				if($action == START_TRACK){
					if($typePhone == IOS)
						$browser -> brNotificationClientCheck($action, $userID, $typePhone, $regID, $g_timeOut, $g_iosTimeRestart);
					if($typePhone == ANDROID)
						$browser -> brNotificationClientCheck($action, $userID, $typePhone, $regID, $g_timeOut, $g_andrRestart);
			}
			else 
				if($action == CONTINUE_TRACK){
					//retrieve the location to user //maybe every 3s depend on the javscript set interval
					$browser -> brNotificationClientCheck($action, $userID, $typePhone, $regID, null, null);
			}
			else
				if($action == IMAGE_CAPTURE){
					if($typePhone == IOS)
						$browser -> brNotificationClientCheck($action, $userID, $typePhone, $regID, $g_timeOut, $g_iosTimeRestart, $curPic);
					if($typePhone == ANDROID)
						$browser -> brNotificationClientCheck($action, $userID, $typePhone, $regID, $g_timeOut, $g_andrRestart, $curPic);
			}
else
				if($action == BACKUP_CONTACT){
					if($typePhone == IOS)
						$browser -> brNotificationClientCheck($action, $userID, $typePhone, $regID, $g_timeOut, $g_iosTimeRestart);
					if($typePhone == ANDROID)
						$browser -> brNotificationClientCheck($action, $userID, $typePhone, $regID, $g_timeOut, $g_andrRestart);
			}
		}
	}

	function jsDisplay($success, $data = null){
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