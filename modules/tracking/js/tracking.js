(function ($) {
  var api = {
	uiObject : null,

	init : function(){
		this.uiObject = new ui();
	},

	navHandle : function(){
		this.uiObject.navAction();
	},

	homePageAction : function(){
		this.uiObject.homePageButtonAction();
    this.uiObject.imageCaptureAction();
    this.uiObject.backupContactAction();
    this.uiObject.profileSettingAction();
	},

  trackingPhoneList : function(){
      this.uiObject.phoneListActionOnTrackingPage();
    },

  fancyBox : function(){
    $('.fancybox').fancybox();
  },

  loadReportDetails : function(){
    this.uiObject.lostReportAction();
  },

  }

  api.init();
  api.navHandle();
  api.homePageAction();
  api.trackingPhoneList();
  api.fancyBox();
  api.loadReportDetails();
  
})(jQuery);