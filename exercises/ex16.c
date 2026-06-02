#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// Exercise 16 — Serve a File over HTTP
//
// Concept: Instead of hardcoding HTML in your C code, read it from a file
// and send that. This is how real web servers work — nginx reads files
// from disk and sends them to clients.
//
// You already know file I/O from ex9. Now combine it with your HTTP server.
//
// The challenge: HTTP requires Content-Length to be the exact byte count
// of the body. So you need to know the file size before sending.
// You can get it with fseek/ftell:
//
//   fseek(fp, 0, SEEK_END);   // seek to end of file
//   long size = ftell(fp);    // get current position (= file size)
//   fseek(fp, 0, SEEK_SET);   // seek back to beginning
//
// Tasks:
// 1. Create a file called index.html in your projects/ folder with some HTML
// 2. Set up the HTTP server the same way as ex14/ex15
// 3. When a request comes in, open index.html, read its contents into a buffer
// 4. Send it back as an HTTP response with the correct Content-Length
// 5. If the file can't be opened, send a 500 response:
//    "HTTP/1.1 500 Internal Server Error"
//
// To test: run bin/ex16 then open http://localhost:8080 in your browser.
// You should see your HTML file rendered.
//
// Goal: understand how static file serving works and connect file I/O
// with your HTTP server knowledge.


int main() {

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    const int port = 8080;
    server_addr.sin_port = htons(port);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        return -1;
    }

    if(listen(server_socket, 1) == -1) {
        return -1;
    }

    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    while(1) {
        int client_fd = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
        FILE* fp = fopen("projects/index.html", "r");
        if(fp == NULL) {
            send(client_fd, "HTTP/1.1 500 Internal Server Error", sizeof("HTTP/1.1 500 Internal Server Error"), 0);
            continue;
        }
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        char* buf = malloc(size + 1);

        if(fread(buf, 1, size, fp) != size) {
            return -1;
        }

        buf[size] = '\0';

        char response[size + 256];
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %ld\r\n\r\n%s", size, buf);

        send(client_fd, response, strlen(response), 0);

        free(buf);
        fclose(fp);
        close(client_fd);

    }


    return 0;
}