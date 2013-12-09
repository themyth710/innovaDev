<?php
	/*==========================================
		@API used to control the display of status and message respond to client
		@Used in db_functions.inc
	==========================================*/
	class dataDisplay{

		private $message;
		private $status;
		/*==================================
	   		@constructor
	   	==================================*/
		function __construct() {
			//list of success or fail status
              $this -> message = array('EMAIL_REGISTERED'         => array('code'   => '101',  'message' => 'Email already registered, please login'),
            			     'MAX_USER'		        => array('code'   => '102',  'message' => 'Maximum user reach'),
                                     'NO_TYPE_PHONE'            => array('code'   => '103',  'message' => 'No type phone declare or wrong format'),
                                     'WRONG_INPUT_FORMAT'       => array('code'   => '104',  'message' => 'Wrong input format'),
                                     'NO_USER_EXIST'            => array('code'   => '105',  'message' => 'User not exist in database'),
                                     'PHONE_REQUEST_SEND_FAIL'  => array('code'   => '106',  'message' => 'Can not send phone request to Google server'),
                                     'QUERY_FAIL'               => array('code'   => '107',  'message' => 'Query fail'),
                                     'INFO_NOT_MATCH'           => array('code'   => '108',  'message' => 'Info send does not match'),
                                     'NO_USER_IN_IOS_USER_TABLE'=> array('code'   => '109',  'message' => 'No user match in IOS user table'),
                                     'NO_USER_ANDR_USER_TABLE'  => array('code'   => '110',  'message' => 'No user match in Android User table'),
                                     'NO_REG_ID_IOS_USER_TABLE' => array('code'   => '111',  'message' => 'No register ID exist in IOS user table'),
                                     'NO_MAC_ANDR_USER_TABLE'   => array('code'   => '112',  'message' => 'No mac phone exist in Android user table'),
                                     'MAC_AND_REGID'            => array('code'   => '113',  'message' => 'Mac phone and register ID does not match'),
                                     'TIME_OUT'                 => array('code'   => '114',  'message' => 'Time out'),
                                     'FILE_NOT_EXIST'           => array('code'   => '115',  'message' => 'File does not exist'),
                                     'OLD_NEW_PASS_PROB'        => array('code'   => '116',  'message' => 'Old password and new password does not match'),
                                     'NO_PROTAG_DETECT'         => array('code'   => '117',  'message' => 'No protag detect with this account'),
                                     'USER_NOT_ACTIVATE'        => array('code'   => '118',  'message' => 'User have not activated account'),
                                     'WRONG_PASSWORD'           => array('code'   => '119',  'message' => 'Email and Password do not match, please try again'),
            			     'LOGIN_REG_UPDATE'         => array('code'   => '201',  'message' => 'Register ID updated'),
            		             'LOGIN_PHONE_ADDED'        => array('code'   => '202',  'message' => 'Phone added to user'));
            $this -> status =  array('SUCCESS'                  => array('status' => 'success', 'code' => '200'),
            						 'FAIL'	                    => array('status' => 'fail',    'code' => '100'));
	    }

	    /*==================================
    		@destructor
    	==================================*/
    	function __destruct() {

    	}

    	/*===================================================
    		@display the message to client in JSON form
    		@param string, string, array
    		@param data for additional data added to the json
    		@return json
    	===================================================*/
    	public function displayJSON($status, $message = null, $data = null){
            
            if($message === null && $data === null)
                $arr  = array('status' => $this -> status[$status]);
            else 
                if($message === null && $data !== null)
                    $arr  = array('status' => $this -> status[$status], 'data' => $data);
            else 
                if($message !== null && $data === null)
                    $arr  = array('status' => $this -> status[$status], 'message' => $this -> message[$message]);
            else    
    		    $arr  = array('status' => $this -> status[$status], 'message' => $this -> message[$message], 'data' => $data);
    		
            $json = array();
    		$json = json_encode($arr);
			
			header('Content-Type: application/json');
			echo $json;
    	}
    }
?>