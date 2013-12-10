<?php

	require_once('../../database/browser.inc');
	$currdir = getcwd();
    chdir($_SERVER['DOCUMENT_ROOT'] . "/development/");
    define('DRUPAL_ROOT', getcwd());
    include_once("./includes/bootstrap.inc");
    drupal_bootstrap(DRUPAL_BOOTSTRAP_SESSION, true);
    chdir($currdir);
	#$browser 	= new browser();
	$xml=file_get_contents("../../communication/test.txt");
	header('Content-type: text/xml');
	echo $xml;
	//$userID 	= $browser -> brRetrieveUserID($hashUserID);
	//echo file_get_contents($userID.'_contact/backup.xml');
?>