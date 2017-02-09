<?php
/**
 * @file
 * Contains functions to alter Drupal's markup for the Zen theme.
 *
 * IMPORTANT WARNING: DO NOT MODIFY THIS FILE.
 *
 * The base Zen theme is designed to be easily extended by its sub-themes. You
 * shouldn't modify this or any of the CSS or PHP files in the root zen/ folder.
 * See the online documentation for more information:
 *   https://drupal.org/documentation/theme/zen
 */

// Auto-rebuild the theme registry during theme development.
if (theme_get_setting('zen_rebuild_registry') && !defined('MAINTENANCE_MODE')) {
  // Rebuild .info data.
  system_rebuild_theme_data();
  // Rebuild theme registry.
  drupal_theme_rebuild();
  // Turn on template debugging.
  $GLOBALS['conf']['theme_debug'] = TRUE;
}


/**
 * Implements HOOK_theme().
 */
function zen_theme(&$existing, $type, $theme, $path) {
  include_once './' . drupal_get_path('theme', 'zen') . '/zen-internals/template.theme-registry.inc';
  return _zen_theme($existing, $type, $theme, $path);
}

/**
 * Override or insert variables for the breadcrumb theme function.
 *
 * @param $variables
 *   An array of variables to pass to the theme function.
 * @param $hook
 *   The name of the theme hook being called ("breadcrumb" in this case).
 *
 * @see zen_breadcrumb()
 */
