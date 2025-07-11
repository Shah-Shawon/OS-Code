// message_sender.c
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

// Define the message structure
struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    // Generate a unique key (same file & id must be used in receiver)
    key_t key = ftok("mqfile", 65);

    // Create message queue or get its ID if already exists
    int msgid = msgget(key, 0666 | IPC_CREAT);

    // Fill the message
    struct msgbuf message;
    message.mtype = 1;
    strcpy(message.mtext, "Hello from sender");

    // Send the message
    msgsnd(msgid, &message, sizeof(message.mtext), 0);

    printf("Message sent: %s\n", message.mtext);
    return 0;
}