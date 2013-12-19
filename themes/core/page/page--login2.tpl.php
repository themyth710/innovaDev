<!--wrapper-->
<div class = 'wrapper'>
	
	<div class = 'container'>
		<!-- world background -->
		<div class = 'row'>
				<div class = 'background-img center-block text-center'></div>
		</div>

		<!-- split -->
		<div class="row">&nbsp;</div>

		<!-- main section -->
		<div class = 'row'>
			
			<!-- split column -->
			<div class = 'col-md-2 col-lg-2 col-sm-1 col-xs-0'></div>

			<!-- protag help column -->
			<div class = 'col-md-4 col-xs-12 col-sm-5 col-lg-4'>
				<div class = 'row'>
					<div class = 'logo center-block'><h1 class = 'hidden'>INNOVA LOGO</h1></div>
				</div>
				<div class="row">&nbsp;</div>
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
			<div class = 'col-md-4 col-xs-12 col-sm-5 col-lg-4'>
				<?php $output = drupal_get_form('form_login_form'); print render($output); ?>
			</div>

			<!-- split column -->
			<div class = 'col-md-2 col-lg-2 col-sm-1 col-xs-0'></div>
		</div>
	</div>

	<div class = 'push'></div>
</div>