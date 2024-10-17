#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#include "msg_send_recv.h"

#define PERMS 0666
#define FILE_NAME "msg.txt"

key_t key;
int len;
long mtype_recv, mtype_send;
bool toend;

int msgid;

int main() {
    struct my_msgbuf buf1;
    struct my_msgbuf buf2;

    if((key = ftok(FILE_NAME, 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    if((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    printf("setup message queue success, msgid = %d\n", msgid);

    int pid = fork();

    if(pid < 0) {
        perror("fork");
        exit(1);
    }

    if(pid == 0) {
        printf("this is child process\n");
        sleep(1);
        mtype_recv = 2;
        recv_msg(msgid, buf1, mtype_recv); //child process receive message from parent process in msg_send1
    }

    if(pid > 0) {
        printf("this is parent process, pid = %d\n", pid);
        sleep(2);
        mtype_send = 1;
        send_msg(msgid, buf2, mtype_send); //parent process send message to child process in msg_send1
        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL); 
    }
}
