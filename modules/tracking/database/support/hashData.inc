<?php
	/*==========================================
		@API used to control the hashing of data
		@Used in db_functions.inc
	==========================================*/

	class hash{
		private $hash;

		/*==================================
	   		@constructor
	   	==================================*/
		function __construct() {
        	
			require_once(dirname(__FILE__).'/../db_connect.inc');
        	
        	// connecting to database
        	$this -> hash = new DB_Connect();
        	$this -> hash -> connect();
	    }

	    /*==================================
    		@destructor
    	==================================*/
    	function __destruct() {
    		
    	}	

	    /*==================================================================
		  	@Generate a random salt in the crypt(3) standard Blowfish format.
		  	@param int $cost Cost parameter from 4 to 31.
		  	@throws Exception on invalid cost parameter.
		  	@return string A Blowfish hash salt for use in PHP's crypt()
		==================================================================*/
		private function blowfishSalt($cost = 13)
		{
		    if (!is_numeric($cost) || $cost < 4 || $cost > 31) {
		        throw new Exception();
		    }

		    $rand 	= array();
		    for ($i = 0; $i < 8; $i += 1) {
		        $rand[] = pack('S', mt_rand(0, 0xffff));
		    }
		    
		    $rand[] = substr(microtime(), 2, 6);
		    $rand 	= sha1(implode('', $rand), true);
		    $salt 	= '$2a$' . sprintf('%02d', $cost) . '$';
		    $salt  .= strtr(substr(base64_encode($rand), 0, 22), array('+' => '.'));

		    return $salt;
		}

		/*===============================================================
			@Generate hash data based on data and blowfish using crypt()
			@param string $data
			@return hashed string
		===============================================================*/
	    public function hashData($data){

	    	//hash the using crypt function. The final length of the hash should be 60 bytes
	    	//$hashedData = crypt($data, $this -> blowfishSalt());
	    	$hashedData   = hash('sha256', $data);

	    	//futher check if the length of the data exceed 64 bytes then substring the string
	    	if(strlen($hashedData) > MAXIMUM_HASH_LENGTH)
					$hashedData = substr($hashedData, 0, MAXIMUM_HASH_LENGTH);
	    	
	    	return $hashedData;
	    }

	    /*===============================================================
	    	@compare the input data with the hashed data that is stored in the database
	    	@params string inputdata, hasheddata
	 		@return boolean value for true if it is matched and false if it is not matched
	    ===============================================================*/
	    public function compareHashData($inputData, $hashedData){
	    	if(strlen($hashedData) > MAXIMUM_HASH_LENGTH){				
				$hashedData = substr($hashedData, 0, MAXIMUM_HASH_LENGTH);
		    }

	    	//if($hashedData === substr(crypt($inputData, $hashedData), 0, MAXIMUM_HASH_LENGTH)){
		    if($hashedData === substr(hash('sha256', $inputData), 0, MAXIMUM_HASH_LENGTH)){
	    		return true;
	    	}
	    	else{
	    		return false;
	    	}
		    
	    }

	    /*=========================================================================
	    	@insert into the the table the hashed data
	    	@this function is used only to generate the hashed directory on server
	    ==========================================================================*/
	    public function insertHashData($hashedData, $tableName, $columnName){

	    	//the query to execute
	    	$query = sprintf("INSERT INTO %s ( $columnName ) VALUES ( '%s' )", 
	    					 mysql_real_escape_string($tableName),
	    					 mysql_real_escape_string($hashedData));

	    	//execute the query
	    	$executeQuery = mysql_query($query);

	    	//check the query and free the result
	    	if(!$executeQuery){

	    		//query fail to execute
	    		return false;
	    	}else{

	    		//query execute successfully
	    		return true;
	    	}
	    }
	}
?>