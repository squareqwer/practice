//publish/subscribe, 一个one-to-many的消息发布。一个publisher，多个subscriber。
//如果pub发布消息的时候，sub没有连接上来，则此消息，sub是收不到的。
//注意：subscribe 初始化的时候一定要设置filter，否则收不到任何消息。



#include <zmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static char *
s_recv (void *socket) {
    zmq_msg_t message;
    zmq_msg_init (&message);
    if (zmq_recv (socket, &message, 0))
        exit (1);           //  Context terminated, exit

    int size = zmq_msg_size (&message);
    char *string = malloc (size + 1);
    memcpy (string, zmq_msg_data (&message), size);
    zmq_msg_close (&message);
    string [size] = 0;
    return (string);
}

void *sub_thread(void *ctx)
{
    void *sub = zmq_socket(ctx, ZMQ_SUB);
    zmq_connect(sub, "tcp://127.0.0.1:8888");
    zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "", 0);    // no filter

    while (1)
    {
        char *msg = s_recv(sub);
        printf("client in-sub: %s\n", msg);
        free(msg);
    }

    return (void *)0;
}

int main()
{
    void *ctx, *sub;
    pthread_t pid;

    ctx = zmq_init(1);
    sub = zmq_socket(ctx, ZMQ_SUB);
    zmq_connect(sub, "tcp://127.0.0.1:8888");
    zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "", 0);    // no filter

    printf("begin client-sub!\n");
    pthread_create(&pid, NULL, sub_thread, ctx);

    while (1)
    {
        char *msg = s_recv(sub);
        printf("client sub: %s\n", msg);
        free(msg);
    }

    zmq_term(ctx);
    return 0;
}