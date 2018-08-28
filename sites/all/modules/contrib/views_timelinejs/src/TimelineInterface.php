<?php

/**
 * Provides an interface for defining TimelineJS3 timelines.
 */
interface TimelineInterface extends TimelineObjectInterface {

  /**
   * Adds a new slide to the timeline's events array.
   *
   * @param TimelineSlideInterface $slide
   *   The new slide.
   */
  public function addEvent(TimelineSlideInterface $slide);

  /**
   * Returns the timeline's array of event slides.
   *
   * @return array
   *   An array of TimelineSlideInterface objects.
   */
  public function getEvents();

  /**
   * Adds a new era to the timeline's eras array.
   *
   * @param TimelineEraInterface $era
   *   The new era.
   */
  public function addEra(TimelineEraInterface $era);

  /**
   * Returns the timeline's array of eras.
   *
   * @return array
   *   An array of TimelineEraInterface objects.
   */
  public function getEras();

  /**
   * Sets the timeline's title slide.
   *
   * @param TimelineSlideInterface $slide
   *   The new slide.
   */
  public function setTitleSlide(TimelineSlideInterface $slide);

  /**
   * Returns the timeline's title slide.
   *
   * @return TimelineSlideInterface
   *   The title slide.
   */
  public function getTitleSlide();

  /**
   * Sets the timeline's scale to human.
   */
  public function setScaleToHuman();

  /**
   * Sets the timeline's scale to cosmological.
   */
  public function setScaleToCosomological();

  /**
   * Returns the timeline's scale.
   */
  public function getScale();

}
