
ZEND_BEGIN_ARG_INFO_EX(arginfo_brunsli_encode, 0, 0, 1)
  ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_brunsli_decode, 0, 0, 1)
  ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(brunsli_encode);
ZEND_FUNCTION(brunsli_decode);


static const zend_function_entry brunsli_functions[] = {
  ZEND_FE(brunsli_encode, arginfo_brunsli_encode)
  ZEND_FE(brunsli_decode, arginfo_brunsli_decode)
  ZEND_FE_END
};
