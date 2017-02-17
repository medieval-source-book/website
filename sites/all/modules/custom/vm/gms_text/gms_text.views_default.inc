<?php
/**
 * @file
 * gms_text.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gms_text_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'texts';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Texts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Texts';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '9';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = '3';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'cropped_rectangle',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_image']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_image']['delta_offset'] = '0';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'text' => 'text',
  );
  /* Filter criterion: Content: Language (field_language) */
  $handler->display->display_options['filters']['field_language_tid']['id'] = 'field_language_tid';
  $handler->display->display_options['filters']['field_language_tid']['table'] = 'field_data_field_language';
  $handler->display->display_options['filters']['field_language_tid']['field'] = 'field_language_tid';
  $handler->display->display_options['filters']['field_language_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_language_tid']['expose']['operator_id'] = 'field_language_tid_op';
  $handler->display->display_options['filters']['field_language_tid']['expose']['label'] = 'Language';
  $handler->display->display_options['filters']['field_language_tid']['expose']['operator'] = 'field_language_tid_op';
  $handler->display->display_options['filters']['field_language_tid']['expose']['identifier'] = 'field_language_tid';
  $handler->display->display_options['filters']['field_language_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_language_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_language_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_language_tid']['vocabulary'] = 'language';
  $handler->display->display_options['filters']['field_language_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Period (field_period) */
  $handler->display->display_options['filters']['field_period_tid']['id'] = 'field_period_tid';
  $handler->display->display_options['filters']['field_period_tid']['table'] = 'field_data_field_period';
  $handler->display->display_options['filters']['field_period_tid']['field'] = 'field_period_tid';
  $handler->display->display_options['filters']['field_period_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_period_tid']['expose']['operator_id'] = 'field_period_tid_op';
  $handler->display->display_options['filters']['field_period_tid']['expose']['label'] = 'Period';
  $handler->display->display_options['filters']['field_period_tid']['expose']['operator'] = 'field_period_tid_op';
  $handler->display->display_options['filters']['field_period_tid']['expose']['identifier'] = 'field_period_tid';
  $handler->display->display_options['filters']['field_period_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_period_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_period_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_period_tid']['vocabulary'] = 'period';
  $handler->display->display_options['filters']['field_period_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Genre (field_genre) */
  $handler->display->display_options['filters']['field_genre_tid']['id'] = 'field_genre_tid';
  $handler->display->display_options['filters']['field_genre_tid']['table'] = 'field_data_field_genre';
  $handler->display->display_options['filters']['field_genre_tid']['field'] = 'field_genre_tid';
  $handler->display->display_options['filters']['field_genre_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_genre_tid']['expose']['operator_id'] = 'field_genre_tid_op';
  $handler->display->display_options['filters']['field_genre_tid']['expose']['label'] = 'Genre';
  $handler->display->display_options['filters']['field_genre_tid']['expose']['operator'] = 'field_genre_tid_op';
  $handler->display->display_options['filters']['field_genre_tid']['expose']['identifier'] = 'field_genre_tid';
  $handler->display->display_options['filters']['field_genre_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_genre_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_genre_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_genre_tid']['vocabulary'] = 'genre';
  $handler->display->display_options['filters']['field_genre_tid']['error_message'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'texts';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Browse Texts';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['texts'] = $view;

  return $export;
}
