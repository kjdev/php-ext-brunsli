--TEST--
brunsli_encode/decode() Basic test
--SKIPIF--
<?php
if (!extension_loaded('brunsli')) {
  echo 'skip';
}
?>
--FILE--
<?php
$in = file_get_contents(__DIR__ . '/data/brunsli.jpg');
$encode = brunsli_encode($in);
$actual = brunsli_decode($encode);

$expected = file_get_contents(__DIR__ . '/data/brunsli.jpg');

var_dump(strlen($expected) === strlen($actual));
?>
--EXPECT--
bool(true)
