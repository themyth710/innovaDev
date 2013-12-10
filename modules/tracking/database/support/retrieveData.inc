<?php
	/*================================================
		@all neccessary functions for retrieving data from server
	================================================*/

	class dataRetrieve{

        //control hashing data
		private $retrieve;
	   	/*==================================
	   		@constructor
	   	==================================*/
	   	function __construct() {
            require_once(dirname(__FILE__).'/../db_connect.inc');
            
            // connecting to database
            $this -> retrieve = new DB_Connect();
            $this -> retrieve -> connect();
	    }
	
    	/*==================================
    		@destructor
    	==================================*/
    	function __destruct() {
            
    	}

        /*===============================================
            
            @retrieve the user Password from the database
            @to perform the validation
            @param string email 
            @return string user password

        ==============================================*/
        public function retrievePassword($email){

            //the query to execute
            $query = sprintf("SELECT ".USER_INFO_PASSWORD_COL." FROM ".USERS_INFORMATION_TABLE." WHERE ".USER_INFO_EMAIL_COL." = '%s' ",
                              mysql_real_escape_string($email));

            //execute the query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)

                //query failed to execute
                return false;
            
            else{

                //perform check the maximum num rows that can retrieve to be 1 only
                if(mysql_num_rows($executeQuery) === MAXIMUM_USER){
                    
                    $row = mysql_fetch_array($executeQuery);
                    
                    return $row[0];
                }
                else{

                    //if there is no records about this email or the number of email exist in databse > 1
                    return false;
                }
            }
        }

        /*==========================================================================
            
            @retrieve the user ID from data input
            @format follow: 
                           hash         => retrieve user ID using hashed user ID
                           email and isHash => retrieve hashed userID using email
                           email            => retrieve user ID using email

        =========================================================================*/
        public function retrieveUserID($email = null, $hashUserID = null, $isHash = false){
            
            //default value
            $columnName              =  USER_INFO_ID_COL;
            $tableName               =  USERS_INFORMATION_TABLE;
            $columnCondition         =  USER_INFO_ID_HASHED_COL;
            $conditionValue          =  $hashUserID;

            //if email is not null
            if(!is_null($email)){
                
                $columnCondition     = USER_INFO_EMAIL_COL;
                $conditionValue      = $email;

                //if return the hash ID
                if($isHash === true){
                    $columnName      = USER_INFO_ID_HASHED_COL;
                }
                //if return the normal ID
                else{
                    $columnName      = USER_INFO_ID_COL;
                }
            }

            //query to execute
            $query = sprintf("SELECT $columnName FROM $tableName WHERE $columnCondition = '%s' ",
                              mysql_real_escape_string($conditionValue));

            //execute query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)
                die();
            else
                //perform check the maximum num rows that can retrieve to be 1 only
                if(mysql_num_rows($executeQuery) === MAXIMUM_USER){
                    
                    $row = mysql_fetch_array($executeQuery);
                    
                    return $row[0];
                }
                else{

                    //if there is no records about this email or the number of email exist in databse > 1
                    return false;
                }
        }

        /*====================================================================

            @retrieve the userID from Android or iOS user table
            @depend on the macPhone and regID to choose between android or ios
            @return the success of query

        ====================================================================*/
        public function retrieveUserIDFromPhoneUserTable($macPhone = null, $regID = null){
            
            //default value
            $firstIDCol             = ANDROID_FIRST_USER_ID_COL;
            $firstActCol            = ANDROID_FIRST_USER_ACT_COL;
            $secondIDCol            = ANDROID_SECOND_USER_ID_COL;
            $secondActCol           = ANDROID_SECOND_USER_ACT_COL;
            $tableName              = ANDROID_USER_TABLE;
            $columnCondition        = ANDROID_USER_MAC_COL;
            $conditionValue         = $macPhone;
            
            if(is_null($macPhone)){
                
                $firstIDCol         = IOS_FIRST_USER_ID_COL;
                $firstActCol        = IOS_FIRST_USER_ACT_COL;
                $secondIDCol        = IOS_SECOND_USER_ID_COL;
                $secondActCol       = IOS_SECOND_USER_ACT_COL;
                $columnCondition    = IOS_USER_REGID_COL;
                $tableName          = IOS_USER_TABLE;
                $conditionValue     = $regID;
            }

            $query = sprintf("SELECT $firstIDCol, $firstActCol, $secondIDCol, $secondActCol FROM $tableName WHERE $columnCondition = '%s'",
                              mysql_real_escape_string($conditionValue));

            
            $executeQuery = mysql_query($query);
            if(!$executeQuery)

                //query failed to execute
                die();
            
            else{

                //perform check the maximum num rows that can retrieve to be 1 only
                if(mysql_num_rows($executeQuery) === MAXIMUM_USER){
                    
                    $row = mysql_fetch_array($executeQuery);
                    //return the array ID1, act1, ID2, act2      
                    return $row;
                }
                else{

                    //if there is no records about this email or the number of email exist in databse > 1
                    return false;
                }
            } 
        }

        /*==================================================================

            @this function return the mac address of the phone using reg ID
            @param string regID
            @return the regID of the phone
            @this function is used for android only

        =================================================================*/
        public function retrieveMacPhoneUsingRegID($regID){

            //the query: select phone reg ID from phone information table where phone mac address = ''
            $query = sprintf("SELECT ".PHONE_INFO_MAC_COL." FROM "
                                      .PHONE_INFORMATION_TABLE." WHERE "
                                      .PHONE_INFO_REGID_COL." = '%s' ",
                              mysql_real_escape_string($regID));

            //execute the query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)

                //query failed to execute
                die();
            
            else{

                //perform check the maximum num rows that can retrieve to be 1 only
                if(mysql_num_rows($executeQuery) === MAXIMUM_REGID_PHONE){
                    
                    $row = mysql_fetch_array($executeQuery);
                    
                    return $row[0];
                }
                else{

                    //if there is no records about this email or the number of email exist in databse > 1
                    return false;
                }
            }
        }

        /*===============================================================================

            @return the notification column
            @depends on the action, the return will be an array of column or just one column only
            @this function is used on iOSdataChecking and doing in long polling for user

        ===============================================================================*/
        public function retrieveNotification($userID, $action = null){
            //select trac, loc, contact from noti table when userID = ''
             $query = sprintf("SELECT ".NOTI_TRACK_COL.","
                                       .NOTI_LOCK_COL.","
                                       .NOTI_B_CONTACT_COL.","
                                       .NOTI_IMG_CAP_COL." FROM "
                                       .NOTIFICATION_TABLE." WHERE "
                                       .NOTI_USER_ID_COL." = '%s'",
                               mysql_real_escape_string($userID));

              //execute the query
            
            $executeQuery = mysql_query($query);
            if(!$executeQuery){

                //query fail to execute
                die();
            }
            else{
                if(mysql_num_rows($executeQuery) == MAXIMUM_REGID_PHONE){
                    
                    $row = mysql_fetch_array($executeQuery);
                    
                    if(is_null($action))
                        return $row;
                    else{
                        switch ($action) {
                            //start track is sent from broser when user start to track the phone
                            case START_TRACK:
                            case TEST_TRACK:
                                return $row[0];
                                break;
                            case LOCK:
                                return $row[1];
                                break;
                            case BACKUP_CONTACT:
                                return $row[2];
                                break;
                            //when phone send ok then send next to check if the phone has sent the location yet
                            case TRACK:
                                return $row[0];
                                break;
                            case IMAGE_CAPTURE:
                                return $row[3];
                                break;
                            default:
                                return false;
                                break;
                        }
                    }
                }
                else
                    return false;
            }
        }

        /*============================

            @retrieve the location of the phone according to register ID
            @because we just need the register ID to be primary key in Phone Information table and it is easier for the browser to take out the value because the browser only have @register ID 
            @param string regID
            @return array of location

        =============================*/
        public function retrievePhoneLocation($regID){

            //query: SELECT lat, long, acc, bat from information table where regID = ''
            $query = sprintf("SELECT ".PHONE_INFO_LAT_COL.","
                                      .PHONE_INFO_LONG_COL.","
                                      .PHONE_INFO_ACC_COL.","
                                      .PHONE_INFO_BAT_COL." FROM "
                                      .PHONE_INFORMATION_TABLE." WHERE "
                                      .PHONE_INFO_REGID_COL." = '%s'",
                               mysql_real_escape_string($regID));

            //execute query
            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){

                //query fail to execute
                return false;
            }
            else{
                if(mysql_num_rows($executeQuery) == MAXIMUM_REGID_PHONE){
                    
                    //query execute successfully
                    $row = mysql_fetch_array($executeQuery);
                    
                    //return array of return value 
                    return $row;
                }
                else
                    return false;
            }
        }

        /*=====================================================================

            @retrieve the macphone/ regID from phone user table
            @depend on android or ios, it will return array of regID or macPhone
            @param int userId, bool isAndroid
            @return array

        ======================================================================*/
        public function retrieveMacPhoneOrRegIDFromPhoneUserTableUsingUserID($userID, $isAndroid = true){
            
            //default condition
            $returnValueCol = ANDROID_USER_MAC_COL;
            $tableName      = ANDROID_USER_TABLE;
            $firstIDCol     = ANDROID_FIRST_USER_ID_COL;
            $firstActCol    = ANDROID_FIRST_USER_ACT_COL;
            $secondIDCol    = ANDROID_SECOND_USER_ID_COL;
            $secondActCol   = ANDROID_SECOND_USER_ACT_COL;

            if(!$isAndroid){
                
                $returnValueCol = IOS_USER_REGID_COL;
                $tableName      = IOS_USER_TABLE;
                $firstIDCol     = IOS_FIRST_USER_ID_COL;
                $firstActCol    = IOS_FIRST_USER_ACT_COL;
                $secondIDCol    = IOS_SECOND_USER_ID_COL;
                $secondActCol   = IOS_SECOND_USER_ACT_COL;

            }

            //query: select iosRegID/androidMacphone from table where firstId = '' and active or secondID = '' and active
            $query = sprintf("SELECT $returnValueCol FROM $tableName WHERE ($firstIDCol = '%s' AND $firstActCol = '%s') OR ($secondIDCol = '%s' AND $secondActCol = '%s')",
                              mysql_real_escape_string($userID),
                              mysql_real_escape_string(USER_ACTIVE),
                              mysql_real_escape_string($userID),
                              mysql_real_escape_string(USER_ACTIVE));

            $executeQuery = mysql_query($query);
            //echo $query;
            if(!$executeQuery){

                //query fail to execute
                return false;
            }
            else{
                $returnArray = array();

                while($row = mysql_fetch_array($executeQuery))
                    array_push($returnArray, $row[0]);

                //depend on android or ios then return array of regID or macPhone
                return $returnArray;
            }
        }

        /*========================================================================

            @this function is used on android side only
            @it will retrieve the list of registeId from android phone using macPhone
            @param array macPhoneList
            @return array of regID

        ==========================================================================*/
        public function retrieveRegIDFromMacPhoneList($macPhoneList){
            
            //list of regID
            $regID = array();

            if(!is_null($macPhoneList)){

                foreach($macPhoneList as $macPhone){

                    //query: select phone regid col from phone info table where mac col = ''
                    $query = sprintf("SELECT ".PHONE_INFO_REGID_COL." FROM "
                                              .PHONE_INFORMATION_TABLE." WHERE "
                                              .PHONE_INFO_MAC_COL." = '%s'",
                                      mysql_real_escape_string($macPhone));    
                     //execute the query
                     $executeQuery = mysql_query($query);

                    if(!$executeQuery){

                        //query fail to execute
                        die();
                    }
                    else{
                        if(mysql_num_rows($executeQuery) == MAXIMUM_USER){
                            
                            $row = mysql_fetch_array($executeQuery);
                            
                            //push the value has just retrieve the list of RegisterID
                            array_push($regID, $row[0]);
                        }
                        else
                            return false;
                    }
                }
            }

            return $regID;
        }

        /*==================================================================

            @this function is used to retrieve the date and user id from token
            @this function is only used for password reset

        ===================================================================*/
        public function retrieveUserIDUsingToken($token){
            //the query to execute
            $query = sprintf("SELECT ".USERS_PASSWORD_ID_COL.",".USERS_PASSWORD_TOKEN_DATE_COL." FROM ".USERS_PASSWORD_HANDLE_TABLE." WHERE ".USERS_PASSWORD_TOKEN_COL." = '%s' ",
                              mysql_real_escape_string($token));

            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){
                die();
            }
            else{
                if(mysql_num_rows($executeQuery) == MAXIMUM_USER){

                    $row = mysql_fetch_array($executeQuery);
                    return $row;
                }
                else
                    return false;
            }
        }

        /*============================================================

            @retrieve the user directory from the hash directory table

        ===========================================================*/
        public function retrieveDirectory($hashDir, $folderName){
            //the query to execute
            $query = sprintf("SELECT ".DIRECTORY_COL." FROM ".HASH_DIRECTORY_TABLE." WHERE ".HASH_DIRECTORY_COL." = '%s' ",
                              mysql_real_escape_string($hashDire));

            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){
                die();
            }
            else{
                if(mysql_num_rows($executeQuery) == MAXIMUM_USER){

                    $row = mysql_fetch_array($executeQuery);
                    return $row.'/'.$folderName;
                }
                else
                    return false;
            }
        }

        /*============================================

            @retrieve the email using user ID
            @this function is used on reset password

        =============================================*/
        public function retrieveEmailUsingUserID($userID){
            //the query to execute
            $query = sprintf("SELECT ".USER_INFO_EMAIL_COL." FROM ".USERS_INFORMATION_TABLE." WHERE ".USER_INFO_ID_COL." = '%s' ",
                              mysql_real_escape_string($userID));

            $executeQuery = mysql_query($query);
            if(!$executeQuery){
                die();
            }
            else{
            	$row = mysql_fetch_array($executeQuery);
                return $row[0];
            }
        }

        public function retrieveImageNum($userID){
            //select trac, loc, contact from noti table when userID = ''
             $query = sprintf("SELECT ".NOTI_EXPECTED_IMAGE_COL." FROM "
                                       .NOTIFICATION_TABLE." WHERE "
                                       .NOTI_USER_ID_COL." = '%s'",
                               mysql_real_escape_string($userID));

              //execute the query
            
            $executeQuery = mysql_query($query);
            if(!$executeQuery){

                //query fail to execute
                die();
            }
            else{
                if(mysql_num_rows($executeQuery) == MAXIMUM_REGID_PHONE){
                    
                    $row = mysql_fetch_array($executeQuery);
                    
                    return $row[0];
                }
                else
                    return false;
            }
        }
        
        public function retrieve_iOS_NotiTokenUsingRegID($regID){
       	    //the query to execute
            $query = sprintf("SELECT ".IOS_PUSH_TOKEN." FROM ".IOS_USER_TABLE." WHERE ".IOS_USER_REGID_COL." = '%s' ",
                              mysql_real_escape_string($regID));

            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){
                die();
            }
            else{
                if(mysql_num_rows($executeQuery) == MAXIMUM_USER){

                    $row = mysql_fetch_array($executeQuery);
                    return $row[0];
                }
                else
                    return false;
            }
        }

		public function retrieve_iOS_NotiTokenUsingUserID($userID){
			//the query to execute
            $query = sprintf("SELECT ".IOS_PUSH_TOKEN." FROM ".IOS_USER_TABLE." WHERE ".IOS_FIRST_USER_ID_COL." = '%s' ",
                              mysql_real_escape_string($userID));

            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){
                return false;
            }
            else{
                if(mysql_num_rows($executeQuery) != 0){
                    //$row = mysql_fetch_array($executeQuery);
                    $returnArray = array();
					//$row = mysql_fetch_array($executeQuery);
                	while($row = mysql_fetch_array($executeQuery)){
                		array_push($returnArray, $row[IOS_PUSH_TOKEN]);
                	}
                    	
                	return $returnArray;
                } else {
                	return false;
                }
            }
		}
		public function retrieve_android_registrationids_using_userid($userID){
			//the query to execute
            $query = sprintf("SELECT ".ANDROID_REGISTRATION_ID_COL." FROM ".ANDROID_USER_TABLE." WHERE ".ANDROID_FIRST_USER_ID_COL." = '%s' ",
                              mysql_real_escape_string($userID));

            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){
                return false;
            }
            else{
                if(mysql_num_rows($executeQuery) != 0){
                    //$row = mysql_fetch_array($executeQuery);
                    $returnArray = array();
					//$row = mysql_fetch_array($executeQuery);
                	while($row = mysql_fetch_array($executeQuery)){
                		array_push($returnArray, $row[ANDROID_REGISTRATION_ID_COL]);
                	}
                    	
                	return $returnArray;
                } else {
                	return false;
                }
            }
		}
        /*==================================================================

            @retrieve the location of the protag inside the database
            @it depends on the user ID to retrieve a list of protag
            @param userID
            @return array as defined (0 =>(location), (1) => (location) ...)

        ==================================================================*/
        public function retrieveProtagInformation($userID){

            //query: SELECT lat, long, acc, bat from information table where regID = ''
            $query = sprintf("SELECT ".PROTAG_INFO_LAT_COL.","
                                      .PROTAG_INFO_LONG_COL.","
                                      .PROTAG_INFO_NAME_COL.","
                                      .PROTAG_INFO_LAST_DATE_COL.","
                                      .PROTAG_INFO_MAC_COL.","
                                      .PROTAG_INFO_IS_LOST_COL.","
                                      .PROTAG_INFO_SERIAL_COL." FROM " 
                                      .PROTAG_INFORMATION_TABLE." WHERE "
                                      .PROTAG_INFO_USER_ID_COL." = '%s'",
                               mysql_real_escape_string($userID));


            //execute query
            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){

                //query fail to execute
                return false;
            }
            else{
                    
                    if(mysql_num_rows($executeQuery) >= MAXIMUM_PROTAG_MAC){

                        $arr = array();

                        while($row = mysql_fetch_array($executeQuery))
                            array_push($arr, array('protag' => $row));

                        return $arr;
                    }
                    else
                        return false;
            }
        }
		
		/*==================================================================

            @retrieve the location of the protag inside the database
            @it depends on the user ID to retrieve a list of protag
            @param serialNum
            @return the info of the protag.

        ==================================================================*/
        public function retrieveProtagInformationViaSerialNum($serialNum){

            //query: SELECT lat, long, acc, bat from information table where regID = ''
            $query = sprintf("SELECT * FROM "
                                      .PROTAG_INFORMATION_TABLE." WHERE "
                                      .PROTAG_INFO_SERIAL_COL." = '%s'",
                               mysql_real_escape_string($serialNum));

            //execute query
            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){

                //query fail to execute
                return false;
            }
            else{
                    if(mysql_num_rows($executeQuery) >= MAXIMUM_PROTAG_MAC){
                        $row = mysql_fetch_array($executeQuery);
                        return $row;
                    }
                    else
                        return false;
            }
        }

        public function retrieveProtagInformationViaMacAddr($mac_addr){
            $query = sprintf("SELECT * FROM "
                                      .PROTAG_INFORMATION_TABLE." WHERE "
                                      .PROTAG_INFO_MAC_COL." = '%s'",
                               mysql_real_escape_string($mac_addr));

            //execute query
            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){

                //query fail to execute
                return false;
            }
            else{
                    if(mysql_num_rows($executeQuery) >= MAXIMUM_PROTAG_MAC){
                        $row = mysql_fetch_array($executeQuery);
                        return $row;
                    }
                    else
                        return false;
            } 
        }        
        public function retrieveFoundReportMessageCount($macAddr){
            $query = sprintf("SELECT count(*) FROM ".NONUSER_FOUND_REPORT_TABLE." WHERE "
                                                    .NONUSER_FOUND_REPORT_MAC_COL." = '%s' AND "
                                                    .NONUSER_FOUND_REPORT_ACTIVE_COL." = 1" , 
                                                    mysql_real_escape_string($macAddr));

            $executeQuery = mysql_query($query);
            $count = mysql_fetch_array($executeQuery, MYSQL_NUM);
            return $count[0];
        }
		
		public function retrieveFoundReport($macAddr){
            $query = sprintf("SELECT * FROM ".NONUSER_FOUND_REPORT_TABLE." WHERE "
                                             .NONUSER_FOUND_REPORT_MAC_COL." = '%s' AND "
                                             .NONUSER_FOUND_REPORT_ACTIVE_COL." = 1" , 
                                             mysql_real_escape_string($macAddr));

            $executeQuery = mysql_query($query);
            return mysql_fetch_array($executeQuery);
        }

		/*==================================================================

            @retrieve the lost status of the protag inside the database
            @it depends on the mac address of the protag
            @param macAddress
            @return an integer. (0 -> not lost, 1 -> lost， -1 -> database error, -2 -> no such protag)

        ==================================================================*/
        public function retrieveProtagStatus($macAddress){

            $query = sprintf("SELECT ".PROTAG_INFO_IS_LOST_COL." FROM "
                                      .PROTAG_INFORMATION_TABLE." WHERE "
                                      .PROTAG_INFO_MAC_COL." = '%s'",
                               mysql_real_escape_string($macAddress));

            //execute query
            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){

                //no result
                return -1;
            }
            else if(mysql_num_rows($executeQuery) == 0){
                return -2;
            } else {
            	$row = mysql_fetch_array($executeQuery, MYSQL_NUM);
				return $row[0];
            }
        }
		
		public function retrieveProtagOwnerID($mac_addr){
			$query = sprintf("SELECT ".PROTAG_INFO_USER_ID_COL." FROM "
                                      .PROTAG_INFORMATION_TABLE." WHERE "
                                      .PROTAG_INFO_MAC_COL." = '%s'",
                               mysql_real_escape_string($mac_addr));
							   
	        $executeQuery = mysql_query($query);
		    if(!$executeQuery){

                //no result
                return FALSE;
            }
            else if(mysql_num_rows($executeQuery) == 0){
                return FALSE;
            } else {
            	$row = mysql_fetch_array($executeQuery, MYSQL_NUM);
				return $row[0];
            }
		}
		
		/*==================================================================

            @retrieve the lost report of the protag inside the database
            @param macAddress
            @return an integer. (0 -> not lost, 1 -> lost， -1 -> database error, -2 -> no such report)

        ==================================================================*/
        public function retrieveLostReport($macAddress){

            //query: SELECT lat, long, acc, bat from information table where regID = ''
            $query = sprintf("SELECT * FROM "
                                      .PROTAG_LOST_REPORT_TABLE." WHERE "
                                      .PROTAG_LOST_REPORT_MAC_ADDR_COL." = '%s' AND "
                                      .PROTAG_LOST_REPORT_ACTIVE_COL."= TRUE",
                               mysql_real_escape_string($macAddress));

            //execute query
            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){
                return -1;
            }
            else if(mysql_num_rows($executeQuery) == 0){
                return -2;
            } else {
            	$row = mysql_fetch_array($executeQuery, MYSQL_ASSOC);
				return $row;
            }
        }

        /*=================================================
            
            @retrieve the phone name according to the regID
            @param regID
        
        =================================================*/
        public function retrievePhoneName($regID){
            //the query to execute
            $query = sprintf("SELECT ".PHONE_INFO_NAME_COL." FROM ".PHONE_INFORMATION_TABLE." WHERE ".PHONE_INFO_REGID_COL." = '%s' ",
                              mysql_real_escape_string($regID));

            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){
                die();
            }
            else{
                if(mysql_num_rows($executeQuery) == MAXIMUM_USER){

                    $row = mysql_fetch_array($executeQuery);
                    return $row[0];
                }
                else
                    return false;
            }
        }

        public function retrievePhoneLostNotification($macPhone, $regID){

            $columnCondition = PHONE_INFO_MAC_COL;
            $conditionValue  = $macPhone;

            if(is_null($macPhone)){
                $columnCondition = PHONE_INFO_REGID_COL;
                $conditionValue  = $regID;
            }

            //the query to execute
            $query = sprintf("SELECT ".PHONE_INFO_LOST_COL." FROM ".PHONE_INFORMATION_TABLE." WHERE ".$columnCondition." = '%s' ",
                              mysql_real_escape_string($conditionValue));

            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){
                die();
            }
            else{
                if(mysql_num_rows($executeQuery) == MAXIMUM_USER){

                    $row = mysql_fetch_array($executeQuery);
                    return $row[0];
                }
                else
                    return false;
            }
        }

        public function retrievePhoneLocationLastDateTime($macPhone, $regID){

            $columnCondition = PHONE_INFO_MAC_COL;
            $conditionValue  = $macPhone;

            if(is_null($macPhone)){
                $columnCondition = PHONE_INFO_REGID_COL;
                $conditionValue  = $regID;
            }

            //the query to execute
            $query = sprintf("SELECT ".PHONE_INFO_DATE_CREATE_COL." FROM ".PHONE_INFORMATION_TABLE." WHERE ".$columnCondition." = '%s' ",
                              mysql_real_escape_string($conditionValue));

            $executeQuery = mysql_query($query);
            
            if(!$executeQuery){
                die();
            }
            else{
                if(mysql_num_rows($executeQuery) == MAXIMUM_USER){

                    $row = mysql_fetch_array($executeQuery);
                    return $row[0];
                }
                else
                    return false;
            }
        }

        public function retrieveUserActivity($userID){              
                //the query to execute
                    $query = sprintf("SELECT ".ACTIVITY_USER_ACTIVITY_COL." FROM ".ACTIVITY_UPDATES_TABLE." WHERE ".ACTIVITY_USER_ID_COL." = '%s' ",
                                  mysql_real_escape_string($userID));
    
                    $executeQuery = mysql_query($query);
                
                if(!$executeQuery || mysql_num_rows($executeQuery) == 0){
                    return "";
                }else{
                    $row = mysql_fetch_array($executeQuery);
                            return $row[0];
                }
        }
	}
?>