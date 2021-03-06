<?php
	/*======================================
	*	The preprocess function to add element to the page 
	======================================*/
	function INNOVA_THEME_preprocess_page(&$variables,$hook) {
		
		if (drupal_get_path_alias() == 'login'){
			drupal_add_js("http://code.jquery.com/jquery-2.0.3.min.js");
			drupal_add_js("//netdna.bootstrapcdn.com/bootstrap/3.0.1/js/bootstrap.min.js");
			drupal_add_css(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/css/login/login.css');
			drupal_add_js(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/js/login/jquery.formvalidate.min.js');
			drupal_add_js(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/js/login/login.js');
			$variables['theme_hook_suggestions'][] = 'page__login';
		}

		if (drupal_get_path_alias() == 'login2'){
			drupal_add_js("//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js");
			drupal_add_js('/development/misc/drupal.js');
			drupal_add_js("//netdna.bootstrapcdn.com/bootstrap/3.0.3/js/bootstrap.min.js", array('scope' => 'footer'));
			drupal_add_js("//ajax.aspnetcdn.com/ajax/jquery.validate/1.11.1/jquery.validate.min.js", array('scope' => 'footer'));
			drupal_add_js(drupal_get_path('module', 'Tracking') . '/web_front/javascript/_script/login/login.js', array('scope' => 'footer'));

			drupal_add_css(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/active/style/desktop/login/login.css');
			drupal_add_css(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/active/style/style.css');
			drupal_add_css("//netdna.bootstrapcdn.com/bootstrap/3.0.3/css/bootstrap.min.css", array('type' => 'external'));

			$variables['theme_hook_suggestions'][] = 'page__login2';
		}

		if (drupal_get_path_alias() == 'tracking2'){
			drupal_add_js("//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js");
			drupal_add_js('/development/misc/drupal.js');
			drupal_add_js("//netdna.bootstrapcdn.com/bootstrap/3.0.3/js/bootstrap.min.js", array('scope' => 'footer'));
			drupal_add_js(drupal_get_path('module', 'Tracking') . '/web_front/javascript/module/jquery.mCustomScrollbar.concat.min.js', array('scope' => 'footer'));
			drupal_add_js("//ajax.aspnetcdn.com/ajax/jquery.validate/1.11.1/jquery.validate.min.js", array('scope' => 'footer'));
			drupal_add_js("//ajax.googleapis.com/ajax/libs/angularjs/1.2.6/angular.min.js", array('scope' => 'footer'));
			drupal_add_js(drupal_get_path('module', 'Tracking') . '/web_front/javascript/_script/track/tracking.js', array('scope' => 'footer'));

			drupal_add_css("//netdna.bootstrapcdn.com/bootstrap/3.0.0/css/bootstrap.min.css", array('type' => 'external'));
			drupal_add_css(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/active/style/style.css');
			drupal_add_css(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/active/style/desktop/track/tracking.css');

			$variables['theme_hook_suggestions'][] = 'page__tracking2';
		}

		if(drupal_get_path_alias() == 'tracking'){
			drupal_add_js("http://code.jquery.com/jquery-2.0.3.min.js");
			drupal_add_js("//netdna.bootstrapcdn.com/bootstrap/3.0.1/js/bootstrap.min.js");
			drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/x-editable/1.5.0/bootstrap3-editable/js/bootstrap-editable.min.js");
			drupal_add_js(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/js/tracking/bootstrap-switch.min.js');
			$variables['theme_hook_suggestions'][] = 'page__tracking';
			drupal_add_css(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/css/tracking/tracking.css');
			//drupal_add_library('system', 'ui');
		}
		if(drupal_get_path_alias() == 'reset'){
			$variables['theme_hook_suggestions'][] = 'page__reset';
			drupal_add_css(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/css/login/login.css');
			drupal_add_js(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/js/login/jquery.formvalidate.min.js');
			drupal_add_js(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/js/login/login.js');
		}
		if(drupal_get_path_alias() == 'activation'){
			$variables['theme_hook_suggestions'][] = 'page__activation';
			drupal_add_css(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/css/login/login.css');
			drupal_add_js(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/js/login/jquery.formvalidate.min.js');
			drupal_add_js(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/js/login/login.js');
		}
		if(drupal_get_path_alias() == 'activated'){
			$variables['theme_hook_suggestions'][] = 'page__activated';
			drupal_add_css(drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/css/login/login.css');
		}
	}
	
	/*=========================================
	*	Remove default css to increase the load of the web page
	=========================================*/
	function INNOVA_THEME_css_alter(&$css) {
		global $user;
		if (!in_array('administrator', array_values($user->roles))) {
			unset($css[drupal_get_path('module', 'system') . '/system.base.css']);
			unset($css[drupal_get_path('module', 'system') . '/system.messages.css']);
			unset($css[drupal_get_path('module', 'system') . '/system.theme.css']);
			unset($css[drupal_get_path('module', 'system') . '/system.menus.css']);
			unset($css[drupal_get_path('module', 'comment') . '/comment.css']);
			unset($css[drupal_get_path('module', 'field') . '/theme/field.css']);
			unset($css[drupal_get_path('module', 'node') . '/node.css']);
			unset($css[drupal_get_path('module', 'search') . '/search.css']);
			unset($css[drupal_get_path('module', 'user') . '/user.css']);

			if (drupal_get_path_alias() == 'login2' || drupal_get_path_alias() == 'tracking2'){
				unset($css[drupal_get_path('theme', 'INNOVA') . 'sites/all/themes/core/css/style.css']);
			}
		}
	}

	function INNOVA_THEME_js_alter(&$js){

		if (drupal_get_path_alias() == 'login2' || drupal_get_path_alias() == 'tracking2'){
			unset($js[drupal_get_path('module', 'jquery_update') . '/replace/jquery/1.5/jquery.min.js']);
			unset($js['misc/drupal.js']);
			unset($js['misc/jquery.once.js']);				
		}
	}

	/**
	 * Preprocesses the wrapping HTML.
	 *
	 * @param array &$variables
	 *   Template variables.
	 */
	function INNOVA_THEME_preprocess_html(&$vars) {
	    
	    // Setup IE meta tag to force IE rendering mode
	    $meta_ie_render_engine = array(
	    	'#type' => 'html_tag',
	    	'#tag' => 'meta',
	    	'#attributes' => array(
	      	'content' =>  'IE=EmulateIE9,chrome=1',
	      	'http-equiv' => 'X-UA-Compatible',
	    	),
	    	'#weight' => '-99999',
	 	);
		
		$html5shiv = array(
			'#tag' => 'script',
			'#attributes' => array( // Set up an array of attributes inside the tag
			    'src' => "https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js", 
			),
			'#value'  => '',
			'#prefix' => '<!--[if lte IE 9]>',
			'#suffix' => '<![endif]-->',
		);

		$respondJS = array(
			'#tag' 	      => 'script',
			'#attributes' => array( // Set up an array of attributes inside the tag
			    'src' => "https://oss.maxcdn.com/libs/respond.js/1.3.0/respond.min.js", 
			),
			'#value'  => '',
			'#prefix' => '<!--[if lte IE 9]>',
			'#suffix' => '<![endif]-->',
		);

		$viewPort = array(
			'#tag' => 'meta',
			'#attributes' => array( // Set up an array of attributes inside the tag
			    'name' => "viewport",
			    'content' => 'width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no', 
			),
		);
		
		// Add header meta tag for IE to head
		drupal_add_html_head($viewPort, 'viewPort');
		drupal_add_html_head($html5shiv, 'html5shiv');
		drupal_add_html_head($respondJS, 'respondJS'); 
	  	drupal_add_html_head($meta_ie_render_engine, 'meta_ie_render_engine');
	}

	function INNOVA_THEME_html_head_alter(&$head_elements) {
  		unset($head_elements['system_meta_generator']);
	}

	function INNOVA_THEME_status_messages($variables) {
	  	
	  	$display = $variables['display'];
	  	$output = '';

	  	$status_heading = array(
	    	'status' => t('Status message'),
	    	'error' => t('Error message'),
	    	'warning' => t('Warning message'),
	  	);
	  	
	  	foreach (drupal_get_messages($display) as $type => $messages) {
		    
		    if($type == 'status'){
		      	
			    if (count($messages) > 1) {
			      
			      $output .= " <ul>\n";
			      

			      foreach ($messages as $message) {
			     	  
			        $output .= '  <li>' . $message . "</li>\n";
			      
			      }
			      
			      $output .= " </ul>\n";
			    }
			    else {
			      $output .= $messages[0];
			    }
			}
		}

	  	return $output;
	}
?>