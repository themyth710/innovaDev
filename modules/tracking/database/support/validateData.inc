<?php
	/*==========================================
		@API used to control any data the comes to server
		@Used in db_functions.inc
	==========================================*/
	class validate{

        private $validate;
		/*==================================
	   		@constructor
	   	==================================*/
		function __construct() { 
            require_once(dirname(__FILE__).'/../db_connect.inc');
            
            // connecting to database
            $this -> validate = new DB_Connect();
            $this -> validate -> connect();       	
	    }

	    /*==================================
    		@destructor
    	==================================*/
    	function __destruct() {

    	}

    	/*===========================================

    		@validate the email address come from user
    		@param string email
    		@return true if it is valid email address
    		@return false if it is not valid

    	============================================*/
    	public function isEmail($email){
            if($email !=null){
        		if(filter_var($email, FILTER_VALIDATE_EMAIL))
        			return true;
        		else
        			return false;
            }else
                return true;          
    	}

    	/*====================================================

    		@validate the numeric type
    		@param string number
    		@return true if it is numeric
    		@this function also accept float number and integer

    	======================================================*/
    	public function isNumber($number){
            if($number!=null){
        		if(is_numeric($number))
        			return true;
        		else
        			return false;
            }
            else
                return true;
    	}

    	/*==================================================

			@check the string length of data
			@param string data, int maxlength
			@return true if lengh is smaller than max length

    	===================================================*/	
    	public function isExceedStringLength($data, $maxLength){
    		if($data !=null){
                if(strlen($data) < $maxLength)
    				return true;
    			else
    				return false;
            }
            else
                return true;
    	}

        /*=================================================
            @check the datatime format
            @the format of the date is YYYY-MM-DD hh-mm-ss 
            @param string data
            @return boolean
        ================================================*/
        public function isDateTime($data){
            if($data != null){
                //the format of the date time, change for other format
                $dateTimeFormat = 'Y-m-d H:i:s';
                
                if (date($dateTimeFormat, strtotime($data)) === $data) 
                    return true;
                else 
                    return false;
            }
            else
                return true;
        }

        /*==================================================

            @check the mac address data type from the phone
            @the mac address format is XX:XX:XX:XX:XX:XX
            @param string data
            @return boolean variable

        ==================================================*/
        public function isMacPhone($data){
            if($data != null){
                if(preg_match('/^[0-9a-fA-F]{2}(?=([:;.]?))(?:\\1[0-9a-fA-F]{2}){5}$/', $data))
                    return true;
                else
                    return false;
            }
            else
                return true;
        }

        /*============================================================================

            @compare the current date time with the previous time
            @if it is > $dateCompare -> return true;

        ============================================================================*/
        public function isDateExceed($prevDataTime, $dateCompare = 1){

            $previous = strtotime($prevDataTime);
            $now      = strtotime(date('Y-m-d h:i:s', time()));     
            $diff     = round(($now - $previous)/60/60/24);

            //check if the current time and the time store in database > 1 day
            if($diff > $dateCompare)
                return true;
            else
                return false;
        }

        public function isDateExceedOtherDate($prevDateTime, $currentDateTime, $dateCompare){
            $previous = strtotime($prevDataTime);
            $current  = strtotime($currentDateTime);
            $diff     = round(($now - $previous)/60/60);

            //return to hours
            if($diff > $dateCompare)
                return true;
            else
                return false;
        }

        /*===========================================================

            @check if the email address already exist in the database
            @param string email
            @return true if email already exist
            @return false if email does not exist

        ===========================================================*/
        public function isEmailExist($email){

            //query to execute
            $query = sprintf("SELECT COUNT(".USER_INFO_EMAIL_COL.") AS COUNT FROM ".USERS_INFORMATION_TABLE." WHERE ".USER_INFO_EMAIL_COL." = '%s'",
                              mysql_real_escape_string($email));
            
            //execute the query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)          
                die();
            else{

                $row = mysql_fetch_assoc($executeQuery);
                
                if($row['COUNT'] == MAXIMUM_EMAIL){
                    return true;
                }
                else{
                    //if there is no records about this email 
                    return false;
                }
            }
        }

        /*========================================================================================

            @check if user already exist in the phone user table
            @depend on the boolean value, we can check if first, second or both exist in database
            @formular
                check first user: function(list, nul, true, false)
                check second user: function(list, null, false, true)
                check if first or second: function(list, usrId, false, false)

        ==========================================================================================*/
        public function isUserExistInPhoneUserTable($userList, $userID, $isFirstUser = false, $isSecondUser = false){

            if(is_null($userList)){

               return false; 
            }
            //if the user ID is null, we just want to check if there is any user there
            else
                if(is_null($userID)){
                    if($isFirstUser){
                        if($userList[0] != null && $userList[1] == USER_ACTIVE)
                            return true;
                        else
                            return false;
                    }
                    else
                        if($isSecondUser){
                            if($userList[2] != null && $userList[3] == USER_ACTIVE)
                                return true;
                            else
                                return false;
                    }
                }

            else{

                //check if we want to clarify that the first user exist or mnot
                //userList => array (1stID, 1stAct, 2ndId, 2ndAct)
                if($isFirstUser){

                    //if we want to do that, we need to key in the userID = null
                    //retrieve the userID, if it is null and active
                    //never have the situation that userID null and user inactive because the dedfault value of user_active is 1 
                    //and if we set the user to inactive, the userID is not null
                    if($userList[0] == $userID && $userList[1] == USER_ACTIVE)

                        return true;
                    else
                        return false;
                }

                else
                    //similar to first user
                    if($isSecondUser){
                                                    file_put_contents('vlin.txt', 'this is a test');
                        if($userList[2] == $userID && $userList[3] == USER_ACTIVE)
                            return true;
                        else
                            return false; 
                }
                
                else{
                    
                    //if we have usr ID and we want to clarify that user is there only
                    if($userList[0] == $userID && $userList[1] == USER_ACTIVE)
                    
                        return true;     
            
                    else 
                        if($userList[2] == $userID && $userList[3] == USER_ACTIVE)
                        
                        return true;
                    else
                        return false;
                }
            }
        }

        /*===============================================
        
            @check for the register ID in iOS user table
            @param string regID
            @return  bool

        ===============================================*/
        public function isIOSRegisterIDExist($regID){
            $query = sprintf("SELECT COUNT(*) AS COUNT FROM ".IOS_USER_TABLE." WHERE ".IOS_USER_REGID_COL." = '%s'",
                              mysql_real_escape_string($regID));

            //execute the query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)          
                die();
            else{

                $row = mysql_fetch_assoc($executeQuery);
                if($row['COUNT'] == MAXIMUM_REGID_PHONE){

                    return true;
                }
                else{
                    //if there is no records about this mac address
                    return false;
                }
            }
        }

        /*=============================================================================

            @this function is used for android only
            @check the mac address exist in android user table
            @param string mac address
            @return bool true if main user exist
            @false if main user does not exist
            @note: the main user table is the table that contains the latest mac address
            @it is used to constrained that every phone has the main user

        ==============================================================================*/
        public function isMacPhoneExist($macPhone){
            
            //query to execute
            $query = sprintf("SELECT COUNT(*) AS COUNT FROM ".ANDROID_USER_TABLE." WHERE ".ANDROID_USER_MAC_COL." = '%s' ",
                              mysql_real_escape_string($macPhone));

            //execute the query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)          
                die();
            else{

                $row = mysql_fetch_assoc($executeQuery);
                if($row['COUNT'] == MAXIMUM_MAC_PHONE){
                    return true;
                }
                else{
                    //if there is no records about this mac address
                    return false;
                }
            }
        }

        /*========================================================

            @this function check if the the mac address already
            @exist in the protag database
            @it will perform update if the mac address exist 
            @or perform insert if the mac does not exist
            @param string macProtag
            @return boolean

        ======================================================*/
        public function isMacProtagExist($macProtag){
            //query to execute
            $query = sprintf("SELECT COUNT(*) AS COUNT FROM ".PROTAG_INFORMATION_TABLE." WHERE ".PROTAG_INFO_MAC_COL." = '%s' ",
                              mysql_real_escape_string($macProtag));

            //execute the query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)          
                die();
            else{

                $row = mysql_fetch_assoc($executeQuery);
                if($row['COUNT'] == MAXIUM_PROTAG_MAC){
                    return true;
                }
                else{
                    //if there is no records about this mac address
                    return false;
                }
            }
        }

        /*===============================================

			@check if user has activated their account
			@param email to retrieve the user information
			@return boolean variables

        ===============================================*/
        public function isUserActivateTheirAccount($email){
        	//query to execute
            $query = sprintf("SELECT ".USER_INFO_ACTIVE_COL." FROM ".USERS_INFORMATION_TABLE." WHERE ".USER_INFO_EMAIL_COL." = '%s' ",
                              mysql_real_escape_string($email));
 
            //execute the query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)          
                die();
            else{

                $row = mysql_fetch_assoc($executeQuery);
                if($row[USER_INFO_ACTIVE_COL] == USER_ACTIVE){
                    return true;
                }
                else{
                    //if there is no records about this mac address
                    return false;
                }
            }
        }

        /*=====================================================

            @check if the activation token exist in the database
            @return boolean value for token existence

        ======================================================*/
        public function isAccountActivationTokenExist($token){
            //query to execute
            $query = sprintf("SELECT COUNT(*) AS COUNT FROM ".USERS_INFORMATION_TABLE." WHERE ".USER_INFO_TOKEN_COL." = '%s' ",
                              mysql_real_escape_string($token));
            
            //execute the query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)          
                die();
            else{

                $row = mysql_fetch_assoc($executeQuery);
                if($row['COUNT'] == MAXIMUM_EMAIL){
                    return true;
                }
                else{
                    //if there is no records about this mac address
                    return false;
                }
            }
        }
	}
?>