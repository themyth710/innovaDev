<?php
	
	require_once(dirname(__FILE__).'/../database/phone.inc');
	require_once(dirname(__FILE__).'/../database/config.inc');

	$content = file_get_contents('php://input');
#	$content  = file_get_contents('test.txt');
	$xml_source = str_replace(array("&amp;", "&"), array("&", "&amp;"), $content);
    #$xml = preg_replace('#&(?=[a-z_0-9]+=)#', '&amp;', $content);

    $xml = simplexml_load_string($xml_source);
	
	$userID = null;
	$email  = null;
	
	if(isset($xml->userID)){
		$userID = $xml->userID;
		file_put_contents('test.txt', $content);

	}
	else{
		$email = $xml->email;
	}
	
	$phone = new phone();
	$phone -> phBackupUserContact($xml_source, $userID, $email);

?>