#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#define   group_size  10

#pragma pack(1)
//member info
typedef struct _member_{
    char id;
    struct sockaddr_in si;
}member;
#pragma pack()

//member group
typedef struct _group_{
    int capacity;
    int pos;
    member  member_array[group_size];
}group;


#define  client_hello      0x00
#define  server_hello      0x01
#define  member_report     0x02
#define  member_talk       0x03
#define  heart_beat        0x04
#define  ack               0x05
#define  member_request    0x06

#endif
