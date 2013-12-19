<link href="//netdna.bootstrapcdn.com/bootstrap/3.0.0/css/bootstrap.min.css" rel="stylesheet">

<!--wrapper-->
<div id = 'wrapper'>
	<!--background-->
	<div class = 'container-1'>
		<div class = 'background'></div>
	</div>
	<!--main content-->
	<div class = 'container-2 center'>
			<div class = 'error-text small-text' id = 'login-fail'>
				<?php
					echo $messages;
				?>
			</div>
			<!--logo-->
			<div id = 'logo' class = 'grid-1'>
				<a href = 'http://theprotag.com'>
					<h1 class = 'text-remove logo'>INNOVA LOGO</h1>
				</a>
				<div id="reportFound">
					<button class="btn btn-danger" id="protagHelpBtn" data-toggle="modal" data-target="#myModal">
					PROTAGERS HELP
					</button>
					<br></br>
					<p>
						Find the PROTAG card and want to help?
					</p>
					<hr>
					<div id="errorMessage" style="color: red;"></div>
					<div id="successMessage" style="color: green;"></div>
				</div>
			</div>

			<!--login form -->
			<div id = 'login-form' class = 'grid-2'>
				<?php $output = drupal_get_form('form_registration_form'); 
								print render($output); ?> 
				<a id = 'forgot-psw' href = 'reset'>Forgot password</a>
			</div>

			<!--clear float-->
			<div class = 'clear'></div>
	</div>
		<!-- Modal -->
	<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
	  <div class="modal-dialog">
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
	        <h4 class="modal-title" id="myModalLabel"><span class="badge" id="orderNum">1</span> Enter PROTAG ID</h4>
	      </div>
	      <div class="modal-body">
<!-- 	      	<form action="#">
 -->	          <strong>PROTAG ID number</strong>
	    		  <input type="textarea" id="serialNumber" class="form-control" >
	          <!-- <strong>Your Name*</strong>
	    		  <input type="textarea" name="reporter_name" class="form-control">
	          <strong>Your Email-address*</strong>
	    		  <input type="textarea" name="reporter_email" class="form-control">
	          <strong>Contact Number</strong>
	    		  <input type="textarea" name="contact_number" class="form-control">
	          <strong>Message</strong></br>
	    		  <textarea type="textarea" name="message" class="form-control" rows="3"></textarea> -->
	    		  <button class="mybtn btn" id="searchBtn" >Search</button>
<!-- 	    	</form>
 -->	    	<hr>
	    	<div id="returnMessage">
<!-- 	    		//sites/all/modules/tracking/communication/non_user_found_report.php
 -->	    		
	    	</div>
	  	  </div>
	      <!-- <div class="modal-footer">
	      	<button type="submit" class="btn btn-primary" >Save changes</button>
	        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
	      </div> -->
	  		
	    </div><!-- /.modal-content -->
	  </div><!-- /.modal-dialog -->
	</div><!-- /.modal -->


	<!-- <div class="modal fade" id="myModal2" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
	  <div class="modal-dialog">
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
	        <h4 class="modal-title" id="myModalLabel"><span class="badge" id="orderNum">2</span> Please enter your details</h4>
	      </div>
	      <div class="modal-body">
      		<form action='#'>
	      		  <input type='hidden' id='serial_number'>
	          <strong>Your Name*</strong>
	    		  <input type="textarea" id="reporter_name" class="form-control">
	          <strong>Email</strong>
	    		  <input type="textarea" id="reporter_email" class="form-control">
	          <strong>Contact Number</strong>
	    		  <input type="textarea" id="contact_number" class="form-control">
	          <strong>Message</strong></br>
	    		  <textarea type="textarea" id="message" class="form-control" rows="3"></textarea>
	    		  <button class="mybtn btn" id="sendBtn" >SEND</button>
    		</form>
	  	  </div>
	      <!-- <div class="modal-footer">
	      	<button type="submit" class="btn btn-primary" >Save changes</button>
	        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
	      </div> -->
	  		
	    </div><!-- /.modal-content -->
	  </div><!-- /.modal-dialog -->
	</div><!-- /.modal --> -->
	<!--full page-->
	<div id = 'push'></div>
</div>