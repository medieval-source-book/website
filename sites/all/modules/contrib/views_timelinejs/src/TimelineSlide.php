<?php

/**
 * Defines a TimelineJS3 slide.
 */
class TimelineSlide implements TimelineSlideInterface {

  /**
   * The slide start date.
   *
   * @var TimelineDateInterface
   */
  protected $start_date;

  /**
   * The slide end date.
   *
   * @var TimelineDateInterface
   */
  protected $end_date;

  /**
   * The slide headline and text.
   *
   * @var TimelineTextInterface
   */
  protected $text;

  /**
   * The slide media and its metadata.
   *
   * @var TimelineMediaInterface
   */
  protected $media;

  /**
   * The slide group.
   *
   * @var string
   */
  protected $group;

  /**
   * The slide display date.
   *
   * @var string
   */
  protected $display_date;

  /**
   * The slide background url and color.
   *
   * @var TimelineBackgroundInterface
   */
  protected $background;

  /**
   * The slide autolink property
   *
   * @var bool
   */
  protected $autolink = TRUE;

  /**
   * The slide unique id.
   *
   * @var int|string
   */
  protected $unique_id;

  public function __construct(TimelineDateInterface $start_date, TimelineDateInterface $end_date = NULL, TimelineTextInterface $text = NULL) {
    $this->start_date = $start_date;
    if (!empty($end_date)) {
      $this->end_date = $end_date;
    }
    if (!empty($text)) {
      $this->text = $text;
    }
  }

  /**
   * {@inheritdoc}
   */
  public function setMedia(\TimelineMediaInterface $media) {
    $this->media = $media;
  }

  /**
   * {@inheritdoc}
   */
  public function setGroup($group) {
    $this->group = $group;
  }

  /**
   * {@inheritdoc}
   */
  public function setDisplayDate($display_date) {
    $this->display_date = $display_date;
  }

  /**
   * {@inheritdoc}
   */
  public function setBackground(\TimelineBackgroundInterface $backgound) {
    $this->background = $backgound;
  }

  /**
   * {@inheritdoc}
   */
  public function setUniqueId($id) {
    $this->unique_id = $id;
  }

  /**
   * {@inheritdoc}
   */
  public function enableAutolink() {
    $this->autolink = TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public function disableAutolink() {
    $this->autolink = FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function buildArray() {
    $slide = array('start_date' => $this->start_date->buildArray());
    // Don't render end dates that are the same as the start date.  TimelineJS
    // won't display them anyway, but skipping them can make the rendered data
    // array smaller.
    if (!empty($this->end_date) && $this->start_date != $this->end_date) {
      $slide['end_date'] = $this->end_date->buildArray();
    }
    if (!empty($this->text)) {
      $slide['text'] = $this->text->buildArray();
    }
    if (!empty($this->media)) {
      $slide['media'] = $this->media->buildArray();
    }
    if (!empty($this->group)) {
      $slide['group'] = $this->group;
    }
    if (!empty($this->display_date)) {
      $slide['display_date'] = $this->display_date;
    }
    if (!empty($this->background)) {
      $slide['background'] = $this->background->buildArray();
    }
    if (!$this->autolink) {
      $slide['autolink'] = FALSE;
    }
    if (!empty($this->unique_id)) {
      $slide['unique_id'] = $this->unique_id;
    }
    // Filter any empty values before returning.
    return array_filter($slide);
  }

}
