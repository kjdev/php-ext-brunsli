--TEST--
Check if brunsli is loaded
--SKIPIF--
<?php
if (!extension_loaded('brunsli')) {
  echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "brunsli" is available';
?>
--EXPECT--
The extension "brunsli" is available
