<!DOCTYPE html>
<html>
<body>
	<?php $dateTime = strtotime($params['date']);
		  $date     = date('F j, Y', $dateTime);
		  $time     = date('g:i a', $dateTime);
		  /*require('../../../themes/core/mail/googleMapEnc.php');
		  $PolyEnc   = new PolylineEncoder();
		  $convertAcc= $params['acc']/1000;
 		  $EncString = $PolyEnc->GMapCirlce($params['lat'], $params['long'], $convertAcc);
 		  $encodePath= "&path=fillcolor:0xE85F0E33%7Ccolor:0x91A93A00%7Cenc:".$EncString;*/
		  ?>
	<div style = 'width: 600px'>
		<div style = 'border-left-style: solid; border-left-color:#CCCCCC; border-left-width:30px;
					  border-right-style: solid; border-right-color:#CCCCCC; border-right-width:30px;
					  border-bottom-style: solid; border-bottom-color:#CCCCCC; border-bottom-width:2px;
					  border-top-style: solid; border-top-color:#CCCCCC; border-top-width:2px;'>
			<div style = 'margin-bottom: 20px; margin-top:10px'>
				<h1 style = 'padding-bottom: 20px; margin: 0 20px 0 20px ; border-bottom: 1px solid #cccccc; text-align:center; font-weight : bold; color : black !important; font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;'>Your battery is really low now, therefore we located your device with our Last Flare feature.</h1>
			</div>
			<div style = 'color:black !important; margin-bottom:10px; text-align: center; padding: 0 20px 0 20px; '>This is one time message to tell you about Last Flare, which give you the best possible chance to find your tablet or phone. This feature automatically locates it when the battery level is in danger.</div>
			<div style = 'color:black !important; margin-bottom:10px; text-align:center; padding : 0 20px 0 20px;'>Here is your device location, captured by Last Flare :</div>
			<div>
				<img src = "http://maps.googleapis.com/maps/api/staticmap?center=<?php echo $params['lat'] ?>,<?php echo $params['long'] ?>&zoom=17&size=540x300&markers=color:red%7Clabel:S%7Csize:mid%7C<?php echo $params['lat']?>,<?php echo $params['long']?>&sensor=false" alt = 'Your phone location'/>
			<!--	<img src = "http://maps.googleapis.com/maps/api/staticmap?center=<?php echo $params['lat'] ?>,<?php echo $params['long'] ?>&size=540x300&markers=color:red%7Clabel:S%7Csize:mid%7C<?php echo $params['lat']?>,<?php echo $params['long']?><?php echo $encodePath ?>&sensor=false" alt = 'Your phone location'/>-->
			</div>
			<div style ='padding:10px 30px 0 30px;'>
				<div style = 'float:left'>
					<div style = 'font-weight:bold; color:black !important'>Phone information:</div>
					<div>&nbsp;</div>
					<div><div style = 'color:blue'>Phone name:</div> 
						 <div style = 'color:black !important'><?php echo $params['phoneName']?></div>
					</div>
					<div>&nbsp;</div>
					<div><div style ='color:blue'>Latitude: </div>
						 <div><?php echo $params['lat']?></div>
					</div>
					<div>&nbsp;</div>
					<div><div style ='color:blue'>Longitude:</div>
						 <div><?php echo $params['long']?></div>
					</div>
					<div>&nbsp;</div>
					<div><div style ='color:blue'>Accuracy:</div>
						 <div><?php echo $params['acc']?> meters</div>
					</div>
					<div>&nbsp;</div>
					<div><div style ='color:blue'>Battery:</div>
						 <div><?php echo $params['bat']?></div>
					</div>
				</div>
				<div style = 'float:left; padding-left:30px; color:black !important'>
					<div style = 'font-weight:bold'>Date send:</div>
					<div>&nbsp;</div>
					<div>
						<div><?php echo $time ?></div> 
						<div><?php echo $date?></div>
					</div>
				</div>
				<div style = 'clear:both; display:block !important'>&nbsp;</div>
			</div>
		</div>
		<div style ='text-align:center; margin-top:10px;'>
			<div style = 'color: black !important'>
				Copyright &copy;2013, Innova Technology Pte Ltd. 80 Anson Road Fuji Xerox Towers Singapore
			</div>
			<div>
				<ul style = 'list-style-type: none !important; padding : 0'>
					<li style = 'margin: 0; display:inline-block'><a style = 'text-decoration: none !important' href = 'http://www.theprotag.com/#!contact-us/c23tz'>Contact us</a></li>
					<li style = 'display:inline-block'><a style = 'text-decoration: none !important' href = 'http://www.theprotag.com/#!privacy/c23ro'>Privacy</a></li>
				</ul>
			</div>
		</div>
		<div style = 'color:black !important'>
			<?php 
				$currentDate = date('F j, Y');
				$currentTime = date('g:i a'); 
			?>

			<div><?php echo $currentDate; ?></div>
			<div><?php echo $currentTime; ?></div>
	        <div>Singapore(GMT+7)</div>
	    </div>
	</div>
</body>
</html>