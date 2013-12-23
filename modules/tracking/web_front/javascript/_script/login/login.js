jQuery(document).ready(function(){
	
	var form = {
		
		loginForm : '#form-login-form',

		validateForm : function(form){
			
			jQuery(form).validate({
				
				rules: {
				    
				    email: {
				      	minlength: 2,
				      	required: true,
				      	email: true
				    },
				    
				    password: {
				      	required: true		      
				    },
				},

				highlight: function(element) {
					console.log(element);
				  	jQuery(element).closest('.form-group').addClass('has-error');
				},

				 unhighlight: function(element) {
		            jQuery(element).closest('.form-group').removeClass('has-error');
		        },

				errorElement: 'span',
		        errorClass: 'help-block',

		        errorPlacement: function(error, element) {
		            
		            if(element.parent('.input-group').length) {
		                
		                error.insertAfter(element.parent());
		            
		            } 
		            else {
		                
		                error.insertAfter(element);
		            }
		        }
			})		
		}
	}

	form.validateForm(form.loginForm);
})