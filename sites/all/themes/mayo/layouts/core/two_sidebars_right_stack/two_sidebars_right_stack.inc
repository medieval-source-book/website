<?php

/**
 * @file
 * Implimentation of a Page Layout Plugin for MAYO.
 *
 * @see three_col_grail.inc for detailed documentation.
 */
function two_sidebars_right_stack() {
  $page_layout['two_sidebars_right_stack'] = array(
    'title'    => t('Two Sidebars Right'),
    'method'   => 'two_sidebars_right_stack',
    'type'     => 'page_layout',
    'device_groups' => array(
      'tablet_landscape',
      'tablet_portrait',
     ),
  );

  return $page_layout;
}

/**
 * CSS Builder for the two_sidebars_right_stack layout.
 * Both sidebars are pushed to the right, however the second sidebar wraps below
 * the main content column and is 100% width. Sometimes known as a "column drop"
 * layout, and conceptually similar to the two_sidebars_left_stack.
 *
 * @param $sidebar_first, an arbitary numeric value.
 * @param $sidebar_second, an arbitary numeric value.
 * @param $sidebar_unit, a value unit, one of px, em or %.
 */
function two_sidebars_right_stack_layout($sidebar_first, $sidebar_second, $sidebar_unit) {

  $left = 'left';
  $right = 'right';

  $sidebar_first = $sidebar_first . $sidebar_unit;
  $push_right    = $sidebar_first;

  $styles = <<<EOF
.two-sidebars #content .section {margin-$left: 0; margin-$right: $push_right}
.one-sidebar #content .section {margin-$left: 0; margin-$right: $push_right}
#sidebar-first {width: $sidebar_first; margin-$left: -$push_right; float: left; clear: none;}
#sidebar-first .section { margin-left: 10px; margin-right: 0;}
#sidebar-second .region-sidebar-second { display: table; width: 100%;border-spacing: 10px;}
#sidebar-second {width: 100%; margin-left: 0; margin-right: 0; margin-top: 20px; clear: both; overflow: hidden; display: table-row;}
#sidebar-second .block {display: table-cell;}
#sidebar-second .section { margin: 0 -10px;}
EOF;

  return $styles;
}
