(function ($) {
	/*==================================================Public function=========================================================*/
	//inner action class is used to transfer user information between server and browser through ajax call 
	//private values
	var api = {
		USER_ACTION:{
			phoneLoad : 'phoneListLoad',
			activityLoad : 'activityListLoad',

			removePhone: 'removePhone',
			retrieveImgCap: 'loadImageCapture',
			retrieveProfile : 'retrieveProfile',
			saveProfile : 'saveProfile',
			retrieveProtag : 'retrieveProtag',
			savePhoneName: 'savePhoneName',
		},
		PHONE_ACTION:{
			track : 'track',
			startTrack : 'startTrack',
			testTrack: 'testTrack',
			tracking : 'tracking',
			stopTrack : 'stopTrack',
			lock : 'lock',
			backupContact:'bContact',
			takePicture:'imageCapture',	
			passiveTrack : 'passiveTrack',
			stopPassiveTrack : 'stopPassiveTrack', 
		},
		_this : null,
		fail  : 'fail',
		error_code : 100,
		success_code : 200,
	};

	//constructor
	Drupal.behaviors.innerAction = function(){
	   
	   //default path properties
	   this.userAjaxAddr  		  = Drupal.settings.basePath + 'ajax/userAction';
	   this.phoneAjaxAddr 		  = Drupal.settings.basePath + 'ajax/phoneAction'; 
	   this.sendPhoneMessageAddr  = Drupal.settings.basePath + 'ajax/sendMessage'; 
	   api._this 		          = this;
	};

	/*=================================================

		@all ajax action
		@these actions not inclue the send message to the phone

	===================================================*/
	Drupal.behaviors.innerAction.prototype.ajaxAction = function(action, message, successCallBack, errorCallBack){
		if(action == api.USER_ACTION.phoneLoad ||
		   action == api.USER_ACTION.removePhone||
		   action == api.USER_ACTION.retrieveImgCap||
		   action == api.USER_ACTION.retrieveProfile||
		   action == api.USER_ACTION.saveProfile||
		   action == api.USER_ACTION.retrieveProtag||
		   action == api.USER_ACTION.savePhoneName||
		   action == api.USER_ACTION.activityLoad ||
		   action == api.USER_ACTION.retrieveLostReport){
			api._this.ajaxCall(action, message, successCallBack, errorCallBack, 0);
		}
		else 
			if(action == api.PHONE_ACTION.track ||
			   action == api.PHONE_ACTION.startTrack ||
			   action == api.PHONE_ACTION.stopTrack ||
			   action == api.PHONE_ACTION.tracking ||
			   action == api.PHONE_ACTION.lock ||
			   action == api.PHONE_ACTION.backupContact ||
			   action == api.PHONE_ACTION.takePicture ||
			   action == api.PHONE_ACTION.testTrack){
				api._this.ajaxCall(action, message, successCallBack, errorCallBack, 1);
			}
		return false;	
	};

	/*===================================================

		@includes all the send message to the phone action

	=====================================================*/
	Drupal.behaviors.innerAction.prototype.phoneSendMsgAction = function(action, message, successCallBack, errorCallBack){
		if(action == api.PHONE_ACTION.track ||
		   action == api.PHONE_ACTION.startTrack ||
		   action == api.PHONE_ACTION.stopTrack ||
		   action == api.PHONE_ACTION.tracking ||
		   action == api.PHONE_ACTION.lock ||
		   action == api.PHONE_ACTION.backupContact||
		   action == api.PHONE_ACTION.takePicture ||
		   action == api.PHONE_ACTION.testTrack ||
		   action == api.PHONE_ACTION.passiveTrack ||
		   action == api.PHONE_ACTION.stopPassiveTrack){
			api._this.ajaxCall(action, message, successCallBack, errorCallBack, 2);
		}
		
		return false;	
	};
	/*=========================================================Private function==================================================================*/
	/*===============================================================================================

		@call ajax to fixed ajax address used for inner action
		@param action: action that need php to do
		@message : always null if needed some information
		@successCallBack and errorCallBack are both function to call when can or can not retrieve data
		@this function is private
		@param object is the dom that html will prepend

	===============================================================================================*/
	Drupal.behaviors.innerAction.prototype.ajaxCall = function(action, message, successCallBack, errorCallBack, address){
		
		//initialize the address
		var addr = api._this.userAjaxAddr;

		if(address == 1) 
			addr = api._this.phoneAjaxAddr;
		if(address == 2)
			addr = api._this.sendPhoneMessageAddr;

		$.ajax({
	        url      : addr,
	        type     :'POST',
	        dataType :'json',
	        cache	 : false,
	        data     : {
	        			'action' : action,
	        			'message': message,
	        },
	        
	        //the success call back when all the data are sent to server
	        success: function(data){console.log(data);

	        	if(successCallBack){
	        		if(data)

	        			//if got error when the string return got error
	        			//we need to detect whether the error got message or not so that we can display it to user
	        			if(data.status.code == api.error_code)
	        				if(!data.message)
	        					errorCallBack();
	        				else
	        					successCallBack(data, action);
	        			else
	        				successCallBack(data, action);      			
	        		else
	        			errorCallBack();
	        	}
	        },
	        //the error call back when we can not connect to server or server down
	        error: function(xhr,err){
	        	if(errorCallBack){
	        		console.log(xhr + '   ' + err);
                 }
	        }
        });
	};
}(jQuery));