<?php

/**
 * @file
 * Implimentation of a Page Layout Plugin for MAYO.
 *
 * @see three_col_grail.inc for detailed documentation.
 */
function one_col_stack() {
  $page_layout['one_col_stack'] = array(
    'title'    => t('One Column Stacked'),
    'method'   => 'one_col_stack',
    'type'     => 'page_layout',
    'device_groups' => array(
      'tablet_portrait',
      'smalltouch_landscape',
     ),
  );

  return $page_layout;
}

/**
 * CSS Builder for the one_col_stack layout.
 * Note: this is the only layout for smalltouch portrait, and for mobile first.
 * All columns and regions are 100% width, stacked.
 *
 * @param $sidebar_first, an arbitary numeric value.
 * @param $sidebar_second, an arbitary numeric value.
 * @param $sidebar_unit, a value unit, one of px, em or %.
 */
function one_col_stack_layout($sidebar_first, $sidebar_second, $sidebar_unit) {
  $styles = <<<EOF
#sidebar-first,#sidebar-second {float:none;clear:both;display:block;width:100%;margin-left:0;margin-right:0}
#top-columns .column-block-wrapper {width: 100% !important; margin-top: 1em;}
#top-columns .column-block-wrapper .column-block {height: auto ; margin: 0 !important;}
#bottom-columns .column-block-wrapper {width: 100% !important; margin-top: 1em;}
#bottom-columns .column-block-wrapper .column-block {height: auto ; margin: 0 !important;}
#footer-columns .column-block-wrapper {width: 100% !important; margin-top: 1em;}
#footer-columns .column-block-wrapper .column-block {height: auto ; margin: 0 !important;}
EOF;

  return $styles;
}