function zen_preprocess_breadcrumb(&$variables, $hook) {
  // Define variables for the breadcrumb-related theme settings. This is done
  // here so that sub-themes can dynamically change the settings under
  // particular conditions in a preprocess function of their own.
  $variables['display_breadcrumb'] = check_plain(theme_get_setting('zen_breadcrumb'));
  $variables['display_breadcrumb'] = ($variables['display_breadcrumb'] == 'yes' || $variables['display_breadcrumb'] == 'admin' && arg(0) == 'admin') ? TRUE : FALSE;
  $variables['breadcrumb_separator'] = filter_xss_admin(theme_get_setting('zen_breadcrumb_separator'));
  $variables['display_trailing_separator'] = theme_get_setting('zen_breadcrumb_trailing') ? TRUE : FALSE;

  // Optionally get rid of the homepage link.
  if (!theme_get_setting('zen_breadcrumb_home')) {
    array_shift($variables['breadcrumb']);
  }

  // Add the title of the page to the end of the breadcrumb list.
  if (theme_get_setting('zen_breadcrumb_title')) {
    $item = menu_get_item();
    if (!empty($item['tab_parent'])) {
      // If we are on a non-default tab, use the tab's title.
      $variables['breadcrumb'][] = check_plain($item['title']);
    }
    else {
      $variables['breadcrumb'][] = drupal_get_title();
    }
    // Turn off the trailing separator.
    $variables['display_trailing_separator'] = FALSE;
  }

  // Provide a navigational heading to give context for breadcrumb links to
  // screen-reader users.
  if (empty($variables['title'])) {
    $variables['title'] = t('You are here');
  }
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $variables
 *   - title: An optional string to be used as a navigational heading to give
 *     context for breadcrumb links to screen-reader users.
 *   - title_attributes_array: Array of HTML attributes for the title. It is
 *     flattened into a string within the theme function.
 *   - breadcrumb: An array containing the breadcrumb links.
 *   - display_breadcrumb: A boolean indicating whether the breadcrumbs should
 *     be displayed.
 *   - breadcrumb_separator: A string representing the text to be used as the
 *     breadcrumb separator.
 *   - display_trailing_separator: A boolean indicating whether a trailing
 *     seperator should be added at the end of the breadcrumbs.
 *
 * @return
 *   A string containing the breadcrumb output.
 */
function zen_breadcrumb($variables) {
  $output = '';

  // Determine if we are to display the breadcrumb.
  if ($variables['display_breadcrumb'] && !empty($variables['breadcrumb'])) {
    $variables['title_attributes_array']['class'][] = 'breadcrumb__title';
    $separator = '<span class="breadcrumb__separator">' . $variables['breadcrumb_separator'] . '</span>';
    // Build the breadcrumb trail.
    $output = '<nav class="breadcrumb" role="navigation">';
    $output .= '<h2' . drupal_attributes($variables['title_attributes_array']) . '>' . $variables['title'] . '</h2>';
    $output .= '<ol class="breadcrumb__list"><li class="breadcrumb__item">';
    $output .= implode($separator . '</li><li class="breadcrumb__item">', $variables['breadcrumb']);
    if ($variables['display_trailing_separator']) {
      $output .= $separator;
    }
    $output .= '</li></ol></nav>';
  }

  return $output;
}

/**
 * Override or insert variables into the html template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered. This is usually "html", but can
 *   also be "maintenance_page" since zen_preprocess_maintenance_page() calls
 *   this function to have consistent variables.
 */
function zen_preprocess_html(&$variables, $hook) {
  // Add variables and paths needed for HTML5 and responsive support.
  $variables['base_path'] = base_path();
  $variables['path_to_zen'] = drupal_get_path('theme', 'zen');
  // Get settings for HTML5 and responsive support. array_filter() removes
  // items from the array that have been disabled.
  $meta = array_filter((array) theme_get_setting('zen_meta'));
  $variables['add_html5_shim']          = in_array('html5', $meta);
  $variables['default_mobile_metatags'] = in_array('meta', $meta);

  // If the user is silly and enables Zen as the theme, add some styles.
  if ($GLOBALS['theme'] == 'zen') {
    include_once './' . $variables['path_to_zen'] . '/zen-internals/template.zen.inc';
    _zen_preprocess_html($variables, $hook);
  }

  // Attributes for html element.
  $variables['html_attributes_array'] = array(
    'lang' => $variables['language']->language,
    'dir' => $variables['language']->dir,
  );

  // Send X-UA-Compatible HTTP header to force IE to use the most recent
  // rendering engine.
  // This also prevents the IE compatibility mode button to appear when using
  // conditional classes on the html tag.
  if (is_null(drupal_get_http_header('X-UA-Compatible'))) {
    drupal_add_http_header('X-UA-Compatible', 'IE=edge');
  }

  $variables['skip_link_anchor'] = check_plain(theme_get_setting('zen_skip_link_anchor'));
  $variables['skip_link_text']   = check_plain(theme_get_setting('zen_skip_link_text'));

  // Return early, so the maintenance page does not call any of the code below.
  if ($hook != 'html') {
    return;
  }

  // Serialize RDF Namespaces into an RDFa 1.1 prefix attribute.
  if ($variables['rdf_namespaces']) {
    $prefixes = array();
    foreach (explode("\n  ", ltrim($variables['rdf_namespaces'])) as $namespace) {
      // Remove xlmns: and ending quote and fix prefix formatting.
      $prefixes[] = str_replace('="', ': ', substr($namespace, 6, -1));
    }
    $variables['rdf_namespaces'] = ' prefix="' . implode(' ', $prefixes) . '"';
  }

  // Classes for body element. Allows advanced theming based on context
  // (home page, node of certain type, etc.)
  if (!$variables['is_front']) {
    // Add unique class for each page.
    $path = drupal_get_path_alias($_GET['q']);
    // Add unique class for each website section.
    list($section, ) = explode('/', $path, 2);
    $arg = explode('/', $_GET['q']);
    if ($arg[0] == 'node' && isset($arg[1])) {
      if ($arg[1] == 'add') {
        $section = 'node-add';
      }
      elseif (isset($arg[2]) && is_numeric($arg[1]) && ($arg[2] == 'edit' || $arg[2] == 'delete')) {
        $section = 'node-' . $arg[2];
      }
    }
    $variables['classes_array'][] = drupal_html_class('section-' . $section);
  }

  // Store the menu item since it has some useful information.
  $variables['menu_item'] = menu_get_item();
  if ($variables['menu_item']) {
    switch ($variables['menu_item']['page_callback']) {
      case 'views_page':
        // Is this a Views page?
        $variables['classes_array'][] = 'page-views';
        break;
      case 'page_manager_blog':
      case 'page_manager_blog_user':
      case 'page_manager_contact_site':
      case 'page_manager_contact_user':
      case 'page_manager_node_add':
      case 'page_manager_node_edit':
      case 'page_manager_node_view_page':
      case 'page_manager_page_execute':
      case 'page_manager_poll':
      case 'page_manager_search_page':
      case 'page_manager_term_view_page':
      case 'page_manager_user_edit_page':
      case 'page_manager_user_view_page':
        // Is this a Panels page?
        $variables['classes_array'][] = 'page-panels';
        break;
    }
  }
}

/**
 * Override or insert variables into the html templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("html" in this case.)
 */
function zen_process_html(&$variables, $hook) {
  // Flatten out html_attributes.
  $variables['html_attributes'] = drupal_attributes($variables['html_attributes_array']);
}

/**
 * Override or insert variables in the html_tag theme function.
 */
function zen_process_html_tag(&$variables) {
  $tag = &$variables['element'];

  if ($tag['#tag'] == 'style' || $tag['#tag'] == 'script') {
    // Remove redundant CDATA comments.
    unset($tag['#value_prefix'], $tag['#value_suffix']);

    // Remove redundant type attribute.
    if (isset($tag['#attributes']['type']) && $tag['#attributes']['type'] !== 'text/ng-template') {
      unset($tag['#attributes']['type']);
    }

    // Remove media="all" but leave others unaffected.
    if (isset($tag['#attributes']['media']) && $tag['#attributes']['media'] === 'all') {
      unset($tag['#attributes']['media']);
    }
  }
}

/**
 * Implement hook_html_head_alter().
 */
function zen_html_head_alter(&$head) {
  // Simplify the meta tag for character encoding.
  if (isset($head['system_meta_content_type']['#attributes']['content'])) {
    $head['system_meta_content_type']['#attributes'] = array('charset' => str_replace('text/html; charset=', '', $head['system_meta_content_type']['#attributes']['content']));
  }
}

/**
 * Override or insert variables into the page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */
function zen_preprocess_page(&$variables, $hook) {
  // Find the title of the menu used by the secondary links.
  $secondary_links = variable_get('menu_secondary_links_source', 'user-menu');
  if ($secondary_links) {
    $menus = function_exists('menu_get_menus') ? menu_get_menus() : menu_list_system_menus();
    $variables['secondary_menu_heading'] = isset($menus[$secondary_links]) ? $menus[$secondary_links] : '';
  }
  else {
    $variables['secondary_menu_heading'] = '';
  }
}

/**
 * Override or insert variables into the maintenance page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("maintenance_page" in this case.)
 */
function zen_preprocess_maintenance_page(&$variables, $hook) {
  zen_preprocess_html($variables, $hook);
  // There's nothing maintenance-related in zen_preprocess_page(). Yet.
  //zen_preprocess_page($variables, $hook);
}

/**
 * Override or insert variables into the maintenance page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("maintenance_page" in this case.)
 */
function zen_process_maintenance_page(&$variables, $hook) {
  zen_process_html($variables, $hook);
  // Ensure default regions get a variable. Theme authors often forget to remove
  // a deleted region's variable in maintenance-page.tpl.
  foreach (array('header', 'navigation', 'highlighted', 'help', 'content', 'sidebar_first', 'sidebar_second', 'footer', 'bottom') as $region) {
    if (!isset($variables[$region])) {
      $variables[$region] = '';
    }
  }
}

/**
 * Override or insert variables into the node templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 */
function zen_preprocess_node(&$variables, $hook) {
  // Add $unpublished variable.
  $variables['unpublished'] = (!$variables['status']) ? TRUE : FALSE;

  // Set preview variable to FALSE if it doesn't exist.
  $variables['preview'] = isset($variables['preview']) ? $variables['preview'] : FALSE;

  // Add pubdate to submitted variable.
  $variables['pubdate'] = '<time pubdate datetime="' . format_date($variables['node']->created, 'custom', 'c') . '">' . $variables['date'] . '</time>';
  if ($variables['display_submitted']) {
    $variables['submitted'] = t('Submitted by !username on !datetime', array('!username' => $variables['name'], '!datetime' => $variables['pubdate']));
  }

  // If the node is unpublished, add the "unpublished" watermark class.
  if ($variables['unpublished'] || $variables['preview']) {
    $variables['classes_array'][] = 'watermark__wrapper';
  }

  // Add a class for the view mode.
  if (!$variables['teaser']) {
    $variables['classes_array'][] = 'view-mode-' . $variables['view_mode'];
  }

  // Add a class to show node is authored by current user.
  if ($variables['uid'] && $variables['uid'] == $GLOBALS['user']->uid) {
    $variables['classes_array'][] = 'node-by-viewer';
  }
}

/**
 * Override or insert variables into the comment templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("comment" in this case.)
 */
function zen_preprocess_comment(&$variables, $hook) {
  // Add $unpublished variable.
  $variables['unpublished'] = ($variables['status'] == 'comment-unpublished') ? TRUE : FALSE;

  // Add $preview variable.
  $variables['preview'] = ($variables['status'] == 'comment-preview') ? TRUE : FALSE;

  // If comment subjects are disabled, don't display them.
  if (variable_get('comment_subject_field_' . $variables['node']->type, 1) == 0) {
    $variables['title'] = '';
  }

  // Add pubdate to submitted variable.
  $variables['pubdate'] = '<time pubdate datetime="' . format_date($variables['comment']->created, 'custom', 'c') . '">' . $variables['created'] . '</time>';
  $variables['submitted'] = t('!username replied on !datetime', array('!username' => $variables['author'], '!datetime' => $variables['pubdate']));

  // If the comment is unpublished/preview, add a "unpublished" watermark class.
  if ($variables['unpublished'] || $variables['preview']) {
    $variables['classes_array'][] = 'watermark__wrapper';
  }

  // Zebra striping.
  if ($variables['id'] == 1) {
    $variables['classes_array'][] = 'first';
  }
  if ($variables['id'] == $variables['node']->comment_count) {
    $variables['classes_array'][] = 'last';
  }
  $variables['classes_array'][] = $variables['zebra'];

  // Add the comment__permalink class.
  $uri = entity_uri('comment', $variables['comment']);
  $uri_options = $uri['options'] + array('attributes' => array('class' => array('comment__permalink'), 'rel' => 'bookmark'));
  $variables['permalink'] = l(t('Permalink'), $uri['path'], $uri_options);

  // Remove core's permalink class and add the comment__title class.
  $variables['title_attributes_array']['class'][] = 'comment__title';
  $uri_options = $uri['options'] + array('attributes' => array('rel' => 'bookmark'));
  $variables['title'] = l($variables['comment']->subject, $uri['path'], $uri_options);
}

/**
 * Preprocess variables for region.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("region" in this case.)
 */
function zen_preprocess_region(&$variables, $hook) {
  // Use a template with no wrapper for the sidebar regions.
  if (strpos($variables['region'], 'sidebar_') === 0) {
    // Allow a region-specific template to override Zen's region--no-wrapper.
    array_unshift($variables['theme_hook_suggestions'], 'region__no_wrapper');
  }
  // Use a template with no wrapper for the content region.
  elseif ($variables['region'] == 'content') {
    // Allow a region-specific template to override Zen's region--no-wrapper.
    array_unshift($variables['theme_hook_suggestions'], 'region__no_wrapper');
  }
  // Add a BEM-style class for header region.
  elseif ($variables['region'] == 'header') {
    array_unshift($variables['classes_array'], 'header__region');
  }
}

/**
 * Override or insert variables into the block templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function zen_preprocess_block(&$variables, $hook) {
  // Use a template with no wrapper for the page's main content.
  if ($variables['block_html_id'] == 'block-system-main') {
    $variables['theme_hook_suggestions'][] = 'block__no_wrapper';
  }

  // Classes describing the position of the block within the region.
  if ($variables['block_id'] == 1) {
    $variables['classes_array'][] = 'first';
  }
  // The last_in_region property is set in zen_page_alter().
  if (isset($variables['block']->last_in_region)) {
    $variables['classes_array'][] = 'last';
  }
  $variables['classes_array'][] = $variables['block_zebra'];

  $variables['title_attributes_array']['class'][] = 'block__title';

  // Add Aria Roles via attributes.
  switch ($variables['block']->module) {
    case 'system':
      switch ($variables['block']->delta) {
        case 'main':
          // Note: the "main" role goes in the page.tpl, not here.
          break;
        case 'help':
        case 'powered-by':
          $variables['attributes_array']['role'] = 'complementary';
          break;
        default:
          // Any other "system" block is a menu block.
          $variables['attributes_array']['role'] = 'navigation';
          break;
      }
      break;
    case 'menu':
    case 'menu_block':
    case 'blog':
    case 'book':
    case 'comment':
    case 'forum':
    case 'shortcut':
    case 'statistics':
      $variables['attributes_array']['role'] = 'navigation';
      break;
    case 'search':
      $variables['attributes_array']['role'] = 'search';
      break;
    case 'help':
    case 'aggregator':
    case 'locale':
    case 'poll':
    case 'profile':
      $variables['attributes_array']['role'] = 'complementary';
      break;
    case 'node':
      switch ($variables['block']->delta) {
        case 'syndicate':
          $variables['attributes_array']['role'] = 'complementary';
          break;
        case 'recent':
          $variables['attributes_array']['role'] = 'navigation';
          break;
      }
      break;
    case 'user':
      switch ($variables['block']->delta) {
        case 'login':
          $variables['attributes_array']['role'] = 'form';
          break;
        case 'new':
        case 'online':
          $variables['attributes_array']['role'] = 'complementary';
          break;
      }
      break;
  }
}

/**
 * Override or insert variables into the block templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function zen_process_block(&$variables, $hook) {
  // Drupal 7 should use a $title variable instead of $block->subject.
  $variables['title'] = isset($variables['block']->subject) ? $variables['block']->subject : '';
}

/**
 * Implements hook_page_alter().
 *
 * Look for the last block in the region. This is impossible to determine from
 * within a preprocess_block function.
 *
 * @param $page
 *   Nested array of renderable elements that make up the page.
 */
function zen_page_alter(&$page) {
  // Look in each visible region for blocks.
  foreach (system_region_list($GLOBALS['theme'], REGIONS_VISIBLE) as $region => $name) {
    if (!empty($page[$region])) {
      // Find the last block in the region.
      $blocks = array_reverse(element_children($page[$region]));
      while ($blocks && !isset($page[$region][$blocks[0]]['#block'])) {
        array_shift($blocks);
      }
      if ($blocks) {
        $page[$region][$blocks[0]]['#block']->last_in_region = TRUE;
      }
    }
  }
}

/**
 * Implements hook_form_BASE_FORM_ID_alter().
 *
 * Prevent user-facing field styling from screwing up node edit forms by
 * renaming the classes on the node edit form's field wrappers.
 */
function zen_form_node_form_alter(&$form, &$form_state, $form_id) {
  // Remove if #1245218 is backported to D7 core.
  foreach (array_keys($form) as $item) {
    if (strpos($item, 'field_') === 0) {
      if (!empty($form[$item]['#attributes']['class'])) {
        foreach ($form[$item]['#attributes']['class'] as &$class) {
          // Core bug: the field-type-text-with-summary class is used as a JS hook.
          if ($class != 'field-type-text-with-summary' && strpos($class, 'field-type-') === 0 || strpos($class, 'field-name-') === 0) {
            // Make the class different from that used in theme_field().
            $class = 'form-' . $class;
          }
        }
      }
    }
  }
}

/**
 * Returns HTML for primary and secondary local tasks.
 *
 * @ingroup themeable
 */
function zen_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="visually-hidden">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="tabs">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="visually-hidden">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="tabs tabs--secondary">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}

