<!--wrapper-->
<div class = 'wrapper'>
	
	<div class = 'container transition'>
		<!-- world background -->
		<div class = 'row'>
				<div class = 'background-img center-block text-center'></div>
		</div>

		<!-- split -->
		<div class="row">&nbsp;</div>

		<!-- main section -->
		<div class = 'row'>
			
			<!-- split column -->
			<div class = 'col-md-2 col-lg-2 col-sm-1 col-xs-1'></div>

			<!-- protag helper column -->
			<div class = 'col-md-4 col-xs-10 col-sm-5 col-lg-4'>
				<div class = 'row'>
					<div class = 'logo center-block'><h1 class = 'hidden'>INNOVA LOGO</h1></div>
				</div>

				<!-- split -->
				<div class="row">&nbsp;</div>

				<!-- protag help button -->
				<div class = 'row'>
					<div class = 'col-md-12'>
						<div class = 'row text-center' id="reportFound">
							<button class="btn btn-danger">PROTAGERS HELP</button>
						</div>
						<div class="row">&nbsp;</div>
						<div class = 'row'>
							<p class = 'text-center'>Find the PROTAG card and want to help?</p>
						</div>
						<hr>
					</div>
				</div>
			</div>

			<!-- login form column -->
			<div class = 'col-md-4 col-xs-10 col-sm-5 col-lg-4 col-lg-offset-0 col-sm-offset-0 col-md-offset-0 col-xs-offset-1'>

				<!-- error -->
				<div class = 'row'>
					<?php
						if($messages == INCORRECT_ACCOUNT){
							echo '<div class = "alert alert-danger">Your email or password is not correct. Please try again or <span><a href = "reset">click here</a></span> to recover your password.</div>';
						}
						else
							if($messages == ACCOUNT_NOT_ACTIVATE){
								echo '<div class = "alert alert-danger">Your account has not been activated. Please check your mail box for confirmation email or <span><a href = "activation">click here</a></span> to reactivate your account.</div>';
							}
					?>
				</div>

				<!-- form -->
				<div class = 'row'>
					<?php $output = drupal_get_form('form_login_form'); print render($output); ?>
				</div>
			</div>

			<!-- split column -->
			<div class = 'col-md-2 col-lg-2 col-sm-1 col-xs-1'></div>
		</div>
	</div>

	<!-- full page -->
	<div class = 'push'></div>
</div>