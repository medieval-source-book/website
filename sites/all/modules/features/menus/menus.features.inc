<?php
/**
 * @file
 * menus.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function menus_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
