<?php
/**
 * @file
 * gms_text.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function gms_text_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_texts:texts-table.
  $menu_links['main-menu_texts:texts-table'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'texts-table',
    'router_path' => 'texts-table',
    'link_title' => 'Texts',
    'options' => array(
      'identifier' => 'main-menu_texts:texts-table',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Texts');

  return $menu_links;
}
