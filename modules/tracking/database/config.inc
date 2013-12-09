<?php
	/*=============================================
		@GLOBAL VARAIBLES
	==============================================*/

	/*
	  	define host information
	*/
	define('DB_HOST', 						'sg61.singhost.net');
	define('DB_USER', 						'mycloset_innova');
	define('DB_PASSWORD', 					'themyth@92');
	define('DB_DATABASE', 					'mycloset_develop');
	
	/*
	  		Google API Key
	*/
	define('GOOGLE_API_KEY'					, 'AIzaSyCeEeARC5go704gtTRNqf6iH9OFZzgzhEA'); // Place your Google API Key
	
	/*
	    	Table name
	*/
	define('USERS_INFORMATION_TABLE'		,'tr_users_information');
	define('PHONE_INFORMATION_TABLE'		,'tr_phone_information');
	define('ANDROID_USER_TABLE'				,'tr_android_phone_user');
	define('USERS_PASSWORD_HANDLE_TABLE'	,'tr_users_password');
	define('NOTIFICATION_TABLE'				,'tr_notification_center');
	define('HASH_DIRECTORY_TABLE'			,'tr_hash_directory');
	define('IOS_USER_TABLE'     			,'tr_ios_phone_user');
	define('PROTAG_INFORMATION_TABLE'		,'tr_protag_information');
	define('PROTAG_LOST_REPORT_TABLE'       ,'tr_user_lost_report');
	define('NONUSER_FOUND_REPORT_TABLE'	,'tr_nonuser_found_report');
	/*
			Success code
	*/
	define('QUERY_SUCCESS'					,'Success');
	
	/*
			Error code
	*/
	define('DATABASE_CONNECTION_ERROR'		,'Could not connect to database');
	define('QUERY_FAILED'					,'Failed');
	/*
			Phone type
	*/
	define('ANDROID'						,'Android');
	define('IOS'							,'iOS');
	define('ANDROID_ID'						, 1);
	define('IOS_ID'							, 2);
	/*
			Const string
	*/
	define('MODULE'							,'Tracking');
	define('EMAIL_FROM'						,'INNOVA@innovatechnology.com.sg');
	/*
			Mail
	*/
	define('ACTIVATION_MAIL'				,'activation_mail');
	define('RESET_MAIL'						,'reset_mail');
	define('LAST_FLARE_MAIL'				,'lastFlare');
	define('PASSIVE_TRACK_MAIL'				,'passive_track_mail');
	define('NON_USER_FOUND_MAIL'			,'non_user_found_mail');
	/*
			Number
	*/
	define('MAXIMUM_HASH_LENGTH'			, 64);
	define('MAXIMUM_USER'					, 1);
	define('MAXIMUM_EMAIL'					, 1);
	define('MAXIMUM_PASS_LENGTH'			, 32);
	define('MAXIMUM_EMAIL_LENGTH'			, 64);
	define('MAXIMUM_MAC_PHONE'				, 1);
	define('USER_ACTIVE'					, 1);
	define('USER_INACTIVE'					, 0);
	define('MAXIMUM_REGID_PHONE'			, 1);
	define('MAXIMUM_REGID_LENGTH'			, 250);
	define('OK_CMD_VAL'						, 1);
	define('SEND_TRACK_CMD_VAL'				, 2);
	define('USER_CMD_SET'					, 0);
	define('MAXIMUM_IMAGE'					, 6);
	define('MAXIMUM_PROTAG_MAC'				, 1);
	define('SEND_MAIL_ACCURACY'				, 15);
	define('MAXIMUM_NON_USER_REPORT'        , 3);
	/*
			Table column
	*/
	define('USER_INFO_ID_COL'				,'userID');
	define('USER_INFO_EMAIL_COL'			,'email');
	define('USER_INFO_PASSWORD_COL'			,'password');
	define('USER_INFO_ID_HASHED_COL'		,'hashID');
	define('USER_INFO_DATE_CREATED_COL'		,'dateCreated');
	define('USER_INFO_TOKEN_COL'			,'token');
	define('USER_INFO_ACTIVE_COL'			,'active');
	define('USER_INFO_TOKEN_DATE_CREATE_COL','tokenDateCreate');
	
	define('PROTAG_LOST_REPORT_MAC_ADDR_COL'        ,'protag_mac_address');
	define('PROTAG_LOST_REPORT_ACTIVE_COL'          ,'is_active');
	define('PROTAG_LOST_REPORT_LOCATION_COL'        ,'location');
	define('PROTAG_LOST_REPORT_MESSAGE_COL'         ,'message');
	define('PROTAG_LOST_REPORT_DESC_COL'        ,'description');
	define('PROTAG_LOST_REPORT_NOTIFY_COL'          ,'will_notify');
	define('PROTAG_LOST_REPORT_TIME_LOST_COL'       ,'time_lost');
	define('PROTAG_LOST_REPORT_CONTACT_NAME_COL'    ,'contact_name');
	define('PROTAG_LOST_REPORT_CONTACT_NUMBER_COL'  ,'contact_number');
	
	define('NONUSER_FOUND_REPORT_CONTACT'			,'reporter_contact_number');
	define('NONUSER_FOUND_REPORT_EMAIL'				,'reporter_email');
	define('NONUSER_FOUND_REPORT_NAME_COL'			,'reporter_name');
	define('NONUSER_FOUND_REPORT_MESSAGE_COL'		,'message');
	define('NONUSER_FOUND_REPORT_ACTIVE_COL'		,'is_active');
	define('NONUSER_FOUND_REPORT_MAC_COL'			,'protag_mac_address');
	define('NONUSER_FOUND_REPORT_TIME'				,'time_found');

	define('PHONE_INFO_MAC_COL'				,'macPhoneAddress');
	define('PHONE_INFO_LAT_COL'				,'currentLatitude');
	define('PHONE_INFO_LONG_COL'			,'currentLongitude');
	define('PHONE_INFO_DATE_CREATE_COL'		,'dateCreated');
	define('PHONE_INFO_ACC_COL'				,'accuracy');
	define('PHONE_INFO_BAT_COL'				,'battery');
	define('PHONE_INFO_REGID_COL'			,'regID');	
	define('PHONE_INFO_PHONE_TYPE_COL'		,'phoneType');
	define('PHONE_INFO_NAME_COL'			,'phoneName');
	define('PHONE_INFO_LOST_COL'			,'lost');

	define('NOTI_USER_ID_COL'				,'userID');
	define('NOTI_TRACK_COL'					,'track');
	define('NOTI_LOCK_COL'					,'locked');
	define('NOTI_B_CONTACT_COL'				,'bContact');
	define('NOTI_IMG_CAP_COL'				,'imgCapture');
	define('NOTI_EXPECTED_IMAGE_COL'		,'expectedImage');

	define('ANDROID_FIRST_USER_ID_COL'		,'firstUserID');
	define('ANDROID_SECOND_USER_ID_COL'		,'secondUserID');
	define('ANDROID_USER_MAC_COL'			,'macPhoneAddress');
	define('ANDROID_FIRST_USER_ACT_COL'		,'firstActive');
	define('ANDROID_SECOND_USER_ACT_COL'	,'secondActive');
	define('ANDROID_REGISTRATION_ID_COL'    ,'registrationID');

	define('IOS_FIRST_USER_ID_COL'			,'firstUserID');
	define('IOS_SECOND_USER_ID_COL'			,'secondUserID');
	define('IOS_USER_REGID_COL'				,'regID');
	define('IOS_USER_PHONE_NAME_COL'		,'phoneName');
	define('IOS_FIRST_USER_ACT_COL'			,'firstActive');
	define('IOS_SECOND_USER_ACT_COL'		,'secondActive');
	define('IOS_PUSH_TOKEN'					,'push_token');

	define('USERS_PASSWORD_ID_COL'			,'userID');
	define('USERS_PASSWORD_TOKEN_COL'		,'token');
	define('USERS_PASSWORD_TOKEN_DATE_COL'	,'dateCreated');

	define('HASH_DIRECTORY_COL'				,'directoryHash');
	define('DIRECTORY_COL'					,'directory');

	define('PROTAG_INFO_MAC_COL'			,'macAddress');
	define('PROTAG_INFO_USER_ID_COL'		,'userID');
	define('PROTAG_INFO_NAME_COL'			,'protagName');
	define('PROTAG_INFO_LAT_COL'			,'currentLatitude');
	define('PROTAG_INFO_LONG_COL'			,'currentLongitude');
	define('PROTAG_INFO_DATE_CREATE_COL'	,'dateCreate');
	define('PROTAG_INFO_LAST_DATE_COL'		,'lastDateKnown');
	define('PROTAG_INFO_IS_LOST_COL'		,'isLost');
	define('PROTAG_INFO_SERIAL_COL'			,'serialNumber');
	/*
		browser command
	*/
	define('START_TRACK'					,'startTrack');
	define('STOP_TRACK'						,'stopTrack');
	define('TEST_TRACK'						,'testTrack');
	define('LOCK'							,'lock');
	define('BACKUP_CONTACT'					,'bContact');
	define('MESSAGE'						,'message');
	define('TRACK'							,'track');
	define('CONTINUE_TRACK'					,'tracking');
	define('FOLDER'							,'folder');
	define('DIRECTORY'						,'directory');
	define('DATA'							,'data');
	define('HOST'							,'http://themyth92.com/home/');
	define('IMAGE_CAPTURE'					,'imageCapture');
	define('PHONE_NAME'						,'phoneName');

	/*
		browser action
	*/
	define('LOAD_PHONE'						,'phoneListLoad');
	define('REMOVE_PHONE'					,'removePhone');
	define('RETRIEVE_IMAGE_CAPTURE'			,'loadImageCapture');
	define('RETRIEVE_PROFILE'				,'retrieveProfile');
	define('SAVE_PROFILE'					,'saveProfile');
	define('RETRIEVE_PROTAG'				,'retrieveProtag');
	define('SAVE_PHONE_NAME'				,'savePhoneName');
	/*
		phone command
	*/
	define('TYPE_PHONE'						,'typePhone');
	define('USER_ID'						,'userID');
	define('REG_ID'							,'regID');
	define('ACTION'							,'action');
	define('ACCESS_DENIED'					,'Access denied');
	define('REGISTER'						,'register');
	define('LOGIN'							,'login');
	define('EMAIL'							,'email');
	define('PASSWORD'						,'password');
	define('MAC_PHONE'						,'macPhone');
	define('DATE_CREATE'					,'dateCreate');
	define('SEND_REGID'						,'sendRegID');
	define('OK_TRACK'						,'okTrack');
	define('OK_LOCK'						,'okLock');
	define('OK_B_CONTACT'					,'okBackUpContact');
	define('PROTAG_REGISTER'				,'protagCardApply');
	define('SEND_TRACK_DATA'				,'sendTrack');
	define('LAT'							,'latitude');
	define('LONG'							,'longitude');
	define('ACC'							,'accuracy');
	define('BAT'							,'battery');
	define('IMAGE'							,'image');
	define('OK_IMAGE_CAPTURE'				,'okImageCapUpload');
	define('IMAGE_NUM'						,'imageNum');
	define('PROTAG_NAME'					,'protagName');
	define('LAST_DATE'						,'lastDateKnown');
	define('PROTAG_MAC'						,'macAddress');
	define('SEND_IOS_NOTI_TOKEN'			,'sendiOSNotiToken');
	define('IOS_NOTI_TOKEN'					,'iOSNotiToken');
	define('PASSIVE_TRACK'					,'passiveTrack');
	define('LAST_FLARE'						,'lastFlare');
	/*
		messages
	*/
	define('MSG_IOS_TEST_TRACK'				,'Please enter PROTAG application and send the request again');
?>