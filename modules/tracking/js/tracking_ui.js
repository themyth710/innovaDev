//this includes all the ui front end
var ui = (function ($){
	//constant value
	var api = {
		ERROR:{
			retrieve:{
				code:100,
				message:'Fail to retrieve data',
			},
			timeOut:{
				code:114,
				message:'Timeout we have not receieved your phone data, your phone may be logged out or tracking disabled please try again',
			},
			sendMessageFail:{
				code:106,
				message:'Fail to send your command to your phone. Please try again',
			},
			oldAndNewPasswordProb:{
				code:116,
				message:'Your password does not match',
			},
		},

		MESSAGE:{
			deletePhone:'Are you sure you want to delete this phone ? This phone will be removed from your account and you can not retrieve it again.',
			sending:'Tracking ...',
			waitingReply:'Waiting for location',
			locked:'Your phone has been locked',
			backuped:'All your data has been backed up',
			done:'Done!',
			phoneResponseFirstTime:'Location received ...',
			tracked:'Tracking',
			sendMessageProb:'Unable to perform task, please try again',
			noPhoneSelection: 'You do not have any phones to select',
			trackingExcuse: 'Sorry you are performing tracking. You should press stop track before choose another phone',
			trackBelongingExcuse: 'Sorry you are performing tracking. You can not tracking belonging location. Please wait/press stop track',
			testTrackSuccess: 'Test Track was successful',
			newPassAndRepeatPassProb : 'Your new password and repeat password does not match',
			passwordSaveSuccess: 'Your password has been changed successfully',
			defaultiOSImageMessage: 'My account is 068-3572-4, the card behind says 577. Please delete this message after reading',
			phoneNameSaved:'Your phone name has been saved',
                        stopTrack:' ',  
		},

		NAV_ATTR:{
			home:'nav-home',
			trackMobile:'nav-tr-mobile',
			imageCapture:'nav-img',
			trackBelonging: 'nav-tr-belong',
			profileSetting : 'nav-profile',
                        backupDetails : 'nav-backup',
			signOut : 'nav-signout',
		},

		USER_ACTION:{
			phoneLoad : 'phoneListLoad',
			removePhone: 'removePhone',
			retrieveImgCap: 'loadImageCapture',
			retrieveProfile : 'retrieveProfile',
			saveProfile : 'saveProfile',
			retrieveProtag : 'retrieveProtag',
			savePhoneName: 'savePhoneName',
			retrieveLostReport : 'retrieveLostReport',
		},

		PHONE_ACTION:{
			track : 'track',
			startTrack : 'startTrack',
			testTrack : 'testTrack',
			tracking : 'tracking',
			stopTrack : 'stopTrack',
			lock : 'lock',
			backupContact:'bContact',
			takePicture:'imageCapture',
			passiveTrack :'passiveTrack',
			stopPassiveTrack : 'stopPassiveTrack',
		},

		_this: null,
		_ajaxObject: null,
		_map:null,
		_marker:null,
		_circle:null,
		_markerList:null,
		_protag_name_list: null,
		_location_list: null,
		_tagDate_list: null,
		_serail_list: null,
		_lost_info_list: null,
		_phoneList: null,
		_firstTimeLoadMap: true,
		_firstTimeLoadMap2 : true,
		_trackInterval: 3000,
		_timeOutObject: null,
		_curPhoneID : null,
		_curPhoneType: null,
		
		_firstTimeLoadImageCapturePage : true,
        _firstTimeLoadBackUpDetailsPage : true,
		_firstTimeLoadProfileSettingPage : true,

		_curImageNumber : 0,
		_isTracking : false,
		_customiOSMessage: '',

		error_code : 100,
		success_code : 200,

		_directory : 'http://innovatechnology.com.sg/homepage/sites/all/modules/tracking/UserRegion/ImageCapture/',
                _directoryBackUp :
'http://innovatechnology.com.sg/homepage/sites/all/modules/tracking/UserRegion/BackUp/',

	};

	/*==============

		constructor

	===============*/
	function ui(){

		//create an instance of 
		this.ajaxObject = new Drupal.behaviors.innerAction();
		api._ajaxObject = this.ajaxObject; 
		api._this 	= this;
		api._phoneList  = new Array();
		api._ad_mac_list = new Array();
		this.init();
	}

	/*==================================

		@initialize all the ui for user
	
	=================================*/
	ui.prototype.init = function(){
		//this.adJustMainPanelWidth();
		
		//loading the phone list and added to user
		api._this.bigScreenAction(false);
		api._ajaxObject.ajaxAction(api.USER_ACTION.phoneLoad, null, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);	
	}

	/*=============================================================

		@add and remove active class according to the nav user click
		@e is event, object is #side-nav a

	==============================================================*/
	ui.prototype.navAction = function(){
		$('#side-nav a').click(function(e){
			//prevent default action
			e.preventDefault();
			e.stopPropagation();

			//add in the class for the navigation
			if(!$(this).hasClass('nav-active'))
				$(this).closest('ul').find('.nav-active').removeClass('nav-active');

			//check the attribue for click navigation
			if($(this).parent().attr('id') == api.NAV_ATTR.home){

				$('#title h1').text('My Mobile');
				api._this.displayObject($('#content'), true);
				api._this.displayObject($('#content-2'), false);
				if(!$(this).hasClass('nav-active')){
					
					api._this.bigScreenAction(false);
					
					$(this).addClass('nav-active');
					
					api._ajaxObject.ajaxAction(api.USER_ACTION.phoneLoad, null, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);				
				}
				api._this.displayObject($('#map-region'), false);
				api._this.displayObject($('#title'), true);
			}
			else
				if($(this).parent().attr('id') == api.NAV_ATTR.trackMobile){
					if(!$(this).hasClass('nav-active')){

						$(this).addClass('nav-active');
						
						if(api._phoneList instanceof Array){
							
							var phoneID   = 0;
							var typePhone = api._phoneList[0];

							if(api._curPhoneType != null && api._curPhoneID != null){
								phoneID   = api._curPhoneID;
								typePhone = api._curPhoneType;
							}
							
							api._this.showPhoneTrackingPage(phoneID, typePhone); 
						}
						else
							api._this.showPhoneTrackingPage(null, null);
					}		
			}
			else 
				if($(this).parent().attr('id') == api.NAV_ATTR.imageCapture){
					if(!$(this).hasClass('nav-active')){
						$(this).addClass('nav-active');
						api._this.showImageCapturePage();
					}
				}
			else
				if($(this).parent().attr('id') == api.NAV_ATTR.trackBelonging){
					if(api._isTracking){
						$('#nav-tr-mobile a').addClass('nav-active');
						alertify.alert(api.MESSAGE.trackBelongingExcuse);
					}
					else{
						if(!$(this).hasClass('nav-active')){
							$(this).addClass('nav-active');
							api._this.showTrackBelongingPage();
						}
					}
				}
                        else 
				if($(this).parent().attr('id') == api.NAV_ATTR.backupDetails){
					if(!$(this).hasClass('nav-active')){
						$(this).addClass('nav-active');
						api._this.showBackUpDetailsPage();
					}
				}
			else 
				if($(this).parent().attr('id') == api.NAV_ATTR.signOut){
					window.location = 'user/logout';
			}
			else
				if($(this).parent().attr('id') == api.NAV_ATTR.profileSetting){
					if(!$(this).hasClass('nav-active')){
						$(this).addClass('nav-active');
						api._this.showProfileSettingPage();
					}
			}
		})	
	};
	
	/*===================================================

		@list all click event on homepage 
		@include remove the phone and select the phone

	====================================================*/
	ui.prototype.homePageButtonAction = function(){

		//remove phone click 
 		$(document).on('click','#remove-phone',function(){
			
			//take the id of the phone into message and call ajax	
			var message = $(this).attr('data-id'); 

			alertify.confirm(api.MESSAGE.deletePhone, function (e) {
			    if (e) {			    	
			    	api._this.bigScreenAction(false);
			        api._ajaxObject.ajaxAction(api.USER_ACTION.removePhone, message, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
			        return true;
			    }
			    else
			    	return false; 
			});
		});

 		//select phone click
		$(document).on('click','#select-phone', function(e){
			
			e.preventDefault();
			if(api._isTracking){
				alertify.alert(api.MESSAGE.trackingExcuse);
				return false;
			}	

			//take the phone id from the selection
			var phoneID   = $(this).closest('.phone-list').children('#remove-phone').attr('data-id');
			var typePhone = $(this).closest('.phone-list').children('#remove-phone').attr('type-phone');

			//show the phone tracking page
			api._this.showPhoneTrackingPage(phoneID, typePhone);

			//add class to navigation sidebar
			$('#nav-home a').removeClass('nav-active');
			$('#nav-tr-mobile').addClass('nav-active');
		})

		$(document).on('click','#save-phone-name', function(e){
			e.preventDefault();

			//take the phone id from the selection
			var phoneID   = $(this).closest('.phone-list').children('#remove-phone').attr('data-id');
			var phoneName = $(this).prev().prev().children('h2').text();

			var message   = phoneID + '_' + phoneName; 

			api._ajaxObject.ajaxAction(api.USER_ACTION.savePhoneName, message, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
		})

		$(document).on('click','#lost-phone', function(e){
			e.preventDefault();

			//take the phone id from the selection
			var phoneID   = $(this).closest('.phone-list').children('#remove-phone').attr('data-id');
			var typePhone = $(this).closest('.phone-list').children('#remove-phone').attr('type-phone');

			var message   = phoneID + '_' + typePhone; 

			api._ajaxObject.phoneSendMsgAction(api.PHONE_ACTION.passiveTrack, message, null, null);
		})

		$(document).on('click','#receive-phone', function(e){
			e.preventDefault();

			//take the phone id from the selection
			var phoneID   = $(this).closest('.phone-list').children('#remove-phone').attr('data-id');
			var typePhone = $(this).closest('.phone-list').children('#remove-phone').attr('type-phone');

			var message   = phoneID + '_' + typePhone; 
			api._ajaxObject.phoneSendMsgAction(api.PHONE_ACTION.stopPassiveTrack, message, null, null);
		})

		$(document).on('click','#backup-contact', function(e){
			e.preventDefault();

			//take the phone id from the selection
			var phoneID   = $(this).closest('.phone-list').children('#remove-phone').attr('data-id');
			var typePhone = $(this).closest('.phone-list').children('#remove-phone').attr('type-phone');

			var message   = phoneID + '_' + typePhone; 
			api._ajaxObject.phoneSendMsgAction(api.PHONE_ACTION.backupContact, message, null, null);
		})

		$(document).on('click', '#see-backup', function(){
			window.open('http://innovatechnology.com.sg/development/sites/all/modules/tracking/UserRegion/Backup/yourfile.php', '_blank');
		})
	};

	/*=================================================
	
		@includes the action for select the phone list

	==================================================*/
	ui.prototype.phoneListActionOnTrackingPage = function(){

		//all the list option for the phone includes track, lock, wipe
		$('.mobile-options').click(function(e){
			e.preventDefault();
			e.stopPropagation();

			$(this).closest('ul').find('.active').removeClass('active');
			$(this).addClass('active');
			$(this).children(':first').addClass('active');

			return false;
		})

		//phone select action
		// $('#mo-phone-select').toggle(
		// 	function(){
		// 		$(this).addClass('active');
		// 		$(this).children(':first').addClass('active');
		// 	}, 
		// 	function(e){
		// 		e.preventDefault();
		// 		e.stopPropagation();

		// 		if(api._isTracking){
		// 			alertify.alert(api.MESSAGE.trackingExcuse);
		// 		}
		// 		else{
		// 			//select the phoneID and typePhone from the current target
		// 			var phoneID   = $(e.target).attr('data-id');				
		// 			var typePhone = $(e.target).attr('type-phone');

		// 			api._curPhoneID   = phoneID;
		// 			api._curPhoneType = typePhone;

		// 			$('#top-nav-phone-name').attr('data-id'   , phoneID);
		// 			$('#top-nav-phone-name').attr('type-phone', typePhone);
		// 			$('#top-nav-phone-name').text( typePhone);
		// 			api._this.refreshToolbar();
		// 			api._this.refreshTrackButtonText();
		// 		}

		// 		$(this).removeClass('active');
		// 		$(this).children(':first').removeClass('active');
		// 	}
		// )

		//close button on phone options bar
		$('.dialog-top-nav .remove-icon').click(function(e){
			e.preventDefault();
			e.stopPropagation();

			$(this).closest('ul').find('.active').removeClass('active');
		})

		api._this.trackingPageButtonClickAction();	
	}

	/*=================================================== private method =========================================================*/
	
	/*==========================================

		@adjust the main panel width to fix the screen

	==========================================*/
	ui.prototype.adJustMainPanelWidth = function(){
		var mainPanel  = $('#main-panel');
		var sideNav    = $('#nav-panel');	

		mainPanel.css('width',screen.width - sideNav.width());
	};

	/*====================================================

		@display the message for error call back function
	
	====================================================*/
	ui.prototype.displayErrorCallBackAction = function(){
		var message = api.ERROR.retrieve.message;
		alertify.alert(message);
		api._this.bigScreenAction(true);
	};

	/*=========================================================================

		@display success call back
		@includes: remove, retrive phone list, all client data checking action

	==========================================================================*/
	ui.prototype.displaySuccessCallBackAction = function(data, action){

		switch(action){
			case api.USER_ACTION.phoneLoad:
				api._this.removeHtml($('#content'));
				var content = api._this.phoneListDisplay(data);
				api._this.displayHtml($('#content'), content);
				break;
			case api.USER_ACTION.removePhone:
				api._ajaxObject.ajaxAction(api.USER_ACTION.phoneLoad, null, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
				break;
			case api.USER_ACTION.retrieveImgCap:
				api._this.imageCapRefresh(data);
				break;
			case api.USER_ACTION.retrieveProfile:
				api._this.profileRetrieve(data);
				break;
			case api.USER_ACTION.retrieveLostReport:
				api._this.retrieveLostReportInfo(data);
				break;
			case api.USER_ACTION.saveProfile:
				api._this.profileSave(data);
				break;
			case api.USER_ACTION.retrieveProtag:
				api._this.retrieveProtagAction(data);
				break;
			case api.USER_ACTION.savePhoneName:
				alertify.alert(api.MESSAGE.phoneNameSaved);
				break;
			case api.PHONE_ACTION.track:
				api._this.dataSuccessCheckingHandle(action, data);
				break;
			case api.PHONE_ACTION.testTrack:
				api._this.dataSuccessCheckingHandle(action, data);
				break;
			case api.PHONE_ACTION.startTrack:
				api._this.dataSuccessCheckingHandle(action, data);
				break;
			case api.PHONE_ACTION.tracking:
				api._this.dataSuccessCheckingHandle(action, data);
				break;
			case api.PHONE_ACTION.lock:
				api._this.dataSuccessCheckingHandle(action, data);
				break;
			case api.PHONE_ACTION.backupContact:
				api._this.dataSuccessCheckingHandle(action, data);
				break;
			case api.PHONE_ACTION.takePicture:
				api._this.imageCaptureSuccessCheckingHandle(action, data);
				break;
			default:
				break;
		}

		api._this.bigScreenAction(true);
	}

	/*===============================

		@map initialize and display

	================================*/
	ui.prototype.mapInit = function(){
		
		var latitude  = 0;
	    var longitude = 0;
		
		api._map = new google.maps.Map(document.getElementById("map"), {
		        center: new google.maps.LatLng(latitude, longitude),
		        zoom: 4,
		        mapTypeId: 'roadmap'
		});
	}

	/*=============================================================

		@load the location according to the latitude and longitude
		@it also add in the battery level to text that correspoding to battery

	=============================================================*/
	ui.prototype.loadMapLocation = function(lat, long, accuracy, battery){
		var point = new google.maps.LatLng(lat,long);
		
		if(api._marker)	
			api._marker.setMap(null);
		api._marker = new google.maps.Marker({
				map: api._map,
				position: point,
		});			  
		 
		api._marker.setPosition(point);
			api._map.panTo(point);
			 
			if(api._circle)
			 	api._circle.setMap(null);
			
			api._circle = new google.maps.Circle({
                center: point,
                radius: Math.round(accuracy),
                map: api._map,
                fillColor: '#8EE5FF',
                fillOpacity: 0.2,
                strokeColor: '#968FFF',
                strokeOpacity: 0.5
	        });
		         
		api._map.fitBounds(api._circle.getBounds());

		//add text to battery level
		$('#battery-level').text(battery);
	}

	/*================================================

		@prepend the content of the html to home page
		@param value : json data received from server
	================================================*/
	ui.prototype.phoneListDisplay = function(value){
		
		var content;

		//the phone list that we store in an array for easy taken in future
		api._phoneList = new Array();

		content = '<ul>';
		
		//check for value to be an array

		if(value.data && value.data instanceof Array){
			for(var i = 0; i < value.data.length; i++){
				//check if value  data is not null
				if(value.data[i]){

					content += "<li>";
					content += "<div class = 'phone-list transition'>";
					content += "<span class = 'remove-icon transition' id = 'remove-phone' data-id = '" + i + "' type-phone = '" + value.data[i][0] + "'></span>"
		        	content += "<div>";
		        	content += "<div class = 'phone-title center'>";
		        	content += "<h2 class = 'text-bold large-text' contenteditable = 'true'>" + value.data[i][1] + "</h2>";
		        	content += "</div>";
		        	content += "<div class = 'button center' id = 'select-phone'>Select</div>";
		        	content += "<div class = 'button center' id = 'save-phone-name'>Save</div>"; 
		        	content += "<div class = 'button center' id = 'lost-phone'>Lost</div>"; 
		        	content += "<div class = 'button center' id = 'receive-phone'>StopPassive</div>";
		        	content += "<div class = 'button center' id = 'backup-contact'>Backup</div>";
		        	content += "<div class = 'button center' id = 'see-backup'>Backup file</div>";
		        	content += "</div></div></li>";

		        	//add to phone list global variables
		        	api._phoneList.push(value.data[i][0]);
	        	}
			}
		}
		content += '<ul>';
		//initialize the current phone type and id for user incase user forgot to choose their phone
		if(value.data && value.data instanceof Array){
			if(value.data[0]){
				if(api._curPhoneID == null || api._curPhoneType == null){
					api._curPhoneID   = 0;
					api._curPhoneType = value.data[0][0];
				}
			}
		}
		else{
			api._curPhoneID   = null;
			api._curPhoneType = null;
		}

		return content;
	}

	/*===============================================================================================================

		@refresh the phone list on tracking page that display to the user according to the global variables phonelist 
		@so it is really easy for js to display

	================================================================================================================*/
	ui.prototype.refreshPhoneListOnTrackingPage = function(){
		
		var content = '';

		for(var i = 0 ; i < api._phoneList.length ; i++){
			content += "<div class ='button-top-nav top-nav-child' data-id = '" + i + "' type-phone = '" + api._phoneList[i] 
			+ "'>" + api._phoneList[i] + "</div>";
		}

		api._this.removeHtml($('#mo-phone-select #top-nav-phone-child-list'));

		//if the content is null then we no need to display anything
		if(content)
			api._this.displayHtml($('#mo-phone-select #top-nav-phone-child-list'), content);
	}

	/*=================================================

		@steps to show the phone tracking page to user

	=================================================*/	

	ui.prototype.showPhoneTrackingPage = function(phoneID, typePhone){

		if(api._markerList){
			for(var i = 0; i < api._markerList.length; i++){
				api._markerList[i].setMap(null);
				google.maps.event.clearInstanceListeners(api._markerList[i]);
			}
		}

		//hide all the title and main-content of the page
		api._this.displayObject($('#title'), false);
		api._this.displayObject($('#content'), false);
		api._this.displayObject($('#content-2') ,false);

		if(phoneID == null || typePhone == null){
			$('#top-nav-phone-name').text('No phone');
		}
		else{
			$('#top-nav-phone-name').text(typePhone);
			$('#top-nav-phone-name').attr('data-id', phoneID);
			$('#top-nav-phone-name').attr('type-phone',typePhone);

			//store all the phone ID and phone type to the user show that we can not which phone they choose at the first time
			api._curPhoneID   = phoneID;
			api._curPhoneType = typePhone;
		}

		api._this.refreshToolbar();
		api._this.refreshTrackButtonText();

		//display the phone child list to the user 
		api._this.refreshPhoneListOnTrackingPage();

		//display the map to user
		api._this.displayObject($('#map-region'), true);

		api._this.displayObject($('#options-bar'), true);
		api._this.displayObject($('#track-button'), true);
		$('#text-status').css('display','inline-block');	

		//check if it is the first time user load the map
		//if not then just display, no need to load the map again
		if(api._firstTimeLoadMap){
			api._this.mapInit();
			api._firstTimeLoadMap = false;
		}
	}

	/*



	*/
	ui.prototype.showImageCapturePage = function(){
		//change the title
		api._this.displayObject($('#title'), true);
		$('#title h1').text('Image Capture');
		

		if(api._firstTimeLoadImageCapturePage){
			api._this.bigScreenAction(false);

			var content  = "<div id = 'image-capture-container' class = 'img-cap-container'>";
				content +=		"<div class = 'text-bold large-text'><h2>Your picture</h2></div>";
				content +=		    "<div id = 'cap-img-list' class ='cap-img-list'>";
				content +=			"<ul>";
				content	+=				"<li id = 'img-pic-0'><span class = 'smallest-reloader'></span></li>";
				content	+=				"<li id = 'img-pic-1'><span class = 'smallest-reloader'></span></li>";
				content	+=				"<li id = 'img-pic-2'><span class = 'smallest-reloader'></span></li>";
				content	+=				"<li id = 'img-pic-3'><span class = 'smallest-reloader'></span></li>";
				content	+=				"<li id = 'img-pic-4'><span class = 'smallest-reloader'></span></li>";
				content	+=				"<li id = 'img-pic-5'><span class = 'smallest-reloader'></span></li>";
				content	+=			"</ul>";
				content	+=			"<div class = 'button' id ='take-picture-button'>Take Picture</div>";
				content	+=		"</div>";
				content	+= "</div>";
			
			//show the content of image capture
			api._this.displayHtml($('#content-2'), content);

			api._firstTimeLoadImageCapturePage = false;
			
			api._ajaxObject.ajaxAction(api.USER_ACTION.retrieveImgCap, null, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
		}
		else{
			api._this.displayObject($('#image-capture-container'), true);
		}
                api._this.displayObject($('#backup-Details-container'), false);
		api._this.displayObject($('#profile-settings-container'), false);
		api._this.displayObject($('#content-2'), true);
		api._this.displayObject($('#map-region'), false);
		api._this.displayObject($('#content'), false);
		
	}

	ui.prototype.imageCapRefresh = function(value){
		if(value.data && value.data instanceof Array){
			var content = '';
			for(var i = 0; i < value.data[1]; i++){
				
				content       = '<a class="fancybox" href="' + api._directory + value.data[0] + 'pic_' + i + '.jpg?timestamp=' + $.now() + '" data-fancybox-group="gallery" ><img class = "img-cap-thumbnail" src="' + api._directory + value.data[0] + 'pic_' + i + '.jpg?timestamp=' + $.now() + '" alt="Protag Image Capture for your phone" /></a>'

				api._this.displayHtml($('#img-pic-' + i), content);
				api._curImageNumber++;
			}
		}

		//update the current image number
		if(api._curImageNumber > 5)
			api._curImageNumber = 0;
		api._this.bigScreenAction(true);
	}

	ui.prototype.imageCaptureAction = function(){
	
		$('#take-picture-button').on('click', function(){
			
			if(api._curPhoneType == null|| api._curPhoneID == null){
				alertify.alert(api.MESSAGE.noPhoneSelection);
				return false;
			}

			if(!$(this).hasClass('active')){
				if(api._curPhoneType == 'Android'){
					if(api._this.sendMessage(api.PHONE_ACTION.takePicture, api._this.dataSuccessSendMessageHandle, api._this.displayErrorCallBackAction)){
	
						$(this).addClass('active');
	
						var currentImage = 'img-pic-' + api._curImageNumber;
	
						$('#' + currentImage +' .smallest-reloader').addClass('reloader-active');
					}
				}
				else if(api._curPhoneType == 'iOS'){
					alertify.prompt('Enter bogus message to send', function (e,str) {
					    if (e) {
					    	//erase all underscore because it is used as seperator
					    	api._customiOSMessage = str.replace(/_/g,"");
					    	if(api._this.sendMessage(api.PHONE_ACTION.takePicture, api._this.dataSuccessSendMessageHandle, api._this.displayErrorCallBackAction)){
							$(this).addClass('active');
							var currentImage = 'img-pic-' + api._curImageNumber;
							$('#' + currentImage +' .smallest-reloader').addClass('reloader-active');
						}
					    }
					},api.MESSAGE.defaultiOSImageMessage);
				}
			}		
		})
	}

	ui.prototype.imageCaptureSuccessCheckingHandle = function(action, value){

		if(value.data){	

			$('#img-pic-' + api._curImageNumber +' a').remove();

			var content       = '<a class="fancybox" href="' + api._directory + value.data + '?timestamp=' + $.now() + '" data-fancybox-group="gallery" ><img class = "img-cap-thumbnail" src="' + api._directory + value.data + '?timestamp=' + $.now() + '" alt="Protag Image Capture for your phone" /></a>'

			api._this.displayHtml($('#img-pic-' + api._curImageNumber), content);
			
			var currentImage = 'img-pic-' + api._curImageNumber;

			$('#' + currentImage +' .smallest-reloader').removeClass('reloader-active');

			//update the current image number
			if(api._curImageNumber > 4)
				api._curImageNumber = 0;
			else
				api._curImageNumber ++;

			$('#take-picture-button').removeClass('active');

		}
		else{
			//time out
			//reset all action of user
			alertify.alert(api.ERROR.timeOut.message);
			$('#take-picture-button').removeClass('active');
			
			var currentImage = 'img-pic-' + api._curImageNumber;

			$('#' + currentImage +' .smallest-reloader').removeClass('reloader-active');
		}
	}

	ui.prototype.showBackUpDetailsPage = function(){
		//change the title
		api._this.displayObject($('#title'), true);
		$('#title h1').text('BackUp Contacts');


		if(api._firstTimeLoadBackUpDetailsPage){
			api._this.bigScreenAction(false);

			var content  = "<div id = 'backup-Details-container' class = 'backup-Details-container'>";
				content +=		"<div class = 'text-bold large-text'><h2>Your Backup Contacts</h2></div>";
				content +=		    "<div id = 'backup-list' class ='backup-list'>";
				content +=			"<ul>";
				content	+=			"</ul>";
				content	+=			"<div class = 'button' id ='backup-button'>BackUp</div>";
				content	+=		"</div>";
				content	+= "</div>";
			
			//show the content of backup Details
			api._this.displayHtml($('#content-2'), content);

			api._firstTimeLoadBackUpDetailsPage = false;
			
			//api._ajaxObject.ajaxAction(api.USER_ACTION.retrieveImgCap, null, //api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
		}
		else{
			api._this.displayObject($('#backup-Details-container'), true);
		}
                api._this.displayObject($('#image-capture-container'), false);
		api._this.displayObject($('#profile-settings-container'), false);
		api._this.displayObject($('#content-2'), true);
		api._this.displayObject($('#map-region'), false);
		api._this.displayObject($('#content'), false);
		
	}

        ui.prototype.backupContactAction = function(){
          $('#backup-button').on('click', function(){
			
			if(api._curPhoneType == null|| api._curPhoneID == null){
				alertify.alert(api.MESSAGE.noPhoneSelection);
				return false;
			}

			if(!$(this).hasClass('active')){
		                  if(api._curPhoneType == 'iOS'){
					alertify.prompt('Enter bogus message to send', function (e,str) {
					    if (e) {
					    	//erase all underscore because it is used as seperator
					    	api._customiOSMessage = str.replace(/_/g,"");
					    	if(api._this.sendMessage(api.PHONE_ACTION.backupContact, api._this.dataSuccessSendMessageHandle, api._this.displayErrorCallBackAction)){
							$(this).addClass('active');
						}
					    }
					},api.MESSAGE.defaultiOSImageMessage);
				}
			}
		})
	}

        ui.prototype.showProfileSettingPage = function(){
		//change the title
		api._this.displayObject($('#title'), true);
		$('#title h1').text('Profile Settings');

		if(api._firstTimeLoadProfileSettingPage){
			api._this.bigScreenAction(false);

			var content  = "<div id = 'profile-settings-container' class = 'prof-set-container'>";
				content +=		"<form id = 'profile-settings-form' class = 'prof-set-form'>";
				content +=		    "<div class = 'text-bold large-text prof-title'>Email</div>";
				content +=			"<div class = 'prof-input-row'>";
				content	+=				"<div class = 'prof-input-title'>Email Address</div>";
				content	+=				"<div class = 'prof-input'><input type='text' name='email' id='profile-email' readonly></div>";
				content	+=			"</div>";
				content	+=			"<div class= 'text-bold large-text prof-title'>Password</div>";
				content	+=			"<div class = 'prof-input-row'>";
				content	+=				"<div class = 'prof-input-title'>Current Password</div>";
				content	+=				"<div class = 'prof-input'><input type='password' name='cur-pass' id='prof-cur-pass'></div>";
				content	+=			"</div>";
				content	+=			"<div class = 'prof-input-row'>";
				content	+=				"<div class = 'prof-input-title'>New Password</div>";
				content	+=				"<div class = 'prof-input'><input type='password' name='new-pass' id='prof-new-pass'></div>";
				content	+= 			"</div>";
				content	+=			"<div class = 'prof-input-row'>";
				content	+=				"<div class = 'prof-input-title'>Repeat Password</div>";
				content	+=				"<div class = 'prof-input'><input type='password' name='repeat-pass' id='prof-repeat-pass'></div>";
				content	+=			"</div>";
				content	+=			"<div class = 'prof-input-row'>";
				content	+=			"<div ><span class = 'button' id = 'prof-save-button'>Save changes</span><span class = 'smallest-reloader'></span></div>";
				content	+=			"</div>";
				content	+=		"</form>";
				content	+= "</div>";
			
			//show the content of image capture
			api._this.displayHtml($('#content-2'), content);

			api._firstTimeLoadProfileSettingPage = false;
			api._ajaxObject.ajaxAction(api.USER_ACTION.retrieveProfile, null, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
		}
		else{
			api._this.displayObject($('#profile-settings-container'), true);
		}
		api._this.displayObject($('#image-capture-container'), false);
		api._this.displayObject($('#content-2'), true);
		api._this.displayObject($('#map-region'), false);
		api._this.displayObject($('#content'), false);
	}

	ui.prototype.profileRetrieve = function(value){
		if(value.data){
			
			var email = value.data;

			$('#profile-email').val(email);
			api._this.bigScreenAction(true);
		}
	}

	ui.prototype.profileSettingAction = function(){
		$('#prof-save-button').on('click', function(e){

			if(!$(this).hasClass('active')){

				e.preventDefault();
				e.stopPropagation();

				var curPass 	= $('#prof-cur-pass').val();
				var newPass 	= $('#prof-new-pass').val();
				var repeatPass  = $('#prof-repeat-pass').val(); 

				if(curPass && newPass && repeatPass){
					if(newPass != repeatPass){
						alertify.alert(api.MESSAGE.newPassAndRepeatPassProb);
					}
					else{
						$(this).addClass('active');
						$('#profile-settings-form .smallest-reloader').addClass('reloader-active');

						var message = curPass + '_' + newPass;
						api._ajaxObject.ajaxAction(api.USER_ACTION.saveProfile, message, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
					}			
				}
			}		
		})
	}

	ui.prototype.profileSave = function(value){
		if(value.message){
			alertify.alert(api.ERROR.oldAndNewPasswordProb.message);
		}
		else{
			alertify.alert(api.MESSAGE.passwordSaveSuccess);
		}
		$('#profile-settings-form .smallest-reloader').removeClass('reloader-active');
		$('#prof-cur-pass').val('');
		$('#prof-new-pass').val('');
		$('#prof-repeat-pass').val('');
		$('#prof-save-button').removeClass('active');
	}

	ui.prototype.showTrackBelongingPage = function(){

		//hide all the title and main-content of the page
		api._this.displayObject($('#title'), false);
		api._this.displayObject($('#content'), false);
		api._this.displayObject($('#content-2') ,false);

		//display the map to user
		api._this.displayObject($('#map-region'), true);

		api._this.displayObject($('#options-bar'), false);
		api._this.displayObject($('#track-button'), false);
		api._this.displayObject($('#battery-status'), false);
		api._this.displayObject($('#text-status'), false);

		//check if it is the first time user load the map
		//if not then just display, no need to load the map again
		if(api._firstTimeLoadMap){
			api._this.mapInit();
			api._firstTimeLoadMap = false;
		}

		api._ajaxObject.ajaxAction(api.USER_ACTION.retrieveProtag, null, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
	}

	ui.prototype.retrieveLostReportInfo= function(value){

	}

	ui.prototype.retrieveProtagAction = function(value){
		api._this.loadListMapLocation(value);
	}

	ui.prototype.lostReportAction = function (){
		// for(var i=0; i<3; i++){
		$(document).on('click', '#link0', function(){
			console.log("here0");
			api._this.listenClicker(0);
		});
		$(document).on('click', '#link1', function(){
			console.log("here1");
			api._this.listenClicker(1);
		});
		$(document).on('click', '#link2', function(){
			console.log("here2");
			api._this.listenClicker(2);
		});
		// }
		$(document).on('click', '#link3', function(){
			console.log("here3");
			api._this.listenClicker(3);
		});		
	}
	
	ui.prototype.googleReverseGeo = function(lat,lng, i){
		 var latlng = new google.maps.LatLng(lat, lng);
		 var geocoder = new google.maps.Geocoder();
		 geocoder.geocode({'latLng': latlng}, function(results, status) {
		    if (status == google.maps.GeocoderStatus.OK) {
		      if (results[0]) {
		      	var detailedAddress = results[0].formatted_address;
		        api._location_list[i]= detailedAddress;
		      } else {
		        console.log("lat:"+lat+"long"+lng);
		      }
		    } else {
	          api._location_list[i]= "latitude:"+lat+" longitude:"+lng;
		      console.log("no results found");
	          console.log("lat:"+lat+"long"+lng);
		    }
		  });

	}

	ui.prototype.loadListMapLocation = function(value){
		
		if(api._marker)	
			api._marker.setMap(null);
		
		if(api._markerList){
			for(var i = 0; i < api._markerList.length; i++){
				api._markerList[i].setMap(null);
				google.maps.event.clearInstanceListeners(api._markerList[i]);
			}
		}

		api._markerList = new Array();
		infoWindowArray = new Array();
		api._protag_name_list = new Array();
		api._location_list = new Array();
		api._tagDate_list = new Array();
		api._serial_list = new Array();
		api._lost_info_list = new Array();

		if(value && value.data && value.data instanceof Array){
			for(var i = 0; i < value.data.length ;i++){

				api._protag_name_list[i]  = value.data[i].protag[2];
				api._tagDate_list[i]      = value.data[i].protag[3];
				lat   	   = value.data[i].protag[0];
				long  	   = value.data[i].protag[1];
				api._ad_mac_list[i]  = value.data[i].protag[4];
				api._lost_info_list[i]  = value.data[i].protag[5]; //lost status
				api._serial_list[i] = value.data[i].protag['serialNumber'];
				console.log("data");
				console.log(value.data[i]);

				if(lat && long){
					var point = new google.maps.LatLng(lat,long);	

					api._this.googleReverseGeo(lat,long,i);

					var marker = new google.maps.Marker({
						map: api._map,
						position: point,
					});			  

					api._markerList[i]=marker;

					marker.setPosition(point);
				}
				else
					continue;

				var contentString =  '<div id="infowindowDiv"><center><div><strong><a id="link'+i+'" href="#" data-toggle="modal" data-target="#myModal2">'+ api._protag_name_list[i] + '</a></strong></div>';					
					if(api._lost_info_list[i]==1){
						contentString += "<div id='lostLabel'> LOST </div></dvi></div></center>";
					}
					else{
						contentString += "<div id='securedLabel'> Secured </div></center></div>";
					}
				var infowindow = new google.maps.InfoWindow({
				    content: contentString
				});

				infoWindowArray[i]=infowindow;

				api._this.listenMarker(marker, infowindow, i);
			}
			if(infoWindowArray){
		        for(j in infoWindowArray){
		            infoWindowArray[j].open(api._map,api._markerList[j]);
		        }
	    	}
		}

		api._this.setBound();
		return false;
	}

	ui.prototype.listenClicker = function(i){
	   
   	   $('#serial_num').editable({
   	   		url: "/development/sites/all/modules/tracking/communication/set_serial_number.php",
   	   		value: api._serial_list[i],
   	   		params: function(params){
   	   			params.mac_ad = api._ad_mac_list[i];
   	   			console.log("params here");
   	   			console.log(params);
   	   			return params;
   	   		},
   	   		success: function(response, newValue){
   	   			console.log("success");
   	   			if(response.status == 'error') return response.msg;
   	   		}
   	   });   
       if(api._lost_info_list[i]==1){
       		$('#mySwitch').bootstrapSwitch('setState', false);
       		console.log(api._lost_info_list[i]);
       		console.log("false");
       		$('#reportMessage').html("Your device is reported as lost please slide back if you already find your device or it will keep tracking and drain battery.")
       		$('#saveBtn').html("<button  class='btn mybtn pull-right' data-toggle='modal' data-target='#myModal'>Edit Report</button>")
       }
       else{
       		$('#mySwitch').bootstrapSwitch('setState', true);
       		$('#reportMessage').html("Your device is in secured status. To mark it as lost please slide the button.");
       		console.log("true");
       }

   	    $('#mySwitch').on('switch-change', function (e, data) {
		    var val = data.value;
		    if(!val && api._lost_info_list[i]==0){
		    	console.log("wtf");
		    	$('#myModal').modal({
		    		show: true
		    	});

		    	$('#myModal').on('hidden.bs.modal', function () {
				  $('#mySwitch').bootstrapSwitch('setState', true);  
				  console.log('please hideen calsl s');
				});
		    }
		    else if(api._lost_info_list[i]==1){
		    	$.ajax({
		    		type: "POST",
		    		dataType: "json",
		    		url: "/development/sites/all/modules/tracking/communication/found_report.php",
		    		data:{
		    			"mac_ad": api._ad_mac_list[i]
		    		},
		    		success: function(data,textStatus,xhr){
		    			console.log("success");
					    $('#mySwitch').bootstrapSwitch('setState', true);  
   				   		window.location.assign(window.location.pathname);
		    		},
		    		error: function(textStatus,xhr){
		    			console.log("failure");
				        $('#mySwitch').bootstrapSwitch('setState', true);  
		    		}
		    	})

		    }
		});

	   $("#mac_addr").val(api._ad_mac_list[i]);
	   $("#mac_addr2").val(api._ad_mac_list[i]);
	   $('#protagName').html(api._protag_name_list[i]);
	   $('#lastKnownLoc').html(api._location_list[i]);
	   $('#timeLost').html(api._tagDate_list[i]);
	   $('#deleteProtag').on('click',function(e){
	   		window.location.assign(window.location.pathname);
	   });
	   $('#serial_num').html(api._serial_list[i]);
	   
	}
	ui.prototype.listenMarker = function(marker, tooltip, i){
		
	    // so marker is associated with the closure created for the listenMarker function call
	    google.maps.event.addListener(marker, 'click', function() {
	    					 //   if(infoWindowArray){
							    //     for(j in infoWindowArray){
							    //         infoWindowArray[j].close(api._map,api._markerList[j]);
							    //     }
						    	// }
						    	tooltip.open(api._map,marker);
						    	// api._this.listenClicker(i);
								// $('#myModal').modal({
								//     show: true,
								// });
	                    });
		}

	ui.prototype.setBound = function(){
		var bounds = new google.maps.LatLngBounds();

	    for (var i = 0; i < api._markerList.length; i++) {
	        bounds.extend(api._markerList[i].getPosition());
	    }

	    api._map.fitBounds(bounds);
	}

	ui.prototype.clientDataChecking = function(action, successCallBack, errorCallBack){

		var message   = api._curPhoneID + '_' + api._curPhoneType; 

		if(action == api.PHONE_ACTION.takePicture)
			message   = api._curPhoneID + '_' + api._curPhoneType + '_' + api._curImageNumber; 

		api._this.ajaxObject.ajaxAction(action, message, successCallBack, errorCallBack);
                
	}
	/*==================================================================
	
		@function support for client data checking successfull callback
				
	==================================================================*/
	ui.prototype.dataSuccessCheckingHandle = function(action, value){
		if(value.status){ 
			if(value.status.code == api.success_code){
				
				switch(action){

					case api.PHONE_ACTION.lock:
						alertify.alert(api.MESSAGE.locked);
						$('#lock-dialog-child-paragraph').show();
						$('#lock-button').addClass('first');
						$('#lock-button').text('Lock it');
						$('#mo-lock .smallest-reloader').removeClass('reloader-active');
						break;

					case api.PHONE_ACTION.backupContact:
						api._this.statusBarAction(api.done, false);
						alertify.alert(api.MESSAGE.backuped);
						break;

					case api.PHONE_ACTION.track:
						var message   = api._curPhoneID + '_' + api._curPhoneType;
						if(value.data == 1){
							//this is for android when there is 0 -> 1 action
							api._this.statusBarAction(api.MESSAGE.phoneResponseFirstTime, true);
							api._this.ajaxObject.ajaxAction(api.PHONE_ACTION.startTrack, message, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
						}
						else
							if(value.data == 2){
								//this is for ios when there is no 0 -> 1 action, just have 0 -> 2 action
								api._this.statusBarAction(api.MESSAGE.tracked, true);
								api._this.ajaxObject.ajaxAction(api.PHONE_ACTION.tracking, message, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
								//let the user to click stop track
								$('#track-button').removeClass('active').removeClass('start').addClass('stop').text('STOP TRACK');		
							}
						break;

					case api.PHONE_ACTION.startTrack:
						var message   = api._curPhoneID + '_' + api._curPhoneType;
						api._this.statusBarAction(api.MESSAGE.tracked, true);
						api._this.ajaxObject.ajaxAction(api.PHONE_ACTION.tracking, message, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
						//now we let the user click the button again
						$('#track-button').removeClass('active').removeClass('start').addClass('stop').text('STOP TRACK');		
						break;

					case api.PHONE_ACTION.tracking:
						var message   = api._curPhoneID + '_' + api._curPhoneType;

						if(value.data){
							api._timeOutObject = setTimeout(function(){api._this.ajaxObject.ajaxAction(api.PHONE_ACTION.tracking, message, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);}, 
				                          		api._trackInterval);
							api._this.loadMapLocation(value.data[0], value.data[1], value.data[2], value.data[3]);
						}
						else
							alertify.alert(api.ERROR.retrieve.message);
						
						break;
					case api.PHONE_ACTION.testTrack:
						if(value.data){
							api._this.loadMapLocation(value.data[0], value.data[1], value.data[2], value.data[3]);
							api._this.statusBarAction(api.MESSAGE.testTrackSuccess, false);
						}else{
							alertify.alert(api.ERROR.retrieve.message);
						}
						api._isTracking = false;
						break;
					default:break;
				}
			}
			else{
				api._isTracking = false;
				//time out
				//reset all action of user
				alertify.alert(api.ERROR.timeOut.message);

				//if the action is lock then reset all lock action
				//if not mean track then reset all track action
				if(action == api.PHONE_ACTION.lock){
					//add lock and wipe also
					$('#lock-dialog-child-paragraph').show();
					$('#lock-button').addClass('first');
					$('#lock-button').text('Lock it');
					$('#mo-lock .smallest-reloader').removeClass('reloader-active');
				}
				else{
					$('#track-button').removeClass('active');				
					api._this.statusBarAction(' ', false);
				}
			}
		}
		return false;
	}

	/*===================================
		
		@status bar show on tracking page

	====================================*/
	ui.prototype.statusBarAction = function(text, isShow){
		if(!isShow){
			api._this.displayObject($('#status-bar .small-reloader'), false);
			if(text)
				$('#status-label').text(text);
			return false;
		}
		else{
			api._this.displayObject($('#status-bar .small-reloader'), true);
			$('#status-label').text(text);
		}
	}

	/*=========================================================

		@display the html according to the html param
		@param object is #phone-list ul

	==========================================================*/
	ui.prototype.displayHtml = function(object, html){
		object.append(html);
	};

	/*====================================
	
		@prepend the text to the object

	====================================*/
	ui.prototype.removeHtml = function(object){
		object.empty();
	}

	/*==========================================

		@display the object to the user 
		@param isShow: show to the user or not

	===========================================*/

	ui.prototype.displayObject = function(object, isShow){
		if(isShow)
			object.css('display','block');
		else
			object.css('display','none');
	}
	
	/*==========================================
		@update the display of buttons according to the current phone selected
	===========================================*/
	
	ui.prototype.refreshToolbar= function(){
		//do not do anything if NULL, will cause problems
		if(api._curPhoneType == 'Android'){
			api._this.displayObject($('#mo-lock'), true);
		}
		else if(api._curPhoneType == 'iOS'){
			//api._this.displayObject($('#mo-test-track'), true);
			api._this.displayObject($('#mo-lock'), false);
		}
	}
	
	/*==========================================
		@update the text of the track button according to the current phone selected
	===========================================*/
	
	ui.prototype.refreshTrackButtonText= function(){
		if(api._curPhoneType == 'Android'){
			$('#track-button').text('START TRACK');
		}else if(api._curPhoneType == 'iOS'){
			$('#track-button').text('TEST TRACK');
		}
	}

	/*==================================================================

		@the action to fade the background and display the reloader on top
		
	==================================================================*/
	ui.prototype.bigScreenAction = function(isFade){
		var reloader   = $('.big-reloader');
		var background = $('#main-panel'); 

		if(!isFade){
			reloader.addClass('active');
			background.fadeTo('slow', 0.6);
		}
		else{
			reloader.removeClass('active');
			background.fadeTo('slow', 1);
		}
	};

	/*==========================================

		@function to send message to the phone

	===========================================*/
	ui.prototype.sendMessage = function(action, successCallBack, errorCallBack){
		if(api._curPhoneID == null || api._curPhoneType == null){
			alertify.alert(api.MESSAGE.noPhoneSelection);
			return false;
		}

		var message = '';
		//message = curphoneid + curphonetype + password + message
		if(action == api.PHONE_ACTION.lock){
			message = api._curPhoneID + '_' + api._curPhoneType + '_' + $('#lock-password').val() + '_' + $('#lock-message').val();
		}
		else if(action == api.PHONE_ACTION.takePicture){
			message = api._curPhoneID + '_' + api._curPhoneType + '_' + api._curImageNumber;
			if(api._curPhoneType=='iOS'){
				message += '_' + api._customiOSMessage;
			}
		}else if(action == api.PHONE_ACTION.backupContact){
			message = api._curPhoneID + '_' + api._curPhoneType;
                        if(api.curPhoneType == 'iOS'){
                                message += '_' +api._customeiOSMessage;
                        }
		}
		
		api._ajaxObject.phoneSendMsgAction(action, message, successCallBack, errorCallBack);

		return true; 
	}

	/*=========================================================

		@includes the action of button on tracking mobile page

	=========================================================*/
	ui.prototype.trackingPageButtonClickAction = function(){
		//track button click

		$('#track-button.start').on('click', function(e){
			e.preventDefault();
			e.stopPropagation();

			if(api._curPhoneType == null|| api._curPhoneID == null){
				alertify.alert(api.MESSAGE.noPhoneSelection);
				return false;
			}

			if($(this).hasClass('active')){
				return false;
			}
			else{
				//sending data ajax here
				//the successfull include releases the class active for button
				if(api._curPhoneType == 'Android' && api._this.sendMessage(api.PHONE_ACTION.startTrack, api._this.dataSuccessSendMessageHandle, api._this.displayErrorCallBackAction)){

					api._isTracking = true;
					//we want to remove all user actions on this button ulti the ajax is sent
					$(this).addClass('active');
					//display reloader
					api._this.statusBarAction(api.MESSAGE.sending, true);
					
				}else if(api._curPhoneType=='iOS'){
					if(api._isTracking){
						alertify.alert(api.MESSAGE.trackingExcuse);
					}else if(api._this.sendMessage(api.PHONE_ACTION.testTrack, api._this.dataSuccessSendMessageHandle, api._this.displayErrorCallBackAction)){
						api._isTracking = true;
						//display reloader
						api._this.statusBarAction(api.MESSAGE.sending, true);
					}
				}
			}
		});

		//stop track button click
		$('#track-button.stop').on('click', function(e){
			e.preventDefault();
			e.stopPropagation();

			if($(this).hasClass('active')){
				return false;
			}
			else{
				api._isTracking = false;
				//we want to remove all user actions on this button ulti the ajax is sent
				$(this).removeClass('stop').addClass('start').text('START TRACK');
				//display reloader
				api._this.statusBarAction(' ', false);
				api._this.sendMessage(api.PHONE_ACTION.stopTrack, api._this.dataSuccessSendMessageHandle, api._this.displayErrorCallBackAction);
				//remove the interval if exist in js and send stopTrack to phone
			    clearTimeout(api._timeOutObject);
			}
		})

		$('#lock-button').click(function(e){
			
			e.preventDefault();
			e.stopPropagation();

			if(api._curPhoneType == null|| api._curPhoneID == null){
				alertify.alert(api.MESSAGE.noPhoneSelection);
				return false;
			}

			if($(this).hasClass('first')){
				$(this).removeClass('first').addClass('second');
				$('#lock-dialog-child-paragraph').slideUp('slow');
				$('#lock-dialog-child-form').show('slow');
			}
			else
				if($(this).hasClass('second')){				
					$('#lock-dialog-child-form').formvalidate({
						//do not show message to user when input is not correct
						failureMessages: false,
						
						messageFailureClass: 'label label-important',
						
						onSuccess:function(form){
							$('#lock-button').removeClass('second').addClass('active');
							$('#lock-dialog-child-form').slideUp('slow');
							$('#lock-button').text('Locking');
							$('#mo-lock .smallest-reloader').addClass('reloader-active');
							//send ajax message
							api._this.sendMessage(api.PHONE_ACTION.lock, api._this.dataSuccessSendMessageHandle, api._this.displayErrorCallBackAction);
						},
					})	
				}
			return false;
		});
		
		/*$('#test-track-button').click(function(e){
			e.preventDefault();
			e.stopPropagation();
			
			if(api._curPhoneType=='iOS' && api._this.sendMessage(api.PHONE_ACTION.testTrack, api._this.dataSuccessSendMessageHandle, api._this.displayErrorCallBackAction)){
				//api._isTracking = true; //not sure whether to put this
				//display reloader
				api._this.statusBarAction(api.MESSAGE.sending, true);
			}
			return false;
		});*/
	}

	/*=======================================================

		@includes all the send message successfull handling
		@includes: start, stopTrack, lock, bContact

	========================================================*/
	ui.prototype.dataSuccessSendMessageHandle = function(value, action){

		//got message return and status code => fail to send data
		if(value.status.code == api.error_code){
			//if got problem in sending message -> retrieve to user
			alertify.alert(api.MESSAGE.sendMessageProb);
                        api._isTracking = false;
                        $('#status-label').text(api.MESSAGE.stopTrack);
                        $('#track-button').removeClass('active');
			api._this.statusBarAction(' ',false);
                        api._this.bigScreenAction(false);
	                clearTimeout(api._timeOutObject);
                        if(api._marker)	
			   api._marker.setMap(null);
                        api._this.bigScreenAction(true);
                        return false;
		}
  
		//success full send message
		switch(action){
			case api.PHONE_ACTION.startTrack:
				$('#status-label').text(api.MESSAGE.waitingReply);
				//send command to clientDataChecking to start checking data
				api._this.clientDataChecking(api.PHONE_ACTION.track, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
				break;
			case api.PHONE_ACTION.stopTrack:
				break;
			case api.PHONE_ACTION.testTrack:
				$('#status-label').text(api.MESSAGE.waitingReply);
				api._this.clientDataChecking(api.PHONE_ACTION.testTrack, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
				break;
			case api.PHONE_ACTION.lock:
				api._this.clientDataChecking(api.PHONE_ACTION.lock, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
				break;
			case api.PHONE_ACTION.backupContact:
                                $('#status-label').text(api.MESSAGE.backuped);
                                api._this.clientDataChecking(api.PHONE_ACTION.backupContact, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
				break;
			case api.PHONE_ACTION.takePicture:
				api._this.clientDataChecking(api.PHONE_ACTION.takePicture, api._this.displaySuccessCallBackAction, api._this.displayErrorCallBackAction);
				break;
			default:break;
		}
	}

	return ui;
}(jQuery));