<?php

/**
 * Style plugin to render items as TimelineJS3 slides.
 *
 * @ingroup views_style_plugins
 */
class views_timelinejs_plugin_style_timelinejs extends views_plugin_style {

  /**
   * The row index of the slide at which the timeline should first be rendered.
   */
  protected $start_slide_index;

  /**
   * {@inheritdoc}
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['timeline_config'] = array(
      'contains' => array(
        'width' => array('default' => '100%'),
        'height' => array('default' => '40em'),
        'hash_bookmark' => array('default' => ''),
        'scale_factor' => array('default' => '2'),
        'timenav_position' => array('default' => 'bottom'),
        'timenav_height' => array('default' => ''),
        'timenav_height_percentage' => array('default' => ''),
        'timenav_mobile_height_percentage' => array('default' => ''),
        'timenav_height_min' => array('default' => ''),
        'start_at_end' => array('default' => ''),
        'language' => array('default' => ''),
      ),
    );
    $options['additional_config'] = array(
      'contains' => array(
        'font' => array('default' => ''),
        'start_at_current' => array('default' => ''),
      ),
    );
    $options['timeline_fields'] = array(
      'contains' => array(
        'caption' => array('default' => ''),
        'credit' => array('default' => ''),
        'media' => array('default' => ''),
        'thumbnail' => array('default' => ''),
        'group' => array('default' => ''),
        'start_date' => array('default' => ''),
        'end_date' => array('default' => ''),
        'display_date' => array('default' => ''),
        'text' => array('default' => ''),
        'headline' => array('default' => ''),
        'background' => array('default' => ''),
        'background_color' => array('default' => ''),
        'type' => array('default' => ''),
        'unique_id' => array('default' => ''),
      ),
    );
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    $initial_labels = array('' => t('- None -'));
    $view_fields_labels = $this->display->handler->get_field_labels();
    $view_fields_labels = array_merge($initial_labels, $view_fields_labels);

    // Timeline general configuration.  Values within this fieldset will be
    // passed directly to the TimelineJS settings object.  As a result, form
    // element keys should be given the same ID as TimelineJS settings, e.g.
    // $form['timeline_config']['id_of_timelinejs_option'].  See the list of
    // options at https://timeline.knightlab.com/docs/options.html.
    $form['timeline_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('TimelineJS Options'),
      '#description' => t('Each of these settings maps directly to one of the TimelineJS presentation options.  See the <a href="@options-doc">options documentation page</a> for additional information.', array('@options-doc' => 'https://timeline.knightlab.com/docs/options.html')),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_config']['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Timeline width'),
      '#description' => t('The width of the timeline, e.g. "100%" or "650px".'),
      '#default_value' => $this->options['timeline_config']['width'],
      '#size' => 10,
      '#maxlength' => 10,
    );
    $form['timeline_config']['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Timeline height'),
      '#description' => t('The height of the timeline, e.g. "40em" or "650px".  Percent values are not recommended for the height.'),
      '#default_value' => $this->options['timeline_config']['height'],
      '#size' => 10,
      '#maxlength' => 10,
    );
    $form['timeline_config']['hash_bookmark'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add hash bookmarks'),
      '#description' => t('On each slide, a # will be added to the end of the url in the url bar. These urls are bookmarkable, so you can share or return to the same place in the timeline later.'),
      '#return_value' => TRUE,
      '#default_value' => $this->options['timeline_config']['hash_bookmark'],
    );
    $form['timeline_config']['scale_factor'] = array(
      '#type' => 'select',
      '#title' => t('Scale factor'),
      '#description' => t('How many screen widths wide the timeline should be at first presentation.'),
      '#options' => array(
        '0.25' => t('0.25'),
        '0.5' => t('0.5'),
        '1' => t('1'),
        '2' => t('2'),
        '3' => t('3'),
        '4' => t('4'),
        '5' => t('5'),
        '6' => t('6'),
        '7' => t('7'),
        '8' => t('8'),
        '9' => t('9'),
      ),
      '#default_value' => $this->options['timeline_config']['scale_factor'],
    );
    $form['timeline_config']['timenav_position'] = array(
      '#type' => 'select',
      '#title' => t('Timeline navigation position'),
      '#options' => array(
        'bottom' => t('Bottom'),
        'top' => t('Top'),
      ),
      '#default_value' => $this->options['timeline_config']['timenav_position'],
    );
    $form['timeline_config']['timenav_height'] = array(
      '#type' => 'textfield',
      '#title' => t('Timeline navigation height'),
      '#description' => t('The height of the timeline navigation, in pixels.  Enter an integer value.'),
      '#default_value' => $this->options['timeline_config']['timenav_height'],
      '#size' => 10,
      '#maxlength' => 10,
    );
    $form['timeline_config']['timenav_height_percentage'] = array(
      '#type' => 'textfield',
      '#title' => t('Timeline navigation height percentage'),
      '#description' => t('The height of the timeline navigation, in percent.  Enter an integer value.  Overridden by the Timeline navigation height setting.'),
      '#default_value' => $this->options['timeline_config']['timenav_height_percentage'],
      '#size' => 10,
      '#maxlength' => 10,
    );
    $form['timeline_config']['timenav_mobile_height_percentage'] = array(
      '#type' => 'textfield',
      '#title' => t('Timeline navigation mobile height percentage'),
      '#description' => t('The height of the timeline navigation on mobile device screens, in percent.  Enter an integer value.'),
      '#default_value' => $this->options['timeline_config']['timenav_mobile_height_percentage'],
      '#size' => 10,
      '#maxlength' => 10,
    );
    $form['timeline_config']['timenav_height_min'] = array(
      '#type' => 'textfield',
      '#title' => t('Timeline navigation height minimum'),
      '#description' => t('The minimum height of the timeline navigation, in pixels.  Enter an integer value.'),
      '#default_value' => $this->options['timeline_config']['timenav_height_min'],
      '#size' => 10,
      '#maxlength' => 10,
    );
    $form['timeline_config']['start_at_end'] = array(
      '#type' => 'checkbox',
      '#title' => t('Start at the end'),
      '#description' => t('Loads the timeline on the last slide.'),
      '#return_value' => TRUE,
      '#default_value' => $this->options['timeline_config']['start_at_end'],
    );
    $form['timeline_config']['language'] = array(
      '#type' => 'select',
      '#title' => t('Language'),
      '#description' => t("By default, the timeline will be displayed in the site's current language if it is supported by TimelineJS. Selecting a language in this setting will force the timeline to always be displayed in the chosen language."),
      '#options' => array_merge($initial_labels, _views_timelinejs_list_languages()),
      '#default_value' => $this->options['timeline_config']['language'],
    );

    // Timeline additional configuration.
    $form['additional_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('Additional Options'),
      '#description' => t('These settings include extra options to control the TimelineJS presentation or options unique to this plugin.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['additional_config']['font'] = array(
      '#type' => 'select',
      '#title' => t('Font set'),
      '#description' => t('TimelineJS3 offers several pre-selected font sets.  If a set is selected its CSS file will be downloaded from the CDN.'),
      '#options' => array_merge($initial_labels, _views_timelinejs_list_font_sets()),
      '#default_value' => $this->options['additional_config']['font'],
    );
    $form['additional_config']['start_at_current'] = array(
      '#type' => 'checkbox',
      '#title' => t('Start at Current'),
      '#description' => t('Loads the timeline on the slide closest to the current time.  Overrides the "Start at the End" setting.'),
      '#return_value' => TRUE,
      '#default_value' => $this->options['additional_config']['start_at_current'],
    );

    // Field mapping.
    $form['timeline_fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Field mappings'),
      '#description' => t('Map your Views data fields to TimelineJS slide object properties.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_fields']['headline'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Headline'),
      '#description' => t('The selected field may contain any text, including HTML markup.'),
      '#default_value' => $this->options['timeline_fields']['headline'],
    );
    $form['timeline_fields']['text'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Body text'),
      '#description' => t('The selected field may contain any text, including HTML markup.'),
      '#default_value' => $this->options['timeline_fields']['text'],
    );
    $form['timeline_fields']['start_date'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Start date'),
      '#required' => TRUE,
      '#description' => t('The selected field should contain a string representing a date conforming to a <a href="@php-manual">PHP supported date and time format</a>.  Start dates are required by event slides and eras.  If this mapping is not configured or if the field does not output dates in a valid format, then the slides or eras will not be added to the timeline.', array('@php-manual' => 'http://php.net/manual/en/datetime.formats.php')),
      '#default_value' => $this->options['timeline_fields']['start_date'],
    );
    $form['timeline_fields']['end_date'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('End date'),
      '#description' => t('The selected field should contain a string representing a date conforming to a <a href="@php-manual">PHP supported date and time format</a>.  End dates are required by eras.  If this mapping is not configured or if the field does not output dates in a valid format, then the eras will not be added to the timeline.', array('@php-manual' => 'http://php.net/manual/en/datetime.formats.php')),
      '#default_value' => $this->options['timeline_fields']['end_date'],
    );
    $form['timeline_fields']['display_date'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Display date'),
      '#description' => t('The selected field should contain a string.  TimelineJS will display this value instead of the values of the start and end date fields.'),
      '#default_value' => $this->options['timeline_fields']['display_date'],
    );
    $form['timeline_fields']['background'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Background image'),
      '#description' => t('The selected field should contain a raw URL to an image.  Special handling is included for Image fields because they have no raw URL formatter.'),
      '#default_value' => $this->options['timeline_fields']['background'],
    );
    $form['timeline_fields']['background_color'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Background color'),
      '#description' => t('The selected field should contain a string representing a CSS color, in hexadecimal (e.g. #0f9bd1) or a valid <a href="@color-keywords">CSS color keyword</a>.', array('@color-keywords' => 'https://developer.mozilla.org/en-US/docs/Web/CSS/color_value#Color_keywords')),
      '#default_value' => $this->options['timeline_fields']['background_color'],
    );
    $form['timeline_fields']['media'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Media'),
      '#description' => t('The selected field should contain a raw URL to a media resource, an HTML blockquote, or an HTML iframe.  See the <a href="@media-documentation">media types documentation</a> for a list of supported types.  Special handling is included for Image fields because they have no raw URL formatter.', array('@media-documentation' => 'https://timeline.knightlab.com/docs/media-types.html')),
      '#default_value' => $this->options['timeline_fields']['media'],
    );
    $form['timeline_fields']['credit'] = array(
      '#type' => 'select',
      '#title' => t('Media Credit'),
      '#description' => t('The selected field may contain any text, including HTML markup.'),
      '#options' => $view_fields_labels,
      '#default_value' => $this->options['timeline_fields']['credit'],
    );
    $form['timeline_fields']['caption'] = array(
      '#type' => 'select',
      '#title' => t('Media Caption'),
      '#description' => t('The selected field may contain any text, including HTML markup.'),
      '#options' => $view_fields_labels,
      '#default_value' => $this->options['timeline_fields']['caption'],
    );
    $form['timeline_fields']['thumbnail'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Media thumbnail'),
      '#description' => t('The selected field should contain a raw URL for an image to use in the timenav marker for this event. If omitted, TimelineJS will use an icon based on the type of media.  Special handling is included for Image fields because they have no raw URL formatter.'),
      '#default_value' => $this->options['timeline_fields']['thumbnail'],
    );
    $form['timeline_fields']['group'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Group'),
      '#description' => t('The selected field may contain any text. If present, TimelineJS will organize events with the same value for group to be in the same row or adjacent rows, separate from events in other groups. The common value for the group will be shown as a label at the left edge of the navigation.'),
      '#default_value' => $this->options['timeline_fields']['group'],
    );
    $form['timeline_fields']['type'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Type'),
      '#description' => t('Determines the type of timeline entity that is rendered: event, title slide, or era.  This plugin recognizes a limited set of string values to determine the type.  "title" or "timeline_title_slide" will cause a views data row to be rendered as a TimelineJS title slide.  Only one title slide can be created per timeline.  Additional title slides will overwrite previous slides.  "era" or "timeline_era" rows will be rendered as TimelineJS eras.  By default, a row with an empty value or any other input will be rendered as a regular event slide.'),
      '#default_value' => $this->options['timeline_fields']['type'],
    );
    $form['timeline_fields']['unique_id'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Unique ID'),
      '#description' => t('The selected field should contain a string value which is unique among all slides in your timeline, e.g. a node ID. If not specified, TimelineJS will construct an ID based on the headline, but if you later edit your headline, the ID will change. Unique IDs are used when the hash_bookmark option is used.'),
      '#default_value' => $this->options['timeline_fields']['unique_id'],
    );
  }

  /**
   * {@inheritdoc}
   */
  function render() {
    // Return if the start date field mapping is not configured.
    if (empty($this->options['timeline_fields']['start_date'])) {
      drupal_set_message(t('The Start date field mapping must be configured in the TimelineJS format settings before any slides or eras can be rendered.'), 'warning');
      return;
    }

    $timeline = new Timeline();

    // Render the fields.  If it isn't done now then the row_index will be unset
    // the first time that get_field() is called, resulting in an undefined
    // property exception.
    $this->render_fields($this->view->result);

    // Render slide arrays from the views data.
    foreach ($this->view->result as $row_index => $row) {
      $this->view->row_index = $row_index;

      // Determine the type of timeline entity to build.
      $type = 'event';
      if ($this->options['timeline_fields']['type']) {
        $type = $this->get_field($row_index, $this->options['timeline_fields']['type']);
      }
      switch ($type) {
        case 'title':
        case 'timeline_title_slide':
          $slide = $this->build_title_slide();
          // Ensure the slide was built.
          if (!empty($slide)) {
            $timeline->setTitleSlide($slide);
          }
          break;
        case 'era':
        case 'timeline_era':
          $era = $this->build_era();
          // Ensure the era was built.
          if (!empty($era)) {
            $timeline->addEra($era);
          }
          break;
        default:
          $slide = $this->build_slide();
          // Ensure the slide was built.
          if (!empty($slide)) {
            $timeline->addEvent($slide);
          }
      }
    }
    unset($this->view->row_index);

    // Skip theming if the view is being edited or previewed.
    if ($this->view->editing) {
      return '<pre>' . print_r($timeline->buildArray(), 1) . '</pre>';
    }

    // Prepare the options array.
    $this->prepare_timeline_options();

    return theme('views_timelinejs', array(
      'view' => $this->view,
      'timeline_options' => $this->options['timeline_config'],
      'timeline_font' => $this->options['additional_config']['font'],
      'rows' => $timeline->buildArray(),
    ));
  }

