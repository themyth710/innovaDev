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
	  
	  	// Add header meta tag for IE to head
	  	drupal_add_html_head($meta_ie_render_engine, 'meta_ie_render_engine');
	}
?>