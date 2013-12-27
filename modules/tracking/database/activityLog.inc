<?php

	/*=====================================================
		@this file is used to implement functions in browser
	======================================================*/
	require_once 'db_functions.inc';

	class activityLog extends DB_Functions{

		/*==================================
	   		@constructor
	   	==================================*/
	   	function __construct() {
			//re-initiate all variables
			$this -> retrieve = new dataRetrieve();
			$this -> store    = new dataStore();
			$this -> update   = new dataUpdate();
		}
	
	    	/*==================================
	    		@destructor
	    	==================================*/
	    	function __destruct() {
	
	    	}
	    	
	    	public function addLog($userID,$logNum){
	    		//userID should have been checked prior to using this function
	    		$userActivity = $this -> retrieve -> retrieveUserActivity($userID);  
	    		
	    		if(strlen($userActivity)==0){
	    			//Activity do not exist, create new data

	    			$userActivity = $this -> addDateToLogNum($logNum);

	    			$this-> store -> storeUserActivity($userID,$userActivity);
	    			
	    		}else{
	    			$array = $this -> convertActivityToArray($userActivity);
	    			
	    			//Not more than 30 history
	    			while(count($array)>30){
	    				array_shift($array);
	    			}
	    			array_push($array,$this -> addDateToLogNum($logNum));
	    			
	    			$userActivity = $this -> convertArrayToActivity($array);
	    			
	    			//update existing data
	    			$this-> update -> updateUserActivity($userID,$userActivity);
	    		}
	    	}
	    	
	    	public function addActionToLog($userID, $action){
        		if($logNum = $this -> actionToActivityLogNum($action))
 					$this -> addLog($userID,$logNum);
        	}
        	
	        //Converts action in brSendMessage to logNum for activity list
	        private function actionToActivityLogNum($action){
	        	switch($action){
	        		case START_TRACK:
	        			return ACTIVITY_LOG_START_TRACK;
	        		case STOP_TRACK:
	        			return ACTIVITY_LOG_STOP_TRACK;
	        		case TEST_TRACK:
	        			return ACTIVITY_LOG_TEST_TRACK;
	        		case LOCK:
	        			return ACTIVITY_LOG_LOCK;
	        		case BACKUP_CONTACT:
	        			return ACTIVITY_LOG_BACKUP;
	        		case IMAGE_CAPTURE:
	        			return ACTIVITY_LOG_IMAGE_CAPTURE;
	        		default:
	        			return false;
	        	}
	        }
	    	
	    	//Function used to add date to logNum for storage
	    	private function addDateToLogNum($logNum){
	    		/*
	    		$today = date("F j, Y, g:i a");                 // March 10, 2001, 5:16 pm
			$today = date("m.d.y");                         // 03.10.01
			$today = date("j, n, Y");                       // 10, 3, 2001
			$today = date("Ymd");                           // 20010310
			$today = date('h-i-s, j-m-y, it is w Day');     // 05-16-18, 10-03-01, 1631 1618 6 Satpm01
			$today = date('\i\t \i\s \t\h\e jS \d\a\y.');   // it is the 10th day.
			$today = date("D M j G:i:s T Y");               // Sat Mar 10 17:16:18 MST 2001
			$today = date('H:m:s \m \i\s\ \m\o\n\t\h');     // 17:03:18 m is month
			$today = date("H:i:s");                         // 17:16:18
			$today = date("Y-m-d H:i:s");                   // 2001-03-10 17:16:18 (the MySQL DATETIME format)
	    		*/
	    		$date = date('H:i a Y-m-d');
	    		
	    		$data = $logNum." ".$date;

	    		return $data;
	    	}
	    	
	    	//Converts storage data to an array
	    	private function convertActivityToArray($userActivity){
	    		$array = explode("[]",$userActivity);
	    		return $array;
	    	}
	    	
	    	//Converts array to storage data
	    	private function convertArrayToActivity($array){
	    		//Activity stored in format
			//<log num><space><date and time display><use this [] to seperate other log>
			/*It is better to store everything in one column because it allows reordering of information
			after the max num of logs has been reached, but it requires more processing*/   
			
	    		$sizeOfArray = count($array);

	    		$returnString = "";
	    		
	    		for($i = 0; $i < $sizeOfArray; $i++){
	    		
	    			if($i!=0){
	    				$returnString .= "[]";
	    			}
	    			$returnString .= $array[$i];
	    		}
	    		
	    		return $returnString;
	    	}
    	}
?>