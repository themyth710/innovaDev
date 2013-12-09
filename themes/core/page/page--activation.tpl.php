<?php

	$formActivation = true;

	if($messages)
		$formActivation = false;
?>


<!--wrapper-->
<div id = 'wrapper'>
	<!--background-->
	<div class = 'container-1'>
		<div class = 'background'></div>
	</div>
	<!--main content-->
	<div class = 'container-2 center'>
			<!--instruction-->
			<div id = 'instruction' class = 'normal-text instruction'>

			<!--print the instruction to user-->
			<?php 
				if($messages)
					echo $messages;
			?>

			</div>

				<!--logo-->
				<?php if(!$messages){ ?>
					<div id = 'logo' class = 'grid-1'>
						<a href = 'http://theprotag.com'>
							<h1 class = 'text-remove logo'>INNOVA LOGO</h1>
						</a>
					</div>
				<?php } ?>

				<!--reset form-->
				<div class = 'grid-2' id = 're-form'>

				<!--print the form -->
				<?php
					if($formActivation){
						$output = drupal_get_form('form_account_activation'); 
						print render($output);
					}
				?>  

				</div>

			<?php if($messages){ ?>

				<!--logo-->
				<div id = 'logo'>
					<a href = 'http://theprotag.com'>
						<h1 class = 'text-remove logo'>INNOVA LOGO</h1>
					</a>
				</div>

		<	<?php } ?>
			<!--  -->			

			<!--clear float-->
			<div class = 'clear'></div>
	</div>
	<!--full page-->
	<div id = 'push'></div>
	
</div>	