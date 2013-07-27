<?php

class views_plugin_display_extender_drag_drop_operations_drag extends views_plugin_display_extender {

  /** 
   * Provide a form to edit options for this plugin. 
   */
  function options_definition_alter(&$options) {
    $options['ddo_draggable'] = array('default' => 0);
    return $options;
  }

  /**
   * Provide the form to set new option.
   */
  function options_form(&$form, &$form_state) {
    switch ($form_state['section']) {
      case 'ddo_draggable':
        $form['#title'] .= t('Drag and Drop operations: Draggable');
        $form['ddo_draggable'] = array(
          '#type' => 'radios',
          '#options' => array(
            0 => t('No'),
            1 => t('Yes'),
          ),
          '#default_value' => $this->options['ddo_draggable'],
        );
        break;
      default:
        break;
    }
  }

  /**
   * Inserts the code into the view display.
   */
  function options_submit(&$form, &$form_state) {
    $ddo = $form_state['values']['ddo_draggable'];
    switch ($form_state['section']) {
      case 'ddo_draggable':
        $this->display->set_option('ddo_draggable', $ddo);
        break;
    } 
  }

  /**
   * Summarizes new option.
   * 
   * Lists the fields as either 'Yes' if there is text or 'None' otherwise and
   * categorizes the fields under the 'Other' category.
   */
  function options_summary(&$categories, &$options) {
    $ddo = check_plain(trim($this->display->get_option('ddo_draggable')));
    if ($ddo) {
      $ddo = t('Yes');
    }
    else {
      $ddo = t('No');
    }
    $options['ddo_draggable'] = array(
      'category' => 'format',
      'title' => t('Drag and Drop operations: Draggable'),
      'value' => $ddo,
    );
  }

}
