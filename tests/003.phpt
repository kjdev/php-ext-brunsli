--TEST--
brunsli_decode() Basic test
--SKIPIF--
<?php
if (!extension_loaded('brunsli')) {
  echo 'skip';
}
?>
--FILE--
<?php
$in = file_get_contents(__DIR__ . '/data/brunsli.jpg.brn');
$actual = brunsli_decode($in);

$expected = file_get_contents(__DIR__ . '/data/brunsli.jpg');

var_dump(strlen($expected) === strlen($actual));
?>
--EXPECT--
bool(true)
