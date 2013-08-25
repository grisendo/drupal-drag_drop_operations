(function($) {

  Drupal.behaviors.tmpDragDropOperationsDrag = {

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

      $('#ddo-edit-container-draft:not(.element-hidden)', context).hide();

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
                $placeholder.addClass('ddo-ajax-loading');
                $that.val($element.attr('data-entitytype') + ':' + $element.attr('data-entityid'));
                $('#ddo-edit-container-draft').trigger('mousedown');
              }
            }
          );
        }
      );

    }

  };

})(jQuery);
