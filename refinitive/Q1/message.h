#include <arpa/inet.h>
#include <unistd.h>

#define MAX_MSG_SIZE 100
#define PORT 8080 

typedef char *( * func_pack )(void *);
typedef void *(* func_unpack )(char *);

enum {
    msg_id_1,
    msg_id_2
};


/* only  describe the msg head, the msg body has different size according to msg type. 
*/
typedef struct msg
{
    int msg_type;
    int body_len;
} msg;



/*
each message neeed define:
1 pack func:convert message structure into byte stream; the calling side shall free memory
1 unpack func :convert byte stream back to msg structure
*/
typedef struct msg_1 
{
    char body[10];
}msg_1;

char *msg1_pack(void *p_in)
{
    msg *p = malloc(sizeof(msg) + sizeof(msg_1));
    p->msg_type = msg_id_1;
    p->body_len = sizeof(msg_1);
    char *q = (char *)p + sizeof(msg) + 1;
    memcpy(q, p_in, sizeof(msg_1));
    return (char *)p;
}

//calling side need cast the return value to (msg_1 *)
void *msg1_unpack(char *p)
{
    return (p + sizeof(msg));
}

typedef struct msg_2 //used to set max message size
{
    int sz;
}msg_2;

char *msg2_pack(void *p_in)
{
    msg *p = malloc(sizeof(msg) + sizeof(msg_2));
    p->msg_type = msg_id_2;
    p->body_len = sizeof(msg_2);
    char *q =(char *) p + sizeof(msg);
    memcpy(q, p_in, sizeof(msg_2));
    return (char *)p;
}

//calling side need cast the return value to (msg_2 *)
void *msg2_unpack(char *p)
{
    return (p + sizeof(msg));
}

/* 
 * when a new messsge type was added, 
 * it pack/unpack function need defined , and register in below tables according the 
*/

func_pack func_pack_table[]={
    msg1_pack,
    msg2_pack
};

func_unpack func_unpack_table[]={
    msg1_unpack,
    msg2_unpack
};
