<?php

/**
 * Defines a TimelineJS3 era.
 */
class TimelineEra implements TimelineEraInterface {

  /**
   * The era start date.
   *
   * @var TimelineDateInterface
   */
  protected $start_date;

  /**
   * The era end date.
   *
   * @var TimelineDateInterface
   */
  protected $end_date;

  /**
   * The era headline and text.
   *
   * @var TimelineTextInterface
   */
  protected $text;

  public function __construct(TimelineDateInterface $start_date, TimelineDateInterface $end_date, TimelineTextInterface $text = NULL) {
    $this->start_date = $start_date;
    $this->end_date = $end_date;
    if (!empty($text)) {
      $this->text = $text;
    }
  }

  /**
   * {@inheritdoc}
   */
  public function buildArray() {
    $era = array(
      'start_date' => $this->start_date->buildArray(),
      'end_date' => $this->end_date->buildArray(),
    );
    if (!empty($this->text)) {
      $era['text'] = $this->text->buildArray();
    }
    return $era;
  }

}