  /**
   * Builds a timeline slide from the current views data row.
   *
   * @return TimelineSlideInterface|NULL
   *   A slide object or NULL if the start date could not be parsed.
   */
  protected function build_slide() {
    $start_date = $this->build_date($this->options['timeline_fields']['start_date']);
    // Return NULL if the slide has no start date.
    if (empty($start_date)) {
      return NULL;
    }
    $end_date = $this->build_date($this->options['timeline_fields']['end_date']);
    $text = $this->build_text();
    $slide = new TimelineSlide($start_date, $end_date, $text);

    // Check to see if this slide should be the start slide.
    $this->check_start_slide($start_date);

    $slide->setDisplayDate($this->build_display_date());

    $slide->setGroup($this->build_group());

    $slide->setBackground($this->build_background());

    $media = $this->build_media();
    if (!empty($media)) {
      $slide->setMedia($media);
    }

    $slide->setUniqueId($this->build_unique_id());

    return $slide;
  }

  /**
   * Builds a timeline title slide from the current views data row.
   *
   * @return TimelineSlideInterface
   *   A slide object.
   */
  protected function build_title_slide() {
    $text = $this->build_text();
    $slide = new TimelineTitleSlide($text);

    $slide->setBackground($this->build_background());

    $media = $this->build_media();
    if (!empty($media)) {
      $slide->setMedia($media);
    }

    $slide->setUniqueId($this->build_unique_id());

    return $slide;
  }

