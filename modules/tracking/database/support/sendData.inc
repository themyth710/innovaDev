<?php
	class dataSend{
		
		private $send;

		/*==================================
	   		@constructor
	   	==================================*/
		function __construct() {
        	require_once(dirname(__FILE__).'/../db_connect.inc');
        	
        	// connecting to database
        	$this -> send = new DB_Connect();
        	$this -> send -> connect();
	    }

	    /*==================================
    		@destructor
    	==================================*/
    	function __destruct() {
    		
    	}	

    	/*========================================
    		@send request to phone using regID
    		@this function is used only on android
    	========================================*/
    	public function sendPhoneNotification($regID, $message){
    		
    		// Set POST variables
	        $url = 'https://android.googleapis.com/gcm/send';

	        //packet all the information and send to thephone
	    	$regIDSend 		= array($regID);
	    	$messageSend 	= array("price" => $message);

	        $fields = array(
	            'registration_ids' => $regIDSend,
	            'data' => $messageSend,
	        );

	        $headers = array(
	            'Authorization: key=' . GOOGLE_API_KEY,
	            'Content-Type: application/json'
	        );
			
	        // Open connection
	        $ch = curl_init();

	        // Set the url, number of POST vars, POST data
	        curl_setopt($ch, CURLOPT_URL, $url);

	        curl_setopt($ch, CURLOPT_POST, true);
	        curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
	        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

	        // Disabling SSL Certificate support temporarly
	        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);

	        curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($fields));

	        // Execute post
	        $result = curl_exec($ch);

	        if ($result === FALSE) {
	        	return false;
	        }

	        // Close connection
	        curl_close($ch);

	        return true;
    	}
    	
    	/*========================================
    		@send request to phone using regID
    		@this function is used only on iOS
    	========================================*/
    	public function sendiOSNotification($deviceToken, $message, $action){
    		if($deviceToken==NULL){
    			return false;
    		}
    		
		//Remember to set certificate to private (inaccessble by public)
		$ctx = stream_context_create();
		//stream_context_set_option($ctx, 'ssl', 'local_cert', 'iOS_APNS_Production.pem');
		stream_context_set_option($ctx, 'ssl', 'local_cert', 'iOS_APNS_Dev.pem');
		
		// Open a connection to the APNS Server
		//(production)
		/*$fp = stream_socket_client(
		'ssl://gateway.push.apple.com:2195', $err,
		$errstr, 60, STREAM_CLIENT_CONNECT|STREAM_CLIENT_PERSISTENT, $ctx);*/
	
		stream_context_set_option($ctx, 'ssl', 'local_cert', 'iOS_APNS_Dev.pem');
		//(development)
		$fp = stream_socket_client(
		'ssl://gateway.sandbox.push.apple.com:2195', $err,
		$errstr, 60, STREAM_CLIENT_CONNECT|STREAM_CLIENT_PERSISTENT, $ctx);
		
		if (!$fp){
			fclose($fp);
			return false;
		}
		
		// Create the payload body
		$body['aps'] = array(
		'alert' => $message,
		'sound' => 'default',
		'action' => $action
		);
		
		// Encode the payload as JSON
		$payload = json_encode($body);
		
		// Build the binary notification
		$msg = chr(0) . pack('n', 32) . pack('H*', $deviceToken) . pack('n', strlen($payload)) . $payload;
		
		// Send it to the server
		$result = fwrite($fp, $msg, strlen($msg));
		
		// Close the connection to the server
		fclose($fp);
		if (!$result){
			return false;
		}else{
			return true;
		}
    	}

    	/*=========================================================================================

			@handle all sending mail in Drupal 7
			@params: 
				key   : used to detect what is the purpose of the email
				email to : receiver
				subject: content of the email : includes the data and the subject that want to send

    	=========================================================================================*/
    	public function sendMail($key, $emailTo, $params){
    		//module
    		$module   = MODULE; 
    		
    		//send from
    		$emailFrom= EMAIL_FROM;

    		//set the language and some parameters for the email send
    		$language = language_default();
			$send 	  = true;

			//send the email

			$result   = drupal_mail($module, $key, $emailTo, $language, $params, $emailFrom, $send);
			
			return $result['result'];
    	}
	}

?>