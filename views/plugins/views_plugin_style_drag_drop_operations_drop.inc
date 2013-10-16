<?php

/**
 * @file
 * Contains the option plugin to generate views droppable items.
 */

/**
 * The style plugin class to generate views droppable items.
 *
 * @ingroup views_style_plugins
 */
class views_plugin_style_drag_drop_operations_drop extends views_plugin_style {

  public function option_definition() {

    $options = parent::option_definition();
    $options['operation'] = array('default' => '');
    $options['op_label'] = array('default' => 'Submit');
    $options['label_field'] = array('default' => '');
    $options['rows'] = array('default' => '1');
    $options['cols'] = array('default' => '1');
    $options['required_size'] = array('default' => '0');
    $options['required_size_form'] = array('default' => 'select');
    $options['sortable'] = array('default' => 0);
    $options['element_type'] = array('default' => 'select');
    $options['thumb_disp_mode'] = array('default' => 'full');
    $options['requires_full'] = array('default' => 0);
    $options['flush_submit'] = array('default' => 1);
    return $options;

  }

  public function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);
    $options = array('' => t('- None -'));
    $field_labels = $this->display->handler->get_field_labels(TRUE);
    $options += $field_labels;
    // TO-DO 2.x: Remove dependency!
    $operations = views_bulk_operations_get_applicable_operations($this->view->base_table, array());
    $final_ops = array();
    $final_ops[''] = t('- Select an option -');
    foreach ($operations as $op_key => $op) {
      $final_ops[$op_key] = $op_key;
    }
    $form['operation'] = array(
      '#type' => 'select',
      '#title' => t('Operation'),
      '#required' => TRUE,
      '#options' => $final_ops,
      '#default_value' => $this->options['operation'],
    );
    $form['op_label'] = array(
      '#type' => 'textfield',
      '#title' => t('Operation Label'),
      '#required' => TRUE,
      '#default_value' => $this->options['op_label'],
    );
    $form['rows'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of rows'),
      '#required' => TRUE,
      '#default_value' => $this->options['rows'],
    );
    $form['cols'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of cols'),
      '#required' => TRUE,
      '#default_value' => $this->options['cols'],
    );
    $form['required_size'] = array(
      '#type' => 'radios',
      '#title' => t('Require size selection'),
      '#options' => array(
        0 => t('No'),
        1 => t('Yes'),
      ),
      '#required' => TRUE,
      '#default_value' => $this->options['required_size'],
    );
    $form['required_size_form'] = array(
      '#type' => 'radios',
      '#title' => t('Required size element form'),
      '#options' => array(
        'select' => t('Select list'),
        'radios' => t('Radios'),
      ),
      '#required' => TRUE,
      '#default_value' => $this->options['required_size_form'],
    );
    $form['sortable'] = array(
      '#type' => 'radios',
      '#title' => t('Sortable'),
      '#options' => array(
        0 => t('No'),
        1 => t('Yes'),
      ),
      '#required' => TRUE,
      '#default_value' => $this->options['sortable'],
    );
    $entity_info = entity_get_info($this->view->base_table);
    $entity_modes = $entity_info['view modes'];
    foreach ($entity_modes as $key => $mode) {
      $entity_modes[$key] = $mode['label'];
    }
    $form['thumb_disp_mode'] = array(
      '#type' => 'radios',
      '#title' => t('Thumbnail View mode'),
      '#options' => $entity_modes,
      '#required' => TRUE,
      '#default_value' => $this->options['thumb_disp_mode'],
    );
    $form['requires_full'] = array(
      '#type' => 'radios',
      '#title' => t('Requires to full all the cells before the action'),
      '#options' => array(
        0 => t('No'),
        1 => t('Yes'),
      ),
      '#required' => TRUE,
      '#default_value' => $this->options['requires_full'],
    );
    $form['flush_submit'] = array(
      '#type' => 'radios',
      '#title' => t('Empty stored values on submit'),
      '#options' => array(
        0 => t('No'),
        1 => t('Yes'),
      ),
      '#required' => TRUE,
      '#default_value' => $this->options['flush_submit'],
    );
    $form['label_field'] = array(
      '#type' => 'select',
      '#title' => t('Label field (Without JS)'),
      '#options' => $options,
      '#required' => TRUE,
      '#default_value' => $this->options['label_field'],
    );
    $form['element_type'] = array(
      '#type' => 'radios',
      '#title' => t('Element type (Without JS)'),
      '#options' => array(
        'select' => t('Select list'),
        'radios' => t('Radios'),
      ),
      '#required' => TRUE,
      '#default_value' => $this->options['element_type'],
    );
  }

  public function render($result) {

    $id = $this->view->base_field;
    $entity = $this->view->base_table;

    $allowed_values = array();
    $allowed_values[''] = t('- Select an option -');
    foreach ($this->view->result as $row_index => $row) {
      $allowed_values[$entity . ':' . $row->{$id}]
        = $this->view->field[$this->options['label_field']]->theme($row);
    }

    $form = drupal_get_form(
      'drag_drop_operations_form',
      array(
        'view' => $this->view->name,
        'display' => $this->view->current_display,
        'entity' => $entity,
        'op' => $this->options['operation'],
        'rows' => $this->options['rows'],
        'cols' => $this->options['cols'],
        'allowed_values' => $allowed_values,
        'element_type' => $this->options['element_type'],
        'op_label' => $this->options['op_label'],
        'view_mode' => $this->options['thumb_disp_mode'],
        'full' => $this->options['requires_full'],
        'flush' => $this->options['flush_submit'],
        'required_size' => $this->options['required_size'],
        'required_size_form' => $this->options['required_size_form'],
        'sortable' => $this->options['sortable'],
        'redraggable' => $this->view->display_handler->get_option('ddo_draggable'),
      )
    );
    return render($form);

  }

}