  /**
   * Builds a timeline era from the current views data row.
   *
   * @return TimelineEra|NULL
   *   An era object or NULL if the start or end date could not be parsed.
   */
  protected function build_era() {
    $start_date = $this->build_date($this->options['timeline_fields']['start_date']);
    // Return NULL if the era has no start date.
    if (empty($start_date)) {
      return NULL;
    }
    $end_date = $this->build_date($this->options['timeline_fields']['end_date']);
    // Return NULL if the era has no end date.
    if (empty($end_date)) {
      return NULL;
    }
    $text = $this->build_text();
    return new TimelineEra($start_date, $end_date, $text);
  }

  /**
   * Builds a timeline date from the current data row.
   *
   * @param string $field
   *   The machine name of the date field.
   *
   * @return TimelineDate|NULL
   *   A date object or NULL if the start date could not be parsed.
   */
  protected function build_date($field) {
    try {
      // Strip HTML tags from dates so users don't run into problems like Date
      // fields wrapping their output with metadata.
      $date_string = strip_tags($this->get_field($this->view->row_index, $field));
      $date = new TimelineDate($date_string);
    }
    catch (Exception $e) {
      // Return NULL if the field didn't contain a parseable date string.
      views_debug('The date "@date" does not conform to a <a href="@php-manual">PHP supported date and time format</a>.', array('@date' => $date_string, '@php-manual' => 'http://php.net/manual/en/datetime.formats.php'));
      return NULL;
    }
    return $date;
  }

