<?php

	/*=====================================================
		@this file is used to implement functions in browser
	======================================================*/
	require_once 'db_functions.inc';
    require_once 'activityLog.inc';
    
	class browser extends DB_Functions{

		/*==================================
	   		@constructor
	   	==================================*/
	   	function __construct() {
	   		//re-initiate all variables
        	$this -> hash     = new hash();
            $this -> validate = new validate();
            $this -> retrieve = new dataRetrieve();
            $this -> store    = new dataStore();
            $this -> display  = new dataDisplay();
            $this -> update   = new dataUpdate();
            $this -> send     = new dataSend();
	    }
	
    	/*==================================
    		@destructor
    	==================================*/
    	function __destruct() {

    	}

    	/*================================================================================================

            @this function is used for client browser to retrieve list of register id to send back to user
            @param string hashID 
            @return an array of regID according to this format: [0] => ([regID] => '',[typePhone] => '')

        ================================================================================================*/
        public function brRetrieveRegIDList($hashUserID){
           
            if($userID = $this -> retrieve -> retrieveUserID(null, $hashUserID)){

                //retrieve list mac phone from android phone user table
                $andrMacPhoneList = $this -> retrieve -> retrieveMacPhoneOrRegIDFromPhoneUserTableUsingUserID($userID, true);

                //retrieve list of regID from IOS user table
                $iOSRegID  = $this -> retrieve -> retrieveMacPhoneOrRegIDFromPhoneUserTableUsingUserID($userID, false);
       
                //retrieve list of reg ID from list of macphone according to phone information table
                $andrRegID = $this -> retrieve -> retrieveRegIDFromMacPhoneList($andrMacPhoneList);

                //array of data to return
                $sendBackData = array();

                //push the list regID of iosPhone to array
                foreach($iOSRegID as $key){
                    $phoneName = $this -> retrieve -> retrievePhoneName($key);
                    $phoneLost = $this -> retrieve -> retrievePhoneLostNotification($key);
                    $data      = array(REG_ID => $key, TYPE_PHONE => IOS, PHONE_NAME => $phoneName, PHONE_LOST_NOTI => $phoneLost);
                    
                    array_push($sendBackData, $data);
                }

                //push the list regID of android phone to array
                foreach ($andrRegID as $key) {
                     $phoneName = $this -> retrieve -> retrievePhoneName($key);
                     $phoneLost = $this -> retrieve -> retrievePhoneLostNotification($key);
                     $data = array(REG_ID => $key, TYPE_PHONE => ANDROID, PHONE_NAME => $phoneName, PHONE_LOST_NOTI => $phoneLost);

                     array_push($sendBackData, $data);
                }
                
                //return the list of regId and typephone
                return $sendBackData; 
            }
            else
            	return false;
        }

        /*===================================================================

        	@store password token when user required to reset their password

        ===================================================================*/
        public function brStorePasswordToken($email){
           
        	if($userID = $this -> retrieve -> retrieveUserID($email)){
        		
        		$token = $this -> hash -> hashData($email.time());
        		$dateTime = date('Y-m-d h:i:s', time());

        		$this  -> update -> updateHashData($token, USERS_PASSWORD_HANDLE_TABLE, USERS_PASSWORD_TOKEN_COL, USERS_PASSWORD_ID_COL, $userID);
        		$this  -> update -> updateHashData($dateTime, USERS_PASSWORD_HANDLE_TABLE, USERS_PASSWORD_TOKEN_DATE_COL, USERS_PASSWORD_ID_COL, $userID);

        		return $token;
        	}
        	else
        		return false;
        }

        /*============================================
        	@handle the submit token to server
        	@this function only used for password reset 
        ==============================================*/
        public function brTokenSubmit($token){
        	
        	if($list = $this -> retrieve -> retrieveUserIDUsingToken($token)){
        		//return the user ID
        		$userID = $list[0];

        		//return the date
        		$date   = $list[1];

        		//check if the current time and the time that user press reset password does not exceed 1 day
        		if($this -> validate -> isDateExceed($date)){
        			//destroy the token
        			//$this -> brDestroyToken($userID);
        			//if it exceed 1 day
        			return false;
        		}
        		else{
                    $email = $this -> retrieve -> retrieveEmaiUsingUserID($userID);
                    return $email;
                }
        	}
        	else
        		return false;
        }

        /*===================================

        	@update the new password for user

        ===================================*/
        public function brUpdateNewPassword($password, $email){

        	//hash the password
        	$hashPassword = $this -> hash -> hashData($password);

        	//update the data
        	$this -> update -> updateHashData($hashPassword, USERS_INFORMATION_TABLE, USER_INFO_PASSWORD_COL, USER_INFO_EMAIL_COL, $email);
        }

         /*=======================================================================================

            @perform all the client data checking steps
            @this function user long polling for polling data from server
            @depends on the action and the typePhone, the time poll from server will be different

        =======================================================================================*/
        public function brNotificationClientCheck($action, $hashUserID, $typePhone, $regID, $timeOut, $restart, $expectedData = null){
            
            $times = 0;
            $data  = 0;

            $imageEncode = null;
            //retrieve the user ID from hash user ID
            //because client send data to server with hash usr ID therefore we need to restore the userId for user first
            if($userID = $this -> retrieve -> retrieveUserID(null, $hashUserID)){

                //if the action is track, lock, backup (the track here is: current data is 0, we wait for change to 1)
                if($action == TRACK || $action == LOCK || $action == BACKUP_CONTACT || $action == IMAGE_CAPTURE){
                    //count times and wait until the data change to 1
                    while($times < $timeOut && $data == 0){

                        //retrieve the column notification value depend on the userId and action
                        $data = $this -> retrieve -> retrieveNotification($userID, $action);

                        //if data still , wait until $restart second and the poll server again
                        if($data == 0){
                            flush();

                            //increase the time so we can set time out for this while
                            $times ++;

                            //wait for $restart milisecond
                            sleep($restart);
                        }
                        else{
                            if($action == IMAGE_CAPTURE){
                                if(!$imageEncode = $this -> brEncodeImage($userID, $expectedData))
                                    return false;
                                else
                                    //$this -> display -> displayJSON('SUCCESS', null, $imageEncode);
                                    return true;
                            }

                            //if the data is 1 then we need to send back the data
                            $this -> display -> displayJSON('SUCCESS', null, $data);
                            return true;
                        }
                    }
                }

                //if the action is start_track (current: 1 -> wait until 2)
                else if($action == START_TRACK){
                    //the data now 1
                    $data = 1;

                    //loop until time out or data change to something
                    while($times < $timeOut && $data == 1){

                        //retieve the notification in track column
                        $data = $this -> retrieve -> retrieveNotification($userID, $action);
                        if($data == 1){
                            
                            //sleep for $restart
                            flush();
                            $times ++;
                            sleep($restart);
                        }
                        else{

                            $this -> display -> displayJSON('SUCCESS', null, $data);
                            return true;
                        } 
                    }
                }

                //continue track happen when the current track value is 2 already
                //we no need to do long polling here
                //this time we do polling only
                else if($action == CONTINUE_TRACK){
                    //retrieve the location of the phone and send back to user
                    $location     = $this -> retrieve -> retrievePhoneLocation($regID);

                    $this -> display -> displayJSON('SUCCESS',null , $location);
                    return true;
                }
                else if($action == TEST_TRACK){
              	    //starts from 0 because does not require OK from phone
                    $data = 0;
                     //count times and wait until the data change to 2
                    while($times < $timeOut && $data == 0){
                        //retrieve the column notification value depend on the userId and action
                        $data = $this -> retrieve -> retrieveNotification($userID, $action);

                        //if data still , wait until $restart second and the poll server again
                        if($data == 0){
                            flush();
                            //increase the time so we can set time out for this while
                            $times ++;
                            //wait for $restart milisecond
                            sleep($restart);
                        }
                        else
                        {
                        	
                            //if data changes due to receiving location update
                       	    //retrieve the location of the phone and send back to user
	                    $location     = $this -> retrieve -> retrievePhoneLocation($regID);

	                    $this -> display -> displayJSON('SUCCESS', null, $location);
	                    return true;
                        }
                    }
                }

                //time out already
                $this -> display -> displayJSON('FAIL', 'TIME_OUT');
                return false;
                //$this -> display -> displayJSON('SUCCESS', null);
            }

            $this -> display -> displayJSON('FAIL');
            return false;
        }

        /*===========================================

            @this fucntion is used in sendmessage.php
            @send command message to the phone

        ===========================================*/
        public function brSendMessage($typePhone, $message, $regID, $userID, $action){
            //update the notification table
            $this -> dbAction($action, $userID, null, $regID);
            
            $logger = new activityLog();
            //if it is android then send the message to the phone
            //if it is ios then just update the notification table only            
            if($typePhone == ANDROID){
                $logger -> addActionToLog($userID,$action);   
                $this -> brSendPhoneRequest($regID, $message);
            }
            else
                if($typePhone == IOS && ($action==TEST_TRACK || $action==IMAGE_CAPTURE)){
                
                    $tempToken = $this -> retrieve -> retrieve_iOS_NotiTokenUsingRegID($regID);
			         
                    if($tempToken!=NULL && $this -> send -> sendiOSNotification($tempToken, $message, $action)){
                        $logger -> addActionToLog($userID,$action);
	                    $this -> display -> displayJSON('SUCCESS');
	                    return true;
	            }
	            else{
	                $this -> display -> displayJSON('FAIL', 'PHONE_REQUEST_SEND_FAIL');
	                return false;
	            }
            }
        }

        /*================================================================

            @because the session only have userID and regID and email
            @we can not use dbValidateInputInfo to check the exist of user 
            @that why we need to create this function for easy checking

        ================================================================*/
        public function brCheckSession($hashUserID, $email){
            //retrieve the hash User ID from dtb
            $realHashUserID = $this -> retrieve -> retrieveUserID($email, null, true);

            //compare it with the current one
            if($hashUserID === $realHashUserID)
                return true;
            else
                return false;
        }

        /*============================
            @remove the phone for user
        ============================*/
        public function brRemovePhone($hashUserID, $regID){
            if($userID = $this -> retrieve -> retrieveUserID(null, $hashUserID)){
                
                if($macPhone = $this -> retrieve -> retrieveMacPhoneUsingRegID($regID)){
                    if($macPhone != '00:00:00:00:00:00'){   //it is a serious bug, for temporary purpose, will need to improve in the future

                        if($userList = $this -> retrieve -> retrieveUserIDFromPhoneUserTable($macPhone)){
                            
                            if($this -> validate -> isUserExistInPhoneUserTable($userList, $userID, true)){

                                $this -> update -> updatePhoneUser(null, $macPhone, null, null, ANDROID_FIRST_USER_ACT_COL, null);
                                return true;
                            }
                            if($this -> validate -> isUserExistInPhoneUserTable($userList, $userID, false, true)){

                                $this -> update -> updatePhoneUser(null, $macPhone, null, null, ANDROID_SECOND_USER_ACT_COL, null);
                                return true;
                            }
                        }
                    }
                    else{  
                        if($userList = $this -> retrieve -> retrieveUserIDFromPhoneUserTable(null, $regID)){

                            if($this -> validate -> isUserExistInPhoneUserTable($userList, $userID, true)){

                                $this -> update -> updatePhoneUser($regID, null, null, null, IOS_FIRST_USER_ACT_COL, null);
                                return true;
                            }
                            if($this -> validate -> isUserExistInPhoneUserTable($userList, $userID, false, true)){

                                $this -> update -> updatePhoneUser($regID, null, null, null, IOS_SECOND_USER_ACT_COL, null);
                                return true;
                            }
                        }
                    }
                }    
            }
            return false;
        }

        public function brRetrieveUserID($hashUserID){
            return $this -> retrieve -> retrieveUserID(null, $hashUserID);

        }

        /*====================================
            @encode image and return to ajax
        =====================================*/
        public function brEncodeImage($userID, $expectedNumPic){

            $fileAddr = '../development/sites/all/modules/tracking/UserRegion/ImageCapture/'.$userID.'_img/pic_'.$expectedNumPic.'.jpg';
 
            if(file_exists($fileAddr)){
               //  $encode = file_get_contents($fileAddr);
                // $data   = base64_encode($encode);
                 $data = $userID.'_img/pic_'.$expectedNumPic.'.jpg';
                 $this -> display -> displayJSON('SUCCESS',null,$data);
                 return true;
            }
            else{
                $this -> display -> displayJSON('FAIL', 'FILE_NOT_EXIST');
                return false;
            }
        }

        public function brRetrieveUserImageCapture($hashUserID){

            if($userID = $this -> retrieve -> retrieveUserID(null, $hashUserID)){
                
                $addr = 'sites/all/modules/tracking/UserRegion/ImageCapture/'.$userID.'_img/';
              
                $files = glob($addr . '*.jpg');
                
                $numImage = 0;

                if ( $files !== false )
                    $numImage = count($files);

                $data = array($userID.'_img/',$numImage);

                //we return both location and number of Image to user
                $this -> display -> displayJSON('SUCCESS', null, $data); 
            }
            else
                $this -> display -> displayJSON('FAIL', 'NO_USER_EXIST');         
        }

        public function brUpdateImageNum($userID, $num){
            $this -> update ->  updateImageNumber($userID, $num);
        }

        /*===================================

            @return the directory in the dtb
        
        ===================================*/
        public function brRetrieveDirectory($hashDir, $folderName){
            return $this -> retrieve -> retrieveDirectory($hashDir, $folderName);
        }

        public function brValidateOldPassword($oldPass, $email){
            if($pass = $this -> retrieve -> retrievePassword($email)){
                if($this -> hash -> compareHashData($oldPass, $pass)){
                    return true;
                }
                else{
                    $this -> display -> displayJSON('FAIL', 'OLD_NEW_PASS_PROB');
                    return false;
                }
            }
        }

        public function brUpdatePhoneName($regID, $phoneName){
            $this -> update -> updatePhoneName($regID, $phoneName);
            
            $this -> display -> displayJSON('SUCCESS');
        }

        /*

        */
        public function brHandleActivationToken($token){
            
            if($this -> validate -> isAccountActivationTokenExist($token)){
                
                if($this -> update -> updateUserActivation($token))
                    return true;
                else
                    return false;
            }

            return false;
        }

        public function brSendActivationToken($email){

            if(!($this -> validate -> isUserActivateTheirAccount($email))){

                //create hash token for user to activate their account
                $token     =  $this -> hash -> hashData($email.time());
                
                if($this -> update -> updateUserToken($token, null, $email)){
                    global $base_url;
                    $params    = array('subject' => 'Account Activation',
                                       'token'   => $base_url.'/activated?token='.$token
                                      );
                    $this      -> send -> sendMail(ACTIVATION_MAIL, $email, $params); 
                }
            }    
            
            return true;
        }

        public function brCheckActivatedUser($email){
            if($this -> validate ->  isUserActivateTheirAccount($email))
                return true;
            else
                return false;
        }
   
        /*=========================================
            @send request to the phone
            @param string $regID, $message
            @return send boolean if it is sent or not
        ===========================================*/
        private function brSendPhoneRequest($regID, $message){

            if($this -> send -> sendPhoneNotification($regID, $message)){
                
                $this -> display -> displayJSON('SUCCESS');
                
                return true;
            }
            else{
                
                $this -> display -> displayJSON('FAIL', 'PHONE_REQUEST_SEND_FAIL');
                
                return false;
            }
        }

        public function brLoadPhoneInfo($regID, $phoneType){

            if($phoneType == IOS){

            }
            else
                if($phoneType == ANDROID){

                    $macAddr = $this -> retrieve -> retrieveMacPhoneUsingRegID($regID);

                    $data    = $this -> retrieve -> retrievePhoneInformation(null, $macAddr);

                    if($data[0] == null){
                        $data[0] = $phoneType;    
                    }

                    if($data[1] == ANDROID_ID){
                        $data[1] = ANDROID;
                    }
                    else{
                        $data[1] = IOS;
                    }

                    if($data[2] == null){
                        $data[2] = 'None';
                    }
                    
                    $data = array('phoneName' => $data[0], 'phoneType' => $data[1], 'imei' => $data[2]);

                    $this -> display -> displayJSON('SUCCESS', null ,  $data);
                }
        }

        public function retrieveActivityList($hashUserID){
        if($userID = $this -> retrieve -> retrieveUserID(null, $hashUserID))
            return $this -> retrieve -> retrieveUserActivity($userID);
        else
            return false;
        }

        public function brRetrieveLostReport($macAddr){
            if(!($data = $this -> retrieve -> retrieveLostReport($macAddr)))
                $this -> display ->displayJSON('FAIL');
            else
                $this -> display -> displayJSON('SUCCESS', null, $data); 
        }

        public function brDownloadBackupFile($userID){
            $csvFile = "../UserRegion/Backup/".$userID.'_contact/backup.csv';
            if(file_exists($csvFile)){
                $fileName = 'yourBackup.csv';
                header("Cache-Control: public");
                header("Content-Description: File Transfer");
                header("Content-Disposition: attachment; filename=$fileName");
                header("Content-Type: text/csv");
                header("Content-Transfer-Encoding: binary");

                readfile($csvFile);    
            }
        }
        /*==========================================

        	@destroy the token by setting it to null
        
        ===========================================*/
        private function brDestroyToken($userID){
        	$this  -> update -> updateHashData(null, USERS_PASSWORD_HANDLE_TABLE, USERS_PASSWORD_TOKEN_COL, USERS_PASSWORD_ID_COL, $userID);
        }
	}
?>