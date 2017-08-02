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
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Remove filters';
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
  /* Field: Content: Icon */
  $handler->display->display_options['fields']['field_icon']['id'] = 'field_icon';
  $handler->display->display_options['fields']['field_icon']['table'] = 'field_data_field_icon';
  $handler->display->display_options['fields']['field_icon']['field'] = 'field_icon';
  $handler->display->display_options['fields']['field_icon']['label'] = '';
  $handler->display->display_options['fields']['field_icon']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_icon']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_icon']['settings'] = array(
    'image_style' => 'cropped_rectangle',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Original Language Title */
  $handler->display->display_options['fields']['field_original_language_title']['id'] = 'field_original_language_title';
  $handler->display->display_options['fields']['field_original_language_title']['table'] = 'field_data_field_original_language_title';
  $handler->display->display_options['fields']['field_original_language_title']['field'] = 'field_original_language_title';
  $handler->display->display_options['fields']['field_original_language_title']['label'] = '';
  $handler->display->display_options['fields']['field_original_language_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_original_language_title']['type'] = 'text_plain';
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
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Author | (field_author) */
  $handler->display->display_options['filters']['field_author_tid']['id'] = 'field_author_tid';
  $handler->display->display_options['filters']['field_author_tid']['table'] = 'field_data_field_author';
  $handler->display->display_options['filters']['field_author_tid']['field'] = 'field_author_tid';
  $handler->display->display_options['filters']['field_author_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_author_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_author_tid']['expose']['operator_id'] = 'field_author_tid_op';
  $handler->display->display_options['filters']['field_author_tid']['expose']['label'] = 'Filter by Author';
  $handler->display->display_options['filters']['field_author_tid']['expose']['operator'] = 'field_author_tid_op';
  $handler->display->display_options['filters']['field_author_tid']['expose']['identifier'] = 'field_author_tid';
  $handler->display->display_options['filters']['field_author_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_author_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_author_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_author_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_author_tid']['vocabulary'] = 'author';
  $handler->display->display_options['filters']['field_author_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Language | (field_language) */
  $handler->display->display_options['filters']['field_language_tid']['id'] = 'field_language_tid';
  $handler->display->display_options['filters']['field_language_tid']['table'] = 'field_data_field_language';
  $handler->display->display_options['filters']['field_language_tid']['field'] = 'field_language_tid';
  $handler->display->display_options['filters']['field_language_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_language_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_language_tid']['expose']['operator_id'] = 'field_language_tid_op';
  $handler->display->display_options['filters']['field_language_tid']['expose']['label'] = 'Filter by Language';
  $handler->display->display_options['filters']['field_language_tid']['expose']['operator'] = 'field_language_tid_op';
  $handler->display->display_options['filters']['field_language_tid']['expose']['identifier'] = 'field_language_tid';
  $handler->display->display_options['filters']['field_language_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_language_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_language_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_language_tid']['vocabulary'] = 'language';
  $handler->display->display_options['filters']['field_language_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Period | (field_period) */
  $handler->display->display_options['filters']['field_period_tid']['id'] = 'field_period_tid';
  $handler->display->display_options['filters']['field_period_tid']['table'] = 'field_data_field_period';
  $handler->display->display_options['filters']['field_period_tid']['field'] = 'field_period_tid';
  $handler->display->display_options['filters']['field_period_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_period_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_period_tid']['expose']['operator_id'] = 'field_period_tid_op';
  $handler->display->display_options['filters']['field_period_tid']['expose']['label'] = 'Filter by Period';
  $handler->display->display_options['filters']['field_period_tid']['expose']['operator'] = 'field_period_tid_op';
  $handler->display->display_options['filters']['field_period_tid']['expose']['identifier'] = 'field_period_tid';
  $handler->display->display_options['filters']['field_period_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_period_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_period_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_period_tid']['vocabulary'] = 'period';
  $handler->display->display_options['filters']['field_period_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Keywords | (field_keywords) */
  $handler->display->display_options['filters']['field_keywords_tid']['id'] = 'field_keywords_tid';
  $handler->display->display_options['filters']['field_keywords_tid']['table'] = 'field_data_field_keywords';
  $handler->display->display_options['filters']['field_keywords_tid']['field'] = 'field_keywords_tid';
  $handler->display->display_options['filters']['field_keywords_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_keywords_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['operator_id'] = 'field_keywords_tid_op';
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['label'] = 'Filter by Keywords';
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['operator'] = 'field_keywords_tid_op';
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['identifier'] = 'field_keywords_tid';
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_keywords_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_keywords_tid']['vocabulary'] = 'keywords';
  $handler->display->display_options['filters']['field_keywords_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Genre | (field_genre) */
  $handler->display->display_options['filters']['field_genre_tid']['id'] = 'field_genre_tid';
  $handler->display->display_options['filters']['field_genre_tid']['table'] = 'field_data_field_genre';
  $handler->display->display_options['filters']['field_genre_tid']['field'] = 'field_genre_tid';
  $handler->display->display_options['filters']['field_genre_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_genre_tid']['expose']['operator_id'] = 'field_genre_tid_op';
  $handler->display->display_options['filters']['field_genre_tid']['expose']['label'] = 'Filter by Genre';
  $handler->display->display_options['filters']['field_genre_tid']['expose']['operator'] = 'field_genre_tid_op';
  $handler->display->display_options['filters']['field_genre_tid']['expose']['identifier'] = 'field_genre_tid';
  $handler->display->display_options['filters']['field_genre_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_genre_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_genre_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_genre_tid']['vocabulary'] = 'genre';
  $handler->display->display_options['filters']['field_genre_tid']['error_message'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['path'] = 'texts';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Browse Texts';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['texts'] = $view;

  $view = new view();
  $view->name = 'texts_table';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Texts: Table View';
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
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_author' => 'field_author',
    'field_year' => 'field_year',
    'field_language' => 'field_language',
    'field_genre' => 'field_genre',
    'field_keywords' => 'field_keywords',
  );
  $handler->display->display_options['style_options']['default'] = 'title';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_author' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_year' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_language' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_genre' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_keywords' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Author | */
  $handler->display->display_options['fields']['field_author']['id'] = 'field_author';
  $handler->display->display_options['fields']['field_author']['table'] = 'field_data_field_author';
  $handler->display->display_options['fields']['field_author']['field'] = 'field_author';
  $handler->display->display_options['fields']['field_author']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_author']['delta_offset'] = '0';
  /* Field: Content: Year */
  $handler->display->display_options['fields']['field_year']['id'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year']['field'] = 'field_year';
  /* Field: Content: Period | */
  $handler->display->display_options['fields']['field_period']['id'] = 'field_period';
  $handler->display->display_options['fields']['field_period']['table'] = 'field_data_field_period';
  $handler->display->display_options['fields']['field_period']['field'] = 'field_period';
  $handler->display->display_options['fields']['field_period']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_period']['delta_offset'] = '0';
  /* Field: Content: Language | */
  $handler->display->display_options['fields']['field_language']['id'] = 'field_language';
  $handler->display->display_options['fields']['field_language']['table'] = 'field_data_field_language';
  $handler->display->display_options['fields']['field_language']['field'] = 'field_language';
  $handler->display->display_options['fields']['field_language']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_language']['delta_offset'] = '0';
  /* Field: Content: Genre | */
  $handler->display->display_options['fields']['field_genre']['id'] = 'field_genre';
  $handler->display->display_options['fields']['field_genre']['table'] = 'field_data_field_genre';
  $handler->display->display_options['fields']['field_genre']['field'] = 'field_genre';
  $handler->display->display_options['fields']['field_genre']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_genre']['delta_offset'] = '0';
  /* Field: Content: Keywords | */
  $handler->display->display_options['fields']['field_keywords']['id'] = 'field_keywords';
  $handler->display->display_options['fields']['field_keywords']['table'] = 'field_data_field_keywords';
  $handler->display->display_options['fields']['field_keywords']['field'] = 'field_keywords';
  $handler->display->display_options['fields']['field_keywords']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_keywords']['delta_offset'] = '0';
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
  /* Filter criterion: Content: Author | (field_author) */
  $handler->display->display_options['filters']['field_author_tid']['id'] = 'field_author_tid';
  $handler->display->display_options['filters']['field_author_tid']['table'] = 'field_data_field_author';
  $handler->display->display_options['filters']['field_author_tid']['field'] = 'field_author_tid';
  $handler->display->display_options['filters']['field_author_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_author_tid']['expose']['operator_id'] = 'field_author_tid_op';
  $handler->display->display_options['filters']['field_author_tid']['expose']['label'] = 'Author';
  $handler->display->display_options['filters']['field_author_tid']['expose']['operator'] = 'field_author_tid_op';
  $handler->display->display_options['filters']['field_author_tid']['expose']['identifier'] = 'field_author_tid';
  $handler->display->display_options['filters']['field_author_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_author_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_author_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_author_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_author_tid']['vocabulary'] = 'author';
  $handler->display->display_options['filters']['field_author_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Keywords | (field_keywords) */
  $handler->display->display_options['filters']['field_keywords_tid']['id'] = 'field_keywords_tid';
  $handler->display->display_options['filters']['field_keywords_tid']['table'] = 'field_data_field_keywords';
  $handler->display->display_options['filters']['field_keywords_tid']['field'] = 'field_keywords_tid';
  $handler->display->display_options['filters']['field_keywords_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['operator_id'] = 'field_keywords_tid_op';
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['label'] = 'Keywords';
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['operator'] = 'field_keywords_tid_op';
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['identifier'] = 'field_keywords_tid';
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_keywords_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_keywords_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_keywords_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_keywords_tid']['vocabulary'] = 'keywords';
  $handler->display->display_options['filters']['field_keywords_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Language | (field_language) */
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
    4 => 0,
  );
  $handler->display->display_options['filters']['field_language_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_language_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_language_tid']['vocabulary'] = 'language';
  $handler->display->display_options['filters']['field_language_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Period | (field_period) */
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
    4 => 0,
  );
  $handler->display->display_options['filters']['field_period_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_period_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_period_tid']['vocabulary'] = 'period';
  $handler->display->display_options['filters']['field_period_tid']['error_message'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'texts-table';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Texts';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['texts_table'] = $view;

  return $export;
}