  /**
   * Builds a timeline display date from the current data row.
   *
   * @return string
   *   A string which contains the text to be displayed instead of the start
   *   and end dates of a slide.
   */
  protected function build_display_date() {
    $display_date = '';
    if ($this->options['timeline_fields']['display_date']) {
      $display_date = $this->get_field($this->view->row_index, $this->options['timeline_fields']['display_date']);
    }
    return $display_date;
  }

  /**
   * Builds timeline text from the current data row.
   *
   * @return TimelineText
   *   A text object.
   */
  protected function build_text() {
    $headline = '';
    if ($this->options['timeline_fields']['headline']) {
      $headline = $this->get_field($this->view->row_index, $this->options['timeline_fields']['headline']);
    }

    $text = '';
    if ($this->options['timeline_fields']['text']) {
      $text = $this->get_field($this->view->row_index, $this->options['timeline_fields']['text']);
    }
    return new TimelineText($headline, $text);
  }

  /**
   * Builds a timeline group from the current data row.
   *
   * @return string
   *   The group name.
   */
  protected function build_group() {
    $group = '';
    if ($this->options['timeline_fields']['group']) {
      $group = $this->get_field($this->view->row_index, $this->options['timeline_fields']['group']);
    }
    return $group;
  }

  /**
   * Builds a timeline background from the current data row.
   *
   * @return TimelineBackground
   *   A background object.
   */
  protected function build_background() {
    $url = '';
    if ($this->options['timeline_fields']['background']) {
      $url = $this->get_field($this->view->row_index, $this->options['timeline_fields']['background']);

      // Special handling because core Image fields have no raw URL formatter.
      // Check to see if we don't have a raw URL.
      if (!filter_var($url, FILTER_VALIDATE_URL)) {
        // Attempt to extract a URL from an img or anchor tag in the string.
        $url = $this->extract_url($url);
      }
    }

    $color = '';
    if ($this->options['timeline_fields']['background_color']) {
      $color = $this->get_field($this->view->row_index, $this->options['timeline_fields']['background_color']);
    }
    return new TimelineBackground($url, $color);
  }

