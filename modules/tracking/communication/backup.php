<?php
	
	require_once(dirname(__FILE__).'/../database/phone.inc');
	require_once(dirname(__FILE__).'/../database/config.inc');

	$content = file_get_contents('php://input');

	$xml_source = str_replace(array("&amp;", "&"), array("&", "&amp;"), $content);

	$userID = null;
	$email  = null;
	
	
	//Fixing file formating of iOS
	$start = strpos($xml_source,'<?xml');
	if($start==false){
		$start = strpos($xml_source, '<email>');
		if($start==false)
			return;
	}
	
	$end = strpos($xml_source,'</backup>');
	if($end==false)
		return;
	$end += 9; //strlen of </backup>
	$xml_source = substr($xml_source,$start,$end - $start);
		
	
	$xmlReader = new XMLReader();
	$xmlReader->XML($xml_source);

	while($xmlReader -> read()){
	
		if($xmlReader->name == 'userID'){
			$userID =  $xmlReader -> readString();
			break;
		}
		else 
			if($xmlReader->name == 'email'){
				$email = $xmlReader -> readString();
				break;
		}
	}
	
	$phone = new phone();
	$phone -> phBackupUserContact($xml_source, $userID, $email);
?>