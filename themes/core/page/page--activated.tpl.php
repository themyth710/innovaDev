<?php
	if(isset($_GET['token'])){
		
		$token = $_GET['token'];
		
		if(!activationTokenHandler($token))
			redirectUser('activation');
		else{
			
			$message = '<div class = "message  status">You have successful activated your account. Please <a href = "login">Click here</a> to login. </div>';
		}
		
	}
	else
		redirectUser('activation');
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
				if($message)
					echo $message;
			?>
			</div>

			<!--logo-->
			<?php if($message){ ?>

				<!--logo-->
				<div id = 'logo'>
					<a href = 'http://theprotag.com'>
						<h1 class = 'text-remove logo'>INNOVA LOGO</h1>
					</a>
				</div>

			<?php } ?>
			<!--  -->			

			<!--clear float-->
			<div class = 'clear'></div>
	</div>
	<!--full page-->
	<div id = 'push'></div>
	
</div>	