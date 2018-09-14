<?php

/**
 * Provides an interface for defining TimelineJS3 slides.
 */
interface TimelineSlideInterface extends TimelineObjectInterface {

  /**
   * Sets the media for this slide.
   *
   * @param TimelineMediaInterface $media
   *   The media object.
   */
  public function setMedia(TimelineMediaInterface $media);

  /**
   * Sets the group for this slide.
   *
   * @param string $group
   *   The group name.
   */
  public function setGroup($group);

  /**
   * Sets the display date for this slide.
   *
   * @param string $display_date
   *   The display date.
   */
  public function setDisplayDate($display_date);

  /**
   * Sets the background for this slide.
   *
   * @param TimelineBackgroundInterface $backgound
   *   The background object.
   */
  public function setBackground(TimelineBackgroundInterface $backgound);

  /**
   * Sets the unique ID for this slide.
   *
   * @param int|string $id
   *   The unique ID.
   */
  public function setUniqueId($id);

  /**
   * Sets the slide's autolink property to TRUE.
   */
  public function enableAutolink();

  /**
   * Sets the slide's autolink property to FALSE.
   */
  public function disableAutolink();

}
