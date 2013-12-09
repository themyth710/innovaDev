<?php
	/*=====================================================================================
		@this file is a set of functions to handle the forms that are submitted to server
		@the form include the sign in , reset and phone select form
		@all are controled by handlers respectively
	======================================================================================*/
	/*
		include this file for function to contact with database
	*/

	include_once drupal_get_path('module','Tracking').'/database/config.inc';

	include_once 'handlerClass.inc';

	/* 	
		this function handle the login form when it is submitted to server
	*/	
	function form_registration_handler($form, &$form_state){
		
		//connect to database
		$handler = new handler();
		
		//store the password and email value from the form
		$password = $form_state['values']['password'];
		$email    = $form_state['values']['email'];
		
		if(isset($email) && isset($password))
		{

			//this is drupal function to login the user into system
			if($uid = user_authenticate($email, $password)){
				//this is a hash userID
				if($userID = $handler -> handleLoginCheck($email, $password)){

					if($handler -> handleCheckUserActivation($email)){

						//finalize the login with drupal
						global $user;
						$user = user_load($uid);
						drupal_session_regenerate();
						
						//format : $list, $hashUserID = null, $isRegID = true
						//retrieve the list type phone and register ID 
						$listRegAndType    = $handler -> handleRetreiveListRegIDAndTypePhone(null, $userID);

						//store the email into session because we want to check the userID with email for security purpose
						$_SESSION[USER_ID] = $userID;
						$_SESSION[EMAIL]   = $email;

						//format: $list, $hashUserID = null, $isRegID = true
						//retrieve the list of register ID
						$_SESSION[REG_ID]  = $handler -> handleRetreiveListRegIDAndTypePhone($listRegAndType);

						//redirect user
						$form_state['redirect'] = 'tracking';
					}
					else{
						drupal_set_message(t('Your account has not been activated. Please check your mail box for confirmation email or <span><a href = "activation">click here</a></span> to reactivate your account.'));
					}

				}
				else{
					drupal_set_message(t('Your email or password is not correct. Please try again or <span><a href = "reset">click here</a></span> to recover your password.'));
				}
			}
			else{
					drupal_set_message(t('Your email or password is not correct. Please try again or <span><a href = "reset">click here</a></span> to recover your password.'));
			}
		}
		unset($handler);
	}
	
	/*
		This function handle the resert password form when submitted to server
	*/
	function form_password_reset_handler($form, &$form_state){	

		//email from user and admin
		$emailTo = $form_state['values']['email'];
		$emailFrom = 'INNOVA@innovatechnology.com.sg';

		//create new instance of handler variables
		$handler = new handler();

		if($token = $handler -> handleStorePasswordToken($emailTo)){

			$params = reset_mail_content($token);

			reset_password_mail_send('Tracking','reset_mail',$emailTo, $emailFrom, $params);

			drupal_set_message(t('An email has been sent to the address you provided. Please follow the instructions in the email to change your password.'));
		}
		
		unset($handler);
	}
	
	/*
		form reset password handler	
	*/
	function form_new_password_handler($form, &$form_state){
		
		//get password from user input
		$password = $form_state['values']['password'];
		$email    = $_SESSION[EMAIL];

		$handler  = new handler();
		
		$handler -> handleUpdateNewPassword($password, $email);

		//drupal reset password
		//have to do that because we also login to drupal
		$user     = user_load_by_name($email);
		$uid      = $user->uid;

		$account = user_load($uid);
		$pass    = array('pass' => $password);

		user_save($account, $pass);

		drupal_set_message(t('Your password has been changed successfully.<a href = "login"> Click here</a> to login.'));
	}

	/*=========================================

		@resend token activation hanlder

	=========================================*/
	function form_account_activation_handler($form, &$form_state){

		drupal_set_message(t('An email has been sent to the address you provided. Please follow the instructions in the email to activate your account.'));

		$email = $form_state['values']['email'];

		$handler  = new handler();

		$handler -> handleSendEmailActivation($email);		
	}

	function activationTokenHandler($token){
		$handler  = new handler();

		if($handler -> handleActivationTokenSubmit($token))
		{
			return true;	
		}		
		else
			return false;
	}

	/*
		function in Drupal to send email to user
	*/
	function reset_password_mail_send($module, $key, $emailTo, $emailFrom, $subject){
		$language = language_default();
		$send 	  = true;
		$result   = drupal_mail($module, $key, $emailTo, $language, $subject, $emailFrom, $send);
		if ($result['result'] == TRUE) {
		    return true;
		 }
		 else {
		    return false;
		 }
	}
	
	/*======================================================================================

		Content of the mail sent to user
		the body is the main part of the email. Need to change for the content of the email

	======================================================================================*/
	function reset_mail_content($token){
		global $base_url;
		$params = array(
				'subject' => 'Password reset from INNOVA',
				'token'	  => $base_url.'/reset?token='.$token
			       );
		return $params;
	}

	/*================================================================================
		check the link that user click from their email when they reset their password
	================================================================================*/
	function token_sent_handler($token){

		//create new instance of handler variables
		$handler = new handler();

		if($email = $handler -> handleValidatePasswordToken($token)){

			//store the user ID into session
			$_SESSION[EMAIL] = $email;//this is a realy userID, not hash one

			return true;
		}
		else
			return false;
	}

	/*
		$retrieve the list of typephone according to hash USer ID
	*/
	function returnTypePhoneList($userID){

		$handler = new handler();

		$listRegAndType = $handler -> handleRetreiveListRegIDAndTypePhone(null, $userID);

		$listTypePhone = $handler -> handleRetreiveListRegIDAndTypePhone($listRegAndType, null, false);

		return $listTypePhone;
	}

	function checkUserExist(){
		$handler = new handler();

		if(isset($_SESSION[EMAIL]) && isset($_SESSION[USER_ID])){
			$userID = $_SESSION[USER_ID];
			$email  = $_SESSION[EMAIL];

			if(!$handler -> handleCheckSession($userID, $email))
				redirectUser('login');
		}
		else
			redirectUser('login');
	}

	//redicect to any URL in the page
	function redirectUser($page){
		//URL is starting by http:// plus host plus the current directory of the current page plus the page redirect
		$url='http://'.$_SERVER['HTTP_HOST'].dirname($_SERVER['PHP_SELF']);
		//remove any trailing slahshes
		$url=rtrim($url,'/\\');
		
		$url.='/'.$page;
			
		//redirect to the page
		header("Location:$url");
		exit();
	}

	function removePhone($userID, $regID){

		$handler = new handler();

		if($handler -> handleRemovePhone($userID, $regID))
			return true;
		else
			return false;
	}
?>