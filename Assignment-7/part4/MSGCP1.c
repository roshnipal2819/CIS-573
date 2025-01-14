#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_SIZE 128  // Size of message content

struct message {
    long msg_type;           // Type of message
    char msg_text[MSG_SIZE];  // Message content
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <key> <input file>\n", argv[0]);
        exit(1);
    }

    key_t key = atoi(argv[1]);
    char *input_file = argv[2];
    int msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    FILE *file = fopen(input_file, "r");
    if (!file) {
        perror("fopen");
        exit(1);
    }

    struct message msg;
    msg.msg_type = 1;  // Type 1 for file content messages

    while (fgets(msg.msg_text, MSG_SIZE, file)) {
        if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    // Send a "done" message to indicate end of file
    strcpy(msg.msg_text, "done");
    if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    fclose(file);

    // Wait for type 2 message from MSGCP2
    if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 2, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }

    printf("Copy completed. Deleting message queue.\n");
    msgctl(msgid, IPC_RMID, NULL);  // Delete the message queue

    return 0;
}
