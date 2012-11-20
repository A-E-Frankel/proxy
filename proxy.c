#include <stdio.h>
#include "csapp.h"

#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

static const char *user_agent = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
static const char *accept = "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n";
static const char *accept_encoding = "Accept-Encoding: gzip, deflate\r\n";

int main(int argc, char **argv)
{
    //printf("%s%s%s", user_agent, accept, accept_encoding);
   
    int listenfd, connfd, port, clientlen;
    struct sockaddr_in clientaddr;

    if (argc != 2){
        fprintf(stderr, "Usage: %s <port> \n", argv[0]);
        exit(0);
    }

    /*Initialize a listening port and listen*/

    port = atoi(argv[1]);

    listenfd = Open_listenfd(port);

    /*Main Loop*/
    while(1){

        /*Accept client connection*/
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        
        /*Handle client request*/
        handle_request(connfd);

        /*Close connection*/
        Close(connfd);        
    }

    return 0;
}

int handle_request(int connfd){
    rio_t c_rio, s_rio;
    char c_req_buf[MAXLINE];
    char s_req_buf[MAXLINE];
    char resp_buf[MAXLINE];
    char *host;
    int n, clientfd;
    int port = 80;

    /*Read request line & headers*/
    Rio_readinitb(&c_rio, connfd);
    Rio_readlineb(&c_rio, c_req_buf, MAXLINE);

    //SOBHAGYA - maybe as a separate function? Look at 11.6 for more on this part
    //Please place your final resquest in s_req_buf,
    //and grab the host and port for me, if given
        
    
    /*Send request to server*/
    clientfd = Open_clientf(host, port);
    Rio_readinitb(&s_rio, clientfd);
    Rio_writen(clientfd, s_req_buf, strlen(s_req_buf));

    /*Recieve server response and send to client*/
    while((n = Rio_readlineb(&s_rio, resp_buf, MAXLINE)) > 0){
        Rio_writen(connfd, respbuf, n);
    }

    if (n < 0){
      //Error handling - maybe try again?
    }
    
    /*Close server connection*/
    Close(clientfd);
     
    return;
}
