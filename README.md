# Brunsli Extension for PHP

This extension allows Brunsli.

Documentation for Brunsli can be found at
[» https://github.com/google/brunsli/](https://github.com/google/brunsli/).


## Build

``` bash
% phpize
% ./configure --with-brunsli={DIR}
% make
$ make install
```

> DIR: brunsli include and library directory
>
> ```
> [DIR]
> |-- include
> |   `-- brunsli
> |       |-- decode.h
> |       |-- encode.h
> |       `-- types.h
> `-- lib
>     |-- libbrunslidec-c.so
>     `-- libbrunslienc-c.so
> ```

## Configuration

brunsli.ini:

```
extension=brunsli.so
```

## Function

* brunsli\_encode — Brunsli encodes a string
* brunsli\_decode — Brunsli decodes a string

---
### brunsli\_encode — Brunsli encodes a string

#### Description

string **brunsli\_encode** ( string _$data_ )

This function brunsli encodes a string.

#### Parameters

* _data_

  The JPEG data.

#### Return Values

The brunsli encoded data or FALSE if an error occurred.

---
### brunsli\_decode — Brunsli decodes a string

#### Description

string **brunsli\_decode** ( string _$data_ )

This function brunsli decodes a string.

#### Parameters

* _data_

  The Brunsli encodes data.

#### Return Values

The brunsli decoded data (JPEG data) or FALSE if an error occurred.

## Examples

``` php
/* encode */
$data = file_get_contents('brunsli.jpg'); /* load jpeg data */

$encode = brunsli_encode($data);

file_put_contents('output.brn', $encode); /* output brunsli encode data */

/* decode */
$data = file_get_contents('brunsli.jpg.brn'); /* load brunsli encode data */

$decode = brunsli_decode($data);

file_put_contents('output.jpg', $decode); /* output jpeg data */
```
