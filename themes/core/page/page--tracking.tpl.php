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

					</div>
					<!--contains the phone list-->
					
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

	<!--full page first protag-->
	<div class="modal fade" id="protag0" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
	  <div class="modal-dialog">
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
	        <h4 class="modal-title" id="myModalLabel">Your Belonging PROTAG</h4>
	      </div>
	      <div class="modal-body">
	      		<div class="mylabel"><strong>Name</strong></div><div class="myvalue" id="protagName0"></div><br>
	      		<div class="mylabel"><strong>Location</strong></div><div class="myvalue" id="lastKnownLoc0"></div><br>
	      		<div class="mylabel"><strong>Last Known Time</strong></div><div id="timeLost0" class="myvalue"></div><br>
	      		<div class="mylabel"><strong>Serial Number</strong></div>
	      		<div class="myvalue" id='serialNum0'></div><br>
	      		<hr>
	      		<div id="lostReportMessage">
	      			<div id="toggleBtn" class="toggleBtn">
		      				<div id="mySwitch0" class="make-switch  switch-small" data-on="success" data-on-label="Secured" data-off-label="LOST"data-off="danger">
		      					<input type="checkbox" id='toggleSwitch0' checked>
		      				</div>
	      			</div>
	      			<div id="editBtn0" class="saveBtn"></div>
		      		<br></br>
	      			<div class="reportMessage" id="reportMessage0"></div>
	      		</div>
	      		<br></br>
	      		<div class="alertMessage" id="alertMessage0"></div>
	      		<div id="deletePro">
	      			<a id='deleteProtag0' data-toggle='modal' data-target='#deleteProtag'>Delete This Belonging</a>
	      		</div>
	  	  </div>
	    </div><!-- /.modal-content -->
	  </div><!-- /.modal-dialog -->
	</div><!-- /.modal -->

	<!--full page second protag-->
	<div class="modal fade" id="protag1" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
	  <div class="modal-dialog">
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
	        <h4 class="modal-title" id="myModalLabel">Your Belonging PROTAG</h4>
	      </div>
	      <div class="modal-body">
	      		<div class="mylabel"><strong>Name</strong></div><div class="myvalue" id="protagName1"></div><br>
	      		<div class="mylabel"><strong>Location</strong></div><div class="myvalue" id="lastKnownLoc1"></div><br>
	      		<div class="mylabel"><strong>Last Known Time</strong></div><div id="timeLost1" class="myvalue"></div><br>
	      		<div class="mylabel"><strong>Serial Number</strong></div>
	      		<div class="myvalue" id='serialNum1'></div><br>
	      		<hr>
	      		<div id="lostReportMessage">
	      			<div id="toggleBtn" class="toggleBtn">
		      				<div id="mySwitch1" class="make-switch  switch-small" data-on="success" data-on-label="Secured" data-off-label="LOST"data-off="danger">
		      					<input type="checkbox" id='toggleSwitch1' checked>
		      				</div>
	      			</div>
	      			<div id="editBtn1" class="saveBtn"></div>
		      		<br></br>
	      			<div class="reportMessage" id="reportMessage1"></div>
	      		</div>
				<br></br>
	      		<div class="alertMessage" id="alertMessage1"></div>
	      		<div id="deletePro">
	      			<!-- <form action="sites/all/modules/tracking/communication/delete_protag.php" method="post">
	      				<input type="hidden" id="mac_addr1" name="mac_ad"> -->
	      				<a id='deleteProtag1' data-toggle='modal' data-target='#deleteProtag'>Delete This Belonging</a>
	      			<!-- </form> -->
	      		</div>
	  	  </div>
	    </div><!-- /.modal-content -->
	  </div><!-- /.modal-dialog -->
	</div><!-- /.modal -->

	<!--full page second protag-->
	<div class="modal fade" id="protag2" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
	  <div class="modal-dialog">
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
	        <h4 class="modal-title" id="myModalLabel">Your Belonging PROTAG</h4>
	      </div>
	      <div class="modal-body">
	      		<div class="mylabel"><strong>Name</strong></div><div class="myvalue" id="protagName2"></div><br>
	      		<div class="mylabel"><strong>Location</strong></div><div class="myvalue" id="lastKnownLoc2"></div><br>
	      		<div class="mylabel"><strong>Last Known Time</strong></div><div id="timeLost2" class="myvalue"></div><br>
	      		<div class="mylabel"><strong>Serial Number</strong></div>
	      		<div class="myvalue" id='serialNum2'></div><br>
	      		<hr>
	      		<div id="lostReportMessage">
	      			<div id="toggleBtn" class="toggleBtn">
		      				<div id="mySwitch2" class="make-switch  switch-small" data-on="success" data-on-label="Secured" data-off-label="LOST"data-off="danger">
		      					<input type="checkbox" id='toggleSwitch2' checked>
		      				</div>
	      			</div>
	      			<div id="editBtn2" class="saveBtn"></div>
		      		<br></br>
	      			<div class="reportMessage" id="reportMessage2"></div>
	      		</div>
				<br></br>
	      		<div class="alertMessage" id="alertMessage2"></div>
	      		<div id="deletePro">
	      			<a id='deleteProtag2' data-toggle='modal' data-target='#deleteProtag'>Delete This Belonging</a>
	      		</div>
	  	  </div>
	    </div><!-- /.modal-content -->
	  </div><!-- /.modal-dialog -->
	</div><!-- /.modal -->

	<!--full page second protag-->
	<div class="modal fade" id="protag3" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
	  <div class="modal-dialog">
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
	        <h4 class="modal-title" id="myModalLabel">Your Belonging PROTAG</h4>
	      </div>
	      <div class="modal-body">
	      		<div class="mylabel"><strong>Name</strong></div><div class="myvalue" id="protagName3"></div><br>
	      		<div class="mylabel"><strong>Location</strong></div><div class="myvalue" id="lastKnownLoc3"></div><br>
	      		<div class="mylabel"><strong>Last Known Time</strong></div><div id="timeLost3" class="myvalue"></div><br>
	      		<div class="mylabel"><strong>Serial Number</strong></div>
	      		<div class="myvalue" id='serialNum3'></div><br>
	      		<hr>
	      		<div id="lostReportMessage">
	      			<div id="toggleBtn" class="toggleBtn">
		      				<div id="mySwitch3" class="make-switch  switch-small" data-on="success" data-on-label="Secured" data-off-label="LOST"data-off="danger">
		      					<input type="checkbox" id='toggleSwitch3' checked>
		      				</div>
	      			</div>
	      			<div id="editBtn3" class="saveBtn"></div>
		      		<br></br>
	      			<div class="reportMessage" id="reportMessage3"></div>
	      		</div>
	      		<br></br>
	      		<div class="alertMessage" id="alertMessage3"></div>
	      		<div id="deletePro">
	      			<a id='deleteProtag3' data-toggle='modal' data-target='#deleteProtag'>Delete This Belonging</a>
	      		</div>
	  	  </div>
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
	      	
	          <input type="hidden" name='mac_ad' id="mac_addr">
	          <strong>Lost Location</strong>
	    		  <input type="textarea" id="location" name="location" class="form-control">
	          <strong>Contact Name</strong>
	    		  <input type="textarea" id="contact_name" name="contact_name" class="form-control" >
	          <strong>Contact Number</strong>
	    		  <input type="textarea" id="contact_number" name="contact_number" class="form-control">
	    	  <strong>Belonging Descriptions</strong>
	    		  <textarea type="textarea" id="description" name="description" class="form-control"></textarea>
	          <strong>Reward Message</strong>
	    		  <textarea rows="2" id="message" name="message" class="form-control"></textarea>
	    		  <input type="checkbox" id="will_notify" name="will_notify" value='1'> Will notify other users about your lost portag info
	  		  </div>
	      <div class="modal-footer">
	      	<button class="btn btn-primary" id="sendReport">Save changes</button>
	        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
	      </div>
	    </div><!-- /.modal-content -->
	  </div><!-- /.modal-dialog -->
	</div><!-- /.modal -->

	<div class="modal fade" id="deleteProtag" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
	  <div class="modal-dialog">
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
	        <h4 class="modal-title" id="myModalLabel">Delete Protag </h4>
	      </div>
	      <div class="modal-body">
	          Are you sure to delete this protag?
	      <div class="modal-footer">
	      	<button class="btn btn-primary" id="confirmDelete">Yes</button>
	        <button type="button" class="btn btn-default" data-dismiss="modal">No</button>
	      </div>
	    </div><!-- /.modal-content -->
	  </div><!-- /.modal-dialog -->
	</div><!-- /.modal -->

	<div id = 'push'></div>
</div>