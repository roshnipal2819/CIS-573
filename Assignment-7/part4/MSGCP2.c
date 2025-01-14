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
        printf("Usage: %s <key> <output file>\n", argv[0]);
        exit(1);
    }

    key_t key = atoi(argv[1]);
    char *output_file = argv[2];
    int msgid = msgget(key, 0666);

    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    FILE *file = fopen(output_file, "w");
    if (!file) {
        perror("fopen");
        exit(1);
    }

    struct message msg;

    // Receive messages of type 1 and write to output file
    while (1) {
        if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        if (strcmp(msg.msg_text, "done") == 0) {
            break;  // Stop when "done" message is received
        }

        fputs(msg.msg_text, file);
    }

    fclose(file);

    // Send type 2 message to MSGCP1 to indicate completion
    msg.msg_type = 2;
    strcpy(msg.msg_text, "copy_complete");
    if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    return 0;
}