  /**
   * Builds timeline media from the current data row.
   *
   * @return TimelineMedia|NULL
   *   A media object or NULL if the URL is empty.
   */
  protected function build_media() {
    $url = '';
    if ($this->options['timeline_fields']['media']) {
      $url = $this->get_field($this->view->row_index, $this->options['timeline_fields']['media']);

      // Special handling because core Image fields have no raw URL formatter.
      // Check to see if we don't have a raw URL.
      if (!filter_var($url, FILTER_VALIDATE_URL)) {
        // Attempt to extract a URL from an img or anchor tag in the string.
        $url = $this->extract_url($url);
      }
    }
    // Return NULL if the URL is empty.
    if (empty($url)) {
      return NULL;
    }

    $media = new TimelineMedia($url);
    if ($this->options['timeline_fields']['thumbnail']) {
      $thumbnail = $this->get_field($this->view->row_index, $this->options['timeline_fields']['thumbnail']);

      // Special handling because core Image fields have no raw URL formatter.
      // Check to see if we don't have a raw URL.
      if (!filter_var($thumbnail, FILTER_VALIDATE_URL)) {
        // Attempt to extract a URL from an img or anchor tag in the string.
        $thumbnail = $this->extract_url($thumbnail);
      }
      $media->setThumbnail($thumbnail);
    }
    if ($this->options['timeline_fields']['caption']) {
      $media->setCaption($this->get_field($this->view->row_index, $this->options['timeline_fields']['caption']));
    }
    if ($this->options['timeline_fields']['credit']) {
      $media->setCredit($this->get_field($this->view->row_index, $this->options['timeline_fields']['credit']));
    }
    return $media;
  }

  /**
   * Builds a timeline unique id from the current data row.
   *
   * @return string
   *   A unique ID for a slide.
   */
  protected function build_unique_id() {
    $unique_id = '';
    if ($this->options['timeline_fields']['unique_id']) {
      $unique_id = $this->get_field($this->view->row_index, $this->options['timeline_fields']['unique_id']);
    }
    return $unique_id;
  }

