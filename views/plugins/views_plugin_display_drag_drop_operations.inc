<?php

class views_plugin_display_drag_drop_operations extends views_plugin_display_attachment {

  /*function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
    $row_plugins = views_fetch_plugin_names('row', $this->get_style_type(), array($view->base_table));
    $default_row_plugin = key($row_plugins);
    if ($this->options['row_plugin'] == '') {
      $this->options['row_plugin'] = $default_row_plugin;
    }
  }

  function uses_breadcrumb() {
    return FALSE;
  }

  function execute() {
    $output = $this->view->render();
    if (empty($output)) {
      return drupal_not_found();
    }
    print $output;
  }*/

  function preview() {
    if (!empty($this->view->live_preview)) {
      return $this->view->render();
    }
    return $this->view->render();
  }

  function render() {
    return $this->view->style_plugin->render($this->view->result);
  }

  /*function defaultable_sections($section = NULL) {
    if (in_array($section, array('style_options', 'style_plugin', 'row_options', 'row_plugin'))) {
      return FALSE;
    }
    $sections = parent::defaultable_sections($section);
    if ($section == 'title') {
      $sections[] = 'sitename_title';
    }
    elseif (!$section) {
      $sections['title'][] = 'sitename_title';
    }
    return $sections;
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['displays'] = array('default' => array());
    $options['style_plugin']['default'] = 'drag_drop_operations';
    $options['style_options']['default']  = array('description' => '');
    $options['sitename_title']['default'] = FALSE;
    $options['row_plugin']['default'] = '';
    $options['defaults']['default']['style_plugin'] = FALSE;
    $options['defaults']['default']['style_options'] = FALSE;
    $options['defaults']['default']['row_plugin'] = FALSE;
    $options['defaults']['default']['row_options'] = FALSE;
    return $options;
  }

  function options_summary(&$categories, &$options) {
    parent::options_summary($categories, $options);
    $categories['page'] = array(
      'title' => t('Settings'),
      'column' => 'second',
      'build' => array(
        '#weight' => -10,
      ),
    );

    if ($this->get_option('sitename_title')) {
      $options['title']['value'] = t('Using the site name');
    }
    unset($options['menu']);
    $displays = array_filter($this->get_option('displays'));
    if (count($displays) > 1) {
      $attach_to = t('Multiple displays');
    }
    elseif (count($displays) == 1) {
      $display = array_shift($displays);
      if (!empty($this->view->display[$display])) {
        $attach_to = check_plain($this->view->display[$display]->display_title);
      }
    }
    if (!isset($attach_to)) {
      $attach_to = t('None');
    }
    $options['displays'] = array(
      'category' => 'page',
      'title' => t('Attach to'),
      'value' => $attach_to,
    );
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    switch ($form_state['section']) {
      case 'title':
        $title = $form['title'];
        unset($form['title']);
        $form['sitename_title'] = array(
          '#type' => 'checkbox',
          '#title' => t('Use the site name for the title'),
          '#default_value' => $this->get_option('sitename_title'),
        );
        $form['title'] = $title;
        $form['title']['#dependency'] = array('edit-sitename-title' => array(FALSE));
        break;
      case 'displays':
        $form['#title'] .= t('Attach to');
        $displays = array();
        foreach ($this->view->display as $display_id => $display) {
          if (!empty($display->handler) && $display->handler->accept_attachments()) {
            $displays[$display_id] = $display->display_title;
          }
        }
        $form['displays'] = array(
          '#type' => 'checkboxes',
          '#description' => t('The feed icon will be available only to the selected displays.'),
          '#options' => $displays,
          '#default_value' => $this->get_option('displays'),
        );
        break;
      case 'path':
        $form['path']['#description'] = t('This view will be displayed by visiting this path on your site. It is recommended that the path be something like "path/%/%/feed" or "path/%/%/rss.xml", putting one % in the path for each contextual filter you have defined in the view.');
    }
  }

  function options_submit(&$form, &$form_state) {
    parent::options_submit($form, $form_state);
    switch ($form_state['section']) {
      case 'title':
        $this->set_option('sitename_title', $form_state['values']['sitename_title']);
        break;
      case 'displays':
        $this->set_option($form_state['section'], $form_state['values'][$form_state['section']]);
        break;
    }
  }

  function uses_link_display() {
    return TRUE;
  }*/

}
