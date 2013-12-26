<div id = 'map'></div>
<div id = 'options-bar' class = 'options top-nav'>
	<ul>
		<li id = 'mo-phone-select'>
			<div class ='button-top-nav top-nav-header first last'>
				<span class = 'top-nav-icon'></span>
				<span id = 'top-nav-phone-name'>
					<!--contains current phone name-->
				</span>
			</div>
			<div class ='pre-top-nav-child' id = 'top-nav-phone-child-list'>
				<!--Will be filled with all other phones-->
			</div>
		</li>	
		
		<li id = 'mo-lock' class = 'float-right mobile-options'>
			<div class ='button-top-nav text-bold first last'>
				<span class = 'top-nav-icon '></span>
				<span> Lock&Ring </span>
			</div>
			<!--lock dialog -->
			<div class ='dialog-top-nav'>
				<!--header-->
				<span class="remove-icon transition"></span>
				<div class="dialog-header text-bold ">
					Lock it
				</div>
				<!--body-->		
				<div class="dialog-body" id ='lock-dialog-body'>
					<div id = 'lock-dialog-child-paragraph'>
						<p><strong>Lost your phone? And you have some private things inside?</strong></p>
						<br/>
						<p>Even if you lost your device, you can upgrade right now and prevent anyone from accessing information from your device</p>
					</div>
					<form id = 'lock-dialog-child-form'>
						<input type ='password' name = 'lock-password' size = '24' maxlength = '4' id = 'lock-password' placeholder = 'password' data-int class ='required'>
						<br/>
						<br/>
						<textarea name = 'lock-message' id = 'lock-message' placeholder = 'message' cols = '20' rows = '4'></textarea>
					</form>
				</div>					
				<div class="top-nav-icon">
				</div>
				<div class='smallest-reloader' style = 'width:100%'>
				</div>
				<div id = 'lock-button' class="button first">
					Lock it
				</div>
			</div>
		</li>
		
		<?php 
		//Hide the buttons not being used
		/*
		<li id = 'mo-ring' class = 'float-right mobile-options'>
			<div class ='button-top-nav text-bold last'><span class = 'top-nav-icon '></span><span>Ring</span></div>
			<!--ring dialog-->
			<div class ='dialog-top-nav'>
				<!--header-->
				<span class="remove-icon transition"></span>
				<div class="dialog-header text-bold ">Ring it</div>
				<!--body-->	
				<div class="dialog-body">
					<p><strong>Is your phone nearby but you can't see it? Sound an alarm to get to it</strong></p>
					<br/>
					<p>Keep in mind it's a very loud siren. You can make it stop from this screen by turning your phone off</p>
				</div>					
				<div class="top-nav-icon"></div>
				<div id = 'ring-button' class="button">Ring it</div>
			</div>
		</li>
		
		<li id = 'mo-test-track' class = 'float-right mobile-options'>
			<div class ='button-top-nav text-bold first last'><span class = 'top-nav-icon '></span><span>Test Track</span></div>
			<!--ring dialog-->
			<div class ='dialog-top-nav'>
				<!--header-->
				<span class="remove-icon transition"></span>
				<div class="dialog-header text-bold ">Test Track</div>
				<!--body-->	
				<div class="dialog-body">
					<p><strong>Test whether PROTAG can truly track your phone</strong></p>
					<br/>
					<p>This saves the trouble of requiring you to walk a long distance to initialize the track</p>
					<br/>
					<p>Requires app to be in the foreground for iOS.</p>
				</div>					
				<div class="top-nav-icon"></div>
				<div id = 'test-track-button' class="button">Test Track</div>
			</div>
		</li>	
		<li id = 'mo-wipe' class = 'float-right mobile-options'>
			<div class ='button-top-nav text-bold first'>
				<span class = 'top-nav-icon '></span>
				<span>Wipe</span>
			</div>
			<!-- wipe dialog -->
			<div class ='dialog-top-nav'>
				<!--header-->
				<span class="remove-icon transition"></span>
				<div class="dialog-header text-bold ">
					Wipe data
				</div>
				<!--body-->
				<div class="dialog-body">
					<p><strong>Lost your device, and you want to keep your data safe</strong></p>
					<br/>
					<p>Keep in mind it's a very loud siren. You can make it stop from this screen by turning your phone off</p>
				</div>					
				<div class="top-nav-icon">
				</div>
				<div id = 'wipe-button' class="button">
					Wipe Data
				</div>
			</div>
		</li>
		
		*/ ?>
		
		
	</ul>

</div>


<div class = 'pre-track-button'>
	<div id = 'track-button' class = 'track-button small-text start'>START TRACK</div>
</div>

<div id = 'status-bar' class = 'status'>
	<div id = 'battery-status'>
		Battery level: <span id = 'battery-level'></span>
	</div>
	<div id = 'text-status'>
		<span id = 'status-label'></span>
		<span class = 'small-reloader'></span>
	</div>
</div>