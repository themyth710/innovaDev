<?php
	/*================================================
		@all neccessary functions for update data from server
	================================================*/

	class dataUpdate{

        //control hashing data
  		  private $update;
  	   	/*==================================
  	   		@constructor
  	   	==================================*/
  	   	function __construct() {
              require_once(dirname(__FILE__).'/../db_connect.inc');
              
              // connecting to database
              $this -> update = new DB_Connect();
              $this -> update -> connect();
  	    }
  	
      	/*==================================
      		@destructor
      	==================================*/
      	function __destruct() {
             
      	}

    	 /*===============================================================
            @perform storing hashed data on the database
            @param string hasedData, tablename where the hashed will be stored
            @param string columname where the hashed is store
            @param string columnCondition and conditionValue to check the row which the hashed is stored
            @return string failed if the query is not successfully execute
            @return success if query is successfully executed
        ===============================================================*/
        public function updateHashData($hashedData, $tableName, $columnName, $columnCondition, $conditionValue){
            
            //the query to execute
            $query = sprintf("UPDATE %s SET $columnName = '%s' WHERE %s = '%s'", 
                             mysql_real_escape_string($tableName),
                             mysql_real_escape_string($hashedData),
                             mysql_real_escape_string($columnCondition),
                             mysql_real_escape_string($conditionValue));

            //execute the query
            $executeQuery = mysql_query($query);
            
            //check the query and free the result
            if(!$executeQuery){

                //query fail to execute
                return false;
            }
            else{

                //query execute successfully
                return true;
            }
        }

        /*======================================================================================================================

            @update the user ID in phone user table
            @param string macphone/regID, int userID (this user id can be first or second user id depends on the column name)
            @set active or inactive according to string columnActiveName and columnActivevalue
            @this function can also be used to set just the active or inactive for user(which is used in remove device function)
            @return success query

        =======================================================================================================================*/
        public function updatePhoneUser($regID, $macPhone, $userID = null, $columnName = null, $columnActiveName, $columnActiveValue){

            //default condition
            $tableName           = ANDROID_USER_TABLE;
            $columnCondition     = ANDROID_USER_MAC_COL;

            if(!is_null($regID)){
                
                $tableName       = IOS_USER_TABLE;
                $columnCondition = IOS_USER_REGID_COL;
                $macPhone        = $regID;

            }

            if(is_null($userID)){
                
                //update the active or inactive for user
                $query = sprintf("UPDATE $tableName SET $columnActiveName = '%s' WHERE $columnCondition = '%s'",
                                  mysql_real_escape_string($columnActiveValue),
                                  mysql_real_escape_string($macPhone));
            }
            else{

                $query = sprintf("UPDATE $tableName SET $columnName = '%s', $columnActiveName = '%s' WHERE $columnCondition = '%s'", 
                                    mysql_real_escape_string($userID),
                                    mysql_real_escape_string($columnActiveValue),
                                    mysql_real_escape_string($macPhone));
            }

            //execute the query
            $executeQuery = mysql_query($query);

            //check the query and free the result
            if(!$executeQuery){

                //query fail to execute
                return false;
            }
            else{

                //query execute successfully
                return true;
            }
        }

        /*=================================================================================
            @this function is used for android only
            @find the mac address of the phone inside phone information table and update it
            @param string
            @return success of query
        ================================================================================*/
        public function updateRegIDForAndroidPhone($macPhone, $regID){

            $query = sprintf("UPDATE ".PHONE_INFORMATION_TABLE." SET ".PHONE_INFO_REGID_COL." = '%s' WHERE ".PHONE_INFO_MAC_COL." = '%s'", 
                              mysql_real_escape_string($regID),
                              mysql_real_escape_string($macPhone));

            //execute the query
            $executeQuery = mysql_query($query);

            //check the query and free the result
            if(!$executeQuery){

                //query fail to execute
                return false;
            }
            else{

                //query execute successfully
                return true;
            }
        } 
        /*==========================================================================
        
            @update the notication table according to the command sent from browser
            @param int, string, int
            @return success of query

        ==========================================================================*/  
        public function updateNotification($userID, $action, $value){
            
            //default value
            $tableName           = NOTIFICATION_TABLE;
            $columnCondition     = NOTI_USER_ID_COL;
            $columnName          = NOTI_TRACK_COL;

            switch($action){
                //send from browser
                case START_TRACK:
                case TEST_TRACK:
                case STOP_TRACK:
                    $columnName  = NOTI_TRACK_COL;
                    break;
                case LOCK:
                    $columnName  = NOTI_LOCK_COL;
                    break;
                case BACKUP_CONTACT:
                    $columnName  = NOTI_B_CONTACT_COL;
                    break;
                case IMAGE_CAPTURE:
                    $columnName  = NOTI_IMG_CAP_COL;
                    break;

                //send from phone
                case OK_TRACK:
                    $columnName  = NOTI_TRACK_COL;
                    break;
                case OK_LOCK:
                    $columnName  = NOTI_LOCK_COL;
                    break;
                case OK_B_CONTACT:
                    $columnName  = NOTI_B_CONTACT_COL;
                    break;
                case SEND_TRACK_DATA:
                    $columnName  = NOTI_TRACK_COL;
                    break;
                case OK_IMAGE_CAPTURE:
                    $columnName  = NOTI_IMG_CAP_COL;
                    break;
                default:
                    return false;
                    break;
            }

            $query = sprintf("UPDATE $tableName SET $columnName = '%s' WHERE $columnCondition = '%s'", 
                              mysql_real_escape_string($value),
                              mysql_real_escape_string($userID));

            //execute the query
            $executeQuery = mysql_query($query);

            //check the query and free the result
            if(!$executeQuery){

                //query fail to execute
                return false;
            }
            else{

                //query execute successfully
                return true;
            }
        }

        /* ============================================================================================== 
            @update the location of the phone in phone information table
            @this function is used for both ios and android depends on whether macphone or regID is null
        ===============================================================================================*/

        public function updatePhoneLocation($macPhone, $regID, $lat, $long, $acc, $bat, $dateCreate){
            if($macPhone == null){
                $query = sprintf("UPDATE ".PHONE_INFORMATION_TABLE." SET ".PHONE_INFO_LAT_COL        ." = '%s',"
                                                                          .PHONE_INFO_LONG_COL       ." = '%s',"
                                                                          .PHONE_INFO_ACC_COL        ." = '%s',"
                                                                          .PHONE_INFO_BAT_COL        ." = '%s',"
                                                                          .PHONE_INFO_DATE_CREATE_COL." = '%s' WHERE "
                                                                          .PHONE_INFO_REGID_COL      ." = '%s'", 
                                  mysql_real_escape_string($lat),
                                  mysql_real_escape_string($long),
                                  mysql_real_escape_string($acc),
                                  mysql_real_escape_string($bat),
                                  mysql_real_escape_string($dateCreate),
                                  mysql_real_escape_string($regID));
            }
            else if($regID == null){
                $query = sprintf("UPDATE ".PHONE_INFORMATION_TABLE." SET ".PHONE_INFO_LAT_COL        ." = '%s',"
                                                                          .PHONE_INFO_LONG_COL       ." = '%s',"
                                                                          .PHONE_INFO_ACC_COL        ." = '%s',"
                                                                          .PHONE_INFO_BAT_COL        ." = '%s',"
                                                                          .PHONE_INFO_DATE_CREATE_COL." = '%s' WHERE "
                                                                          .PHONE_INFO_MAC_COL        ." = '%s'", 
                                  mysql_real_escape_string($lat),
                                  mysql_real_escape_string($long),
                                  mysql_real_escape_string($acc),
                                  mysql_real_escape_string($bat),
                                  mysql_real_escape_string($dateCreate),
                                  mysql_real_escape_string($macPhone));
            }
            
            $executeQuery = mysql_query($query);

            if(!($executeQuery)){
                return false;
            }
            else{
                return true;
            }
        } 

        /*==========================================================================
          @this function is used to update the image capture number in the database
        ==========================================================================*/
        public function updateImageNumber($userID, $value){
            $tableName           = NOTIFICATION_TABLE;
            $columnCondition     = NOTI_USER_ID_COL;
            $columnName          = NOTI_EXPECTED_IMAGE_COL;

            $query = sprintf("UPDATE $tableName SET $columnName = '%s' WHERE $columnCondition = '%s'", 
                              mysql_real_escape_string($value),
                              mysql_real_escape_string($userID));

            //execute the query
            $executeQuery = mysql_query($query);

            //check the query and free the result
            if(!$executeQuery){

                //query fail to execute
                return false;
            }
            else{

                //query execute successfully
                return true;
            }
        }
        
         /*==========================================================================
          @this function is used to update the Notification Token for iOS
        ==========================================================================*/
        public function updateNotificationTokenForiOS($regID, $token){
            $tableName 		= IOS_USER_TABLE;
            $regIDColumnName	= IOS_USER_REGID_COL;
            $tokenColumnName 	= IOS_PUSH_TOKEN;
            
            $query = sprintf("UPDATE $tableName SET $tokenColumnName = '%s' WHERE $regIDColumnName = '%s'", 
                              mysql_real_escape_string($token),
                              mysql_real_escape_string($regID));

            //execute the query
            $executeQuery = mysql_query($query);

            //check the query and free the result
            if(!$executeQuery){
                //query fail to execute
                return false;
            }
            else{
                //query execute successfully
                return true;
            }
        }
		
		public function updateRegistrationIDForAndroid($phone_mac_ad, $reg_id){
            $query = sprintf("UPDATE ".ANDROID_USER_TABLE." SET ".ANDROID_REGISTRATION_ID_COL." = '%s' WHERE ".ANDROID_USER_MAC_COL." = '%s'", 
                              mysql_real_escape_string($reg_id),
                              mysql_real_escape_string($phone_mac_ad));

            //execute the query
            $executeQuery = mysql_query($query);

            //check the query and free the result
            if(!$executeQuery){
                //query fail to execute
                return false;
            }
            else{
                //query execute successfully
                return true;
            }
		}

        /*==================================================

            @update the protag infortion inside the database
            @the protag must exist inside the database
            @param as follow 

        ===================================================*/
        public function updateProtagInformation($macProtag, $userID, $protagName, $latitude, $longitude, $lastDateKnown){
           	$query = sprintf("UPDATE ".PROTAG_INFORMATION_TABLE." SET "  .PHONE_INFO_USER_ID_COL     ." = '%s',"
                                                                         .PHONE_INFO_NAME_COL        ." = '%s',"
                                                                         .PROTAG_INFO_LAT_COL        ." = '%s',"
                                                                         .PROTAG_INFO_LONG_COL       ." = '%s',"
                                                                         .PROTAG_INFO_LAST_DATE_COL  ." = '%s' WHERE "
                                                                         .PROTAG_INFO_MAC_COL        ." = '%s'", 
                                  mysql_real_escape_string($userID),
                                  mysql_real_escape_string($protagName),
                                  mysql_real_escape_string($latitude),
                                  mysql_real_escape_string($longitude),
                                  mysql_real_escape_string($lastDateKnown),
                                  mysql_real_escape_string($macProtag));
            
            $executeQuery = mysql_query($query);

            if(!($executeQuery)){
                return false;
            }
            else{
                return true;
            }
        }

		public function updateProtagSerial($mac_addr, $serial_num){
			$query = sprintf("UPDATE ".PROTAG_INFORMATION_TABLE." SET "  .PROTAG_INFO_SERIAL_COL     ." = '%s' WHERE "
                                                                         .PROTAG_INFO_MAC_COL        ." = '%s'", 
                                  mysql_real_escape_string($serial_num),
                                  mysql_real_escape_string($mac_addr));
            
            $executeQuery = mysql_query($query);
            if(!($executeQuery)){
                return false;
            }
            else{
                return true;
            }
		}


		/*==================================================

            @update the protag's location inside the database
            @the protag must exist inside the database
            @param as follow 

        ===================================================*/
        public function updateProtagLocation($macProtag, $latitude, $longitude){
             $query = sprintf("UPDATE ".PROTAG_INFORMATION_TABLE." SET "  .PROTAG_INFO_LAT_COL        ." = '%s',"
                                                                          .PROTAG_INFO_LONG_COL       ." = '%s' WHERE "
                                                                          .PROTAG_INFO_MAC_COL        ." = '%s'", 
                                  mysql_real_escape_string($latitude),
                                  mysql_real_escape_string($longitude),
                                  mysql_real_escape_string($macProtag));
            
            $executeQuery = mysql_query($query);

            if(!($executeQuery)){
                return false;
            }
            else{
                return true;
            }
        }
		
		/*==================================================

            @update the protag's isLost field inside the database,
		    @which means user has found his protag
            @the protag must exist inside the database
            @param as follow 

        ===================================================*/
        public function protagFound($macProtag){
             $query = sprintf("UPDATE ".PROTAG_INFORMATION_TABLE." SET "  .PROTAG_INFO_IS_LOST_COL        ." = 0 WHERE "
                                                                          .PROTAG_INFO_MAC_COL        ." = '%s'",
                                  mysql_real_escape_string($macProtag));
            
            $executeQuery = mysql_query($query);

            if(!($executeQuery)){
                return false;
            } else {
                $query = sprintf("UPDATE ".PROTAG_LOST_REPORT_TABLE." 
									SET ".PROTAG_LOST_REPORT_ACTIVE_COL." = 0 
									WHERE ".PROTAG_LOST_REPORT_MAC_ADDR_COL." = '%s' AND ".PROTAG_LOST_REPORT_ACTIVE_COL." = 1", mysql_real_escape_string($macProtag));
				$result = mysql_query($query);
				return true;
            }
        }
		
		public function deleteProtag($macProtag){
			$query = sprintf("DELETE FROM ".PROTAG_INFORMATION_TABLE." WHERE "
                                      .PROTAG_INFO_MAC_COL        ." = '%s'",
                                  mysql_real_escape_string($macProtag));
            
            $executeQuery = mysql_query($query);

            if(!($executeQuery)){
                return false;
            } else {
				return true;
            }
		}
        
        public function updatePhoneName($regID, $phoneName){
            $query = sprintf("UPDATE ".PHONE_INFORMATION_TABLE." SET ".PHONE_INFO_NAME_COL." = '%s' WHERE "
                                                                      .PHONE_INFO_REGID_COL." = '%s'", 
                                  mysql_real_escape_string($phoneName),
                                  mysql_real_escape_string($regID));

            $executeQuery = mysql_query($query);

            if(!($executeQuery)){
                return false;
            }
            else{
                return true;
            }
        }

        /*==================================================

			@update the activation account for user
			@param token to retrive the account information
			@return boolean varaibles

        ===================================================*/
		public function updateUserActivation($token){
			 $query = sprintf("UPDATE ".USERS_INFORMATION_TABLE." SET ".USER_INFO_ACTIVE_COL." = '%s' WHERE "
                                                                 .USER_INFO_TOKEN_COL." = '%s'", 
                                  mysql_real_escape_string(USER_ACTIVE),
                                  mysql_real_escape_string($token));

            $executeQuery = mysql_query($query);
			

            if(!($executeQuery)){
                return false;
            }
            else{
                return true;
            }
		}

		/*=====================================================

			@update the token if the token has already expired
			@or user has requested a new token
			@param token
			@param email
			@return boolean variables	

		=====================================================*/
		public function updateUserToken($newToken, $token = null, $email = null){

			$conditionColumn     = USER_INFO_EMAIL_COL;
			$conditionValue      = $email;

			if(!is_null($token)){
				$conditionColumn = USER_INFO_TOKEN_COL;
				$conditionValue  = $token;
			}

			$query = sprintf("UPDATE ".USERS_INFORMATION_TABLE." SET ".USER_INFO_TOKEN_COL." = '%s' WHERE "
                                                                .$conditionColumn." = '%s'", 
                        mysql_real_escape_string($newToken),
                        mysql_real_escape_string($conditionValue));

      $executeQuery = mysql_query($query);

      if(!($executeQuery)){
          return false;
      }
      else{
          return true;
      }
		}

    public function updatePhoneLostNotification($macPhone = null, $regID = null, $lostValue){
      
      $conditionColumn     = PHONE_INFO_MAC_COL;
      $conditionValue      = $macPhone;
      
      if(is_null($macPhone)){
        $conditionColumn     = PHONE_INFO_REGID_COL;
        $conditionValue      = $regID;
      }

      $query = sprintf("UPDATE ".PHONE_INFORMATION_TABLE." SET ".PHONE_INFO_LOST_COL." = '%s' WHERE "
                                                                .$conditionColumn." = '%s'", 
                        mysql_real_escape_string($lostValue),
                        mysql_real_escape_string($conditionValue));

      $executeQuery = mysql_query($query);

      if(!($executeQuery)){
          return false;
      }
      else{
          return true;
      }
    }
  }
?>