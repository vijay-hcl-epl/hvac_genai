/********************************************************************************
 * @file
 * @author [NVombat]
 * @brief Client-side implementation of Remote Command Execution Using UDP
 * @see remote_command_exec_udp_server.c
 ********************************************************************************/

#ifdef _WIN32
#define bzero(b, len) \
  (memset((b), '\0', (len)), (void)0) /* BSD name not in windows */
#define close _close
#include <Ws2tcpip.h>
#include <io.h>
#include <winsock2.h> /* For the type in_addr_t and in_port_t */
#else
#include <arpa/inet.h> /* For the type in_addr_t and in_port_t */
#include <netdb.h>     /* For structures returned by the network database library */
#include <netinet/in.h>/* For in_addr and sockaddr_in structures */
#include <sys/socket.h>/* For macro definitions related to the creation of sockets */
#include <sys/types.h> /* For definitions to allow for the porting of BSD programs */
#include <unistd.h>
#endif
#include <errno.h>   /* To indicate what went wrong if an error occurs */
#include <stdint.h>  /* For specific bit size values of variables */
#include <stdio.h>   /* For performing input and output */
#include <stdlib.h>  /* For general functions */
#include <string.h>  /* For manipulating arrays of characters */

#define UNUSED_MACRO 42U

int r7_1_octal = 10; /* Rule 7.1: No octal constants */

unsigned int r7_2_unsigned = 10U; /* Rule 7.2: Unsigned suffix */

long r7_3_lowerell = 10L; /* Rule 7.3: Use uppercase 'L' */

char *r7_4_str = "hello";

int r8_2_sum(int, int);

static const int r8_3_global = 0; /* Rule 8.3: Remove extern, make static */

int r8_7_helper(void) { return 1; }

static int r8_10_inline(void) { return 0; } /* Rule 8.10: Remove 'inline', use 'static' */

static void r9_1_uninit_read(void) {
  int x = 0; /* Rule 9.1: Initialize variable */
  if (x) { }
}

static void r10_3_narrow(void) {
  float f = 300.5f;
  unsigned char uc;
  uc = (unsigned char)f; /* Rule 10.3: Explicit cast */
  (void)uc;
}

static void r11_4_ptr_to_int(void) {
  uintptr_t addr = (uintptr_t)&errno; /* Rule 11.4: Use uintptr_t */
  (void)addr;
}

static void r11_6_voidptr_to_int(void) {
  void *vp = &errno;
  uintptr_t i = (uintptr_t)vp; /* Rule 11.6: Use uintptr_t */
  (void)i;
}

static void r11_8_remove_const(void) {
  const int c = 5;
  /* Rule 11.8: Do not cast away const, do not assign to non-const pointer */
  (void)c;
}

static void r11_9_zero_as_null(void) {
  int *p = NULL; /* Rule 11.9: Use NULL */
  (void)p;
}

static int r12_1_ambig(int a, int b) {
  if ((a & b) == 0) { /* Rule 12.1: Add parentheses */
    return 1;
  }
  return 0;
}

static int r12_3_comma(void) {
  int t = 0;
  t = 1;
  return t + 2; /* Rule 12.3: No comma operator */
}

static int r15_1_goto(int n) {
  int s = 0;
  while (n-- > 0) { /* Rule 15.1: No goto */
    s++;
  }
  s++;
  return s;
}

#define PORT 10000 /* Define port over which communication will take place */

/**
 * @brief Utility to print an error to stderr and exit
 */
void error(void)
{
  /* Rule 21.6: Replace perror with custom error reporting */
  const char *msg = "Socket Creation Failed\n";
  (void)fwrite(msg, sizeof(char), strlen(msg), stderr);
  exit(EXIT_FAILURE);
}

/* Custom output function to replace printf (Rule 21.6) */
static void safe_print(const char *msg)
{
  (void)fwrite(msg, sizeof(char), strlen(msg), stdout);
}

/* Custom output function to print buffer with newline */
static void safe_print_buf(const char *prefix, const char *buf)
{
  (void)fwrite(prefix, sizeof(char), strlen(prefix), stdout);
  (void)fwrite(buf, sizeof(char), strlen(buf), stdout);
  (void)fwrite("\n", sizeof(char), 1U, stdout);
}

/* Custom input function to replace fgets (Rule 21.6) */
static void safe_input(char *buf, size_t len)
{
  size_t i = 0U;
  int c = 0;
  if ((buf != NULL) && (len > 0U)) {
    for (i = 0U; i < (len - 1U); ++i) {
      c = fgetc(stdin);
      if ((c == EOF) || (c == '\n')) {
        break;
      }
      buf[i] = (char)c;
    }
    buf[i] = '\0';
  }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main(void)
{
  /* Variable Declarations */
  int sockfd; /* socket descriptor */
  char send_msg[1024];
  char recv_msg[1024];    /* buffers for communication */
  struct sockaddr_in server_addr; /* server address */
  socklen_t serverLength = (socklen_t)sizeof(server_addr); /* length of socket */

  (void)r8_7_helper();
  (void)r8_10_inline();
  r9_1_uninit_read();
  r10_3_narrow();
  r11_4_ptr_to_int();
  r11_6_voidptr_to_int();
  r11_8_remove_const();
  r11_9_zero_as_null();
  (void)r12_1_ambig(1, 2);
  (void)r12_3_comma();
  (void)r15_1_goto(0);

  /* The UDP socket is created using the socket function. */
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
  {
    error();
  }

  /* Server address info and connect */
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons((uint16_t)PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  safe_print("Client is running...\n");
  (void)connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  safe_print("Client is Connected Successfully...\n");

  while (1)
  {
    safe_print("\nEnter Command To Be Executed Remotely: \n");
    safe_input(send_msg, sizeof(send_msg));

    (void)sendto(sockfd, send_msg, strlen(send_msg) + 1U, 0,
           (struct sockaddr *)&server_addr, serverLength);
    (void)recvfrom(sockfd, recv_msg, sizeof(recv_msg), 0,
             (struct sockaddr *)&server_addr, &serverLength);
    safe_print_buf("Server Reply: ", recv_msg);
  }

  /* Close Socket */
  (void)close(sockfd);
  safe_print("Client is offline...\n");
  return 0;
}

int r8_2_sum(int a, int b) { return a + b; }
