<?php

/**
 * @file
 * Helper functions.
 */

/**
 * Get the settings values in array format.
 */
function bg_image_formatter_extract_settings_values(array $settings, $key) {
  if(isset($settings[$key])) {
    return array_map(function ($value) {
      $value = strip_tags($value);
      return trim($value, ',');
    }, explode(PHP_EOL, trim($settings[$key])));
  }
}

/**
 * Function taken from the module 'bg_image'.
 *
 * Adds a background image to the page using the
 * css 'background' property.
 *
 * @param string $image_path
 *    The path of the image to use. This can be either
 *      - A relative path e.g. sites/default/files/image.png
 *      - A uri: e.g. public://image.png.
 * @param array $css_settings
 *    An array of css settings to use. Possible values are:
 *      - bg_image_selector: The css selector to use
 *      - bg_image_color: The background color
 *      - bg_image_x: The x offset
 *      - bg_image_y: The y offset
 *      - bg_image_attachment: The attachment property (scroll or fixed)
 *      - bg_image_repeat: The repeat settings
 *      - bg_image_background_size: The background size property if necessary
 *    Default settings will be used for any values not provided.
 * @param string $image_style
 *   Optionally add an image style to the image before applying it to the
 *   background.
 *
 * @return bool
 *   Returns TRUE if successful or FALSE otherwise
 */
function bg_image_formatter_add_background_image_css($image_path, $css_settings = array(), $image_style = NULL) {
  // Check if path is a stream wrapper.
  $image_uri = file_uri_scheme($image_path) ? $image_path : _bg_image_formatter_path_to_uri($image_path);
  $image_path = file_uri_scheme($image_path) ? file_create_url($image_path) : $image_path;

  // Pull the default css setting if not provided.
  $selector = isset($css_settings['bg_image_selector']) ? $css_settings['bg_image_selector'] : '';
  $bg_color = isset($css_settings['bg_image_color']) ? $css_settings['bg_image_color'] : '#FFFFFF';
  $bg_x = isset($css_settings['bg_image_x']) ? $css_settings['bg_image_x'] : 'left';
  $bg_y = isset($css_settings['bg_image_y']) ? $css_settings['bg_image_y'] : 'top';
  $attachment = isset($css_settings['bg_image_attachment']) ? $css_settings['bg_image_attachment'] : 'scroll';
  $repeat = isset($css_settings['bg_image_repeat']) ? $css_settings['bg_image_repeat'] : 'no-repeat';
  $important = isset($css_settings['bg_image_important']) ? $css_settings['bg_image_important'] : 1;
  $background_size = isset($css_settings['bg_image_background_size']) ? $css_settings['bg_image_background_size'] : '';
  $background_size_ie8 = isset($css_settings['bg_image_background_size_ie8']) ? $css_settings['bg_image_background_size_ie8'] : 0;
  $media_query = isset($css_settings['bg_image_media_query']) ? $css_settings['bg_image_media_query'] : 'all';

  // Apply an Image Style?
  $image_style = $image_style ? $image_style : '';

  // If important is true, we turn it into a string for css output.
  if ($important) {
    $important = '!important';
  }
  else {
    $important = '';
  }

  // Handle the background size property.
  $bg_size = '';
  $ie_bg_size = '';
  if ($background_size) {
    // CSS3.
    $bg_size = sprintf('background-size: %s %s;', $background_size, $important);
    // Let's cover ourselves for other browsers as well...
    $bg_size .= sprintf('-webkit-background-size: %s %s;', $background_size, $important);
    $bg_size .= sprintf('-moz-background-size: %s %s;', $background_size, $important);
    $bg_size .= sprintf('-o-background-size: %s %s;', $background_size, $important);
    // IE filters to apply the cover effect.
    if ($background_size == 'cover' && $background_size_ie8) {
      $ie_bg_size = sprintf("filter: progid:DXImageTransform.Microsoft.AlphaImageLoader(src='%s', sizingMethod='scale');", $image_path);
      $ie_bg_size .= sprintf("-ms-filter: progid:DXImageTransform.Microsoft.AlphaImageLoader(src='%s', sizingMethod='scale');", $image_path);
    }
  }

  // Check if we need to run this through an image style.
  if ($image_style) {
    $image_path = image_style_url($image_style, $image_uri);
  }

  // Add the css if we have everything we need.
  if ($selector && $image_path) {
    $style = sprintf('%s {', $selector);
    $style .= sprintf('background-color: %s %s;', $bg_color, $important);
    $style .= sprintf("background-image: url('%s') %s;", $image_path, $important);
    $style .= sprintf('background-repeat: %s %s;', $repeat, $important);
    $style .= sprintf('background-attachment: %s %s;', $attachment, $important);
    $style .= sprintf('background-position: %s %s %s;', $bg_x, $bg_y, $important);
    $style .= $bg_size;
    $style .= $background_size_ie8 ? $ie_bg_size : '';
    $style .= "}";

    return array(
      'type' => 'inline',
      'style' => $style,
      'media' => $media_query,
      'group' => CSS_THEME,
    );
  }

  return FALSE;
}

/**
 * Converts a path to a uri relative to the public files directory.
 *
 * @param string $path
 *    The path to convert. Can be an absolute or relative path. If the path
 *    contains the public files directory in it, it will be stripped before
 *    building the uri, since we're building a public:// uri.
 *
 * @return string
 *    The path to the file as a uri.
 */
function _bg_image_formatter_path_to_uri($path) {
  // Strip off the protocol and domain.
  $relative_path = parse_url($path, PHP_URL_PATH);
  // The public files directory (as configured).
  $file_public_path = '/' . variable_get('file_public_path', 'sites/default/files');
  // Remove the public path if the path starts with it.
  if (strpos($relative_path, $file_public_path) === 0) {
    $relative_path = str_replace($file_public_path, '', $relative_path);
    return file_build_uri($relative_path);
  }
  else {
    // If the public files directory isn't in the path, just return it as a uri.
    return file_build_uri($relative_path);
  }
}
