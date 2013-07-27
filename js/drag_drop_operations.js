(function($) {

  Drupal.behaviors.tmpDragDropOperationsDrag = {

    attach: function(context, settings) {
      $('.ddo-draggable-set').draggable(
        {
          helper: 'clone'
        }
      );
      // TO-DO: Style en Vista
      $('.views-view-grid td').draggable(
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
          $placeholder.droppable(
            {
              hoverClass: 'drop-hover',
              drop: function(e, ui) {
                /*var $this = $(this);
                var $clone = $(ui.draggable).clone();
                $clone.removeClass('ui-draggable');
                $clone.draggable();
                $this.html($clone);*/
                // TO-DO: Style en Vista
                $that.val('node:52');
                $('#edit-draft').trigger('mousedown');
              },
              out: function(e, ui) {
                $that.val('');
                $('#edit-draft').trigger('mousedown');
              }
            }
          );
        }
      );

    }

  };

})(jQuery);
