/**
 * @file
 * Invokes the timeline js plugin.
 */

(function ($) {
  Drupal.behaviors.timelineJS = {
    attach: function(context, settings) {
      $.each(Drupal.settings.timelineJS, function(key, timeline) {
        if (timeline['processed'] != true) {
          window.timeline = new TL.Timeline(timeline['embed_id'], timeline['source'], timeline['options']);
        }
        timeline['processed'] = true;
      });
    }
  }
})(jQuery);
