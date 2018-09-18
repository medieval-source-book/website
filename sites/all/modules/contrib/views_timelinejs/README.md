Views TimelineJS
================
This module adds a new style plugin for Views which renders result rows as
TimelineJS slides and eras.  The 7.x-3.x branch was created to work with the
TimelineJS3 version of the library.  For more information about TimelineJS visit
https://timeline.knightlab.com/index.html or the GitHub repository
https://github.com/NUKnightLab/TimelineJS3.

Installation
------------
Download the module from http://drupal.org/project/views_timelinejs and enable
it.  By default, there are no library files to download because they are served
from the NU Knight Lab CDN.

Optional: If you want to serve the library files from your own site instead of
the CDN, then you need to download the library files.  You MUST put the
TimelineJS library in the sites/all/libraries directory inside your Drupal
installation.  Alternate library locations such as those checked by the
Libraries API module will not work.

You can download or clone the entire TimelineJS3 GitHub repository.
```
git clone --branch master https://github.com/NUKnightLab/TimelineJS3.git
```

If you don't want to download the entire repository, then you can download the
Javascript and CSS files selectively.  The timeline.js and timeline.css files
are required to use TimelineJS.  The library also includes several font
library CSS files that must be downloaded if you want to use them.  In the end,
you need to have the following files in these directories:

1. sites/all/libraries/TimelineJS3/compiled/js/timeline.js
2. sites/all/libraries/TimelineJS3/compiled/css/timeline.css
3. sites/all/libraries/TimelineJS3/compiled/css/fonts/font.FONT-NAME.css
   (optional)

Finally, visit the admin settings form admin/config/development/views_timelinejs
to change the library location setting to Local path.

Upgrading
---------
If you are upgrading this module from version 7.x-1.x then make sure you test
your view and reconfigure it before deploying to a production environment!  Much
of the plugin's functionality was changed in the upgrade to TimelineJS3.
Version 3 of the library offers several nice enhancements over version 2.  The
plugin has received a lot of updates in order to take full advantage of the new
library.  Some settings have been changed or removed.  New settings have been
added.  The fact that the Date field setting has been split into separate Start
date and End date field settings means that all existing views that were built
with version 7.x-1.x will need to be reconfigured for 7.x-3.x.

Configuring the Plugin
----------------------
Configuring this plugin can be a challenge.  That's because TimelineJS has a
large number of data fields and settings.  This is especially true for setting
up media fields.  Extensive documentation has been written to help guide you in
this process.  Please don't try to do it alone!

The configuration documentation is maintained on Drupal.org.  Don't be concerned
that the documentation says it was written for the Drupal 8 version.  The 3.x
branches of this module have identical feature sets.  Any differences in how the
branches have to be configured are noted.  The available documentation includes:

* [How to install and use Views TimelineJS](
https://www.drupal.org/docs/8/modules/views-timelinejs/how-to-install-and-use-views-timelinejs
)
* [The types of field data that TimelineJS expects](
https://www.drupal.org/docs/8/modules/views-timelinejs/configuring-the-plugin)
* [Date and time formats that can be parsed by the plugin](
https://www.drupal.org/docs/8/modules/views-timelinejs/date-and-time-formats)
* [Configuring your site and view to use different types of media](
https://www.drupal.org/docs/8/modules/views-timelinejs/media-field-configuration
)

Maintainers
-----------
* Juha Niemi (juhaniemi)
* Olli Erinko (operinko)
* Jon Peck (fluxsauce)
* WorldFallz
* David Cameron (dcam)
