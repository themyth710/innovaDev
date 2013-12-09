<?php
 	/*=========================
 		@connect to the database 
 	==========================*/
	class DB_Connect {
	 
	    /*======================
	     	@constructor
	    =======================*/
	    function __construct() {

	    }
	 
	    /*=====================
	    	@destructor
	    ======================*/
	    function __destruct() {

	    }
	 
	    /*===========================
	    	@Connecting to database
	    ============================*/
	    public function connect() {
	    
	        require_once 'config.inc';
	        
	        //connect to mysql
	        $con = mysql_connect(DB_HOST, DB_USER, DB_PASSWORD);
			
			if (!$con) {

				//could not connect to database
				die(DATABASE_CONNECTION_ERROR . mysql_error());
				return false;

			}else{

				// selecting database
				mysql_select_db(DB_DATABASE);
	 
				// return database handler
				return $con;
			}
	    }
	 
	    // Closing database connection
	    public function close() {
	        mysql_close();
	    }
	} 
?>