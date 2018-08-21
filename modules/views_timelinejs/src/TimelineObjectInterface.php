<?php

/**
 * Provides an interface for defining TimelineJS3 objects.
 */
interface TimelineObjectInterface {

  /**
   * Creates an array representing the TimelineJS javascript object.
   *
   * @return array
   *   The formatted array.
   */
  public function buildArray();

}
