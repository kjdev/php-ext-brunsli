/* brunsli extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "ext/standard/php_smart_string.h"
#include "php_brunsli.h"
#include "brunsli_arginfo.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
  ZEND_PARSE_PARAMETERS_START(0, 0)  \
  ZEND_PARSE_PARAMETERS_END()
#endif

static size_t php_brunsli_output_smart_string(void* data,
                                              const unsigned char* buf,
                                              const size_t count)
{
  smart_string* str = (smart_string*) data;
  smart_string_appendl(str, buf, count);
  return count;
}


ZEND_FUNCTION(brunsli_encode)
{
  int argc = ZEND_NUM_ARGS();
  char* in;
  size_t in_len;
  smart_string out = {0};

  if (zend_parse_parameters(argc, "s", &in, &in_len) == FAILURE) {
    RETURN_FALSE;
  }

  if (EncodeBrunsli(in_len, (unsigned char*)in, &out,
                    php_brunsli_output_smart_string) != 1) {
    php_error_docref(NULL, E_WARNING, "Encodes brunsli failed\n");
    RETURN_FALSE;
  }

  RETVAL_STRINGL(out.c, out.len);

  smart_string_free(&out);
}

ZEND_FUNCTION(brunsli_decode)
{
  int argc = ZEND_NUM_ARGS();
  char* in;
  size_t in_len;
  smart_string out = {0};

  if (zend_parse_parameters(argc, "s", &in, &in_len) == FAILURE) {
    return;
  }

  if (DecodeBrunsli(in_len, (unsigned char*)in, &out,
                    php_brunsli_output_smart_string) != 1) {
    php_error_docref(NULL, E_WARNING, "Decodes brunsli failed\n");
    smart_string_free(&out);
    RETURN_FALSE;
  }

  RETVAL_STRINGL(out.c, out.len);

  smart_string_free(&out);
}


ZEND_RINIT_FUNCTION(brunsli)
{
#if defined(ZTS) && defined(COMPILE_DL_BRUNSLI)
  ZEND_TSRMLS_CACHE_UPDATE();
#endif

  return SUCCESS;
}

ZEND_MINFO_FUNCTION(brunsli)
{
  php_info_print_table_start();
  php_info_print_table_header(2, "brunsli support", "enabled");
  php_info_print_table_end();
}

zend_module_entry brunsli_module_entry = {
  STANDARD_MODULE_HEADER,
  "brunsli",            /* Extension name */
  brunsli_functions,    /* zend_function_entry */
  NULL,                 /* ZEND_MINIT - Module initialization */
  NULL,                 /* ZEND_MSHUTDOWN - Module shutdown */
  ZEND_RINIT(brunsli),  /* ZEND_RINIT - Request initialization */
  NULL,                 /* ZEND_RSHUTDOWN - Request shutdown */
  ZEND_MINFO(brunsli),  /* ZEND_MINFO - Module info */
  PHP_BRUNSLI_VERSION,  /* Version */
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_BRUNSLI
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(brunsli)
#endif
