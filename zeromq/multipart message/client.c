//数据可能很长，比如一个大文件，所以可以将数据分成多个 message 来发送，但逻辑上知道这些 message 应该合并成一个处理。
//注意：ZMQ_REQ / ZMQ_REP (request / reply pattern) 在 recv 消息后，一定要 send back 信息，这就是 request-reply 的核心。
#include <zmq.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void myfree(void *data, void *hint)
{
        printf("free\n");
        free(data);
}

#define MY_BUF_SIZE     1024

/* ./fclient <file> */
int main(int argc, char *argv[])
{
        FILE *fp;
        char *buf;
        size_t n;
        void *ctx, *s;
        zmq_msg_t msg;

        if ( argc != 2 )
        {
                fprintf(stderr, "./fclient <file>\n");
                return 1;
        }

        fp = fopen(argv[1], "rb");
        if ( fp == NULL )
        {
                fprintf(stderr, "open file fail: %d\n", errno);
                return 2;
        }

        ctx = zmq_init(1);
        s   = zmq_socket(ctx, ZMQ_REQ);
        zmq_connect(s, "tcp://127.0.0.1:5555");

        // filename
        zmq_msg_init_size(&msg, strlen(argv[1])+1);
        memcpy(zmq_msg_data(&msg), argv[1], strlen(argv[1])+1);
        zmq_send(s, &msg, 0);
        zmq_msg_close(&msg);

        zmq_msg_init(&msg);
        zmq_recv(s, &msg, 0);
        zmq_msg_close(&msg);

        // content
        while (1)
        {
                buf = (char *)malloc(MY_BUF_SIZE);
                n = fread(buf, 1, MY_BUF_SIZE, fp);
                printf("n = %d\n", n);
                if ( n < MY_BUF_SIZE )
                {
                        printf("feof = %d\n", feof(fp));
                        zmq_msg_init_data(&msg, buf, n, myfree, NULL);
                        zmq_send(s, &msg, 0);
                        zmq_msg_close(&msg);
                        break;
                }

                zmq_msg_init_data(&msg, buf, n, myfree, NULL);
                zmq_send(s, &msg, ZMQ_SNDMORE);
                zmq_msg_close(&msg);
        }

        zmq_msg_init(&msg);
        zmq_recv(s, &msg, 0);
        zmq_msg_close(&msg);


        zmq_close(s);
        zmq_term(ctx);

        fclose(fp);
        puts("done.");
        return 0;
}

