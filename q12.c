#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>  // For wait()

// Define message structure
struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    // Generate unique key using a file and an integer ID
    key_t key = ftok("mqfile", 65);
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create or get message queue with rw permissions
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget failed");
        exit(1);
    }

    struct msgbuf msg;

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process: receive message
        msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0);  // mtype == 1
        printf("Child received: %s\n", msg.mtext);
    } else {
        // Parent process: send message
        msg.mtype = 1;  // Message type 1
        sprintf(msg.mtext, "Hello from parent");
        msgsnd(msgid, &msg, sizeof(msg.mtext), 0);  // Send message

        wait(NULL);  // Wait for child to finish

        // Delete message queue
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}

