# Install script for directory: /root/esp-idf/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aesni.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/arc4.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/blowfish.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/bn_mul.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/certs.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cipher_internal.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/compat-1.3.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecp_internal.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/entropy_poll.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/havege.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md2.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md4.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md_internal.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/padlock.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pk_internal.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs11.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/rsa_internal.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_internal.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    "/root/esp-idf/components/mbedtls/mbedtls/include/mbedtls/xtea.h"
    )
endif()

