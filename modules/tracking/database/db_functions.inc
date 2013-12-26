<?php
	/*================================================
		@all neccessary functions for database control
        @include also the data checking from client
	================================================*/

    require      'support/hashData.inc';
    require      'support/validateData.inc';
    require      'support/retrieveData.inc';
    require      'support/storeData.inc';
    require      'support/displayData.inc';
    require      'support/updateData.inc';
    require      'support/sendData.inc';

    abstract class DB_Functions{

        //control hashing data
	protected $hash;
        //control validate input
        protected $validate;
        //control taking data from database
        protected $retrieve;
        //control store data into database
        protected $store;
        //control other function used for display purpose
        protected $display;
        //control function to send data
        protected $send;

	   	/*==================================
	   		@constructor
	   	==================================*/
	   	function __construct() {
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

        /*====================================================
            @perform all the validate for all the input value
        ====================================================*/
        public function dbValidateInputFormat($email = null, $password = null, $regID = null, $macPhone = null, $dateCreate = null, $lat = null, $long = null, $bat = null, $acc = null){
            if($this -> validate -> isEmail($email) &&
               $this -> validate -> isExceedStringLength($email, MAXIMUM_EMAIL_LENGTH) &&
               $this -> validate -> isExceedStringLength($password, MAXIMUM_PASS_LENGTH) &&
               $this -> validate -> isMacPhone($macPhone) &&
               $this -> validate -> isDateTime($dateCreate) &&
               $this -> validate -> isExceedStringLength($regID, MAXIMUM_REGID_LENGTH) &&
               $this -> validate -> isNumber($lat) &&
               $this -> validate -> isNumber($long) &&
               $this -> validate -> isNumber($bat) &&
               $this -> validate -> isNumber($acc))
                return true;
            else{
                $this -> display -> displayJSON('FAIL', 'WRONG_INPUT_FORMAT');
                return false;
            }               
        }
        
        /*========================================================================

            @this function is used to check the input from client or phone to server
            @to see if the information is match or not
            @if the userID is a hash user id, it will return it to it real user ID
            @for example is this case it can check:
                for ios: email and regID
                for android: userID and macPhone
                             userID and regID

        =========================================================================*/
        public function dbValidateInputInfo($userID, $regID, $macPhone, $email ,$isHash, $isIOS){

            //check if the user ID is hash user ID
            if($isHash){

                //retrieve user ID usng hash user ID
                if(!($userID = $this -> retrieve -> retrieveUserID(null, $userID))){
                    //if the hash doesnot exist
                    $this -> display -> displayJSON('FAIL','NO_USER_EXIST');
                    return false;
                }
            }
            //check if the user ID is null
            //this happens when the input is regID, email (on ios side only) so we can use email to retrieve user ID 
          
            if(is_null($userID)){
                if(!($userID = $this -> retrieve -> retrieveUserID($email))){
                    $this -> display -> displayJSON('FAIL','NO_USER_EXIST');
                    return false;
                }
            }
            

            //if it is on ios side
             
            if($isIOS){
                //we retrieve a list of user ID so that we can compare it with the current one
                if($userList = $this -> retrieve -> retrieveUserIDFromPhoneUserTable(null, $regID)){
                    //if it is ios and user ID we retrieve above
                    if($this -> validate -> isUserExistInPhoneUserTable($userList, $userID))
                        return true;
                    else{
                        $this -> display -> displayJSON('FAIL','NO_USER_IN_IOS_USER_TABLE');
                        return false;
                    }
                }
                else{
                    $this -> display -> displayJSON('FAIL','NO_REG_ID_IOS_USER_TABLE');
                    return false;
                }
            }

            //if the mac phone is null -> user input regID and user ID only -> we have to retreive the macPhone first(on android side only)
            else
                if($macPhone == null){
                    //retrive the mac phone here
                    if(!($macPhone = $this -> retrieve -> retrieveMacPhoneUsingRegID($regID))){
                        $this -> display -> displayJSON('FAIL', 'MAC_AND_REGID');
                        return false;
                    }
            }

            //retrieve all user in androidUsertable and check with the user ID
            if($userList = $this -> retrieve -> retrieveUserIDFromPhoneUserTable($macPhone)){

                //perform check if user already has the phone
                if($this -> validate -> isUserExistInPhoneUserTable($userList, $userID)){
                    
                    return true;
                }
                else{
                    $this -> display -> displayJSON('FAIL', 'NO_USER_ANDR_USER_TABLE');
                    return false;
                }
            }
            else
                $this -> display -> displayJSON('FAIL', 'NO_MAC_ANDR_USER_TABLE');
                 
        }

        /*================================================
        
            @perform the data checking from client login through browser
            @param 2 string email and password
            @return userID if these things can pass the test

        ================================================*/
        public function dbClientLoginCheck($email, $password, $isHash = false){

            //retrieve the password from database
            if($pass = $this -> retrieve -> retrievePassword($email)){

                //check the data from input and the hashed data retrieve from the database
                if($this -> hash -> compareHashData($password, $pass)){

                    //retrieve the userID from database and return 
                    $userID = $this -> retrieve -> retrieveUserID($email, null, $isHash);
                    return $userID;
                }
                else{
                    $this   -> display -> displayJSON('FAIL', 'WRONG_PASSWORD');   
                    return false;
                }
            }
            else{
                $this   -> display -> displayJSON('FAIL', 'NO_USER_EXIST'); 
                return false;
            }
        }

        /*====================================================================================

            @this function is used on sendmessage.php and phonedatareceive.php
            @this function is used to update the notification column in the database
            @correspoding to the action that browser or phone send
            @param action, userId ,email
            @the email is used for IOS only

        =====================================================================================*/
        public function dbAction($action, $userID, $email = null, $regID = null){
            
            //used for ios if we do not have userID, we need to take it from email
            if($email != null){
                $userID = $this -> retrieve -> retrieveUserID($email);
            }
            
            if($action == OK_TRACK || $action == OK_LOCK || $action == OK_B_CONTACT || $action == OK_IMAGE_CAPTURE){

                //update to 1 that means the phone is ok in actions
                $this -> update -> updateNotification($userID, $action, OK_CMD_VAL);//=1
            }else if($action == SEND_TRACK_DATA){

                //update the track notification column to 2 to tell user that the phone has sent the location data to server
                $this -> update -> updateNotification($userID, $action, SEND_TRACK_CMD_VAL);//=2
            
            }else if($action == START_TRACK || $action == LOCK || $action == BACKUP_CONTACT || $action == IMAGE_CAPTURE || $action == TEST_TRACK){

                $this -> update -> updateNotification($userID, $action, USER_CMD_SET);//=0
            
            }else if($action == STOP_TRACK){

                //update the track column to 1 to tell user that no need to track again
                //this is very important in iphone
                $this -> update -> updateNotification($userID, $action, OK_CMD_VAL);//=1
            }else if($action == PASSIVE_TRACK){
                $this -> update -> updatePhoneLostNotification(null, $regID, '1');
            }else if($action == STOP_PASSIVE_TRACK){
                $this -> update -> updatePhoneLostNotification(null, $regID, '0');
            }
            else{
                //fail if wrong action
                $this -> display -> displayJSON('FAIL', 'WRONG_INPUT_FORMAT');
                exit();
            }
            //return success if dont want to send back to the phone when it has these actions
            //if($action != OK_TRACK || $action !=OK_LOCK || $action !=OK_B_CONTACT)
             //   $this -> display -> displayJSON('SUCCESS');

        }

        /*===============================================================================
            @this function is used just to generate the hash directory for browser client
        ===============================================================================*/
        public function dbStoreDirectoryHash(){
            $directory = array('home/sites/all/modules/tracking/communication/');
            foreach($directory as $value){
                $hashValue = $this -> hash -> hashData($value);

                $this -> store -> storeDirectoryHash($value, $hashValue);
            }
        }        
    }
?>