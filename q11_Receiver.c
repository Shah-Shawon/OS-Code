#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

// Define the message structure
struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    // Generate the same key as the sender (must match)
    key_t key = ftok("mqfile", 65);

    // Access the message queue
    int msgid = msgget(key, 0666 | IPC_CREAT);

    // Prepare message buffer to receive the message
    struct msgbuf message;

    // Receive the message of type 1
    msgrcv(msgid, &message, sizeof(message.mtext), 1, 0);

    // Print the received message
    printf("Message received: %s\n", message.mtext);

    // Destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}