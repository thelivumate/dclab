#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 10

int list[MAX], n, c;

void display() {
    int i;
    printf("\nProcesses-->");
    for(i = 1; i <= n; i++)
        printf("\t %d", i);
    printf("\nAlive-->");
    for(i = 1; i <= n; i++)
        printf("\t %d", list[i]);
    printf("\ncoordinator is::%d", c);
}

void bully() {
    int ch, crash, activate, i, gid, flag = 0, subcdr;
    do {
        printf("\n1.Crash\n2.Activate\n3.Display\n4.Exit\nEnter Your choice::");
        scanf("%d", &ch);
    switch(ch) {
    
        case 1:
    printf("\nEnter Process no. to Crash::");
    scanf("%d", &crash);
    if(list[crash])
        list[crash] = 0;
    else {
        printf("\nProcess is already dead!!");
        break;
    }

    do {
        printf("\nEnter election generator id::");
        scanf("%d", &gid);
        if(gid == crash) {
            printf("\nInvalid election generator ID. Please enter a valid one.\n");
        } else if(gid < 1 || gid > n || !list[gid]) {
            printf("\nInvalid election generator ID. It should be an alive process ID.\n");
        }
    } while(gid == crash || gid < 1 || gid > n || !list[gid]);

    flag = 0;
    if(crash == c) {
        for(i = gid + 1; i <= n; i++) {
            printf("\nmessage is sent from %d to %d", gid, i);
            if(list[i]) {
                subcdr = i;
                printf("Response is sent from %d to %d", i, gid);
                flag = 1;
            }
        }
        if(flag == 1)
            c = subcdr;
        else
            c = gid;
    } else if (c == crash) {
        // If crashed process is the coordinator, find the next highest priority alive process as the new coordinator
        for(i = crash + 1; i <= n; i++) {
            if(list[i]) {
                c = i;
                break;
            }
        }
    }
    display();
    break;



            case 2:
                //activate
                printf("\nEnter Process no. to Activated::");
                scanf("%d", &activate);
                if(!list[activate])
                    list[activate] = 1;
                else {
                    printf("\nProcess is already alive!!");
                    break;
                }

                flag = 0;
                if(activate == n) {
                    c = n;
                    break;
                }

                for(i = activate + 1; i <= n; i++) {
                    printf("\nMessage is sent from %d to %d", activate, i);
                    if(list[i]) {
                        subcdr = i;
                        printf("Response is sent from %d to %d", i, activate);
                        flag = 1;
                    }
                }
                if(flag == 1)
                    c = subcdr;
                else
                    c = activate;
                display();
                break;
            case 3:
                display();
                break;
            case 4:
                break;
        }
    } while(ch != 4);
}

int main() {
    int i, j;
    printf("\nEnter no. of process::");
    scanf("%d", &n);
    for(i = 1; i <= n; i++) {
        printf("\nEnter Process %d is Alive or not(0/1)::", i);
        scanf("%d", &list[i]);
        if(list[i])
            c = i;
    }
    display();
    printf("\nBULLY ALGORITHM\n");
    bully();
    return 0;
}

