--TEST--
brunsli_encode() Basic test
--SKIPIF--
<?php
if (!extension_loaded('brunsli')) {
  echo 'skip';
}
?>
--FILE--
<?php
$in = file_get_contents(__DIR__ . '/data/brunsli.jpg');
$actual = brunsli_encode($in);

$expected = file_get_contents(__DIR__ . '/data/brunsli.jpg.brn');

var_dump(strlen($expected) === strlen($actual));
?>
--EXPECT--
bool(true)
