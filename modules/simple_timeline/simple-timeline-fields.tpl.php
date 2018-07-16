<?php
/**
 * @file
 * simple-timeline-fields.tpl.php
 * Created by JetBrains PhpStorm.
 * User: alan
 *
 * @var $simple_timeline_image
 * @var $simple_timeline_date
 * @var $simple_timeline_text
 */
?>
<div>
  <span class="timeline-image"><?php echo $simple_timeline_image; ?></span>

    <span class="timeline-content">
        <h3 class="timeline-date"><?php echo $simple_timeline_date; ?></h3>
        <span class="timeline-text"><?php echo $simple_timeline_text; ?></span>
    </span>
</div>
