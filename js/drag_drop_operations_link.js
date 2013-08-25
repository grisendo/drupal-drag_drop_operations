(function($) {

  Drupal.ajax.prototype.commands.ddo_link_add = function(ajax, response, status) {
    var $view = response.view;
    var $display = response.display;
    var $box = $('#ddo-' + $view + '-' + $display + '-container');
    var $gaps = $('.ddo-droppable', $box);
    var $found = false;
    for (key in $gaps) {
      $gap = $($gaps[key]);
      if (!$gap.val()) {
        $found = true;
        $gap.val(response.entity + ':' + response.id);
        $('#ddo-edit-container-draft', $box).trigger('mousedown');
        break;
      }
    }
    if (!$found) {
      alert('There are no gaps.');
    }
  };

})(jQuery);
