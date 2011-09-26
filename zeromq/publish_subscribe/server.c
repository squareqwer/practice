//publish/subscribe, 一个one-to-many的消息发布。一个publisher，多个subscriber。
//如果pub发布消息的时候，sub没有连接上来，则此消息，sub是收不到的。
//注意：subscribe 初始化的时候一定要设置filter，否则收不到任何消息。
#include <zmq.h>
#include <pthread.h>
#include <unistd.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

static int
s_send (void *socket, char *string) {
    int rc;
    zmq_msg_t message;
    zmq_msg_init_size (&message, strlen (string));
    memcpy (zmq_msg_data (&message), string, strlen (string));
    rc = zmq_send (socket, &message, 0);
    assert (!rc);
    zmq_msg_close (&message);
    return (rc);
}

void *sub_thread(void *ctx)
{
    void *sub = zmq_socket(ctx, ZMQ_SUB);
    zmq_connect(sub, "inproc://in-pub");
    zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "", 0);    // no filter

    printf("begin in-sub!\n");
    while (1)
    {
        char *msg = s_recv(sub);
        printf("in-sub: %s\n", msg);
        free(msg);
    }

    return (void *)0;
}
int main()
{
    void *ctx, *pub;
    pthread_t pid;

    ctx = zmq_init(1);
    pub = zmq_socket(ctx, ZMQ_PUB);
    zmq_bind(pub, "inproc://in-pub");
    zmq_bind(pub, "tcp://127.0.0.1:8888");

    pthread_create(&pid, NULL, sub_thread, ctx);

    int i = 0;
    printf("begin pub!\n");
    while (1)
    {
        char msg[80];
        sprintf(msg, "num %d", i++);
        s_send(pub, msg);
        sleep(2);
    }

    zmq_close(pub);
    zmq_term(ctx);
    return 0;
}
