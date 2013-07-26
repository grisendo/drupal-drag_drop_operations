<?php

class views_plugin_style_drag_drop_operations extends views_plugin_style {

  function option_definition() {

    $options = parent::option_definition();
    $options['operation'] = array('default' => '');
    $options['label_field'] = array('default' => '');
    $options['element_type'] = array('default' => 'select');
    $options['substyle'] = array('default' => 'default');
    $options['elements'] = array('default' => '1');
    $options['type'] = array('default' => 'ul');
    $options['class'] = array('default' => '');
    $options['wrapper_class'] = array('default' => 'item-list');
    $options['columns'] = array('default' => '4');
    $options['alignment'] = array('default' => 'horizontal');
    $options['fill_single_line'] = array('default' => TRUE, 'bool' => TRUE);
    $options['summary'] = array('default' => '');
    $options['caption'] = array('default' => '');
    return $options;

  }

  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);
    $options = array('' => t('- None -'));
    $field_labels = $this->display->handler->get_field_labels(TRUE);
    $options += $field_labels;
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
    $form['label_field'] = array(
      '#type' => 'select',
      '#title' => t('Label field'),
      '#options' => $options,
      '#required' => TRUE,
      '#default_value' => $this->options['label_field'],
    );
    $form['elements'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of elements'),
      '#required' => TRUE,
      '#default_value' => $this->options['elements'],
    );
    $form['element_type'] = array(
      '#type' => 'radios',
      '#title' => t('Element type'),
      '#options' => array(
        'select' => t('Select list'),
        'radios' => t('Radios'),
      ),
      '#required' => TRUE,
      '#default_value' => $this->options['element_type'],
    );
    $form['substyle'] = array(
      '#type' => 'radios',
      '#title' => t('Style'),
      '#options' => array(
        'default' => t('Unformatted'),
        'list' => t('HTML list'),
        'grid' => t('Grid'),
      ),
      '#required' => TRUE,
      '#default_value' => $this->options['substyle'],
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
      $this->options['elements'],
      $allowed_values,
      $this->options['element_type']      
    );
    return render($form);

  }

}