  /**
   * Checks a slide date to see if it should be displayed first in the timeline.
   *
   * @param DateTime $date
   *   A date from a TimelineJS slide.
   */
  protected function check_start_slide(DateTime $date) {
    static $smallest_difference;
    if (!isset($smallest_difference)) {
      $smallest_difference = NULL;
    }

    $timestamp = $date->getTimestamp();
    // Return if the date was prior to the UNIX Epoch.
    if ($timestamp === FALSE) {
      return;
    }

    // Calculate the absolute difference between the current time and the date.
    $difference = abs(time() - $timestamp);

    // Update the start slide index if this date is closer to the current time.
    if ($smallest_difference == NULL || $difference < $smallest_difference) {
      $smallest_difference = $difference;
      $this->start_slide_index = $this->view->row_index;
    }
  }

  /**
   * Searches a string for HTML attributes that contain URLs and returns them.
   *
   * This will search a string which is presumed to contain HTML for anchor or
   * image tags.  It will return the href or src attribute of the first one it
   * finds.
   *
   * This is basically special handling for core Image fields.  There is no
   * built-in field formatter for outputting a raw URL from an image.  This
   * method allows image fields to "just work" as sources for TimelineJS media
   * and background image URLs.  Anchor tag handling was added for people who
   * forget to output link fields as plain text URLs.
   *
   * @param string $html
   *   A string that contains HTML.
   *
   * @return string
   *   A URL if one was found in the input string, the original string if not.
   */
  protected function extract_url($html) {
    if (!empty($html)) {
      // Disable libxml errors.
      $previous_use_errors = libxml_use_internal_errors(TRUE);

      $document = new DOMDocument();
      $document->loadHTML($html);

      // Handle XML errors.
      foreach (libxml_get_errors() as $error) {
        $this->handle_xml_errors($error, $html);
      }

      // Restore the previous error setting.
      libxml_use_internal_errors($previous_use_errors);

      // Check for anchor tags.
      $anchor_tags = $document->getElementsByTagName('a');
      if ($anchor_tags->length) {
        return $anchor_tags->item(0)->getAttribute('href');
      }

      // Check for image tags.
      $image_tags = $document->getElementsByTagName('img');
      if ($image_tags->length) {
        return $image_tags->item(0)->getAttribute('src');
      }
    }
    return $html;
  }

  /**
   * Sets Drupal messages to inform users of HTML parsing errors.
   *
   * @param \LibXMLError $error
   *   Contains information about the XML parsing error.
   * @param type $html
   *   Contains the original HTML that was parsed.
   */
  protected function handle_xml_errors(\LibXMLError $error, $html) {
    $message = t('A media field has an error in its HTML.<br>Error message: @message<br>Views result row: @row<br>HTML: <pre>@html</pre>', array('@message' => $error->message, '@row' => $this->view->row_index, '@html' => $html));
    drupal_set_message($message, 'warning');
  }

  /**
   * Processes timeline options before theming.
   */
  protected function prepare_timeline_options() {
    // Set the script_path option for locally-hosted libraries.
    if (variable_get('views_timelinejs_library', 'cdn') == 'local') {
      $this->prepareScriptPathOption();
    }

    // Set the language option to the site's default if it is empty.
    if (empty($this->options['timeline_config']['language'])) {
      $this->prepare_language_option();
    }

    // If the custom start_at_current option is set, then set the timeline's
    // start_at_slide option to the start_slide_index and override the
    // start_at_end option.
    if ($this->options['additional_config']['start_at_current']) {
      $this->options['timeline_config']['start_at_slide'] = $this->start_slide_index;
      $this->options['timeline_config']['start_at_end'] = FALSE;
    }
  }

  /**
   * Sets the timeline language option to the site's current language.
   */
  protected function prepare_language_option() {
    global $language;
    $supported_languages = _views_timelinejs_list_languages();
    $language_map = _views_timelinejs_language_map();

    // Check for the site's current language in the list of languages that are
    // supported by TimelineJS.
    if (isset($supported_languages[$language->language])) {
      $this->options['timeline_config']['language'] = $language->language;
    }
    // Check for the site's current language in the list of language codes
    // that are different in Drupal than they are in TimelineJS.
    elseif (isset($language_map[$language->language])) {
      $this->options['timeline_config']['language'] = $language_map[$language->language];
    }
  }

  /**
   * Sets the timeline script_path option to the library's location.
   */
  protected function prepareScriptPathOption() {
    global $base_url;
    $script_path = $base_url . '/sites/all/libraries/TimelineJS3/compiled/js';
    $this->options['timeline_config']['script_path'] = $script_path;
  }

}
