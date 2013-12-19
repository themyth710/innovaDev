jQuery(document).ready(function($){
	$('#form-registration-form input.form-submit').click(function(e){

		e.preventDefault();
		$(this).closest('form').formvalidate({
			failureMessages: true,
			messageFailureClass: 'label label-important',
			
			localization: {
				en: {				
					failure: {
						email: function(title, value, name, input) {
							return 'Invalid email';
						}
					}
				}
			}
		})
	})

	$('#form-reset-password input.form-submit').click(function(e){
		e.preventDefault();
		$(this).closest('form').formvalidate({
			failureMessages: true,
			messageFailureClass: 'label label-important',
			
			localization: {
				en: {				
					failure: {
						email: function(title, value, name, input) {
							return 'Invalid email';
						}
					}
				}
			}
		})
	})

	$('#form-new-password input.form-submit').click(function(e){
		e.preventDefault();
		$(this).closest('form').formvalidate({
			failureMessages: true,
			messageFailureClass: 'label label-important',
		})
	})

	$('#searchBtn').click(function(e){
		$("#returnMessage").empty();
		var serial_num = $("#serialNumber").val();
		var returnMessage = "";
		if(serial_num.length!=8){
			returnMessage += "<p>Invald Serial number. Please enter valid serial number</p>";	
			$("#returnMessage").html(returnMessage);	
			return;
		}
		$.ajax({
			type:"POST",
			url: "/development/sites/all/modules/tracking/communication/non_user_found_report.php",
			data: {
				"serial_num": serial_num
			},
			success: function(data, textStatus, xhr){ 
				console.log(xhr.status);
				console.log(data);
				console.log(textStatus);
				//when status =200
				
				if(xhr.status==200){
					if(serial_num == ""){
						returnMessage += "<p>Serial Number cannot be empty. Please enter valid Serial Number.</p>";
					}
					else if(data.reason== 0){//no such protag id
						returnMessage += "<p>Sorry PROTAG ID is not registered.<br></br>";
						returnMessage += "Please make sure that you entered the correct serial number on the card</p>";				}
					else if(data.reason==2){ //not lost 
						returnMessage += "<p>Serial number "+ serial_num + " has not been reported as lost.<br>";
						returnMessage += "Please enter your details for onwer to contact you.</p>";
						returnMessage += "<form action='#'>";
		      		  	returnMessage += "<input type='hidden' id='serial_number'>";
		          		returnMessage += "<strong>Your Name*</strong>";
		    			returnMessage += "<input type='textarea' id='reporter_name' class='form-control'>";
		          		returnMessage += "<strong>Email</strong>";
		          		returnMessage += "<input type='textarea' id='reporter_email' class='form-control'>";
		    		  	returnMessage += "<strong>Contact Number</strong>";
		    		  	returnMessage += "<input type='textarea' id='contact_number' class='form-control'>";
		    		  	returnMessage += "<strong>Message</strong></br>";
		    		  	returnMessage += "<textarea type='textarea' id='message' class='form-control' rows='3'></textarea>";
		          		returnMessage += "<button class='mybtn btn' id='sendBtn' >SEND</button>";
		    		  	returnMessage += "</form>";
						$('#serial_number').val(serial_num);
					}
					else if(data.reason==3){ //same message sent three times
						console.log("same message sent over three times");
					}	
					else{
						//database error
						console.log("database error");
					}
				}
				else if(xhr.status==201){//the protag reported lost and the serial number existed
					var mac_ad = data.mac_ad;
					var contact_name = data.contact_name;
					var contact_number= data.contact_number;
					var message = data.message;
					returnMessage += "<p>Serial Number " + serial_num + " has been reported as lost, the owner's message is as follows: </p>";
					returnMessage += "<p>Contact Number: "+contact_number + "</p>";
					returnMessage += "<p>Name: " + contact_name + "</p>";
					returnMessage += "<p>Reward Message: " + message + "</p>";
					returnMessage += "<p><hr></hr></p>";
 					returnMessage += "<p>Please contact the owner or enter your details if you wish for owner to contact you instead</p>";
					returnMessage += "<form action='#'>";
	      		  	returnMessage += "<input type='hidden' id='serial_number'>";
	          		returnMessage += "<strong>Your Name*</strong>";
	    			returnMessage += "<input type='textarea' id='reporter_name' class='form-control'>";
	          		returnMessage += "<strong>Email</strong>";
	          		returnMessage += "<input type='textarea' id='reporter_email' class='form-control'>";
	    		  	returnMessage += "<strong>Contact Number</strong>";
	    		  	returnMessage += "<input type='textarea' id='contact_number' class='form-control'>";
	    		  	returnMessage += "<strong>Message</strong></br>";
	    		  	returnMessage += "<textarea type='textarea' id='message' class='form-control' rows='3'></textarea>";
	          		returnMessage += "<button class='mybtn btn' id='sendBtn' >SEND</button>";
	    		  	returnMessage += "</form>";
					$('#serial_number').val(serial_num);
				}

				$("#returnMessage").html(returnMessage);	
			},
			error: function(data, textStatus, xhr){
				returnMessage += "<p>Invald Serial number. Please enter valid serial number</p>";	
				$("#returnMessage").html(returnMessage);
				console.log("hahapiange error");
			}
		});

		
	})
	
	$('#sendBtn').click(function(e){
		var serial_num = $("#serial_number").val();
		var name = $('#reporter_name').val();
		var email = $('#reporter_email').val();
		var contact_number = $('#contact_number').val();
		var message = $('#message').val();
		$.ajax({
			type:"POST",
			url:"/development/sites/all/modules/tracking/communication/non_user_found_report.php",
			data: {
				"serial_num": serial_num,
				"reporter_name": name,
				"reporter_email": email,
				"contact_number": contact_number,
				"message": message
			},
			success: function(data, textStatus, xhr){
				if(xhr.status =200 && data.reason==3){
					$("#errorMessage").html("<p>You have submited too many reports. Please be patient.</p>");
				}
				else if (xhr.status == 201 ){
					$("#successMessage").html("<p>The report has been submitted successfully!</p>");
				}
				console.log("data");
				console.log(data);
				$('#myModal').modal('hide');
        		$('#myModal2').modal('hide');  
			},
			error: function(data,textStatus,xhr){
				console.log(xhr.status);
				console.log("report error");
				$('#myModal').modal('hide');
        		$('#myModal2').modal('hide');  
			}
		});
	});

});