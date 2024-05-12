// Fast Website Content(fwc)

#define _POSIX_C_SOURCE 200112L


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT "443"
void delete_proto(char** buffer, size_t size){
	size_t i = 0;
	while((*buffer)[i] != '\0' && i < size - 3){
		if((*buffer)[i] == ':' && (*buffer)[i+1] == '/' && (*buffer)[i+2] == '/'){
			memmove((*buffer), (*buffer)+i+3, size);
			return;
		}
		i++;
	}

}
unsigned char check_buffer(char** buffer, size_t size){
	size_t i = 0;
	while((*buffer)[i] != '\0' && i < size - 4){
		if((*buffer)[i] == '\r' && (*buffer)[i+1] == '\n' && (*buffer)[i+2] == '\r' && (*buffer)[i+3] == '\n'){
			memmove((*buffer), (*buffer)+i+4, size);
			return 0;
		}
		else if(i < size-sizeof("\nLocation: ") && memcmp((*buffer)+i, "\nLocation: ", sizeof("\nLocation: ")-1) == 0){
			memmove((*buffer), (*buffer)+i+sizeof("\nLocation: ")-1, size);
			i = 0;
			while(i < size - 2){
				if((*buffer)[i] == '\r'){
					(*buffer)[i] = '\0';
					return 1;
				}
				i++;
			}
		}
		i++;
	}
	return 0;
}
void sep_hostname_path(char **hostname, char **path){
	size_t l = 0;
	size_t len = strlen(*hostname);

	while(l < len && (*hostname)[l] != '/'){
		l++;
	}
	if(l != len-1){
	(*path) = malloc(sizeof(char) * (len-l)+1);

	memcpy(*path, (*hostname)+l, len-l);
	(*path)[(len-l)] = '\0';

	(*hostname)[l] = '\0';
	}
	else{
		(*path) = malloc(sizeof(char) * 2);
		(*path)[0] = '/';
		(*path)[1] = '\0';
		(*hostname)[l] = '\0';

	}


}
int print_contents(char* arg){
	delete_proto(&arg, 1024);
	struct addrinfo hints = {0};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
	char* hostname = arg;
	char* path = NULL;
	sep_hostname_path(&hostname, &path);
    struct addrinfo *addrs;
    if (getaddrinfo(hostname, PORT, &hints, &addrs) < 0) {
        //fprintf(stderr, "Could not get address of `"HOST"`: %s\n",
          //      strerror(errno));
        return 1;
    }

    int sd = 0;
    for (struct addrinfo *addr = addrs; addr != NULL; addr = addr->ai_next) {
        sd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

        if (sd == -1) break;
        if (connect(sd, addr->ai_addr, addr->ai_addrlen) == 0) break;

        close(sd);
        sd = -1;
    }
    freeaddrinfo(addrs);

    if (sd == -1) {
        //fprintf(stderr, "Could not connect to "HOST":"PORT": %s\n",
          //      strerror(errno));
        return 1;
    }

    //OpenSSL_add_all_algorithms();
    //SSL_load_error_strings();
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());

    if (ctx == NULL) {
        fprintf(stderr, "ERROR: could not initialize the SSL context: %s\n",
                strerror(errno));
        return 1;
    }

    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sd);

    if (SSL_connect(ssl) < 0) {
        fprintf(stderr, "ERROR: could not connect via SSL: %s\n",
                strerror(errno));
        return 1;
    }

    char *request = NULL;
	request = malloc((sizeof("GET  HTTP/1.0\r\n""Host: \r\n""Connection: close\r\n""\r\n") + strlen(path) + strlen(hostname)) * sizeof(char));
	sprintf(request, "GET %s HTTP/1.0\r\n"
        "Host: %s\r\n"
		"Connection: close\r\n"
        "\r\n", path, hostname);
    SSL_write(ssl, request, strlen(request));
	free(request);
    char* buffer = malloc(1024);
    ssize_t n = SSL_read(ssl, buffer, 1024);
	if(check_buffer(&buffer, 1024)){
		SSL_shutdown(ssl);
		SSL_free(ssl);
		SSL_CTX_free(ctx);
		close(sd);

		return print_contents(buffer);
	}
    while (n > 0) {
        fwrite(buffer, 1, n, stdout);
        n = SSL_read(ssl, buffer, 1024);
    }
		
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sd);
	free(buffer);
	return 0;
}
int main(int argc, char **argv)
{
	return print_contents(argv[1]);
}
