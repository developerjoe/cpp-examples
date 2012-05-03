#include "sockettest.h"
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <fcntl.h>
#include <netinet/in.h>
#include <cstring>

void socketTest()
{
  /* 
   * A socket is an endpoint of and inter-process communication flow
   * across a computer network. 
   * http://en.wikipedia.org/wiki/Network_socket
   * 
   * Parameters
   * 
   * Domain
   * The first parameter selects the protocol family which will be used
   * for communication. Interestingly enough one of the available domains
   * is Amateur radio. We're not going to use that one, but still, it kind
   * of makes me interested in investigating that more.
   * 
   * Parameter Used: AF_INET
   * 
   * AF_INT represents IPv4 Internet Protocols
   * 
   * Type
   * 
   * The second parameter specifies the communication semantics, details such
   * as reliability, ordering, and prevention of duplication of messages.
   * 
   * http://publib.boulder.ibm.com/infocenter/pseries/v5r3/index.jsp?topic=/com.ibm.aix.progcomm/doc/progcomc/skt_types.htm
   * 
   * Parameter Used: SOCK_STREAM
   * 
   * SOCK_STREAM provides reliable two-way, connection-based byte streams.
   * This is implemented on top of TCP.
   * 
   * Protocol
   * 
   * This parameter describes the protcol to be used with the socket. Based 
   * on the parameters we have provided no additional information is needed,
   * so we leave this blank.
   */
  int sock = socket(AF_INET,SOCK_STREAM, 0);
  
  printf("Socket: %u\r\n", sock);
  
  /*
   * Tell the operating system that I can reuse local addresses. Generally
   * when binding to a port, the port will be in a waiting state for a few
   * minutes after you close the socket. This option allows you to bind to 
   * the port again without waiting.
   * 
   * Zero returned on success -1 on failure.
   */
  int reuseAddress = 1;
  int optionResult = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseAddress, sizeof(reuseAddress));
  
  printf("Option Result: %u\r\n", optionResult);
  
  /* 
   * Set the socket as non-blocking, do this prevents read and write calls
   * from blocking the process. Instead they will fail with a request to try again. */
  int options;
  
  /* Go get the current options set on the socket. If options are less than zero
   * There has been an error */
  options = fcntl(sock,F_GETFL);
  
  printf("Initial Socket Options: %u\r\n", options);
  
  // Set O_NONBLOCK
  options = (options | O_NONBLOCK);
  
  printf("Non-block Socket Options: %u\r\n", options);
  
  int socketOptionsResult = fcntl(sock,F_SETFL,options);
  
  printf("Result of Setting Options: %u\r\n", socketOptionsResult);
  
  /*
   * Bind the socket to the requested address and port */
  struct sockaddr_in serverAddress;
  // set all the bits to zero
  memset(&serverAddress, 0, sizeof serverAddress);
  
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = 4000;
  
  /* Attempt to bind the value. In this instance we are binding to 
   * any address with the port of 4000 */
  
  int bindResult = bind(sock, (struct sockaddr *) &serverAddress, sizeof serverAddress);
  
  printf("Bind Result: %u\r\n", bindResult);
  
  // listen for incoming connections
  int listenResult = listen(sock, 5);
  
  printf("Listen Result: %u\r\n", bindResult);
  
  /* This function closes a file descriptor. We use this to clean up after
   * socket. Close returns zero on success or -1 on error */
  int closeResult = close(sock);
  
  printf("Close Result: %u\r\n", closeResult);
}