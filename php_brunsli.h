/* brunsli extension for PHP */

#ifndef PHP_BRUNSLI_H
# define PHP_BRUNSLI_H

extern zend_module_entry brunsli_module_entry;
# define phpext_brunsli_ptr &brunsli_module_entry

# define PHP_BRUNSLI_VERSION "0.1.0"

/* brunsl includes */
#include <brunsli/encode.h>
#include <brunsli/decode.h>

# if defined(ZTS) && defined(COMPILE_DL_BRUNSLI)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif /* PHP_BRUNSLI_H */
