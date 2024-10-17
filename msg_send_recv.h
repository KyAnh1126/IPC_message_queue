#ifndef MSG_SEND_RECV
#define MSG_SEND_RECV

#define TEXT_SZ 256

//my_msgbuf - structure of a message, including a type and text
struct my_msgbuf {
    long mtype;
    char mtext[TEXT_SZ];
};

//define send and receive message function
void send_msg(int msgid, struct my_msgbuf buf, long mtype);
void recv_msg(int msgid, struct my_msgbuf buf, long mtype);


#endif