/**
 * Returns HTML for a single local task link.
 *
 * @ingroup themeable
 */
function zen_menu_local_task($variables) {
  // Views uses hook_menu_local_task without using hook_menu_local_tasks, which breaks all the styling.
  if (isset($variables['element']['#parents'][0]) && $variables['element']['#parents'][0] === 'displays') {
    // Use core's theme hook instead.
    return theme_menu_local_task($variables);
  }
  $link = $variables['element']['#link'];
  $link_text = $link['title'];

  // Add BEM-style class names.
  $link['localized_options']['attributes']['class'][] = 'tabs__tab-link';
  $class = 'tabs__tab';

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = ' <span class="visually-hidden">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));

    $link['localized_options']['attributes']['class'][] = 'is-active';
    $class .= ' is-active';
  }

  return '<li class="' . $class . '">' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
}

/**
 * Implements hook_preprocess_menu_link().
 */
function zen_preprocess_menu_link(&$variables, $hook) {
  // Normalize menu item classes to be an array.
  if (empty($variables['element']['#attributes']['class'])) {
    $variables['element']['#attributes']['class'] = array();
  }
  $menu_item_classes =& $variables['element']['#attributes']['class'];
  if (!is_array($menu_item_classes)) {
    $menu_item_classes = array($menu_item_classes);
  }

  // Normalize menu link classes to be an array.
  if (empty($variables['element']['#localized_options']['attributes']['class'])) {
    $variables['element']['#localized_options']['attributes']['class'] = array();
  }
  $menu_link_classes =& $variables['element']['#localized_options']['attributes']['class'];
  if (!is_array($menu_link_classes)) {
    $menu_link_classes = array($menu_link_classes);
  }

  // Add BEM-style classes to the menu item classes.
  $extra_classes = array('menu__item');
  foreach ($menu_item_classes as $key => $class) {
    switch ($class) {
      // Menu module classes.
      case 'expanded':
      case 'collapsed':
      case 'leaf':
      case 'active':
      // Menu block module classes.
      case 'active-trail':
        $extra_classes[] = 'is-' . $class;
        break;
      case 'has-children':
        $extra_classes[] = 'is-parent';
        break;
    }
  }
  $menu_item_classes = array_merge($extra_classes, $menu_item_classes);

  // Add BEM-style classes to the menu link classes.
  $extra_classes = array('menu__link');
  if (empty($menu_link_classes)) {
    $menu_link_classes = array();
  }
  else {
    foreach ($menu_link_classes as $key => $class) {
      switch ($class) {
        case 'active':
        case 'active-trail':
          $extra_classes[] = 'is-' . $class;
          break;
      }
    }
  }
  $menu_link_classes = array_merge($extra_classes, $menu_link_classes);
}

