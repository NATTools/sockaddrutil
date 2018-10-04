/* See LICENSE file */

#ifndef SOCKADDR_UTIL_H
#define SOCKADDR_UTIL_H

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif


/*static const uint32_t SOCKADDR_MAX_STRLEN = INET6_ADDRSTRLEN + 8; //port, :,
 *[];*/
#define SOCKADDR_MAX_STRLEN  INET6_ADDRSTRLEN + 8


void
sockaddr_reset(struct sockaddr_storage* sa);

/*
 *  Initialize a sockaddr_in (IPv4) as any ("0.0.0.0:0").
 *  Remember to put aside enough memory. (sockaddr_storage)
 */
void
sockaddr_initAsIPv4Any(struct sockaddr_in* sa);



void
sockaddr_initAsIPv6Any(struct sockaddr_in6* sa);

/*
 *  Initialize a sockaddr from string.
 *  Remember to put aside enough memory. (sockaddr_storage)
 */
bool
sockaddr_initFromString(struct sockaddr* sa,
                        const char*      addr_str);

/*
 * Initialize a sockaddr from a IPv4 string
 */
bool
sockaddr_initFromIPv4String(struct sockaddr_in* sa,
                            const char*         addr_str);

/*
 * Initialize a sockaddr from a IPv6 string
 */
bool
sockaddr_initFromIPv6String(struct sockaddr_in6* sa,
                            const char*          addr_str);


/*
 * Initialize IPv4 sockaddr from a int addr and a int port.
 * (Use htons and htonl if your data is stored in host format)
 *
 */
bool
sockaddr_initFromIPv4Int(struct sockaddr_in* sa,
                         uint32_t            addr,
                         uint16_t            port);


/*
 * Initialize IPv6 sockaddr from a int addr and a int port.
 * (Use htons and htonl if your data is stored in host format)
 *
 */
bool
sockaddr_initFromIPv6Int(struct sockaddr_in6* sin,
                         const uint8_t        ipaddr[16],
                         uint16_t             port);


/*
 *  Checks if the address part is the same.
 *  No checking of ports or transport protocol
 */

bool
sockaddr_sameAddr(const struct sockaddr* a,
                  const struct sockaddr* b);


/*
 *  Check if the port is the same.
 *
 */
bool
sockaddr_samePort(const struct sockaddr* a,
                  const struct sockaddr* b);

/*
 *  Get port from address
 *
 */
unsigned int
sockaddr_ipPort (const struct sockaddr* a);

/*
 * Check if two sockaddr are alike
 * (IP proto, port and address)
 *
 */
bool
sockaddr_alike(const struct sockaddr* a,
               const struct sockaddr* b);

/*
 *   Checks if a sockaddr is reasonably initialized
 *
 */
bool
sockaddr_isSet(const struct sockaddr* sa);

/*
 * Checks if a sockaddr has the address of 'any'
 *
 */
bool
sockaddr_isAddrAny(const struct sockaddr* sa);


/*
 * Checks if a sockaddr loop-back
 *
 */
bool
sockaddr_isAddrLoopBack(const struct sockaddr* sa);


/*
 * Checks if a sockaddr is private (RFC 1918)
 *
 */
bool
sockaddr_isAddrPrivate(const struct sockaddr* sa);


/*
 * Checks if a sockaddr is a IPv6 link local address
 * Will return false if it is a IPv4 addr
 */
bool
sockaddr_isAddrLinkLocal(const struct sockaddr* sa);

/*
 * Checks if a sockaddr is a IPv6 site local address
 * Will return false if it is a IPv4 addr
 */

bool
sockaddr_isAddrSiteLocal(const struct sockaddr* sa);

/*
 * Checks if a sockaddr is a IPv6 ULA address
 * Will return false if it is a IPv4 addr
 */
bool
sockaddr_isAddrULA(const struct sockaddr* sa);

#if defined(__APPLE__) && defined(__MACH__)
#include <TargetConditionals.h>
#if TARGET_OS_OSX == 1
/*
 * Get IPv6 Flags.
 * Will return 0 in case if failure or IPv4 addr
 */
int
sockaddr_getIPv6Flags(const struct sockaddr* sa,
                      const char*            ifa_name,
                      int                    ifa_len);

/*
 * Checks if a sockaddr is a IPv6 temporary address
 * Will return false if it is a IPv4 addr
 */
bool
sockaddr_isAddrTemporary(const struct sockaddr* sa,
                         const char*            ifa_name,
                         int                    ifa_len);


/*
 * Checks if a sockaddr is a IPv6 deprecated address
 * Will return false if it is a IPv4 addr
 */
bool
sockaddr_isAddrDeprecated(const struct sockaddr* sa,
                          const char*            ifa_name,
                          int                    ifa_len);
#endif
#endif
/*
 * Converts a sockaddr to string
 * If add port is true the IPv6 string will contain [],
 * if not the IPv6 address is printed without[]
 */
const char*
sockaddr_toString(const struct sockaddr* sa,
                  char*                  dest,
                  size_t                 destlen,
                  bool                   addport);

/*
 *  Copy a sockaddr from src to dst
 */
void
sockaddr_copy(struct sockaddr*       dst,
              const struct sockaddr* src);


/*
 *   Set the port portion of a sockaddr
 */
void
sockaddr_setPort(struct sockaddr* sa,
                 uint16_t         port);

#ifdef __cplusplus
}
#endif

#endif
