<?php
	/*=====================================================
		@this file is used to implement functions in browser
	======================================================*/
	require_once 'db_functions.inc';

	class protag extends DB_Functions{

		/*==================================
	   		@constructor
	   	==================================*/
	   	function __construct() {

            $this -> validate = new validate();
            $this -> retrieve = new dataRetrieve();
            $this -> store    = new dataStore();
            $this -> display  = new dataDisplay();
            $this -> update   = new dataUpdate();
	    }
	
    	/*==================================
    		@destructor
    	==================================*/
    	function __destruct() {

    	}

    	/*=========================================================================
			
			@this function check if the protag is inside the database
			@if it is not inside then perform store the protag card
			@if it is inside then perform update the information for the protag
			@the dateCreate will not be neccessary if we perform the update function

    	===========================================================================*/
    	public function prStoreProtagInformation($macProtag, $userID, $protagName, $latitude, $longitude, $dateCreate = null, $lastDateKnown){
    		
    		//protag does exist in the database
    		if($this -> validate ->  isMacProtagExist($macProtag)){

    			//perform update the protag information
    			$this -> update -> updateProtagInformation($macProtag, $userID, $protagName, $latitude, $longitude, $lastDateKnown);

    		}
    		else{
                
    			//if the protag does not exist then perform insert into the database
    			$this -> store -> storeProtagInformation($macProtag, $userID, $protagName, $latitude, $longitude, $dateCreate, $lastDateKnown);
                
    		}
    	}

        /*=========================================================================
            
            @this function check if the FoundReport is inside the database
            @if it is not inside then perform storing the foundReport
            @if it is inside then make all the other report inative, only the latest report active

        ===========================================================================*/
        public function prStoreFoundReport($mac_protag, $message, $reporter_name, $reporter_email, $reporter_contact_number){
            //foundReport does exist in the database 

            //store the foundReport into the database
            $this -> store -> storeNonUserFoundReport($mac_protag, $message, $reporter_name, $reporter_email, $reporter_contact_number);
            
        }

        public function prRetrieveFoundReportCount($mac_addr){
            return $this -> retrieve -> retrieveFoundReportMessageCount($mac_addr);
        }
		
		public function prRetrieveFoundReport($mac_addr){
			return $this -> retrieve -> retrieveFoundReport($mac_addr);
		}

    	/*=============================================================

			@this function return all the protag information to browser
			@parm hashUserID
			@return boolean value

    	=============================================================*/
    	public function prRetrieveProtagInformation($hashUserID){

    		//check the user ID 
    		if($userID = $this -> retrieve ->  retrieveUserID(null, $hashUserID, true)){

    			//return array of protag for user
	    		if($protagList = $this -> retrieve -> retrieveProtagInformation($userID)){

	    			//display json
	    			$this -> display -> displayJSON('SUCCESS', null, $protagList);
	    			return true;
	    		}

	    		$this -> display -> displayJSON('FAIL', 'NO_PROTAG_DETECT');
	    		return false;
    		}

    		$this -> display -> displayJSON('FAIL', 'NO_USER_EXIST');
    		return false;
    	}

        /*=============================================================

            @this function return all the protag information to browser
            @parm serialNum
            @return boolean value

        =============================================================*/
        public function prRetrieveProtagInformationViaSerialNum($serialNum){
            if($this -> retrieve -> retrieveProtagInformationViaSerialNum($serialNum)){
                $protagInfo= $this -> retrieve -> retrieveProtagInformationViaSerialNum($serialNum);
                return $protagInfo;
            }
            return false;
        }
		
        public function prRetrieveProtagInformationByMacAddr($mac_addr){
            //check the mac_addr
            if($mac_addr = $this -> retrieve ->  retrieveMacAddr(null, $hashUserID, true)){

                //return array of protag for user
                if($protagList = $this -> retrieve -> retrieveProtagInformation($userID)){

                    //display json
                    $this -> display -> displayJSON('SUCCESS', null, $protagList);
                    return true;
                }

                $this -> display -> displayJSON('FAIL', 'NO_PROTAG_DETECT');
                return false;
            } 
        }
		
		
		
		public function prRetrieveProtagOwnerEmail($mac_addr){
			$owner_id = $this -> retrieve -> retrieveProtagOwnerID($mac_addr);
			if ($owner_id) {
				return $this -> retrieve -> retrieveEmailUsingUserID($owner_id);
			} else {
				return false;
			}
		}
		
		
		public function prCheckProtagLostStatus($macAddress){
			return $this -> retrieve -> retrieveProtagStatus($macAddress);			
		}
		
		public function prRetrieveProtagLostReport($macAddress){
			return $this -> retrieve -> retrieveLostReport($macAddress); 
		}
		
		public function prReportLost($location, $message, $will_notify, $mac_addr, $contact_name, $contact_number, $description){
			return $this -> store -> storeProtagLostReport($location, $message, $will_notify, $mac_addr, $contact_name, $contact_number, $description);
		}
		
		public function prUpdateProtagLocation($mac_addr, $latitude, $longitude){
			return $this -> update -> updateProtagLocation($mac_addr, $latitude, $longitude);
		}
		
		public function prProtagFound($mac_addr){
			return $this -> update -> protagFound($mac_addr);
		}
		
		public function prRetrieveProtagOwnerId($mac_addr){
			$result = $this -> retrieve -> retrieveProtagInformationViaMacAddr($mac_addr);
			if(!$result){
				return $result;
			} else {
				return $result[PROTAG_INFO_USER_ID_COL];
			}
		}
		
		public function prRetrieveProtagName($mac_addr){
			$result = $this -> retrieve -> retrieveProtagInformationViaMacAddr($mac_addr);
			if(!$result){
				return $result;
			} else {
				return $result[PROTAG_INFO_NAME_COL];
			}
		}
		
		public function prSetSerialNumber($mac_addr, $serial_number){
			return $this -> update -> updateProtagSerial($mac_addr, $serial_number);
		}
		
		public function prDeleteProtag($mac_addr){
			return $this -> update -> deleteProtag($mac_addr);
		}
    }
?>