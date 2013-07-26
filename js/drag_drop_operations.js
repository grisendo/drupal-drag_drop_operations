(function($) {

  Drupal.behaviors.tmpDragDropOperationsDrag = {

    attach: function(context, settings) {
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
          var $placeholder = $('<div></div>');
          $placeholder.css(
            {
              width: '150px',
              height: '150px',
              border: '1px solid #000'
            }
          );
          $this.addClass('ddo-processed');
          $this.parent().after($placeholder);
          $this.parent().hide();
          $placeholder.droppable(
            {
              hoverClass: 'drop-hover',
              drop: function(e, ui) {
                var $this = $(this);
                var $clone = $(ui.draggable).clone();
                $clone.removeClass('ui-draggable');
                $clone.draggable();
                $this.html($clone);
                $that.val('node:52');
                $('#edit-draft').trigger('mousedown');
              },
              out: function(e, ui) {
                $that.val('');
                $('#edit-draft').trigger('mousedown');
              }
            }
          );
          if ($val) {
            $val = $val.replace(':', '--');
            console.log($val);
            $val = $('.ddo--' + $val);
            if ($val) {
              $placeholder.html($val.clone());
            }
          }
        }
      );

    }

  };

})(jQuery);
