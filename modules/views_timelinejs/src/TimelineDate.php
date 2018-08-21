<?php

/**
 * Converts date strings to TimelineJS3-compatible date arrays.
 */
class TimelineDate extends DateTime implements TimelineDateInterface {

  /**
   * The original date string that was passed to the constructor.
   */
  protected $date_string;

  public function __construct($date_string, DateTimeZone $timezone = NULL) {
    $this->date_string = $date_string;

    // Disallow empty date strings.  They will cause DateTime::__construct() to
    // return a date object with the current time.
    if (empty($date_string)) {
      throw new Exception('Empty date strings are not allowed.');
    }

    // Check for date strings that only include a year value.
    if (is_numeric($date_string)) {
      // Append '-01-01' to year-only values.  By specifying a month and day
      // before the value is parsed, year-only values can be used as input.
      $date_string .= '-01-01';
    }

    // Explicitly set timezone for versions of PHP prior to 5.3.6.
    // @see https://bugs.php.net/bug.php?id=52063
    if ((phpversion() < '5.3.6') && $timezone === NULL) {
      $timezone = new DateTimeZone(date_default_timezone_get());
    }

    parent::__construct($date_string, $timezone);
  }

  /**
   * {@inheritdoc}
   */
  public function buildArray() {
    // The TimelineJS documentation doesn't say anything specific about whether
    // leading zeros should be included in date parts, but the examples do not
    // include them.  Therefore, they are omitted here.
    $exploded_date = explode(',', $this->format('Y,n,j,G,i,s'));

    // Re-key the date array with the property names that TimelineJS expects.
    return array(
      'year' => $exploded_date[0],
      'month' => $exploded_date[1],
      'day' => $exploded_date[2],
      'hour' => $exploded_date[3],
      'minute' => $exploded_date[4],
      'second' => $exploded_date[5],
      'display_date' => $this->date_string,
    );
  }

}
