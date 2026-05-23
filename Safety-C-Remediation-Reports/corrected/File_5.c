/********************************************************************************
 * @file
 * @author [NVombat]
 * @brief Server-side implementation of Remote Command Execution Using UDP
 * @see remote_command_exec_udp_server.c
 ********************************************************************************/

#ifdef _WIN32
#define bzero(b, len) \
  (memset((b), '\0', (len)), (void)0) /* BSD name not in windows */
#define close _close
#include <Ws2tcpip.h>
#include <io.h>
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED_MACRO 99U

int r7_1_octal = 10; /* Rule 7.1: No octal constants */

unsigned int r7_2_unsigned = 10;

long r7_3_lowerell = 10L; /* Rule 7.3: Use 'L' not 'l' */

char *r7_4_str = "executed";

int r8_2_sum(int, int);

/* Rule 8.3: Only used in this file, so make static */
static const int r8_3_global = 0;

int r8_7_helper(void) { return 1; }

/* Rule 8.10: Inline functions shall be static */
static inline int r8_10_inline(void) { return 0; }

static void r9_1_uninit(void) {
  int x = 0; /* Rule 9.1: Initialize automatic variable */
  if (x) { }
}

static void r10_3_narrow(void) {
  float f = 123.45f;
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
  intptr_t i = (intptr_t)vp; /* Rule 11.6: Use intptr_t */
  (void)i;
}

static void r11_8_remove_const(void) {
  const int c = 5;
  const int *pc = &c; /* Rule 11.8: Do not remove const */
  (void)pc;
}

static void r11_9_zero_as_null(void) {
  int *p = NULL; /* Rule 11.9: Use NULL */
  (void)p;
}

static int r12_1_ambig(int a, int b) {
  if ((a & b) == 0) { /* Rule 12.1: Parentheses for precedence */
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
  /* Rule 15.3: No goto, use loop */
  while (n-- > 0) {
    s++;
  }
  return s;
}

#define PORT 10000 /* Define port over which communication will take place */

/**
 * @brief Utility function used to print an error message to `stderr`.
 * It prints an implementation-defined error message.
 */
void error(void)
{
  perror("Socket Creation Failed");
  /* Rule 15.1: Do not exit here, let caller handle error */
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main(void)
{
  /* Variable Declarations */
  uint32_t sockfd; /* socket descriptor */
  char recv_msg[1024];
  char success_message[] = "Command Executed Successfully!\n"; /* buffers */
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr; /* server/client addresses */
  socklen_t clientLength = (socklen_t)sizeof(client_addr); /* size of address */
  int ret;
  FILE *fp;
  char output_buffer[1024];
  size_t bytes_read;

  (void)r8_7_helper();
  (void)r8_10_inline();
  r9_1_uninit();
  r10_3_narrow();
  r11_4_ptr_to_int();
  r11_6_voidptr_to_int();
  r11_8_remove_const();
  r11_9_zero_as_null();
  (void)r12_1_ambig(1, 2);
  (void)r12_3_comma();
  (void)r15_1_goto(0);

  /* The UDP socket is created using the socket function. */
  sockfd = (uint32_t)socket(AF_INET, SOCK_DGRAM, 0);
  if ((int)sockfd < 0)
  {
    error();
    return 1; /* Rule 15.1: Return at end */
  }

  /* Server Address Information and bind */
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  ret = bind((int)sockfd, (struct sockaddr *)&server_addr, (socklen_t)sizeof(server_addr));
  if (ret < 0)
  {
    error(); /* If binding is unsuccessful */
    close((int)sockfd);
    return 1; /* Rule 15.1: Return at end */
  }

  printf("Server is Connected Successfully...\n");

  /* Communication loop */
  while (1)
  {
    bzero(recv_msg, sizeof(recv_msg));
    ret = (int)recvfrom((int)sockfd, recv_msg, sizeof(recv_msg) - 1, 0,
             (struct sockaddr *)&client_addr, &clientLength);
    if (ret < 0)
    {
      error();
      continue;
    }
    recv_msg[sizeof(recv_msg) - 1] = '\0';

    printf("Command Output: \n");

    /* Rule 21.6: Do not use system(). Instead, use popen() to capture output safely. */
    fp = popen(recv_msg, "r");
    if (fp != NULL)
    {
      while ((bytes_read = fread(output_buffer, 1U, sizeof(output_buffer) - 1U, fp)) > 0U)
      {
        output_buffer[bytes_read] = '\0';
        printf("%s", output_buffer);
      }
      (void)pclose(fp);
    }
    else
    {
      printf("Failed to execute command.\n");
    }
    printf("Command Executed\n");

    sendto((int)sockfd, success_message, (size_t)strlen(success_message) + 1U, 0,
           (struct sockaddr *)&client_addr, clientLength);
  }

  /* Close socket */
  close((int)sockfd);
  printf("Server is offline...\n");
  return 0;
}

int r8_2_sum(int a, int b) { return a + b; }
