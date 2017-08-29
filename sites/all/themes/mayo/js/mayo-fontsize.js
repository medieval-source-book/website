/**
 * @file
 * Adds javascript functions for font resizing.
 */
(function ($) {
$(document).ready(function() {
  var originalFontSize = $('body').css('font-size');

  // Reset font size
  $(".resetFont").click(function() {
    mayoColumnsResetHeight();
    $('body').css('font-size', originalFontSize);
    mayoColumnsAdjustHeight();
    return false;
  });

  // Increase font size
  $(".increaseFont").click(function() {
    var currentFontSize = $('body').css('font-size');
    var currentFontSizeNum = parseFloat(currentFontSize, 10);
    var newFontSizeNum = currentFontSizeNum + 1;
    if (20 >= newFontSizeNum) { /* max 20px */
      var newFontSize = newFontSizeNum + 'px';
      mayoColumnsResetHeight();
      $('body').css('font-size', newFontSize);
      mayoColumnsAdjustHeight();
    }
    return false;
  });

  // Decrease font size
  $(".decreaseFont").click(function() {
    var currentFontSize = $('body').css('font-size');
    var currentFontSizeNum = parseFloat(currentFontSize, 10);
    var newFontSizeNum = currentFontSizeNum - 1;
    if (10 <= newFontSizeNum) { /* min 10px */
      var newFontSize = newFontSizeNum + 'px';
      mayoColumnsResetHeight();
      $('body').css('font-size', newFontSize);
      mayoColumnsAdjustHeight();
    }
    return false;
  });
});
})(jQuery);

function mayoEqualHeight(group) {
  var tallest = 0;
  group.each(function() {
    var thisHeight = jQuery(this).height();
    if (thisHeight > tallest) {
      tallest = thisHeight;
    }
  });
  group.height(tallest);
}

function mayoColumnsResetHeight() {
  // reset height of column blocks to 'auto' before chaning font size
  // so that the column blocks can change the size based on the new
  // font size
  if (mayoFunctionExists('mayoEqualHeight')) {
    jQuery("#top-columns .column-block").height('auto');
    jQuery("#bottom-columns .column-block").height('auto');
  }
}
function mayoColumnsAdjustHeight() {
  // equalize the height of the column blocks to the tallest height
  if (mayoFunctionExists('mayoEqualHeight')) {
    mayoEqualHeight(jQuery("#top-columns .column-block"));
    mayoEqualHeight(jQuery("#bottom-columns .column-block"));
  }
}
function mayoFunctionExists(function_name) {
  if (typeof function_name == 'string') {
    return (typeof this.window[function_name] == 'function');
  }
  else {
    return (function_name instanceof Function);
  }
}
