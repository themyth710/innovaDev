<?php
	
	require_once(dirname(__FILE__).'/../database/phone.inc');
	require_once(dirname(__FILE__).'/../database/config.inc');

	$content = file_get_contents('php://input');
#
	$xml_source = str_replace(array("&amp;", "&"), array("&", "&amp;"), $content);
    #$xml = preg_replace('#&(?=[a-z_0-9]+=)#', '&amp;', $content);

	$userID = null;
	$email  = null;

	$xmlReader = new XMLReader();
	$xmlReader->open('php://input');
	
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
	file_put_contents('../UserRegion/Backup/yourfile.xml',$xml_source);
	//$phone = new phone();
	//$phone -> phBackupUserContact($xml_source, $userID, $email);

?>