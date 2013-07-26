<?php

function drag_drop_operations_views_plugins() {

  $path = drupal_get_path('module', 'drag_drop_operations') . '/views';
  return array(
    'module' => 'drag_drop_operations',
    'display' => array(
      'drag_drop_operations' => array(
        'title' => t('Drag drop operations'),
        'help' => t('Drag drop operations.'),
        'handler' => 'views_plugin_display_drag_drop_operations',
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
        'admin' => t('Drag drop operations'),
      ),
    ),
    'style' => array(
      'drag_drop_operations' => array(
        'title' => t('Drag drop operations'),
        'help' => t('Drag drop operations.'),
        'theme' => 'views_view_unformatted',
        'handler' => 'views_plugin_style_drag_drop_operations',
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'uses fields' => TRUE,
        'type' => 'normal', // TO-DO: Sólo para DDO
        'path' => $path . '/plugins',
      ),
    ),
  );

}
