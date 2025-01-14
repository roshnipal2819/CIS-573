#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

// Define the message structure
struct mymsgbuf {
    long msg_type;         // Message type
    char msg_text[128];     // Message content
};

// Function to print usage instructions
void print_usage() {
    printf("Usage:\n");
    printf("  msqQTest -C <key>          Create message queue\n");
    printf("  msqQTest -S <key> <type> <text>  Send message to queue\n");
    printf("  msqQTest -R <key> <type>   Receive message from queue\n");
    printf("  msqQTest -D <key>          Delete message queue\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        print_usage();
        exit(1);
    }

    // Extract the flag and key from command line arguments
    char flag = argv[1][1];
    key_t key = atoi(argv[2]);
    int msqid;

    switch (flag) {
        case 'C':  // Create message queue
        case 'c':
            msqid = msgget(key, IPC_CREAT | 0666);
            if (msqid < 0) {
                perror("msgget");
                exit(1);
            }
            printf("Message queue created with key: %d\n", key);
            break;

        case 'S':  // Send message to queue
        case 's': {
            if (argc < 5) {
                print_usage();
                exit(1);
            }

            long msg_type = atol(argv[3]);
            struct mymsgbuf msg;
            msg.msg_type = msg_type;
            strncpy(msg.msg_text, argv[4], sizeof(msg.msg_text) - 1);
            msg.msg_text[sizeof(msg.msg_text) - 1] = '\0';  // Null-terminate

            msqid = msgget(key, 0666);
            if (msqid < 0) {
                perror("msgget");
                exit(1);
            }

            if (msgsnd(msqid, &msg, sizeof(msg.msg_text), 0) < 0) {
                perror("msgsnd");
                exit(1);
            }
            printf("Message sent (Type: %ld): %s\n", msg_type, msg.msg_text);
            break;
        }

        case 'R':  // Receive message from queue
        case 'r': {
            if (argc < 4) {
                print_usage();
                exit(1);
            }

            long msg_type = atol(argv[3]);
            struct mymsgbuf msg;

            msqid = msgget(key, 0666);
            if (msqid < 0) {
                perror("msgget");
                exit(1);
            }

            if (msgrcv(msqid, &msg, sizeof(msg.msg_text), msg_type, 0) < 0) {
                perror("msgrcv");
                exit(1);
            }
            printf("Message received (Type: %ld): %s\n", msg.msg_type, msg.msg_text);
            break;
        }

        case 'D':  // Delete message queue
        case 'd':
            msqid = msgget(key, 0666);
            if (msqid < 0) {
                perror("msgget");
                exit(1);
            }

            if (msgctl(msqid, IPC_RMID, NULL) < 0) {
                perror("msgctl");
                exit(1);
            }
            printf("Message queue with key %d deleted.\n", key);
            break;

        default:
            print_usage();
            exit(1);
    }

    return 0;
}
