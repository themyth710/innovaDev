<?php
	define('DRUPAL_ROOT', $_SERVER['DOCUMENT_ROOT'].'/development');
	$base_url = 'http://'.$_SERVER['HTTP_HOST'].'/development';
	
	require_once (DRUPAL_ROOT . '/includes/bootstrap.inc');
	drupal_bootstrap(DRUPAL_BOOTSTRAP_SESSION);

	
	require_once(dirname(__FILE__).'/../database/browser.inc');
	require_once(dirname(__FILE__).'/../database/config.inc');
	
	if(isset($_GET[ACTION])){
		if($_GET[ACTION] == BACKUP_CONTACT){
			
			if(isset($_SESSION[USER_ID]) && isset($_SESSION[EMAIL])){
				
				$hashUserID = $_SESSION[USER_ID];
				$email      = $_SESSION[EMAIL];

				$br = new browser();
				if($br -> brCheckSession($hashUserID, $email)){
					$userID = $br -> brRetrieveUserID($hashUserID);
					
					$br -> brDownloadBackupFile($userID);
				}
			}		
		}
	}
	
	
?>