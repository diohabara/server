#ifndef WOLFSSL_USER_SETTINGS_H
#define WOLFSSL_USER_SETTINGS_H

#define HAVE_CRL
#define WOLFSSL_HAVE_ERROR_QUEUE
#define WOLFSSL_MYSQL_COMPATIBLE
#define HAVE_ECC
#define ECC_TIMING_RESISTANT
#define HAVE_HASHDRBG
#define WOLFSSL_AES_DIRECT
#define WOLFSSL_SHA384
#define WOLFSSL_SHA512
#define WOLFSSL_SHA224
#define SESSION_CERT
#define KEEP_OUR_CERT
#define WOLFSSL_STATIC_RSA
#define WOLFSSL_USER_IO
#define WC_RSA_BLINDING
#define HAVE_TLS_EXTENSIONS
#define HAVE_AES_ECB
#define HAVE_AESGCM
#define WOLFSSL_AES_COUNTER
#define NO_WOLFSSL_STUB
#define OPENSSL_ALL
#define WOLFSSL_ALLOW_TLSV10
#define NO_OLD_TIMEVAL_NAME

/* TLSv1.3 definitions (all needed to build) */
#define WOLFSSL_TLS13
#define HAVE_HKDF
#define HAVE_TLS_EXTENSIONS
#define HAVE_SUPPORTED_CURVES
#define HAVE_FFDHE_2048
#define WC_RSA_PSS
/* End of TLSv1.3 defines */

/* Features we exclude */
#define NO_DSA
#define NO_HC128
#define NO_MD4
#define NO_PSK
#define NO_RABBIT
#define NO_RC4

/*
  FP_MAX_BITS is set high solely to satisfy ssl_8k_key.test
  WolfSSL will use more stack space with it, with fastmath
*/
#define FP_MAX_BITS 16384
#define WOLFSSL_AESNI
#define USE_FAST_MATH
#define TFM_TIMING_RESISTANT
#define HAVE_INTEL_RDSEED
#define HAVE_INTEL_RDRAND
#define USE_INTEL_SPEEDUP
#define USE_FAST_MATH
#define WOLFSSL_X86_64_BUILD

#endif  /* WOLFSSL_USER_SETTINGS_H */
