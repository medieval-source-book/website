<?php
/**
 * @file
 * submissions.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function submissions_default_rules_configuration() {
  $items = array();
  $items['rules_new_submission'] = entity_import('rules_config', '{ "rules_new_submission" : {
      "LABEL" : "New Submission",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--submission" : { "bundle" : "submission" } },
      "DO" : [
        { "mail" : {
            "to" : "starkey@stanford.edu, maelp@stanford.edu",
            "subject" : "GMS: New submission",
            "message" : "There is a new submission to the Global Medieval Sourcebook: [node:url]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
