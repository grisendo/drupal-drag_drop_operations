<?php

/**
 * @file
 * Contains the option plugin to make views rows draggable.
 */

/**
 * The option plugin class to make views rows draggable.
 *
 * @ingroup views_display_plugins
 */
class views_plugin_display_extender_drag_drop_operations_drag extends views_plugin_display_extender {

  /**
   * Provide a form to edit options for this plugin. 
   */
  public function options_definition_alter(&$options) {
    $options['ddo_draggable'] = array('default' => 0);
    return $options;
  }

  /**
   * Provide the form to set new option.
   */
  public function options_form(&$form, &$form_state) {

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
  public function options_submit(&$form, &$form_state) {
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
   * Lists the fields as either 'Yes' if there is text or 'No' otherwise and
   * categorizes the fields under the 'Format' category.
   */
  public function options_summary(&$categories, &$options) {
    $ddo = $this->display->get_option('ddo_draggable');
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
