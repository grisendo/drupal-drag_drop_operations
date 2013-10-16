(function($) {

  Drupal.behaviors.dragDropOperationsDrag = {

    attach: function(context, settings) {
      $('.ddo-draggable:not(.ddo-drag-processed)', context).each(
        function() {
          var $this = $(this);
          $this.addClass('ddo-drag-processed');
          var $classes = $this.attr('class');
          var $interest = $classes.match(/ddo-draggable--(.*?)--(\d+)/g)[0].split('--');
          $this.attr('data-entitytype', $interest[1]);
          $this.attr('data-entityid', $interest[2]);
          $this.draggable(
            {
              helper: 'clone',
              cancel: '.ddo-add-link',
              start: function(event, ui) {
                var $this = $(ui.helper);
                $this.addClass('ddo-dragging');
              }
            }
          );
        }
      );
    }

  };

  Drupal.behaviors.dragDropOperationsDrop = {

    attach: function(context, settings) {

      $('#ddo-edit-container-draft:not(.element-hidden)', context).addClass('element-hidden').hide();

      $('.ddo-droppable:not(.ddo-drop-processed)', context).each(
        function() {
          var $this = $(this);
          $this.addClass('ddo-drop-processed');
          var $val = $this.val();
          var $that = $this;
          var $placeholder = $this.parent().next();
          $this.parent().hide();
          var $remove = $placeholder.find('.ddo-remove-item');
          if ($remove.length) {
            $remove.bind(
              'click',
              function() {
                $placeholder.addClass('ddo-ajax-loading');
                $that.val('');
                $('#ddo-edit-container-draft').trigger('mousedown');
                return false;
              }
            );
          }
          $placeholder.droppable(
            {
              hoverClass: 'ddo-hover',
              drop: function(e, ui) {
                var $element = $(ui.draggable);
                if (!$element.hasClass('ddo-element-sortable')) {
                  $placeholder.addClass('ddo-ajax-loading');
                  $that.val($element.attr('data-entitytype') + ':' + $element.attr('data-entityid'));
                  $('#ddo-edit-container-draft').trigger('mousedown');
                }
              }
            }
          );
        }
      );

    }

  };

  Drupal.behaviors.dragDropOperationsSort = {

    attach: function(context, settings) {
      $('.ddo-sort-box:not(.ddo-sort-processed)', context).each(
        function() {
          var $this = $(this);
          $this.addClass('ddo-sort-processed');
          $this.sortable(
            {
              items: '.ddo-element-sortable',
              placeholder: 'ddo-sort-highlight',
              stop: function(event, ui) {
                var $parent = ui.item.parent();
                var $sortables = $('.ddo-droppable-box', $parent);
                var $values = {};
                for ($index in $sortables) {
                  var $classes = $sortables[$index].className;
                  if ($classes) {
                    var $interest = $classes.match(/ddo-droppable-box--(\d+)/g)[0].split('--');
                    var $box_index = $interest[1] - 1;
                    $values[$index] = $('.form-type-select:hidden:eq(' + $box_index + ') select', $parent).val();
                  }
                }
                for ($index in $values) {
                  if (!isNaN($index)) {
                    $('.form-type-select:hidden:eq(' + $index + ') select', $parent).val($values[$index]);
                  }
                }
                $('#ddo-edit-container-draft').trigger('mousedown');
              }
            }
          );
        }
      );
    }

  };

})(jQuery);
