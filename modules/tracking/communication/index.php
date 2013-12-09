<?php
$requestURI = explode('/', $_SERVER['REQUEST_URI']);
require_once('lostReport.php');
require_once('nonUserFoundReport.php');
// Change this value to 2 after deploy.
// Sample API call: qivi.com/api/user
$addr_offset = 3;
echo "reaching index in communication!";
/* $scriptName = explode('/',$_SERVER['SCRIPT_NAME']);
for($i= 0;$i < sizeof($scriptName);$i++) {
	if ($requestURI[$i]	== $scriptName[$i]) {
		unset($requestURI[$i]);
	}
} */

$command = array_values($requestURI);
switch($command[$addr_offset + 0]){
	case 'lost_found':
		switch ($_SERVER['REQUEST_METHOD']) {
			case 'POST':
				checkLost();
				break;
			default:
				invalid_request();
				break;
		}
		break;
	case 'lost_location':
		switch ($_SERVER['REQUEST_METHOD']) {
			case 'POST':
				reportLostProtagLocation();
				break;
			default:
				invalid_request();
				break;
		}
		break;
	case 'lost_found_by_nonuser':
		switch ($_SERVER['REQUEST_METHOD']) {
			case 'POST':
				nonUserReportFound();
				break;
			default:
				invalid_request();
				break;
		}
		break;
	case 'lost_report':
		switch ($_SERVER['REQUEST_METHOD']) {
			case 'POST':
				createLostReport();
				break;
			default:
				invalid_request();
				break;
		}
		break;	
	default:
		invalid_request();
		break;
}

function invalid_request(){
	http_response_code(404);
	echo "";
}
?>
