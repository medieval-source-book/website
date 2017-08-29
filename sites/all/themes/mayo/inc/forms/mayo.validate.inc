<?php

/**
 * @file
 * Validatation for some of the theme settings.
 *
 * @param $form
 * @param $form_state
 */
function mayo_settings_validate($form, &$form_state) {
  $values = $form_state['values'];
  $theme_name = $form_state['build_info']['args'][0];

  // Validate our form #state required fields, #states are UI only.
  // Bigscreen
  if (empty($values['bigscreen_sidebar_first'])) {
    form_set_error('bigscreen_sidebar_first', t('Standard Layout <em>First sidebar</em> width is empty - you must enter a value.'));
  }
  if (empty($values['bigscreen_sidebar_second'])) {
    form_set_error('bigscreen_sidebar_second', t('Standard Layout <em>Second sidebar</em> width is empty - you must enter a value.'));
  }

  // Tablet
  if (empty($values['tablet_landscape_sidebar_first'])) {
    form_set_error('tablet_landscape_sidebar_first', t('Tablet Landscape <em>First sidebar</em> width is empty - you must enter a value.'));
  }
  if ($values['tablet_landscape_layout'] === 'three_col_grail' || $values['tablet_landscape_layout'] === 'two_sidebars_left' || $values['tablet_landscape_layout'] === 'two_sidebars_right') {
    if (empty($values['tablet_landscape_sidebar_second'])) {
      form_set_error('tablet_landscape_sidebar_second', t('Tablet Landscape <em>First sidebar</em> width is empty - you must enter a value. The layout you selected requires values for both sidebars.'));
    }
  }

  // Smalltouch
  if ($values['smalltouch_landscape_layout'] === 'one_col_vert') {
    if (empty($values['smalltouch_landscape_sidebar_first'])) {
      form_set_error('smalltouch_landscape_sidebar_first', t('Smalltouch First Sidebar width is empty - enter a value or choose another layout.'));
    }
    if (empty($values['smalltouch_landscape_sidebar_second'])) {
      form_set_error('smalltouch_landscape_sidebar_second', t('Smalltouch Second Sidebar width is empty - enter a value or choose another layout.'));
    }
  }
}
