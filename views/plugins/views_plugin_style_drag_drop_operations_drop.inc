<?php

class views_plugin_style_drag_drop_operations_drop extends views_plugin_style {

  function option_definition() {

    $options = parent::option_definition();
    $options['operation'] = array('default' => '');
    $options['op_label'] = array('default' => 'Submit');
    $options['label_field'] = array('default' => '');
    $options['rows'] = array('default' => '1');
    $options['cols'] = array('default' => '1');
    $options['element_type'] = array('default' => 'select');
    $options['thumb_disp_mode'] = array('default' => 'full');
    $options['requires_full'] = array('default' => 0);
    $options['flush_submit'] = array('default' => 1);
    return $options;

  }

  function options_form(&$form, &$form_state) {

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

  function render($result) {

    $id = $this->view->base_field;
    $entity = $this->view->base_table;

    $allowed_values = array();
    $allowed_values[''] = t('- Select an option -');
    foreach ($this->view->result as $row_index => $row) {
      $allowed_values[$entity . ':' . $row->{$id}] =
        $this->view->field[$this->options['label_field']]->theme($row);
    }

    $form = drupal_get_form(
      'drag_drop_operations_form',
      $this->view->name,
      $this->view->current_display,
      $entity,
      $this->options['operation'],
      $this->options['rows'],
      $this->options['cols'],
      $allowed_values,
      $this->options['element_type'],
      $this->options['op_label'],
      $this->options['thumb_disp_mode'],
      $this->options['requires_full'],
      $this->options['flush_submit'],
      $this->view->display_handler->get_option('ddo_draggable')
    );
    return render($form);

  }

}
