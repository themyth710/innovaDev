<?php
	require_once('helperFunctions.php');
	function checkLost(){
		$data= json_decode(file_get_contents("php://input"),TRUE);
		//parse_str(file_get_contents("php://input"),$putdataarray);
		//echo "put data is ".print_r($putdataarray, TRUE);
		//echo "post is ".print_r($_POST,TRUE);
		//$data = $_POST['json'];
		//echo "data is ".print_r($data, TRUE);
		$mac_addresses = $data['mac_ads'];
		$protag = new protag();
		$result_array = array();
		foreach ($mac_addresses as $mac_addr) {
			$lost_status = $protag -> prCheckProtagLostStatus($mac_addr);
			if ($lost_status == -2) {
				$current_result = array('mac_ad' => $mac_addr,
										'lost_status' => -1);
				array_push($result_array, $current_result);
			} else if($lost_status == -1){
				$current_result = array('mac_ad' => $mac_addr,
										'lost_status' => -2);
				array_push($result_array, $current_result);	
			} else if($lost_status == 0){
				$current_result = array('mac_ad' => $mac_addr,
										'lost_status' => 0);
				array_push($result_array, $current_result);
			} else {
				$lost_report = $protag -> prRetrieveProtagLostReport($mac_addr);
				//$protag_name = $protag -> prRetrieveProtagName($mac_addr);
				file_put_contents('yourfile.txt', serialize($lost_report));
				if ($lost_report['will_notify']) {
					$protag_name = $protag -> prRetrieveProtagName($mac_addr);
					$current_result = array('mac_ad' => $mac_addr,
											'lost_status' => 2,
											'protag_name' => $protag_name,
											'contact_name' => $lost_report['contact_name'],
											'contact_number' => $lost_report['contact_number'],
											'message' => $lost_report['message']);
									  
					array_push($result_array, $current_result);
					$phone = new phone();
				} else {
					$current_result = array('mac_ad' => $mac_addr,
										'lost_status' => $lost_report['will_notify']);
					array_push($result_array, $current_result);
				}
			}
		}
		if (sizeof($result_array) != 0) {
			$response = array('devices' => $result_array);
			respondToClient(200, $response);
		} else {
			respondToClient(400);
		}
		
		
	}
	checkLost();
?>