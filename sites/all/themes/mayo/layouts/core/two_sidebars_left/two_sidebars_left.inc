<?php

/**
 * @file
 * Implimentation of a Page Layout Plugin for MAYO.
 *
 * @see three_col_grail.inc for detailed documentation.
 */
function two_sidebars_left() {
  $page_layout['two_sidebars_left'] = array(
    'title'    => t('Two Sidebars Left'),
    'method'   => 'two_sidebars_left',
    'type'     => 'page_layout',
    'device_groups' => array(
      'bigscreen',
      'tablet_landscape',
     ),
  );

  return $page_layout;
}

/**
 * CSS Builder for the two_sidebars_left layout.
 * Positions both sidebars to the left of the main content column.
 *
 * @param $sidebar_first, an arbitary numeric value.
 * @param $sidebar_second, an arbitary numeric value.
 * @param $sidebar_unit, a value unit, one of px, em or %.
 */
function two_sidebars_left_layout($sidebar_first, $sidebar_second, $sidebar_unit) {

  $left = 'left';
  $right = 'right';

  $content_margin = $sidebar_second + $sidebar_first . $sidebar_unit;
  $content_margin_one_sidebar = $sidebar_first . $sidebar_unit;
  $sidebar_first  = $sidebar_first . $sidebar_unit;
  $sidebar_second = $sidebar_second . $sidebar_unit;
  $left_margin    = $sidebar_first;
  $right_margin   = $sidebar_second;
  $push_right     = $sidebar_first;

  $styles = <<<EOF
.two-sidebars #content .section {margin-$left: $content_margin; margin-$right: 0}
.one-sidebar #content .section {margin-$left: $content_margin_one_sidebar; margin-$right: 0}
#sidebar-first .section {margin-left: 0; margin-right: 10px;}
#sidebar-second .section {margin-left: 0; margin-right: 10px;}
#sidebar-first {width: $sidebar_first; margin-$left: -100%}
#sidebar-second {width: $sidebar_second; margin-$left: -100%}
.two-sidebars #sidebar-second {width: $sidebar_second; position: relative; $left: $push_right}
EOF;

  return $styles;
}
