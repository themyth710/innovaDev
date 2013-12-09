<?php
	include_once drupal_get_path('module','Tracking').'/database/browser.inc';
	include_once drupal_get_path('module','Tracking').'/database/config.inc';

	class handler{

		private $handler;
		/*==================================
	   		@constructor
	   	==================================*/
	   	function __construct() {
	   		$this -> handler = new browser();
	    }
	
    	/*==================================
    		@destructor
    	==================================*/
    	function __destruct() {

    	}

        /*=========================================

            @check the login and password form user

        =========================================*/
    	public function handleLoginCheck($email, $password){

            //validate inout 
    		if($this -> handler -> dbValidateInputFormat($email, $password)){

                //check login and password
                //format function: $email, $password, $isHash
                //return the hash userID
    			if($userID = $this -> handler -> dbClientLoginCheck($email, $password, true))
    				
                    //return hash user ID
                    return $userID;
    			else
    				return false;
    		}
    		else
    			return false;
    	}

        /*=========================================================

            @retrieve the list of register ID or type phone or both
            @for both -> (null, hash)
            @for list reg -> ($list)
            @for list type -> ($list, null, $false)

        =========================================================*/
        public function handleRetreiveListRegIDAndTypePhone($list, $hashUserID = null, $isRegID = true){
            
            //check if the list is null
            if(is_null($list)){

                //retrieve the list 
                if($list = $this -> handler -> brRetrieveRegIDList($hashUserID)){
                    return $list;
                }
                else
                    return false;
            }

            else
                if($isRegID){

                    $dataSendBack = array();

                    //retrieve the regID inside the list and return to user
                    foreach($list as $data)
                        array_push($dataSendBack, $data[REG_ID]);

                    return $dataSendBack;
            }

            else{
                $dataSendBack = array();

                //retrieve the typePhone inside the list and return to user
                foreach($list as $data)
                    array_push($dataSendBack, $data[TYPE_PHONE]);
                
                return $dataSendBack;
            }
        }

        /*=======================================================

            @store the password token correspoding with the email

        =======================================================*/
        public function handleStorePasswordToken($email){
            if($token = $this -> handler -> brStorePasswordToken($email))
                return $token;
            else
                return false;
        }

        /*===========================

            check the token from user

        ============================*/
        public function handleValidatePasswordToken($token){
            if($email = $this -> handler -> brTokenSubmit($token))
                return $email;
            else
                return false;
        }

        /*==================================

            @update the new password to user

        ==================================*/
        public function handleUpdateNewPassword($password, $email){
            $this -> handler -> brUpdateNewPassword($password, $email);
        }

        /*
            check the session for user to let user go into the system without login
        */
        public function handleCheckSession($userID, $email){
            if($this -> handler -> brCheckSession($userID, $email))
                return true;
            else
                return false;
        }

        public function handleRemovePhone($userID, $regID){
            if($this -> handler -> brRemovePhone($userID, $regID))
                return true;
            else
                return false;
        }

        /*********************
        *********************/
        public function handleSendEmailActivation($email){
            $this -> handler -> brSendActivationToken($email);

            return true;
        }

        public function handleActivationTokenSubmit($token){
            if($this -> handler -> brHandleActivationToken($token))
                return true;
            else
                return false;
        }

        public function handleCheckUserActivation($email){
            if($this -> handler -> brCheckActivatedUser($email))
                return true;
            else
                return false;
        }
	}
?>