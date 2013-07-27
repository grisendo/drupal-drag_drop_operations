<?php

function drag_drop_operations_views_plugins() {

  $path = drupal_get_path('module', 'drag_drop_operations') . '/views';
  return array(
    'module' => 'drag_drop_operations',
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
    'display_extender' => array(
      'views_plugin_display_extender_drag_drop_operations_drag' => array(
        'title' => t('Drag and drop operations: Drag'),
        'uses options' => TRUE,
        'help' => t('Drag and drop operations: Draggable.'),
        'handler' => 'views_plugin_display_extender_drag_drop_operations_drag',
        'path' => $path . '/plugins',
      ),
    ),
  );

}
