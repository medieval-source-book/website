<?php

/**
 * Provides an interface for defining TimelineJS3 media objects.
 */
interface TimelineMediaInterface extends TimelineObjectInterface {

  /**
   * Sets the caption for this media.
   *
   * @param string $text
   *   The caption text.
   */
  public function setCaption($text);

  /**
   * Sets the credit for this media.
   *
   * @param string $text
   *   The credit text.
   */
  public function setCredit($text);

  /**
   * Sets the thumbnail image URL for this media.
   *
   * @param string $url
   *   The thumbnail image URL.
   */
  public function setThumbnail($url);

}
