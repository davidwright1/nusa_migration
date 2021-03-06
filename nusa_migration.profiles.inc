<?php

/*
 * @file
 * Billing profile migration for NumbersUSA.
 */
class NusaProfileMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    
    $this->description = t("NumbersUSA Billing Profiles Migration");
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
    $this->destination = new MigrateDestinationEntityAPI('commerce_customer_profile', 'billing');
    
    // Create the map.
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        // enter  unique key for source
        'unique_id' => array(
          'type' => 'int',
          'description' => 'Universal unique ID of CSV',
        ),
      ),
      $this->destination->getKeySchema('commerce_customer_profile', 'commerce_customer_billing')
    );

    // Field mappings.
    $this->addFieldMapping('field_billing_phone_number', 'phone_number');
    $this->addFieldMapping('uid', ''); // UNSURE.  We'll see.
    $this->addFieldMapping('commerce_customer_address', 'country');
    $this->addFieldMapping('commerce_customer_address:thoroughfare', 'address1');
    $this->addFieldMapping('commerce_customer_address:premise', 'address2');
    $this->addFieldMapping('commerce_customer_address:locality', 'city');
    $this->addFieldMapping('commerce_customer_address:administrative_area', 'state');
    $this->addFieldMapping('commerce_customer_address:postal_code', 'zip_code');
    $this->addFieldMapping('commerce_customer_address:first_name', 'first_name');
    $this->addFieldMapping('commerce_customer_address:last_name', 'last_name');
   // $this->addFieldMapping('commerce_customer_address:name_line',);  TODO:  will require some shenanigans.
    
    // Unmigrated destinations.
    
    // Unmigrated sources.
    
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
