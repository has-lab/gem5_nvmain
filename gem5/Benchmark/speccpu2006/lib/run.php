#!/usr/bin/php -q
<?php
// Copyright 2014 CloudHarmony Inc.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * run script for SPEC CPU 2006 testing
 */
require_once(dirname(__FILE__) . '/SpecCpu2006Test.php');

$test = new SpecCpu2006Test();
$options = $test->getRunOptions();
$verbose = isset($options['verbose']) && $options['verbose'];

// invalid run argument
if ($invalid = $test->validateRunOptions($options)) {
  foreach($invalid as $arg => $err) print_msg(sprintf('argument --%s is invalid - %s', $arg, $err), $verbose, __FILE__, __LINE__, TRUE);
  exit(1);
}

print_msg(sprintf('Starting SPEC CPU 2006 test'), $verbose, __FILE__, __LINE__);
$status = $test->test() ? 0 : 1;
print_msg(sprintf('Exiting SPEC CPU 2006 test with status code %d', $status), $verbose, __FILE__, __LINE__);

exit($status);
?>
