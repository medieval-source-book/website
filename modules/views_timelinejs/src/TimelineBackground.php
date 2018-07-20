<?php

/**
 * Defines a TimelineJS3 background object.
 */
class TimelineBackground implements TimelineBackgroundInterface {

  /**
   * The background image url.
   *
   * @var string
   */
  protected $url;

  /**
   * The background color.
   *
   * A CSS color, in hexadecimal (e.g. #0f9bd1) or a valid CSS color keyword.
   *
   * @var string
   */
  protected $color;

  public function __construct($url = '', $color = '') {
    $this->url = $url;
    $this->color = $color;
  }

  /**
   * {@inheritdoc}
   */
  public function buildArray() {
    $background = array();
    if (!empty($this->url)) {
      $background['url'] = $this->url;
    }
    if (!empty($this->color)) {
      $background['color'] = $this->color;
    }
    return $background;
  }

}
