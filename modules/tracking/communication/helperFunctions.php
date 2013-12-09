<?php
	require_once(dirname(__FILE__).'/../database/protag.inc');
	require_once(dirname(__FILE__).'/../database/phone.inc');
	require_once(dirname(__FILE__).'/../database/config.inc');
	function respondToClient($responseCode, $responseArray = array('whatever' => 'whatever')){
		//http_response_code($responseCode);
		header("HTTP/1.1 ".$responseCode." OK");
		$responseJSON = json_encode($responseArray);
		header('Content-type: text/json');
		echo $responseJSON;
		if ($responseCode >= 400) {
			echo mysql_error();
		}
	}
	function trackingRespond($responseCode, $responseArray = null){
		$trackingUrl = "/development/tracking";
		$responseJSON = json_encode($responseArray);
		header("HTTP/1.1 ".$responseCode." OK");
		header('Content-type: text/json');
		header("Location: ".$trackingUrl);
		echo $responseJSON;
		die();
	}
	
	function android_push_notification($registatoin_ids, $message){
		// Set POST variables
        $url = 'https://android.googleapis.com/gcm/send';
 
        $fields = array(
            'registration_ids' => $registatoin_ids,
            'data' => $message,
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
            die('Curl failed: ' . curl_error($ch));
        }
 
        // Close connection
        curl_close($ch);
        echo $result;
	}
	function ios_push_notification($deviceToken, $message){
		
		// Put your private key's passphrase here:
		$passphrase = 'pushchat';
		
		////////////////////////////////////////////////////////////////////////////////
		
		$ctx = stream_context_create();
		stream_context_set_option($ctx, 'ssl', 'local_cert', 'iOS_APNS_Dev.pem');
		stream_context_set_option($ctx, 'ssl', 'passphrase', $passphrase);
		
		// Open a connection to the APNS server
		$fp = stream_socket_client(
			'ssl://gateway.sandbox.push.apple.com:2195', $err,
			$errstr, 60, STREAM_CLIENT_CONNECT|STREAM_CLIENT_PERSISTENT, $ctx);
		
		// Create the payload body
		$body['aps'] = array(
			'alert' => array('action-loc-key' => 'Open',
							 'body' => $message),
			'sound' => 'default'
			);
		
		// Encode the payload as JSON
		$payload = json_encode($body);
		
		// Build the binary notification
		$msg = chr(0) . pack('n', 32) . pack('H*', $deviceToken) . pack('n', strlen($payload)) . $payload;
		
		// Send it to the server
		$result = fwrite($fp, $msg, strlen($msg));
		
			//respondToClient(200,array());
		
		// Close the connection to the server
		fclose($fp);
	}

	/* use this function to send email to user to notify them.
	 * Email type: 0 for update of current location of the protag,
	 *             1 for protag has been found by non-user.
	 */
	
	function send_email_notification($params, $email_type){
		$phone = new phone();
		$protag = new protag();
		$mac_addr = $params['mac_addr'];
		$email_addr = $protag -> prRetrieveProtagOwnerEmail($mac_addr);
		if ($email_addr) {
			switch ($email_type) {
				case '0':
					break;
				case '1':
					$result = $phone -> phSendNonUserFoundEmail($email_addr, $params);
					break;
				default:
					break;
			} 
		}
	}
?>