<?php

/*
 * @file
 * Order migration for NUSA.
 */
class NusaOrderMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    
    $this->description = t("NumbersUSA Orders Migration");
    $this->dependencies = array();
    
    // Create the CSV source.
    $options = array(
      'header_rows' => 1,
    );
    $this->source = new MigrateSourceCSV(
      'private://nusa_migration.csv',
      $this->csvcolumns(),
      $options
      );
    
    // Create destination.
    $this->destination = new MigrateDestinationEntityAPI('commerce_order', 'commerce_order');
    
    // Create the map.
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        // enter  unique key for source
        'unique_id' => array(
          'type' => 'int',
          'description' => 'Universal Unique ID for CSV',
        ),
      ),
      $this->destination->getKeySchema('commerce_order', 'commerce_order')
    );
    
    // Field mappings.
    $this->addFieldMapping('mail', 'order_owner_email');
    $this->addFieldMapping('created', 'order_created_date');
    //$this->addFieldMapping('commerce_order_total', 'order_total');
    $this->addFieldMapping('field_in_honor_of', 'order_in_honor_of');
    $this->addFieldMapping('field_donation_allocation', 'order_donation_allocation');
    $this->addFieldMapping('field_is_donation', 'order_is_donation');
    $this->addFieldMapping('field_jid', 'order_jid');
    $this->addFieldMapping('field_processor_uid', 'order_processor_email'); // TODO: go from email to uid.
    $this->addFieldMapping('field_legacy_payment_method', 'order_payment_method');
    $this->addFieldMapping('field_legacy_transaction_id', 'order_transaction_id');
    $this->addFieldMapping('commerce_customer_billing', ''); // TODO: reference to the unique_id field from CSV on billing profiles which should already be migrated.
    $this->addFieldMapping('status', ''); // default Value needed
    $this->addFieldMapping('field_legacy_which_account', 'order_which_account');
    
    // Unmigrated Destinations.
    
    // Unmigrated Sources.
  }

  public function csvcolumns() {
    $columns = array();
    
    $columns[0] = array('unique_id', 'Universal Unique ID');
    $columns[1] = array('order_owner_email', 'Email of order\'s owner');
    $columns[2] = array ('order_status', 'Order Status');
    $columns[3] = array('order_created_date', 'Order Creation Timestampe');
    $columns[4] = array('order_in_honor_of', 'Order In Honor Of');
    $columns[5] = array('order_donation_allocation', 'Donation Allocation');
    $columns[6] = array('order_is_donation', 'Order a Donation');
    $columns[7] = array('order_jid', 'Order JID');
    $columns[8] = array('order_processor_email', 'Order\'s Processor Email');
    $columns[9] = array('order_payment_method', 'Payment Method');
    $columns[10] = array('order_transaction_id', 'Transaction ID');
    $columns[11] = array('line_item_quantity', 'LI Quantity');
    $columns[12] = array('line_item_unit_price', 'LI Unit Price');
    $columns[13] = array('line_item_title', 'LI Title');
    $columns[14] = array('country', 'Profile Country');
    $columns[15] = array('address1', 'Profile Address 1');
    $columns[16] = array('address2', 'Profile Address 2');
    $columns[17] = array('city', 'Profile City');
    $columns[18] = array('state', 'Profile State');
    $columns[19] = array('zip_code', 'Profile ZIP Code');
    $columns[20] = array('first_name', 'Profile First Name');
    $columns[21] = array('last_name', 'Profile Last Name');
    $columns[22] = array('company', 'Profile Company');
    $columns[23] = array('phone_number', 'Profile Phone Number');
    $columns[24] = array('order_which_account', 'Contribution to which fund');
  }
}
