<?php

function drag_drop_operations_views_plugins() {

  $path = drupal_get_path('module', 'drag_drop_operations') . '/views';
  return array(
    'module' => 'drag_drop_operations',
    'style' => array(
      'views_plugin_style_drag_drop_operations_drag' => array(
        'title' => t('Drag drop operations: Drag'),
        'help' => t('Drag drop operations: Drag.'),
        'theme' => 'views_view_unformatted',
        'handler' => 'views_plugin_style_drag_drop_operations_drag',
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => TRUE,
        'uses fields' => TRUE,
        'type' => 'normal',
        'path' => $path . '/plugins',
      ),
    ),
    'style' => array(
      'views_plugin_style_drag_drop_operations_drop' => array(
        'title' => t('Drag drop operations: Drop'),
        'help' => t('Drag drop operations: Drop.'),
        'theme' => 'views_view_unformatted',
        'handler' => 'views_plugin_style_drag_drop_operations_drop',
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'uses fields' => TRUE,
        'type' => 'normal',
        'path' => $path . '/plugins',
      ),
    ),
  );

}
