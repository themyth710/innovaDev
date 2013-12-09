<?php
	checkUserExist();
?>
<link href="//netdna.bootstrapcdn.com/bootstrap/3.0.0/css/bootstrap.min.css" rel="stylesheet">
<link href="//cdnjs.cloudflare.com/ajax/libs/x-editable/1.5.0/bootstrap3-editable/css/bootstrap-editable.css" rel="stylesheet"/>
<link href="bootstrap-switch.css" rel="stylesheet">

<div id = 'wrapper'>
	<!--contain the side nav and logo of the page-->
	<div class = 'container-1' id = 'nav-panel'>
		<?php
			//use another page to store the navigation php
			include('sites/all/themes/core/page/page--navigationPanel.php');
		?>
	</div>
	
	
	<!-- store the main contain of the page-->
	<div class = 'container-2' id = 'main-panel'>	
			<div class = 'grid-5 big-reloader'></div>
			<!--title-->
			<div id = 'title' class = 'grid-3'>
				<!--Title used for all pages-->
				<h1 class = 'xxlarge-text text-bold'>My Mobile</h1>
			</div>
			<div>
				<div id = 'activity-updates'>
					<h1 class = 'xxlarge-text text-bold'> Activity Updates </h1>
					<div class='activity-table'>
						<!--contains activity list-->
					</div>
				</div>
				
				<div class = 'grid-4' id = 'content-list'>
					<div id = 'content'>
						<!--contains the phone list-->
					</div>
				
					<div id = 'content-2'>
						<!--contains image capture & backup-->
					</div>
					
					<div id = 'map-region' style ='display:none'>
						<?php
							//use another page to store the map php
							include('sites/all/themes/core/page/page--mapRegion.php');
						?>
					</div>
				</div>
				
			</div>
			
	</div>
	<!--full page-->

	


	<div class="modal fade" id="myModal2" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
	  <div class="modal-dialog">
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
	        <h4 class="modal-title" id="myModalLabel">Your Belonging PROTAG</h4>
	      </div>
	      <div class="modal-body">
	      		<div class="mylabel"><strong>Name</strong></div><div class='myvalue' id="protagName"></div><br>
	      		<div class="mylabel"><strong>Location</strong></div><div class='myvalue' id='lastKnownLoc'></div><br>
	      		<div class="mylabel"><strong>Last Known Time</strong></div><div id='timeLost' class='myvalue'></div><br>
	      		<div class="mylabel"><strong>Serial Number</strong></div>
	      		<div class='myvalue'>
	      			<a href="#" id="serial_num" data-type="text" data-pk="1" data-url="/development/sites/all/modules/tracking/communication/set_serial_number.php" data-title="Enter Serial Number"></a>
	      		</div><br>
	      		<hr>
	      		<div id="lostReportMessage">
	      			<div id="toggleBtn" class="toggleBtn">
		      				<div id="mySwitch" class="make-switch  switch-small" data-on="success" data-on-label="Secured" data-off-label="LOST"data-off="danger">
							    	<input type="checkbox" id='toggleSwitch' checked>
							</div>
	      			</div>
	      			<div id="saveBtn" class="saveBtn"></div>
		      		<br></br>
	      			<div id="reportMessage"></div>
	      		</div>
	      		<br></br>
	      		<div id="deletePro">
	      			<form action="sites/all/modules/tracking/communication/delete_protag.php" method="post">
	      				<input type="hidden" id="mac_addr2" name="mac_ad">
	      				<a id='deleteProtag' onclick="$(this).closest('form').submit()">Delete This Belonging</a>
	      			</form>
	      		</div>

	          <!-- <strong>Your Name*</strong>
	    		  <input type="textarea" name="reporter_name" class="form-control">
	          <strong>Your Email-address*</strong>
	    		  <input type="textarea" name="reporter_email" class="form-control">
	          <strong>Contact Number</strong>
	    		  <input type="textarea" name="contact_number" class="form-control">
	          <strong>Message</strong></br>
	    		  <textarea type="textarea" name="message" class="form-control" rows="3"></textarea> -->
<!-- 	    		  <button class="btn" id="searchBtn" >Search</button>
 -->	  	  </div>
	      <!-- <div class="modal-footer">
	      	<button type="submit" class="btn btn-primary" >Save changes</button>
	        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
	      </div> -->
	  		
	    </div><!-- /.modal-content -->
	  </div><!-- /.modal-dialog -->
	</div><!-- /.modal -->
	
	<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
	  <div class="modal-dialog">
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
	        <h4 class="modal-title" id="myModalLabel">Lost Report </h4>
	      </div>
	      <div class="modal-body">
	      	<form action="sites/all/modules/tracking/communication/lost_report.php" method='post'>
	          <input type="hidden" name='mac_ad' id="mac_addr">
	          <strong>Lost Location</strong>
	    		  <input type="textarea" name="location" class="form-control">
	          <strong>Contact Name</strong>
	    		  <input type="textarea" name="contact_name" class="form-control" >
	          <strong>Contact Number</strong>
	    		  <input type="textarea" name="contact_number" class="form-control">
	    	  <strong>Belonging Descriptions</strong>
	    		  <textarea type="textarea" name="description" class="form-control"></textarea>
	          <strong>Reward Message</strong>
	    		  <textarea rows="2" name="message" class="form-control"></textarea>
	    		  <input type="checkbox" name="will_notify" value='1'> Will notify other users about your lost portag info
	  		  </div>
	      <div class="modal-footer">
	      	<button type="submit" class="btn btn-primary" id="sendReport">Save changes</button>
	        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
	      </div>
	  		</form>
	    </div><!-- /.modal-content -->
	  </div><!-- /.modal-dialog -->
	</div><!-- /.modal -->

	
	<div id = 'push'></div>
</div>