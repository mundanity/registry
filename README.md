# REST API

[![Scrutinizer Code Quality](https://scrutinizer-ci.com/g/mundanity/registry/badges/quality-score.png?b=master)](https://scrutinizer-ci.com/g/mundanity/registry/?branch=master)

The registry module provides hooks for other services and dependencies to register themselves. Registered components can be viewed and managed in a single location.

This module is helpful for Drupal installations that use a lot of dependencies, and struggle to determine what state the service is in, and where it's currently configured to (e.g. are my logging services pointed to a production environment when they should not be?). 
