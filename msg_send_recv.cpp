#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#include "msg_send_recv.h"

//send_msg() performs send a message to a queue based on given msgid, child process in other program can receive message from this function
//buf store mtype & mtext
void send_msg(int msgid, struct my_msgbuf buf, long mtype) {
    buf.mtype = mtype;
    int len;
    printf("Enter lines of text (type 'quit' to quit):\n");
    while(1) {
        fgets(buf.mtext, sizeof buf.mtext, stdin); //get input from user and store in buf.mtext
        len = strlen(buf.mtext);

        if(buf.mtext[len - 1] == '\n') buf.mtext[len - 1] = '\0'; //replace '\n' (if exist) to '\0'

        //handle when user types quit
        //append a string "end" at the end of this mtype (send signal to child process in other program, to terminate receiving message)
        if(strcmp(buf.mtext, "quit") == 0) {
            strcpy(buf.mtext, "end");
            len = strlen(buf.mtext);
            if (msgsnd(msgid, &buf, len + 1, 0) == -1) perror("msgsnd");
            printf("finished send_msg\n");
            break;
        }
        
        if(msgsnd(msgid, &buf, len + 1, 0) == -1) perror("msgsnd"); //send message (buf) to message queue with msgid, len + 1 include '\0', flag 0 means no flag setup

        // printf("send message success, mtype = %ld, mtext = %s\n", buf.mtype, buf.mtext);
    }
}

//recv_msg performs receive a message in a queue from parent process in other program
void recv_msg(int msgid, struct my_msgbuf buf, long mtype) {
    int toend;
    while(1) {
        //receive message from message queue with msgid (type = mtype), store into buffer
        int msgrcv_ret = msgrcv(msgid, &buf, sizeof(buf.mtext), mtype, 0);
        // printf("msgrcv_ret = %d\n", msgrcv_ret);

        if(msgrcv_ret == -1) {
            perror("msgrcv");
            // exit(1);
        }

        //console message from a process
        printf("someone: %s\n", buf.mtext);

        //user type 'quit', so this process stop receiving message
        toend = strcmp(buf.mtext, "end");
        if(toend == 0) {
            printf("finished recv_msg\n");
            break;
        }
    }
}