/**
 * Returns HTML for status and/or error messages, grouped by type.
 */
function zen_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  // Allow a preprocess function to override the default SVG icons.
  if (!isset($variables['icon'])) {
    $variables['icon'] = array();
    foreach (array('status', 'warning', 'error') as $type) {
      // Add a GPL-licensed icon from IcoMoon. https://icomoon.io/#preview-free
      $icon_size = 'width="24" height="24"';
      // All of the IcoMoon SVGs have the same header.
      $variables['icon'][$type] = '<svg version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" ' . $icon_size . ' viewBox="0 0 64 64">';
      switch ($type) {
        case 'error':
          $variables['icon'][$type] .= '<path d="M63.416 51.416c-0-0-0.001-0.001-0.001-0.001l-19.415-19.416 19.415-19.416c0-0 0.001-0 0.001-0.001 0.209-0.209 0.36-0.453 0.457-0.713 0.265-0.711 0.114-1.543-0.458-2.114l-9.172-9.172c-0.572-0.572-1.403-0.723-2.114-0.458-0.26 0.097-0.504 0.248-0.714 0.457 0 0-0 0-0.001 0.001l-19.416 19.416-19.416-19.416c-0-0-0-0-0.001-0.001-0.209-0.209-0.453-0.36-0.713-0.457-0.711-0.266-1.543-0.114-2.114 0.457l-9.172 9.172c-0.572 0.572-0.723 1.403-0.458 2.114 0.097 0.26 0.248 0.505 0.457 0.713 0 0 0 0 0.001 0.001l19.416 19.416-19.416 19.416c-0 0-0 0-0 0.001-0.209 0.209-0.36 0.453-0.457 0.713-0.266 0.711-0.114 1.543 0.458 2.114l9.172 9.172c0.572 0.572 1.403 0.723 2.114 0.458 0.26-0.097 0.504-0.248 0.713-0.457 0-0 0-0 0.001-0.001l19.416-19.416 19.416 19.416c0 0 0.001 0 0.001 0.001 0.209 0.209 0.453 0.36 0.713 0.457 0.711 0.265 1.543 0.114 2.114-0.458l9.172-9.172c0.572-0.572 0.723-1.403 0.458-2.114-0.097-0.26-0.248-0.504-0.457-0.713z" fill="#000000"></path>';
          break;
        case 'warning':
          $variables['icon'][$type] .= '<path d="M26,64l12,0c1.105,0 2,-0.895 2,-2l0,-9c0,-1.105 -0.895,-2 -2,-2l-12,0c-1.105,0 -2,0.895 -2,2l0,9c0,1.105 0.895,2 2,2Z" fill="#000000"></path><path d="M26,46l12,0c1.105,0 2,-0.895 2,-2l0,-42c0,-1.105 -0.895,-2 -2,-2l-12,0c-1.105,0 -2,0.895 -2,2l0,42c0,1.105 0.895,2 2,2Z" fill="#000000"></path>';
          break;
        default:
          $variables['icon'][$type] .= '<path d="M54 8l-30 30-14-14-10 10 24 24 40-40z" fill="#000000"></path>';
      }
      $variables['icon'][$type] .= '</svg>';
    }
  }

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    $output .= "<div class=\"messages messages--$type\">\n";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="visually-hidden">' . $status_heading[$type] . "</h2>\n";
    }

    if (!empty($variables['icon'])) {
      $output .= '<div class="messages__icon">';
      switch ($type) {
        case 'error':
        case 'warning':
          $output .= $variables['icon'][$type];
          break;
        default:
          $output .= $variables['icon']['status'];
      }
      $output .= "</div>";
    }

    if (count($messages) > 1) {
      $output .= " <ul class=\"messages__list\">\n";
      foreach ($messages as $message) {
        $output .= '  <li class="messages__item">' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= reset($messages);
    }
    $output .= "</div>\n";
  }
  return $output;
}

/**
 * Returns HTML for a marker for new or updated content.
 */
function zen_mark($variables) {
  $type = $variables['type'];

  if ($type == MARK_NEW) {
    return ' <mark class="highlight-mark">' . t('new') . '</mark>';
  }
  elseif ($type == MARK_UPDATED) {
    return ' <mark class="highlight-mark">' . t('updated') . '</mark>';
  }
}

/**
 * Alters the default Panels render callback so it removes the panel separator.
 */
function zen_panels_default_style_render_region($variables) {
  return implode('', $variables['panes']);
}

/**
 * Override or insert variables into the panels-pane templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function zen_preprocess_panels_pane(&$variables, $hook) {
  // Use no pane wrapper for common page elements.
  switch ($variables['pane']->subtype) {
    case 'page_content':
    case 'pane_header':
    case 'pane_messages':
    case 'pane_navigation':
      // Allow a pane-specific template to override Zen's suggestion.
      array_unshift($variables['theme_hook_suggestions'], 'panels_pane__no_wrapper');
      break;
  }
  // Add component-style class name to pane title.
  $variables['title_attributes_array']['class'][] = 'pane__title';
}
