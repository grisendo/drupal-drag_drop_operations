(function($) {

  Drupal.behaviors.tmpDragDropOperationsDrag = {

    attach: function(context, settings) {
      // TO-DO: Style en Vista
      $('.views-view-grid td', context).draggable(
        {
          helper: 'clone'
        }
      );
    }

  };

  Drupal.behaviors.dragDropOperationsDrop = {

    attach: function(context, settings) {

      $('.ddo-droppable:not(.ddo-processed)', context).each(
        function() {
          var $this = $(this);
          var $val = $this.val();
          var $that = $this;
          var $placeholder = $this.parent().next();
          $this.parent().hide();
          var $remove = $placeholder.find('.ddo-remove-item');
          if ($remove.length) {
            $remove.bind(
              'click',
              function() {
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
                $placeholder.addClass('ajax-loading');
                // TO-DO: Style en Vista
                $that.val('node:52');
                $('#ddo-edit-container-draft').trigger('mousedown');
              }
            }
          );
        }
      );

    }

  };

})(jQuery);
