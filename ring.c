#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 10

int list[MAX], n, c;

void display() {
    int i;
    printf("\nProcesses-->");
    for (i = 1; i <= n; i++)
        printf("\t %d", i);
    printf("\nAlive-->");
    for (i = 1; i <= n; i++)
        printf("\t %d", list[i]);
    printf("\nCoordinator is::%d", c);
}

void ring() {
    int msg[MAX], ring_n, k, i;
    int ch, crash, activate, gid, flag, subcdr;

    do {
        printf("\n1. Crash\n2. Activate\n3. Display\n4. Exit\nEnter your choice:: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("\nEnter Process no. to Crash:: ");
                scanf("%d", &crash);

                if (crash < 1 || crash > n) {
                    printf("\nInvalid process number. Please enter a valid one.\n");
                    break;
                }

                if (list[crash]) {
                    list[crash] = 0;
                } else {
                    printf("\nProcess is already dead!!\n");
                    break;
                }

                do {
                    printf("\nEnter election generator id:: ");
                    scanf("%d", &gid);

                    if (gid == crash || gid < 1 || gid > n) {
                        printf("\nEnter a valid generator id:: ");
                    }
                } while (gid == crash || gid < 1 || gid > n);

                flag = 0;
                k = 1;

                if (crash == c) {
                    msg[k++] = gid;

                    for (i = (gid + 1) % n; i != gid; i = (i + 1) % n) {
                        if (list[i]) {
                            printf("\nMessage is sent to %d (k = %d)", i, k);
                            msg[k++] = i;
                        }
                    }

                    subcdr = 0;

                    for (i = 1; i < k; i++) {
                        printf("\nmsg:: %d\n", msg[i]);

                        if (subcdr < msg[i]) {
                            subcdr = msg[i];
                        }
                    }

                    c = subcdr;
                }

                display();
                break;

            case 2:
                printf("\nEnter Process no. to Activate:: ");
                scanf("%d", &activate);

                if (activate < 1 || activate > n) {
                    printf("\nInvalid process number. Please enter a valid one.\n");
                    break;
                }

                if (!list[activate]) {
                    list[activate] = 1;
                } else {
                    printf("\nProcess is already alive!!\n");
                    break;
                }

                if (activate == n) {
                    c = n;
                    break;
                }

                for (i = activate + 1; i <= n; i++) {
                    printf("\nMessage is sent from %d to %d", activate, i);

                    if (list[i]) {
                        subcdr = i;
                        printf("\nResponse is sent from %d to %d", i, activate);
                        flag = 1;
                    }
                }

                if (flag == 1) {
                    c = subcdr;
                } else {
                    c = activate;
                }

                display();
                break;

            case 3:
                display();
                break;

            case 4:
                break;

            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
        }
    } while (ch != 4);
}

int main() {
    int i;

    printf("\nEnter the number of processes:: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("\nInvalid number of processes. Please enter a valid value between 1 and %d.\n", MAX);
        return 1;
    }

    for (i = 1; i <= n; i++) {
        printf("\nEnter Process %d is Alive or not (0/1):: ", i);
        scanf("%d", &list[i]);

        if (list[i]) {
            c = i;
        }
    }

    display();
    printf("\nRING ALGORITHM\n");
    ring();
    return 0;
}
