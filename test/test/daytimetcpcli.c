//
//  main.c
//  test
//
//  Created by zuowu on 2020/10/20.
//  Copyright © 2020 zuowu. All rights reserved.
//


#include <unp.h>

int main(int argc, const char ** argv) {
    // insert code here...
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    
    if (argc != 2) {
        err_quit("usage: a.out <IPaddress>");
    }
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_sys("socket error");
    }
    
    bzero(&servaddr, sizeof(servaddr)); //bzero 清空地址结构体
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    
    //inet_pton 将字符串地址转换为数字型 存放到 servaddr.sin_addr
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        err_quit("inet_pton error for %s", argv[1]);
    }
    
    
    /* 在头文件unp.h中，我们使用#define把SA定义为structsockaddr，也就是通用套接字地址结构。每当一个套接字函数需要一个指向某个套接字地址结构的指针时，这个指针必须强制类型转换成一个指向通用套接字地址结构的指针。这是因为套接字函数早于ANSIC标准，20世纪80年代早期开发这些函数时，ANSIC的void*指针类型还不可用。问题是“structsockaddr”长达15个字符，往往造成源代码行超出屏幕（或者书页，若是排印在书上）的右边缘，因此我们把它缩减成SA。我们将在解释图33时详细讨论通用套接字地址结构
     */
    //connect 建立连接
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        err_sys("connect error");
    }
    
    //read 读取 read 返回单次读取长度 每次读取都会吧recvline[n] = 0, 清空字符串最后的结束符号
    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF) {
            err_sys("fputs error");
        }
    }
    
    if (n < 0) {
        err_sys("read error");
    }
    
    exit(0);
    return 0;
}
