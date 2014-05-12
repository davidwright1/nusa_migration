<?php

/*
 * @file
 * Migration registry info.
 */

/**
 * Implements hook_migrate_api().
 */
function nusa_migration_migrate_api() {
  return array(
    'api' => 2,
    'groups' => array(
      'nusa_migration' => array(
        'title' => array(t('NumbersUSA Migrations')),
      ),
    ),
    'migrations' => array(
      'NusaProfile' => array(
        'class_name' => 'NusaProfileMigration',
      ),
      'NusaOrder' => array(
        'class_name' => 'NusaOrderMigration',
      ),
      'NusaLineItem' => array(
        'class_name' => 'NusaLineItemMigration',
      ),
    ),
  );
}