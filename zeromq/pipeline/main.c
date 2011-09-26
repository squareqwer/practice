/*pipeline����������ݷ��͡�

Ҫ�㣺
  1. bind() Ҫ���� connect()������ connecting fail
  2. �������������zmq_connect() / zmq_bind() Ҫ�öԡ�

���Զ�� push һ�� pull����ʱ push Ҫʹ�� zmq_connect()���� pull Ҫʹ�� zmq_bind()��

 
��һ�������һ�� push����� pull���� push ʹ�� zmq_bind()���� pull ʹ�� zmq_connect()
*/
 
#include <zmq.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void *push_thread(void *ctx)
{
        pthread_t pid;
        zmq_msg_t msg;
        void *push;
        char buf[80];

        pid  = pthread_self();
        push = zmq_socket(ctx, ZMQ_PUSH);
        zmq_connect(push, "inproc://pull-it");

        while (1)
        {
                sprintf(buf, "#%p send\n", pid);

                zmq_msg_init_size(&msg, strlen(buf)+1);
                memcpy(zmq_msg_data(&msg), buf, strlen(buf)+1);
                zmq_send(push, &msg, 0);
                zmq_msg_close(&msg);

                sleep(5);
        }

        return (void *)0;
}

int main()
{
        zmq_msg_t msg;
        void *ctx, *pull;
        pthread_t pid1, pid2;

        ctx  = zmq_init(0);
        pull = zmq_socket(ctx, ZMQ_PULL);
        zmq_bind(pull, "inproc://pull-it");

        pthread_create(&pid1, NULL, push_thread, ctx);
        pthread_create(&pid2, NULL, push_thread, ctx);

        while (1)
        {
                zmq_recv(pull, &msg, 0);
                printf("recv: %s", (char *)zmq_msg_data(&msg));
                zmq_msg_close(&msg);
        }

        return 0;
}