<?php

/**
 * @file
 * Implimentation of a Page Layout Plugin for MAYO.
 *
 * @see three_col_grail.inc for detailed documentation.
 */
function one_col_vert() {
  $page_layout['one_col_vert'] = array(
    'title'    => t('One Column Vertical Sidebars'),
    'method'   => 'one_col_vert',
    'type'     => 'page_layout',
    'device_groups' => array(
      'tablet_portrait',
      'smalltouch_landscape',
     ),
  );

  return $page_layout;
}

/**
 * CSS Builder for the one_col_vert layout.
 * Displays sidebars vertically side by side beneath the main content column.
 *
 * @param $sidebar_first, an arbitary numeric value.
 * @param $sidebar_second, an arbitary numeric value.
 * @param $sidebar_unit, a value unit, one of px, em or %.
 */
function one_col_vert_layout($sidebar_first, $sidebar_second, $sidebar_unit) {

  $one_sidebar    = $sidebar_first + $sidebar_second . $sidebar_unit;
  $sidebar_first  = $sidebar_first . $sidebar_unit;
  $sidebar_second = $sidebar_second . $sidebar_unit;

  $styles = <<<EOF
.two-sidebars #content,.one-sidebar #content,#sidebar-first,#sidebar-second {margin-left: 0; margin-right: 0}
#sidebar-first {width: $sidebar_first}
.one-sidebar #sidebar-first {width: 100%;}
#sidebar-second {width: $sidebar_second}
#sidebar-first,#sidebar-second {overflow: hidden; margin-top: 20px; float: left; clear: none}
#sidebar-first .section {margin-right: 5px; margin-left: 0;}
.one-sidebar #sidebar-first .section {margin-right: 0; margin-left: 0;}
#sidebar-second .section {margin-right: 0; margin-left: 5px;}
#top-columns .column-block-wrapper {width: 100% !important; margin-top: 1em;}
#top-columns .column-block-wrapper .column-block {height: auto ; margin: 0 !important;}
#bottom-columns .column-block-wrapper {width: 100% !important; margin-top: 1em;}
#bottom-columns .column-block-wrapper .column-block {height: auto ; margin: 0 !important;}
#footer-columns .column-block-wrapper {width: 100% !important; margin-top: 1em;}
#footer-columns .column-block-wrapper .column-block {height: auto ; margin: 0 !important;}
EOF;

  return $styles;
}
