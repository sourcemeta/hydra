if(NOT CURL_FOUND)
  set(CURL_DIR "${PROJECT_SOURCE_DIR}/vendor/curl")

  # HTTP only
  set(CURL_DISABLE_DICT 1)
  set(CURL_DISABLE_FILE 1)
  set(CURL_DISABLE_FTP 1)
  set(CURL_DISABLE_GOPHER 1)
  set(CURL_DISABLE_IMAP 1)
  set(CURL_DISABLE_LDAP 1)
  set(CURL_DISABLE_LDAPS 1)
  set(CURL_DISABLE_MQTT 1)
  set(CURL_DISABLE_POP3 1)
  set(CURL_DISABLE_RTSP 1)
  set(CURL_DISABLE_SMB 1)
  set(CURL_DISABLE_SMTP 1)
  set(CURL_DISABLE_TELNET 1)
  set(CURL_DISABLE_TFTP 1)

  # Enable IPv6
  set(ENABLE_IPV6 1)

  set(HAVE_ALARM 1)
  if(APPLE)
    set(HAVE_ARC4RANDOM 1)
  endif()
  set(HAVE_ARPA_INET_H 1)
  set(HAVE_ATOMIC 1)
  set(HAVE_FNMATCH 1)
  set(HAVE_BASENAME 1)
  set(HAVE_BOOL_T 1)
  set(HAVE_BUILTIN_AVAILABLE 1)
  set(HAVE_CLOCK_GETTIME_MONOTONIC 1)
  set(HAVE_CLOCK_GETTIME_MONOTONIC_RAW 1)
  set(HAVE_FCNTL 1)
  set(HAVE_FCNTL_H 1)
  set(HAVE_FCNTL_O_NONBLOCK 1)
  set(HAVE_FREEADDRINFO 1)
  set(HAVE_FSEEKO 1)
  set(HAVE_DECL_FSEEKO 1)
  set(HAVE_FTRUNCATE 1)
  set(HAVE_GETADDRINFO 1)
  set(HAVE_GETADDRINFO_THREADSAFE 1)
  set(HAVE_GETEUID 1)
  set(HAVE_GETPPID 1)
  set(HAVE_GETHOSTNAME 1)
  set(HAVE_GETIFADDRS 1)
  set(HAVE_GETPEERNAME 1)
  set(HAVE_GETSOCKNAME 1)
  set(HAVE_IF_NAMETOINDEX 1)
  set(HAVE_GETPWUID 1)
  set(HAVE_GETPWUID_R 1)
  set(HAVE_GETRLIMIT 1)
  set(HAVE_GETTIMEOFDAY 1)
  set(HAVE_GMTIME_R 1)
  set(HAVE_IFADDRS_H 1)
  set(HAVE_INET_NTOP 1)
  set(HAVE_INET_PTON 1)
  set(HAVE_SA_FAMILY_T 1)
  set(HAVE_IOCTL_FIONBIO 1)
  set(HAVE_IOCTL_SIOCGIFADDR 1)
  set(HAVE_LIBGEN_H 1)
  set(HAVE_LIBZ 1)
  set(HAVE_LOCALE_H 1)
  set(HAVE_LONGLONG 1)
  set(HAVE_SUSECONDS_T 1)
  set(HAVE_MSG_NOSIGNAL 1)
  set(HAVE_NETDB_H 1)
  set(HAVE_NETINET_IN_H 1)
  set(HAVE_NETINET_TCP_H 1)
  set(HAVE_NETINET_UDP_H 1)
  set(HAVE_NET_IF_H 1)
  set(HAVE_PIPE 1)
  set(HAVE_POLL_H 1)
  set(HAVE_POSIX_STRERROR_R 1)
  set(HAVE_PTHREAD_H 1)
  set(HAVE_PWD_H 1)
  set(HAVE_SSL_SET0_WBIO 1)
  set(HAVE_RECV 1)
  set(HAVE_SELECT 1)
  set(HAVE_SCHED_YIELD 1)
  set(HAVE_SEND 1)
  set(HAVE_SENDMSG 1)
  set(HAVE_FSETXATTR 1)
  set(HAVE_FSETXATTR_6 1)
  set(HAVE_SETLOCALE 1)
  set(HAVE_SETMODE 1)
  set(HAVE_SETRLIMIT 1)
  set(HAVE_SIGACTION 1)
  set(HAVE_SIGINTERRUPT 1)
  set(HAVE_SIGNAL 1)
  set(HAVE_SIGSETJMP 1)
  set(HAVE_SNPRINTF 1)
  set(HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID 1)
  set(HAVE_SOCKET 1)
  set(HAVE_SOCKETPAIR 1)
  set(HAVE_STDATOMIC_H 1)
  set(HAVE_STDBOOL_H 1)
  set(HAVE_STRCASECMP 1)
  set(HAVE_STRDUP 1)
  set(HAVE_STRERROR_R 1)
  set(HAVE_STRINGS_H 1)
  set(HAVE_STRTOK_R 1)
  set(HAVE_STRTOLL 1)
  set(HAVE_STRUCT_SOCKADDR_STORAGE 1)
  set(HAVE_STRUCT_TIMEVAL 1)
  set(HAVE_SYS_FILIO_H 1)
  set(HAVE_SYS_WAIT_H 1)
  set(HAVE_SYS_IOCTL_H 1)
  set(HAVE_SYS_PARAM_H 1)
  set(HAVE_SYS_POLL_H 1)
  set(HAVE_SYS_RESOURCE_H 1)
  set(HAVE_SYS_SELECT_H 1)
  set(HAVE_SYS_SOCKET_H 1)
  set(HAVE_SYS_STAT_H 1)
  set(HAVE_SYS_TIME_H 1)
  set(HAVE_SYS_TYPES_H 1)
  set(HAVE_SYS_UN_H 1)
  set(HAVE_TERMIOS_H 1)
  set(HAVE_UNISTD_H 1)
  set(HAVE_UTIME 1)
  set(HAVE_UTIMES 1)
  set(HAVE_UTIME_H 1)
  set(HAVE_WRITABLE_ARGV 1)

  # Other
  set(STDC_HEADERS 1)
  set(USE_THREADS_POSIX 1)
  set(USE_LIBSSH2 0)
  set(USE_BEARSSL 1)
  set(USE_UNIX_SOCKETS 1)
  set(_FILE_OFFSET_BITS 64)
  set(USE_TLS_SRP 1)

  # Platform-specific
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(OS "\"Linux\"")
    set(CURL_CA_BUNDLE "/etc/ssl/certs/ca-certificates.crt")
    set(HAVE_SYS_SOCKIO_H 0)
    set(HAVE_MACH_ABSOLUTE_TIME 0)
  elseif(APPLE)
    set(OS "\"Darwin\"")
    set(CURL_CA_BUNDLE "/etc/ssl/cert.pem")
    set(HAVE_SYS_SOCKIO_H 1)
    set(HAVE_MACH_ABSOLUTE_TIME 1)
  endif()

  set(CURL_CA_PATH "/etc/ssl/certs")
  set(RANDOM_FILE "/dev/urandom")
  set(SIZEOF_INT 4)
  set(SIZEOF_LONG 8)
  set(SIZEOF_LONG_LONG 8)
  set(SIZEOF_OFF_T 8)
  set(SIZEOF_CURL_OFF_T 8)
  set(SIZEOF_CURL_SOCKET_T 4)
  set(SIZEOF_SIZE_T 8)
  set(SIZEOF_TIME_T 8)

  configure_file("${CURL_DIR}/lib/curl_config.h.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/curl/curl_config.h")

  set(CURL_PUBLIC_HEADER "${CURL_DIR}/include/curl/curl.h")
  set(CURL_PRIVATE_HEADERS
    "${CURL_DIR}/include/curl/stdcheaders.h"
    "${CURL_DIR}/include/curl/header.h"
    "${CURL_DIR}/include/curl/options.h"
    "${CURL_DIR}/include/curl/mprintf.h"
    "${CURL_DIR}/include/curl/easy.h"
    "${CURL_DIR}/include/curl/websockets.h"
    "${CURL_DIR}/include/curl/curlver.h"
    "${CURL_DIR}/include/curl/system.h"
    "${CURL_DIR}/include/curl/typecheck-gcc.h"
    "${CURL_DIR}/include/curl/multi.h"
    "${CURL_DIR}/include/curl/urlapi.h")

  add_library(curl
    "${CURL_PUBLIC_HEADER}" ${CURL_PRIVATE_HEADERS}
    "${CURL_DIR}/lib/strcase.c"
    "${CURL_DIR}/lib/cf-h2-proxy.h"
    "${CURL_DIR}/lib/easyoptions.c"
    "${CURL_DIR}/lib/dict.c"
    "${CURL_DIR}/lib/llist.c"
    "${CURL_DIR}/lib/mprintf.c"
    "${CURL_DIR}/lib/pingpong.c"
    "${CURL_DIR}/lib/socks_gssapi.c"
    "${CURL_DIR}/lib/memdebug.h"
    "${CURL_DIR}/lib/psl.c"
    "${CURL_DIR}/lib/progress.h"
    "${CURL_DIR}/lib/url.c"
    "${CURL_DIR}/lib/easyif.h"
    "${CURL_DIR}/lib/curl_md4.h"
    "${CURL_DIR}/lib/timeval.c"
    "${CURL_DIR}/lib/http_aws_sigv4.h"
    "${CURL_DIR}/lib/curl_get_line.c"
    "${CURL_DIR}/lib/hmac.c"
    "${CURL_DIR}/lib/curl_addrinfo.h"
    "${CURL_DIR}/lib/md4.c"
    "${CURL_DIR}/lib/curl_range.c"
    "${CURL_DIR}/lib/idn.c"
    "${CURL_DIR}/lib/hostsyn.c"
    "${CURL_DIR}/lib/strtok.c"
    "${CURL_DIR}/lib/smtp.h"
    "${CURL_DIR}/lib/curl_threads.c"
    "${CURL_DIR}/lib/if2ip.c"
    "${CURL_DIR}/lib/c-hyper.c"
    "${CURL_DIR}/lib/cf-socket.c"
    "${CURL_DIR}/lib/http_negotiate.c"
    "${CURL_DIR}/lib/doh.c"
    "${CURL_DIR}/lib/curl_endian.c"
    "${CURL_DIR}/lib/formdata.c"
    "${CURL_DIR}/lib/easygetopt.c"
    "${CURL_DIR}/lib/cf-https-connect.c"
    "${CURL_DIR}/lib/mime.h"
    "${CURL_DIR}/lib/strdup.h"
    "${CURL_DIR}/lib/timediff.c"
    "${CURL_DIR}/lib/fileinfo.h"
    "${CURL_DIR}/lib/curl_ldap.h"
    "${CURL_DIR}/lib/dynbuf.c"
    "${CURL_DIR}/lib/amigaos.h"
    "${CURL_DIR}/lib/telnet.h"
    "${CURL_DIR}/lib/rand.c"
    "${CURL_DIR}/lib/http_chunks.h"
    "${CURL_DIR}/lib/http2.c"
    "${CURL_DIR}/lib/strerror.h"
    "${CURL_DIR}/lib/curl_multibyte.h"
    "${CURL_DIR}/lib/socketpair.h"
    "${CURL_DIR}/lib/netrc.h"
    "${CURL_DIR}/lib/bufref.h"
    "${CURL_DIR}/lib/dynhds.c"
    "${CURL_DIR}/lib/curl_sasl.h"
    "${CURL_DIR}/lib/content_encoding.c"
    "${CURL_DIR}/lib/curl_ctype.h"
    "${CURL_DIR}/lib/hostip.c"
    "${CURL_DIR}/lib/curl_sspi.h"
    "${CURL_DIR}/lib/http.h"
    "${CURL_DIR}/lib/curl_des.h"
    "${CURL_DIR}/lib/curl_gethostname.h"
    "${CURL_DIR}/lib/curl_ntlm_wb.h"
    "${CURL_DIR}/lib/rtsp.h"
    "${CURL_DIR}/lib/splay.h"
    "${CURL_DIR}/lib/escape.c"
    "${CURL_DIR}/lib/version_win32.c"
    "${CURL_DIR}/lib/easy.c"
    "${CURL_DIR}/lib/rename.c"
    "${CURL_DIR}/lib/pop3.h"
    "${CURL_DIR}/lib/curl_path.h"
    "${CURL_DIR}/lib/share.c"
    "${CURL_DIR}/lib/slist.c"
    "${CURL_DIR}/lib/inet_pton.c"
    "${CURL_DIR}/lib/tftp.c"
    "${CURL_DIR}/lib/curl_ntlm_core.h"
    "${CURL_DIR}/lib/mqtt.c"
    "${CURL_DIR}/lib/config-plan9.h"
    "${CURL_DIR}/lib/noproxy.h"
    "${CURL_DIR}/lib/gopher.h"
    "${CURL_DIR}/lib/fopen.c"
    "${CURL_DIR}/lib/multihandle.h"
    "${CURL_DIR}/lib/socks.c"
    "${CURL_DIR}/lib/imap.h"
    "${CURL_DIR}/lib/parsedate.c"
    "${CURL_DIR}/lib/curl_trc.c"
    "${CURL_DIR}/lib/hsts.h"
    "${CURL_DIR}/lib/warnless.c"
    "${CURL_DIR}/lib/cf-haproxy.c"
    "${CURL_DIR}/lib/http_digest.h"
    "${CURL_DIR}/lib/curl_printf.h"
    "${CURL_DIR}/lib/file.h"
    "${CURL_DIR}/lib/cfilters.c"
    "${CURL_DIR}/lib/ftp.h"
    "${CURL_DIR}/lib/strtoofft.h"
    "${CURL_DIR}/lib/cf-h1-proxy.h"
    "${CURL_DIR}/lib/smb.h"
    "${CURL_DIR}/lib/curl_memrchr.h"
    "${CURL_DIR}/lib/conncache.h"
    "${CURL_DIR}/lib/altsvc.h"
    "${CURL_DIR}/lib/ws.h"
    "${CURL_DIR}/lib/connect.h"
    "${CURL_DIR}/lib/system_win32.c"
    "${CURL_DIR}/lib/transfer.c"
    "${CURL_DIR}/lib/curl_gssapi.h"
    "${CURL_DIR}/lib/curl_rtmp.c"
    "${CURL_DIR}/lib/nonblock.c"
    "${CURL_DIR}/lib/select.c"
    "${CURL_DIR}/lib/curl_fnmatch.h"
    "${CURL_DIR}/lib/getinfo.h"
    "${CURL_DIR}/lib/hostip4.c"
    "${CURL_DIR}/lib/http1.c"
    "${CURL_DIR}/lib/inet_ntop.h"
    "${CURL_DIR}/lib/speedcheck.h"
    "${CURL_DIR}/lib/urlapi.c"
    "${CURL_DIR}/lib/ftplistparser.h"
    "${CURL_DIR}/lib/openldap.c"
    "${CURL_DIR}/lib/getenv.c"
    "${CURL_DIR}/lib/setopt.h"
    "${CURL_DIR}/lib/hash.c"
    "${CURL_DIR}/lib/bufq.c"
    "${CURL_DIR}/lib/http_proxy.c"
    "${CURL_DIR}/lib/http_ntlm.h"
    "${CURL_DIR}/lib/vquic/curl_quiche.h"
    "${CURL_DIR}/lib/vquic/vquic.c"
    "${CURL_DIR}/lib/vquic/curl_ngtcp2.c"
    "${CURL_DIR}/lib/vquic/curl_msh3.h"
    "${CURL_DIR}/lib/vquic/curl_quiche.c"
    "${CURL_DIR}/lib/vquic/curl_ngtcp2.h"
    "${CURL_DIR}/lib/vquic/vquic.h"
    "${CURL_DIR}/lib/vquic/vquic_int.h"
    "${CURL_DIR}/lib/vquic/curl_msh3.c"
    "${CURL_DIR}/lib/cookie.h"
    "${CURL_DIR}/lib/krb5.c"
    "${CURL_DIR}/lib/macos.h"
    "${CURL_DIR}/lib/headers.h"
    "${CURL_DIR}/lib/multi.c"
    "${CURL_DIR}/lib/sendf.h"
    "${CURL_DIR}/lib/curl_memory.h"
    "${CURL_DIR}/lib/cf-https-connect.h"
    "${CURL_DIR}/lib/formdata.h"
    "${CURL_DIR}/lib/urldata.h"
    "${CURL_DIR}/lib/multiif.h"
    "${CURL_DIR}/lib/curl_endian.h"
    "${CURL_DIR}/lib/config-win32.h"
    "${CURL_DIR}/lib/strdup.c"
    "${CURL_DIR}/lib/mime.c"
    "${CURL_DIR}/lib/cf-socket.h"
    "${CURL_DIR}/lib/if2ip.h"
    "${CURL_DIR}/lib/socks_sspi.c"
    "${CURL_DIR}/lib/c-hyper.h"
    "${CURL_DIR}/lib/curl_threads.h"
    "${CURL_DIR}/lib/strtok.h"
    "${CURL_DIR}/lib/smtp.c"
    "${CURL_DIR}/lib/doh.h"
    "${CURL_DIR}/lib/http_negotiate.h"
    "${CURL_DIR}/lib/curl_setup_once.h"
    "${CURL_DIR}/lib/curl_get_line.h"
    "${CURL_DIR}/lib/http_aws_sigv4.c"
    "${CURL_DIR}/lib/timeval.h"
    "${CURL_DIR}/lib/sockaddr.h"
    "${CURL_DIR}/lib/curl_hmac.h"
    "${CURL_DIR}/lib/curl_range.h"
    "${CURL_DIR}/lib/idn.h"
    "${CURL_DIR}/lib/setup-os400.h"
    "${CURL_DIR}/lib/curl_addrinfo.c"
    "${CURL_DIR}/lib/curl_setup.h"
    "${CURL_DIR}/lib/pingpong.h"
    "${CURL_DIR}/lib/llist.h"
    "${CURL_DIR}/lib/dict.h"
    "${CURL_DIR}/lib/config-win32ce.h"
    "${CURL_DIR}/lib/easyoptions.h"
    "${CURL_DIR}/lib/strcase.h"
    "${CURL_DIR}/lib/cf-h2-proxy.c"
    "${CURL_DIR}/lib/url.h"
    "${CURL_DIR}/lib/psl.h"
    "${CURL_DIR}/lib/memdebug.c"
    "${CURL_DIR}/lib/progress.c"
    "${CURL_DIR}/lib/curl_sha256.h"
    "${CURL_DIR}/lib/inet_pton.h"
    "${CURL_DIR}/lib/mqtt.h"
    "${CURL_DIR}/lib/curl_ntlm_core.c"
    "${CURL_DIR}/lib/tftp.h"
    "${CURL_DIR}/lib/slist.h"
    "${CURL_DIR}/lib/share.h"
    "${CURL_DIR}/lib/curl_path.c"
    "${CURL_DIR}/lib/rename.h"
    "${CURL_DIR}/lib/hostasyn.c"
    "${CURL_DIR}/lib/pop3.c"
    "${CURL_DIR}/lib/arpa_telnet.h"
    "${CURL_DIR}/lib/fopen.h"
    "${CURL_DIR}/lib/noproxy.c"
    "${CURL_DIR}/lib/gopher.c"
    "${CURL_DIR}/lib/rtsp.c"
    "${CURL_DIR}/lib/curl_ntlm_wb.c"
    "${CURL_DIR}/lib/curl_gethostname.c"
    "${CURL_DIR}/lib/curl_des.c"
    "${CURL_DIR}/lib/curlx.h"
    "${CURL_DIR}/lib/functypes.h"
    "${CURL_DIR}/lib/base64.c"
    "${CURL_DIR}/lib/version_win32.h"
    "${CURL_DIR}/lib/escape.h"
    "${CURL_DIR}/lib/setup-win32.h"
    "${CURL_DIR}/lib/splay.c"
    "${CURL_DIR}/lib/setup-vms.h"
    "${CURL_DIR}/lib/hostip.h"
    "${CURL_DIR}/lib/content_encoding.h"
    "${CURL_DIR}/lib/http.c"
    "${CURL_DIR}/lib/config-amigaos.h"
    "${CURL_DIR}/lib/curl_sspi.c"
    "${CURL_DIR}/lib/http_chunks.c"
    "${CURL_DIR}/lib/config-os400.h"
    "${CURL_DIR}/lib/rand.h"
    "${CURL_DIR}/lib/dynbuf.h"
    "${CURL_DIR}/lib/telnet.c"
    "${CURL_DIR}/lib/amigaos.c"
    "${CURL_DIR}/lib/asyn.h"
    "${CURL_DIR}/lib/fileinfo.c"
    "${CURL_DIR}/lib/timediff.h"
    "${CURL_DIR}/lib/version.c"
    "${CURL_DIR}/lib/ldap.c"
    "${CURL_DIR}/lib/bufref.c"
    "${CURL_DIR}/lib/curl_sasl.c"
    "${CURL_DIR}/lib/dynhds.h"
    "${CURL_DIR}/lib/netrc.c"
    "${CURL_DIR}/lib/socketpair.c"
    "${CURL_DIR}/lib/strerror.c"
    "${CURL_DIR}/lib/curl_multibyte.c"
    "${CURL_DIR}/lib/http2.h"
    "${CURL_DIR}/lib/altsvc.c"
    "${CURL_DIR}/lib/config-riscos.h"
    "${CURL_DIR}/lib/conncache.c"
    "${CURL_DIR}/lib/curl_memrchr.c"
    "${CURL_DIR}/lib/smb.c"
    "${CURL_DIR}/lib/transfer.h"
    "${CURL_DIR}/lib/sha256.c"
    "${CURL_DIR}/lib/system_win32.h"
    "${CURL_DIR}/lib/connect.c"
    "${CURL_DIR}/lib/ws.c"
    "${CURL_DIR}/lib/ftp.c"
    "${CURL_DIR}/lib/strtoofft.c"
    "${CURL_DIR}/lib/md5.c"
    "${CURL_DIR}/lib/vauth/krb5_sspi.c"
    "${CURL_DIR}/lib/vauth/spnego_sspi.c"
    "${CURL_DIR}/lib/vauth/ntlm.c"
    "${CURL_DIR}/lib/vauth/gsasl.c"
    "${CURL_DIR}/lib/vauth/spnego_gssapi.c"
    "${CURL_DIR}/lib/vauth/digest.h"
    "${CURL_DIR}/lib/vauth/ntlm_sspi.c"
    "${CURL_DIR}/lib/vauth/vauth.c"
    "${CURL_DIR}/lib/vauth/oauth2.c"
    "${CURL_DIR}/lib/vauth/ntlm.h"
    "${CURL_DIR}/lib/vauth/cram.c"
    "${CURL_DIR}/lib/vauth/cleartext.c"
    "${CURL_DIR}/lib/vauth/krb5_gssapi.c"
    "${CURL_DIR}/lib/vauth/digest.c"
    "${CURL_DIR}/lib/vauth/digest_sspi.c"
    "${CURL_DIR}/lib/vauth/vauth.h"
    "${CURL_DIR}/lib/file.c"
    "${CURL_DIR}/lib/cfilters.h"
    "${CURL_DIR}/lib/http_digest.c"
    "${CURL_DIR}/lib/cf-haproxy.h"
    "${CURL_DIR}/lib/asyn-thread.c"
    "${CURL_DIR}/lib/cf-h1-proxy.c"
    "${CURL_DIR}/lib/curl_md5.h"
    "${CURL_DIR}/lib/urlapi-int.h"
    "${CURL_DIR}/lib/hsts.c"
    "${CURL_DIR}/lib/vtls/mbedtls.c"
    "${CURL_DIR}/lib/vtls/gtls.c"
    "${CURL_DIR}/lib/vtls/bearssl.c"
    "${CURL_DIR}/lib/vtls/vtls.h"
    "${CURL_DIR}/lib/vtls/hostcheck.c"
    "${CURL_DIR}/lib/vtls/rustls.c"
    "${CURL_DIR}/lib/vtls/wolfssl.h"
    "${CURL_DIR}/lib/vtls/schannel.c"
    "${CURL_DIR}/lib/vtls/openssl.h"
    "${CURL_DIR}/lib/vtls/keylog.h"
    "${CURL_DIR}/lib/vtls/sectransp.c"
    "${CURL_DIR}/lib/vtls/schannel_verify.c"
    "${CURL_DIR}/lib/vtls/x509asn1.h"
    "${CURL_DIR}/lib/vtls/mbedtls_threadlock.h"
    "${CURL_DIR}/lib/vtls/vtls.c"
    "${CURL_DIR}/lib/vtls/bearssl.h"
    "${CURL_DIR}/lib/vtls/hostcheck.h"
    "${CURL_DIR}/lib/vtls/gtls.h"
    "${CURL_DIR}/lib/vtls/mbedtls.h"
    "${CURL_DIR}/lib/vtls/vtls_int.h"
    "${CURL_DIR}/lib/vtls/schannel_int.h"
    "${CURL_DIR}/lib/vtls/rustls.h"
    "${CURL_DIR}/lib/vtls/keylog.c"
    "${CURL_DIR}/lib/vtls/openssl.c"
    "${CURL_DIR}/lib/vtls/wolfssl.c"
    "${CURL_DIR}/lib/vtls/schannel.h"
    "${CURL_DIR}/lib/vtls/mbedtls_threadlock.c"
    "${CURL_DIR}/lib/vtls/x509asn1.c"
    "${CURL_DIR}/lib/vtls/sectransp.h"
    "${CURL_DIR}/lib/parsedate.h"
    "${CURL_DIR}/lib/curl_trc.h"
    "${CURL_DIR}/lib/warnless.h"
    "${CURL_DIR}/lib/socks.h"
    "${CURL_DIR}/lib/vssh/libssh.c"
    "${CURL_DIR}/lib/vssh/libssh2.c"
    "${CURL_DIR}/lib/vssh/ssh.h"
    "${CURL_DIR}/lib/vssh/wolfssh.c"
    "${CURL_DIR}/lib/asyn-ares.c"
    "${CURL_DIR}/lib/imap.c"
    "${CURL_DIR}/lib/config-dos.h"
    "${CURL_DIR}/lib/headers.c"
    "${CURL_DIR}/lib/macos.c"
    "${CURL_DIR}/lib/cookie.c"
    "${CURL_DIR}/lib/curl_krb5.h"
    "${CURL_DIR}/lib/hostip6.c"
    "${CURL_DIR}/lib/sendf.c"
    "${CURL_DIR}/lib/ftplistparser.c"
    "${CURL_DIR}/lib/http_ntlm.c"
    "${CURL_DIR}/lib/http_proxy.h"
    "${CURL_DIR}/lib/bufq.h"
    "${CURL_DIR}/lib/hash.h"
    "${CURL_DIR}/lib/config-mac.h"
    "${CURL_DIR}/lib/setopt.c"
    "${CURL_DIR}/lib/easy_lock.h"
    "${CURL_DIR}/lib/curl_base64.h"
    "${CURL_DIR}/lib/sigpipe.h"
    "${CURL_DIR}/lib/getinfo.c"
    "${CURL_DIR}/lib/speedcheck.c"
    "${CURL_DIR}/lib/http1.h"
    "${CURL_DIR}/lib/inet_ntop.c"
    "${CURL_DIR}/lib/curl_rtmp.h"
    "${CURL_DIR}/lib/curl_gssapi.c"
    "${CURL_DIR}/lib/curl_fnmatch.c"
    "${CURL_DIR}/lib/select.h"
    "${CURL_DIR}/lib/nonblock.h")

  target_compile_definitions(curl PRIVATE BUILDING_LIBCURL)

  if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(curl PRIVATE CURL_STATICLIB)
  endif()

  target_compile_definitions(curl PRIVATE UNICODE)
  target_compile_definitions(curl PRIVATE _UNICODE)
  target_compile_definitions(curl PRIVATE HTTP_ONLY)
  target_compile_definitions(curl PRIVATE HAVE_CONFIG_H)
  target_compile_definitions(curl PRIVATE USE_BEARSSL)
  target_compile_definitions(curl PRIVATE SIZEOF_CURL_OFF_T=${SIZEOF_CURL_OFF_T})

  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # POSIX.1-2008
    target_compile_definitions(curl PRIVATE _POSIX_C_SOURCE=200809L)
  endif()

  target_include_directories(curl PRIVATE "${CURL_DIR}/lib")
  target_include_directories(curl PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/curl")

  target_link_libraries(curl PRIVATE ZLIB::ZLIB)
  target_link_libraries(curl PRIVATE BearSSL::BearSSL)
  if(APPLE)
    target_link_libraries(curl PRIVATE "-framework Foundation")
    target_link_libraries(curl PRIVATE "-framework SystemConfiguration")
  endif()

  target_include_directories(curl PUBLIC
    "$<BUILD_INTERFACE:${CURL_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

  add_library(CURL::libcurl ALIAS curl)

  set_target_properties(curl
    PROPERTIES
      OUTPUT_NAME curl
      PUBLIC_HEADER "${CURL_PUBLIC_HEADER}"
      PRIVATE_HEADER "${CURL_PRIVATE_HEADERS}"
      C_VISIBILITY_PRESET "default"
      C_VISIBILITY_INLINES_HIDDEN FALSE
      EXPORT_NAME curl)

  include(GNUInstallDirs)
  install(TARGETS curl
    EXPORT curl
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/curl"
      COMPONENT sourcemeta_hydra_dev
    PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/curl"
      COMPONENT sourcemeta_hydra_dev
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
      COMPONENT sourcemeta_hydra
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      COMPONENT sourcemeta_hydra
      NAMELINK_COMPONENT sourcemeta_hydra_dev
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      COMPONENT sourcemeta_hydra_dev)
  install(EXPORT curl
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/curl"
    COMPONENT sourcemeta_hydra_dev)

  # TODO: Why does `find_dependency(ZLIB)` fail to locate ZLIB
  # if even `CMAKE_PREFIX_PATH` is correct?
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/curl-config.cmake
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/../zlib/zlib-config.cmake\")\n"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/curl.cmake\")\n"
    "check_required_components(\"curl\")\n")
  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/curl-config.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/curl"
    COMPONENT sourcemeta_hydra_dev)

  set(CURL_FOUND ON)
endif()
