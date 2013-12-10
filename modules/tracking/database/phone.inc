<?php
	require_once 'db_functions.inc';
    $currdir = getcwd();
    chdir($_SERVER['DOCUMENT_ROOT'] . "/development/");
    define('DRUPAL_ROOT', getcwd());
    include_once("./includes/bootstrap.inc");
    drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL, true);
    chdir($currdir);

	class phone extends DB_Functions{

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

        /*=======================================================

            @perform register from phone client
            @step by step implememtation will be conducted below
            @this function is used on phoneDataReceive.php
            
        ========================================================*/
      public function phPhoneRegister($email, $password, $dateCreate){

            //check if email already exist in the database, return false if it is not exist
            if(!($this -> validate -> isEmailExist($email))){
                $this -> phStoreUserInfo($email, $password, $dateCreate);  
                $this -> display -> displayJSON('SUCCESS');                            
            }
            else{
                $this -> display -> displayJSON('FAIL', 'EMAIL_REGISTERED');
            }             
        }	
        /*========================================================

            @perform step by step login for phone into the system

        ========================================================*/
        public function phPhoneLogin($email, $password, $regID, $macPhone, $dateCreate, $typePhone, $userID = null){
            
           //if the email and password is not null
            if(!is_null($email) && !is_null($password)){

                //return the userID from email and password
                //dbClientLoginCheck will display if password mismatch or account does not exist
                if($userID = $this -> dbClientLoginCheck($email, $password)){
                    if($this -> validate -> isUserActivateTheirAccount($email)){
                    	$this -> display -> displayJSON('SUCCESS', null, array('userID' => $userID));
                    }
                    else{
                        $this -> display -> displayJSON('FAIL', 'USER_NOT_ACTIVATE');
                    }
                }
            }
            else{
		if($typePhone == ANDROID){
			//$email and $password will be null here
			//for android only
			//userList will contain ID1, act1, ID2, act2
			if($userList = $this -> retrieve -> retrieveUserIDFromPhoneUserTable($macPhone)){
				//Only if user is in the first column then we reply as true
				if($this -> validate -> isUserExistInPhoneUserTable($userList, $userID, true)){
					//if yes -> update the registration id according to the macphoen
					$this -> update -> updateRegIDForAndroidPhone($macPhone, $regID);
					$this -> display -> displayJSON('SUCCESS');
				}
				else if(!($this -> validate -> isUserExistInPhoneUserTable($userList, null, true))){
					//check if first user column is empty
					//if it is empty, add user to that column and reply as success
					$this -> phStorePhoneUser(null, $macPhone, $typePhone, true, false, null, $userID);  
					$this -> update -> updateRegIDForAndroidPhone($macPhone, $regID);
					$this -> display -> displayJSON('SUCCESS');
				}else{
					//Since userID does not exist as first user in userList
					$this -> display -> displayJSON('FAIL', 'MAX_USER');
				}
	                }
	                else{
	                	//creates row in PHONE_INFORMATION_TABLE
				$this -> phStorePhoneInfo($regID, $macPhone, $dateCreate, $typePhone);
				//Create phone entry and set this user as FirstUser
				//$isFirstUser does not matter, $isStore here is true
				$this -> phStorePhoneUser(null, $macPhone, $typePhone, true, true, null, $userID);
				
				$this -> display -> displayJSON('SUCCESS');
	                }
                }else if($typePhone == IOS){
                	//$email and $password will be null here
                	//retrieveUserIDFromPhoneUserTable($macPhone = null, $regID = null)
                	//userList will contain ID1, act1, ID2, act2
			if($userList = $this -> retrieve -> retrieveUserIDFromPhoneUserTable(null, $regID)){
				//check if the user already has the phone or not
				//isUserExistInPhoneUserTable($userList, $userID, $isFirstUser = false, $isSecondUser = false)
				//Since Phone and user is now 1:1, only the FirstUser is the owner
				if($this -> validate -> isUserExistInPhoneUserTable($userList, $userID, true)){
					//Since userID is already the FirstUser, return success message
					$this -> display -> displayJSON('SUCCESS');
				}else if(!$this -> validate -> isUserExistInPhoneUserTable($userList, null, true)){
					//check if FirstUser is null. If it is, it means that there is no ownership of this phone and it can have a new owner
					//phStorePhoneUser($email, $macPhone, $typePhone, $isFirstUser, $isStore, $regID = null, $userID = null)
					//$isStore is to create the data row
					$this -> phStorePhoneUser(null, null, $typePhone, true, false, $regID, $userID);  
           				$this -> display -> displayJSON('SUCCESS');
				}else{
					//Since userID does not exist as first user in userList
					$this -> display -> displayJSON('FAIL', 'MAX_USER');
				}
			}else{
				//creates row in PHONE_INFORMATION_TABLE
				//phStorePhoneInfo($regID, $macPhone, $dateCreate, $typePhone)
				$this -> phStorePhoneInfo($regID, '00:00:00:00:00:00', $dateCreate, $typePhone);
			
				//Create phone entry and set this user as FirstUser
				//$isFirstUser does not matter, $isStore here is true
				//creates row in iOS_USER_TABLE
				$this -> phStorePhoneUser(null, null, $typePhone, true, true, $regID, $userID);
				
				$this -> display -> displayJSON('SUCCESS');
				//This is just assuming that only this part creates new row in both PHONE_INFORMATION_TABLE and iOS_USER_TABLE
				//In the event that there are other places that create the rows, this logic will inevitably fail
                	}
            	}
             }
        }

        /*==============================================================
            @update the location of the phone in phone information table
            @this function is used in phoneDataReceive.php
        ===============================================================*/
        public function phUpdatePhoneLocation($macPhone, $regID, $lat, $long, $acc, $bat, $dateCreate){

            //update the location
            if($this -> update -> updatePhoneLocation($macPhone, $regID, $lat, $long, $acc, $bat, $dateCreate));
                $this -> display -> displayJSON('SUCCESS');

            //query fail
            #else
            #    $this -> display -> displayJSON('FAIL', 'QUERY_FAIL');
        }

        /*======================================================================================
            @this function is used only in iOSDataChecking.php file
            @this function is used to check the notification table and retrieve the value inside
            @param string email and regID
        =====================================================================================*/
        public function phIOSDataChecking($email, $regID){
                
            if($userID = $this -> retrieve -> retrieveUserID($email)){

                //retrieve the 3 data in notification table
                $notiData = $this -> retrieve -> retrieveNotification($userID);
                
                //create the data to send back to ios phone
                $dataSendBack = array(TRACK => $notiData[0], LOCK => $notiData[1], BACKUP_CONTACT => $notiData[2], IMAGE_CAPTURE => $notiData[3]);

                //displya success message
                $this -> display -> displayJSON('SUCCESS', null, $dataSendBack);
            }
            else{

                $this -> display -> displayJSON('FAIL', 'NO_USER_EXIST');
                return false;
            }
        }
        /*====================================================
            @this function store the image capture by the phone
        =====================================================*/
        public function phStoreImageCapture($userID, $image, $email = null){

            if(is_null($userID)){
                $userID = $this -> retrieve ->retrieveUserID($email);
            }

            $addr = '../UserRegion/ImageCapture/'.$userID.'_img/';

            $imageNum = $this -> retrieve -> retrieveImageNum($userID);

            //firstly we need to retrive the image number inside the database to name the image
            $binary   = base64_decode($image);

            header('Content-Type: bitmap; charset=utf-8');

            $file = fopen($addr.'pic_'.$imageNum.'.jpg', 'w');

            fwrite($file, $binary);

            fclose($file);
        }

        public function phBackupUserContact($content, $userID = null, $email = null){

            if(is_null($userID)){
                $userID = $this -> retrieve -> retrieveUserID($email);
            }

            $xmlFile = "../UserRegion/Backup/".$userID."_contact/backup.xml";
            $xmlHandle = fopen($xmlFile, "w");
            fwrite($xmlHandle, $content);
            fclose($xmlHandle);
        }

        /*=========================================================
            @create the folder to backup and image capture for user
        =========================================================*/
        private function phCreateUserSpace($userID){
            if (!file_exists('../UserRegion/Backup/'.$userID.'_contact')) {
                mkdir('../UserRegion/Backup/'.$userID.'_contact', 0777, true);
            }
            if(!file_exists('../UserRegion/ImageCapture/'.$userID.'_img')) {
                mkdir('../UserRegion/ImageCapture/'.$userID.'_img', 0777, true);
            }
        }
            
        /*=========================================================
            @perform all the steps for storing user in the database
            @this will follow step by step below
            @notice params:
                isFirstUser: the first user params is to update in first or second user column
                isStore: update or store the value
                         the problem here is if the mac phone or register id is new, then perform the insert into table
                         but if the macphone or register id is not new then have to update the first or second user
        =========================================================*/
        /*=================================================================================================================================*/
        /*=================================================================================================================================*/
        private function phStoreUserInfo($email, $password, $dateCreate){
            //hash the password
            $hashedPassword =  $this -> hash -> hashData($password);
            //create hash token for user to activate their account
            $token          =  $this -> hash -> hashData($email.time());
            //set the default active value for user first register the account is 0
            $active 		=  USER_INACTIVE;
            //set the current date time of the system when the user register their phone
            $dateCreateToken=  date('Y-m-d h:i:s', time()); 
            //store the password hash into user information table
            $this           -> store -> storeUserInformation($email, $hashedPassword, $dateCreate, $active, $token, $dateCreateToken);

            //send the user confirmation email here 

            global $base_url;
            $params    = array('subject' => 'Account Activation',
                               'token'   => 'http://innovatechnology.com.sg/development/activation?token='.$token
                              );
            $this           -> send -> sendMail(ACTIVATION_MAIL, $email, $params);

            //retrieve the id in user information table
            $userID         =  $this -> retrieve -> retrieveUserID($email);
            //create user space 
            $this -> phCreateUserSpace($userID);
            //hash the user ID
            $hashedUserId   =  $this -> hash -> hashData($userID);
            //update the hash user ID in user information table
            $this           -> update-> updateHashData($hashedUserId, USERS_INFORMATION_TABLE, USER_INFO_ID_HASHED_COL, USER_INFO_ID_COL, $userID);
            //insert a row in notification table
            $this           -> store -> storeUserIDInNotificationTable($userID);   
            //insert a row in password token table for password retrieval        
            $this           -> store -> storePasswordTokenTable($userID);

            //store new user in drupal
            $new_user = array(
              'name' => $email,
              'pass' => $password,
              'email' => $email,
              'status' => 1,
              'init' => $email,
              'roles' => array(
                DRUPAL_AUTHENTICATED_RID => 'authenticated user',
              ),
            );

            // The first parameter is sent blank so a new user is created.
            user_save('', $new_user);
        }

        public function phPassiveTrackAction($macPhone, $regID, $dateCreate, $lat, $long, $bat, $acc){
            if(is_null($regID)){
               
               $lost = $this -> retrive -> retrievePhoneLostNotification($macPhone);
               if($lost == 1){
                    //send message to user
                    //....
                    $this -> phUpdatePhoneLocation($macPhone, null, $lat, $long, $acc, $bat);
                    $this -> update -> updatePhoneLostNotification($macPhone, null , '2');
               }
               else
                    if($lost == 2){
                        $lastDateTime = $this -> retrieve -> retrievePhoneLocationLastDateTime($macPhone, $regID);
                        if($this -> phCheckAccuracyAndDateTimeForLost($acc, $lastDateTime, $dateCreate)){
                            //send email to user here
                        }
                        else{
                            //not send email to user
                        }
                    }
            }

        }

        public function phCheckAccuracyAndDateTimeForLost($acc, $lastDateTime, $currentDateTime){
            if($this -> validate -> isDateExceedOtherDate($$lastDateTime, $currentDateTime, 0.6)){
                if($acc > SEND_MAIL_ACCURACY){
                     $this -> phUpdatePhoneLocation($macPhone, null, $lat, $long, $acc, $bat, $currentDateTime);
                     return true;
                }
            }
            return false;
        }

        public function phLastFlareAction($userID, $lat, $long, $acc, $dateCreate){
            $email = $this -> retrieve -> retrieveEmailUsingUserID($userID);
            
            $params = array('subject' => 'Send data',
                            'date'    => $dateCreate,
                            'acc'     => $acc,
                            'lat'     => $lat,
                            'long'    => $long
                            );
            $this           -> send -> sendMail(PASSIVE_TRACK_MAIL, $email, $params);   
        }

        /*====================================================
            @this function updates the iOS notification token by the phone
        =====================================================*/
        public function phUpdateNotificationTokenForiOS($regID, $token){
            if($this -> update -> updateNotificationTokenForiOS($regID, $token)){
            	 $this -> display -> displayJSON('SUCCESS');
            } else {
            	$this -> display -> displayJSON('FAIL');
            }
        }
		
		public function phUpdateiOSNotificationToken($reg_id, $token){
			return $this -> update -> updateNotificationTokenForiOS($reg_id, $token);
		}
		
		public function phRetrieveiOSNotificationToken($reg_id){
			return $this -> retrieve -> retrieve_iOS_NotiTokenUsingRegID($reg_id);
		}
		
		public function phRetrieveiOSNotificationTokenViaUserId($user_id){
			return $this -> retrieve -> retrieve_iOS_NotiTokenUsingUserID($user_id);
		}
		
		public function phUpdateAndroidRegistrationID($phone_mac_ad, $reg_id){
			return $this -> update -> updateRegistrationIDForAndroid($phone_mac_ad, $reg_id);
		}
		
		public function phRetrieveAndroidRegistrationIdsViaUserId($user_id){
			return $this -> retrieve -> retrieve_android_registrationids_using_userid($user_id);
		}
		
		public function phSendNonUserFoundEmail($email_addr, $params){
			return $this -> send -> sendMail(NON_USER_FOUND_MAIL, $email_addr, $params);
		}
		

        /*=================================================================================================================================*/
        /*=================================================================================================================================*/
        private function phStorePhoneInfo($regID, $macPhone, $dateCreate, $typePhone){
            //store phone in phone information table, 0 0 0 0 corresponding to lat, long, acc, bat (these are default value)
            $this           -> store -> storePhoneInformation($macPhone, $regID, $typePhone, 0, 0, 0, 0, $dateCreate);      
        }

        /*=================================================================================================================================*/
        /*=================================================================================================================================*/
        private function phStorePhoneUser($email, $macPhone, $typePhone, $isFirstUser, $isStore, $regID = null, $userID = null){
            
            if(is_null($userID))
                //retrieve the id in user information table
                $userID =  $this -> retrieve -> retrieveUserID($email);

            //check if the typephone is android phone
            if($typePhone == ANDROID){
                //if the mac address is new, insert into android user table usr Id
                if($isStore){

                    $this -> store -> storePhoneFirstUser($userID, $macPhone);
                }
                else{                  
                    if($isFirstUser)
                        // update first user column in android usr table
                        $this -> update -> updatePhoneUser(null, $macPhone, $userID, ANDROID_FIRST_USER_ID_COL, ANDROID_FIRST_USER_ACT_COL, USER_ACTIVE);
                    else
                        //update the second user column in android usr table
                        $this -> update -> updatePhoneUser(null, $macPhone, $userID, ANDROID_SECOND_USER_ID_COL, ANDROID_SECOND_USER_ACT_COL, USER_ACTIVE);
                }
            }
            else if ($typePhone == IOS) {
                if($isStore){
                    //insert into phone user table userID
                    $this -> store -> storePhoneFirstUser($userID, null, $regID);
                }
                else{
                    //update first user ID column in ios phone user table
                    if($isFirstUser)
                        $this -> update -> updatePhoneUser($regID, null, $userID, IOS_FIRST_USER_ID_COL, IOS_FIRST_USER_ACT_COL, USER_ACTIVE);
                    else
                        //update the second user column in ios user table
                        $this -> update -> updatePhoneUser($regID, null, $userID, IOS_SECOND_USER_ID_COL, IOS_SECOND_USER_ACT_COL, USER_ACTIVE);
                }
            }
        }
	}
?>