<?php
	require_once(dirname(__FILE__).'/../database/protag.inc');
	require_once(dirname(__FILE__).'/../database/config.inc');

	if(isset($_POST[ACTION])){

		$protag = new protag();

		if($_POST[ACTION] == PROTAG_REGISTER){

			if(isset($_POST[USER_ID]) &&
			   isset($_POST[PROTAG_NAME]) &&
			   isset($_POST[PROTAG_MAC]) &&
			   isset($_POST[LAT]) &&
			   isset($_POST[LONG]) &&
			   isset($_POST[DATE_CREATE]) &&
			   isset($_POST[LAST_DATE])){

				$userID 		= $_POST[USER_ID];
				$protagName     = $_POST[PROTAG_NAME];
				$protagMac      = $_POST[PROTAG_MAC];
				$lat  			= $_POST[LAT];
				$long 	   		= $_POST[LONG];
				$lastDateKnown  = $_POST[LAST_DATE];
				$dateCreate     = $_POST[DATE_CREATE];

				//validate the input format
				if($protag -> dbValidateInputFormat(null, null, null, $protagMac, $lastDateKnown, $lat, $long)){
					
					$protag -> prStoreProtagInformation($protagMac, $userID, $protagName, $lat, $long, $dateCreate , $lastDateKnown);
				}
			}
		}
	}
?>