<?php
    /*================================================
		@all neccessary functions for retrieving data from server
	================================================*/

	class dataStore{

        //control hashing data
  		  private $store;
  	   	/*==================================
  	   		@constructor
  	   	==================================*/
  	   	function __construct() {
              require_once(dirname(__FILE__).'/../db_connect.inc');
              
              // connecting to database
              $this -> store = new DB_Connect();
              $this -> store -> connect();
  	    }
  	
      	/*==================================
      		@destructor
      	==================================*/
      	function __destruct() {
          
      	}

        /*===========================================

            @store the user information in tr_user_information table
            @param string email, password and dateCreate
            @return the success of execute query
            @the password here is hashed password

        ===========================================*/
        public function storeUserInformation($email, $password, $dateCreate, $active, $token, $tokenDate){

            //the query to execute
            $query = sprintf("INSERT INTO ".USERS_INFORMATION_TABLE.
                                        "(".USER_INFO_EMAIL_COL.","
                                           .USER_INFO_PASSWORD_COL.","
                                           .USER_INFO_DATE_CREATED_COL.","
                                           .USER_INFO_TOKEN_COL.","
                                           .USER_INFO_ACTIVE_COL.","
                                           .USER_INFO_TOKEN_DATE_CREATE_COL.") 
                              VALUES('%s', '%s', '%s', '%s', '%s', '%s')",
                              mysql_real_escape_string($email),
                              mysql_real_escape_string($password),
                              mysql_real_escape_string($dateCreate),
                              mysql_real_escape_string($token),
                              mysql_real_escape_string($active),
                              mysql_real_escape_string($tokenDate));
            
            //execute the query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)
                return false;
            else
                return true;
        }

        /*=========================================================================================
            
            @store the first user colum in phone user table
            @why we do not need the second User columm because if the phone is not exist in database
            @we have to store the first user first
            @if we have to store second user that means update the second user column
            @param int user Id , string regID/machphone
            @return success of query

        ===========================================================================================*/
        public function storePhoneFirstUser($userID, $macPhone, $regID = null){

            //default value
            $tableName           = ANDROID_USER_TABLE;
            $columnUserID        = ANDROID_FIRST_USER_ID_COL;
            $columnCondition     = ANDROID_USER_MAC_COL;

            if(!is_null($regID)){
                $tableName       = IOS_USER_TABLE;
                $columnName      = IOS_FIRST_USER_ID_COL;
                $columnCondition = IOS_USER_REGID_COL;
                $macPhone        = $regID;//change the macphone to regId if regID is not null
            }

            //the query to execute            
            $query = sprintf("INSERT INTO $tableName($columnUserID, $columnCondition) VALUES('%s', '%s')",
                              mysql_real_escape_string($userID),
                              mysql_real_escape_string($macPhone)); //notice the macphone has been changed if regID is not null
        
            //execute the query
            $executeQuery = mysql_query($query);
            
            if(!$executeQuery)
                return false;
            else
                return true;
        }

        /*==========================================================

            @store the phone information to database
            @this function is used when user register to server 
            @params string
            @return success of query

        ==========================================================*/
        public function storePhoneInformation($macPhone, $regID, $typePhone, $curLat = 0, $curLong = 0, $accuracy = 0, $battery = 0, $dateCreate, $phoneName, $imei){
            
            //check if phone is android or ios for type phone table id
            if($typePhone == ANDROID)
              $typePhoneID = ANDROID_ID;
            else
              $typePhoneID = IOS_ID;

            //the query to execute
            $query = sprintf("INSERT INTO ".PHONE_INFORMATION_TABLE."(".PHONE_INFO_MAC_COL.","
                                                                       .PHONE_INFO_REGID_COL.","
                                                                       .PHONE_INFO_PHONE_TYPE_COL.","
                                                                       .PHONE_INFO_LAT_COL.","
                                                                       .PHONE_INFO_LONG_COL.","
                                                                       .PHONE_INFO_ACC_COL.","
                                                                       .PHONE_INFO_BAT_COL.","
                                                                       .PHONE_INFO_DATE_CREATE_COL.","
                                                                       .PHONE_INFO_NAME_COL.","
                                                                       .PHONE_INFO_IMEI_COL.")  
                              VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
                              mysql_real_escape_string($macPhone),
                              mysql_real_escape_string($regID),
                              mysql_real_escape_string($typePhoneID),
                              mysql_real_escape_string($curLat),
                              mysql_real_escape_string($curLong),
                              mysql_real_escape_string($accuracy),
                              mysql_real_escape_string($battery),
                              mysql_real_escape_string($dateCreate),
                              mysql_real_escape_string($phoneName),
                              mysql_real_escape_string($imei));
            //execute the query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)
                return false;
            else
                return true;
        }

        /*==============================================================

            @store the notification corresponding with the user ID when
            @user has registered to system
            @param int userID
            @return success of query

        ==============================================================*/
        public function storeUserIDInNotificationTable($userID){
            
            $query = sprintf("INSERT INTO ".NOTIFICATION_TABLE."(".NOTI_USER_ID_COL.") 
                              VALUES( '%s' )",
                              mysql_real_escape_string($userID));

             //execute the query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)
                return false;
            else
                return true;
        }

        /*========================================================================= 
            @store the id in the password token table
            @this tble is used to retrieve password when user forgot their password
            @param int userId
            @return successs of query
        =========================================================================*/
        public function storePasswordTokenTable($userID){

            //the query to execute
            $query = sprintf("INSERT INTO ".USERS_PASSWORD_HANDLE_TABLE."(".USERS_PASSWORD_ID_COL.")  
                              VALUES('%s')",
                              mysql_real_escape_string($userID));

            //execute the query
            $executeQuery = mysql_query($query);

            if(!$executeQuery)
                return false;
            else
                return true;
        }

        /*===========================================

            @this function is not used in the system

        ===========================================*/
        public function storeDirectoryHash($directory, $hashValue){
          //the query to execute
          $query = sprintf("INSERT INTO ".HASH_DIRECTORY_TABLE."(".HASH_DIRECTORY_COL.",".DIRECTORY_COL.")  
                            VALUES('%s','%s')",
                            mysql_real_escape_string($hashValue),
                            mysql_real_escape_string($directory));

          //execute the query
          $executeQuery = mysql_query($query);

          if(!$executeQuery)
              return false;
          else
              return true;
        }

        /*=============================================

          @insert the data of the protag into database
          @param as follow

        ==============================================*/
        public function storeProtagInformation($macProtag, $userID, $protagName, $latitude, $longitude, $dateCreate, $lastDateKnown){
          //the query to execute
          $query = sprintf("INSERT INTO ".PROTAG_INFORMATION_TABLE."(".PROTAG_INFO_MAC_COL.","
                                                                      .PROTAG_INFO_USER_ID_COL.","
                                                                      .PROTAG_INFO_NAME_COL.","
                                                                      .PROTAG_INFO_LAT_COL.","
                                                                      .PROTAG_INFO_LONG_COL.","
                                                                      .PROTAG_INFO_DATE_CREATE_COL.","
                                                                      .PROTAG_INFO_LAST_DATE_COL.")  
                            VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s')",
                            mysql_real_escape_string($macProtag),
                            mysql_real_escape_string($userID),
                            mysql_real_escape_string($protagName),
                            mysql_real_escape_string($latitude),
                            mysql_real_escape_string($longitude),
                            mysql_real_escape_string($dateCreate),
                            mysql_real_escape_string($lastDateKnown));
          
          //execute the query
          $executeQuery = mysql_query($query);

          if(!$executeQuery)
              return false;
          else
              return true;
        }



        /*=============================================

          @insert the data of the lost report into database
          @param as follow

        ==============================================*/
		public function storeProtagLostReport($location, $message, $will_notify, $mac_addr, $contact_name, $contact_number, $description){
			$query = sprintf("UPDATE ".PROTAG_LOST_REPORT_TABLE." 
									SET ".PROTAG_LOST_REPORT_ACTIVE_COL." = 0 
									WHERE ".PROTAG_LOST_REPORT_MAC_ADDR_COL." = '%s' AND ".PROTAG_LOST_REPORT_ACTIVE_COL." = 1", mysql_real_escape_string($mac_addr));
			mysql_query($query);
			
			$query = sprintf("UPDATE ".PROTAG_INFORMATION_TABLE." 
									SET ".PROTAG_INFO_IS_LOST_COL." = 1
									WHERE ".PROTAG_INFO_MAC_COL." = '%s'", mysql_real_escape_string($mac_addr));
			mysql_query($query);
			$query = sprintf("INSERT INTO ".PROTAG_LOST_REPORT_TABLE."(".PROTAG_LOST_REPORT_LOCATION_COL.","
                                                                      	.PROTAG_LOST_REPORT_MESSAGE_COL.","
                                                                      	.PROTAG_LOST_REPORT_NOTIFY_COL.","
                                                                      	.PROTAG_LOST_REPORT_MAC_ADDR_COL.","
																		.PROTAG_LOST_REPORT_CONTACT_NAME_COL.","
																		.PROTAG_LOST_REPORT_CONTACT_NUMBER_COL.","
																		.PROTAG_LOST_REPORT_DESC_COL.")
                            VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s')",
                            mysql_real_escape_string($location),
                            mysql_real_escape_string($message),
                            mysql_real_escape_string($will_notify),
                            mysql_real_escape_string($mac_addr),
                            mysql_real_escape_string($contact_name),
                            mysql_real_escape_string($contact_number),
							mysql_real_escape_string($description));
			$result = mysql_query($query);
			return $result;
		}
        /*=============================================

          @insert the data of the foundReport into database
          @param as follow

        ==============================================*/
        public function storeNonUserFoundReport($mac_protag, $message, $reporter_name, $reporter_email, $reporter_contact_number){
          //the query to execute
          $query = sprintf("INSERT INTO ".NONUSER_FOUND_REPORT_TABLE."(".NONUSER_FOUND_REPORT_MAC_COL.","
                                                                      .NONUSER_FOUND_REPORT_NAME_COL.","
                                                                      .NONUSER_FOUND_REPORT_MESSAGE_COL.","
                                                                      .NONUSER_FOUND_REPORT_EMAIL.","
                                                                      .NONUSER_FOUND_REPORT_CONTACT.") 
                            VALUES('%s','%s','%s', '%s', '%s')",
                            mysql_real_escape_string($mac_protag),
                            mysql_real_escape_string($reporter_name),
                            mysql_real_escape_string($message),
                            mysql_real_escape_string($reporter_email),
                            mysql_real_escape_string($reporter_contact_number));
          //execute the query
          $executeQuery = mysql_query($query);

          if(!$executeQuery)
              return false;
          else
              return true;
        }

        /*=============================================
  
            @insert the data of the activity into database
            @param as follow
  
          ==============================================*/
          public function storeUserActivity($userID, $activity){
            //the query to execute
            $query = sprintf("INSERT INTO ".ACTIVITY_UPDATES_TABLE."(".ACTIVITY_USER_ID_COL.","
                                           .ACTIVITY_USER_ACTIVITY_COL.") 
                        VALUES('%s','%s')",
                        mysql_real_escape_string($userID),
                        mysql_real_escape_string($activity));
            
            //Activity stored in format
            //<log num><space><date and time display><use this [] to seperate other log>
            /*It is better to store everything in one column because it allows reordering of information
            after the max num of logs has been reached, but it requires more processing*/           
            
            //execute the query
            $executeQuery = mysql_query($query);
            
            if(!$executeQuery)
              return false;
            else
              return true;
          }
    }
?>