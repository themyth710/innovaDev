<?php
	require_once('helperFunctions.php');
	
	// function checkMessageCount(){
	// 	$serial_num = $_POST['serial_num'];
	// 	$protag = new protag();
	// 	$protagInfo = $protag -> prRetrieveProtagInformationViaSerialNum($serial_num);
	// 	$mac_protag = $protagInfo['macAddress'];
	// 	$message_count = $protag -> prRetrieveFoundReportCount($mac_protag);
	// 	if ($message_count > 3 ){
	// 		respondToClient(405);// Too many message has been sent
	// 		return false;
	// 	} else{
	// 		respondToClient(200);
	// 		return true;
	// 	}
	// }

	function nonUserReportFound(){
		if(!isset($_POST['serial_num'])) {
			respondToClient(400);
		} else {
			$protag = new protag();
			$serial_num = $_POST['serial_num'];
			$length = strlen($serial_num);
			if($length != VALID_SERIAL_NUM_LENGTH){
				respondToClient(401);
			} else {
				$protagInfo = $protag -> prRetrieveProtagInformationViaSerialNum($serial_num);
				$mac_protag = $protagInfo['macAddress'];
		
				$message_count = $protag -> prRetrieveFoundReportCount($mac_protag);
				$lost_status = $protag -> prCheckProtagLostStatus($mac_protag);
				//(0 -> not lost, 1 -> lost， -1 -> database error, -2 -> no such protag)
				
				if(isset($_POST['reporter_email']) && isset($_POST['reporter_name']) && isset($_POST['message']) && isset($_POST['contact_number'])){
					$reporter_email = $_POST['reporter_email'];
					$reporter_name = $_POST['reporter_name'];
					$message = $_POST['message'];
					$reporter_contact_number = $_POST['contact_number'];
					//(0 -> not lost, 1 -> lost， -1 -> database error, -2 -> no such protag)
					if ($lost_status == -2) {
						$responseArray = array('reason' => 0);
						respondToClient(200, $responseArray);
					} else if($lost_status == -1){
						$responseArray = array('reason' => 1);
						respondToClient(200, $responseArray);
					} else{
						// the protag is lost or not lost
						$lost_report = $protag -> prRetrieveProtagLostReport($mac_protag);
						//echo "Message count = ".$message_count;
						if($message_count >= MAXIMUM_NON_USER_REPORT){
							$responseArray = array('reason' => 3);
							respondToClient(200, $responseArray);// Too many message has been sent
						}
						else{
							$protag -> prStoreFoundReport($mac_protag, $message, $reporter_name, $reporter_email, $reporter_contact_number);
							respondToClient(200);
							//echo "sending";
							$params = array('subject' => 'Protag Found',
											'mac_addr' => $mac_protag,
										    'message' => $message,
											'reporter_name' => $reporter_name,
											'reporter_email' => $reporter_email,
											'reporter_contact_number' => $reporter_contact_number);
							send_email_notification($params, 1);
						}
					}
				} else {
					if ($lost_status == -2) {//No such protag
						$responseArray = array('reason' => 0);
						respondToClient(200, $responseArray);
					} else if($lost_status == -1){//database error
						$responseArray = array('reason' => 1);
						respondToClient(200, $responseArray);
					} else if($lost_status == 0){//not lost!
						$responseArray = array('reason' => 2);
						respondToClient(200, $responseArray);
					} else {
						$lost_report = $protag -> prRetrieveProtagLostReport($mac_protag);
						$response = array('mac_ad' => $mac_protag,
										  'contact_name' => $lost_report['contact_name'],
										  'contact_number' => $lost_report['contact_number'],
										  'message' => $lost_report['message']);
						respondToClient(201, $response);
					}
				}
			}
			
		}
	}
	nonUserReportFound();
?>