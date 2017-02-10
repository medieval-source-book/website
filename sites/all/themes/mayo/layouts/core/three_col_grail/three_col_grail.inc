<?php

/**
 * @file
 * Implimentation of a Page Layout Plugin.
 *
 * Usage:
 * The naming convetion here is very important, the function name must match the
 * method name and the array key. Do not add anything else to it. In the layout
 * function simply append "_layout", this gets called when the user submits the
 * theme settings form.
 *
 */
function three_col_grail() {                     // - function name must be identical to the method and the array key.
  $page_layout['three_col_grail'] = array(       // - array key.
    'title'     => t('Three Column Holy Grail'), // - title, needed for the UI.
    'method'    => 'three_col_grail',            // - method, this must match the function name and the key, definitly not optional!
    'type'      => 'page_layout',                // - type, tell the system this is a page_layout, not optional!
    'admin css' => 'three_col_grail.admin.css',  // - admin css, optional.
    'device_groups' => array(                    // - device_groups, define which device groups this layout can work with, can be one or more of:
      'bigscreen',                               //   'bigscreen', 'tablet_landscape', 'tablet_portrait', 'smalltouch_landscape'
      'tablet_landscape',                        //   What you enter here will dictate the device groups it shows for in theme settings.
     ),
  );

  return $page_layout;
}

/**
 * CSS Builder for the three_col_grail layout.
 * This does not have to be anything like this, but it must return a string of
 * CSS, thats about it, and only has 3 bits of data to work with that come
 * from the theme settings (what the user entered in the UI), of course you can
 * just make up your own data if that works for  your layout, see the
 * one_col_stack for such an implimentation.
 *
 * Remember, if you are building a sub-theme you have full control over the
 * theme settings form via your sub-themes hook_form_system_theme_settings_alter()
 * in theme-settings.php
 *
 * @param $sidebar_first, an arbitary numeric value.
 * @param $sidebar_second, an arbitary numeric value.
 * @param $sidebar_unit, a value unit, one of px, em or %.

 */
function three_col_grail_layout($sidebar_first, $sidebar_second, $sidebar_unit) {

  // Set variables for language direction. In thoery a layout plugin could
  // be RTL compatible.
  $left = 'left';
  $right = 'right';

  // Set vars for your sidebars, this can be very different, and entirely
  // depends on your layout.
  $sidebar_second = $sidebar_second . $sidebar_unit;
  $sidebar_first  = $sidebar_first . $sidebar_unit;

  // Define margins/negative margins if required, AT is a content source
  // ordered layout and uses a negative margin layout system.
  $push_right = $sidebar_second;
  $push_left  = $sidebar_first;
  $pull_right = $sidebar_second;

  $styles = <<<EOF
.two-sidebars #content .section {margin-$left: $push_left; margin-$right: $push_right}
.one-sidebar #content .section {margin-$left: $push_left;}
.sidebar-second #content .section {margin-$left: 0; margin-$right: $pull_right;}
#sidebar-first .section {margin-left: 0; margin-right: 10px;}
#sidebar-second .section {margin-right: 0; margin-left: 10px;}
#sidebar-first {width: $sidebar_first; margin-$left: -100%}
#sidebar-second {width: $sidebar_second; margin-$left: -$pull_right}
EOF;

  return $styles;
}
