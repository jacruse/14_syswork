#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define KEY 48

int main(int argc, char ** argv) {
  int sd;
  int val;
  union semun value_passer;
  
  if (argc < 2) {
    printf("Too few args...\nTry again next time\n");
    printf("Maybe try -c N, -v, or -r\n");
    exit(0);
  }

  if (!strcmp(argv[1], "-c")) {
    if (argc < 3) {
      printf("not enough args supplied\n");
      exit(0);
    }
    
    if ((sd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644)) == -1) {
      if (!(strcmp(strerror(errno), "File exists"))) {
	printf("semaphore already exists\n");
	exit(0);
      }
      printf("%s\n", strerror(errno));
      exit(0);
    }

    printf("semaphore created: %d\n", sd);

    value_passer.val = atoi(argv[2]);
    if ((semctl(sd, 0, SETVAL, value_passer)) == -1) {
       printf("%s\n", strerror(errno));
      exit(0);
    }

    if ((val = semctl(sd, 0, GETVAL)) == -1) {
      printf("%s\n", strerror(errno));
      exit(0);
    }

    printf("value set to: %d\n", val);
  }

  else if (!strcmp(argv[1], "-v")) {
    if ((sd = semget(KEY, 1, 0)) == -1) {
      printf("%s\n", strerror(errno));
      exit(0);
    }

    if ((val = semctl(sd, 0, GETVAL)) == -1) {
      printf("%s\n", strerror(errno));
      exit(0);
    }

    printf("Semaphore %d value: %d\n", sd, val);
	
  }

  else if (!strcmp(argv[1], "-r")) {
    if ((sd = semget(KEY, 1, 0)) == -1) {
      printf("%s\n", strerror(errno));
      exit(0);
    }

    if ((semctl(sd, 0, IPC_RMID)) == -1) {
      printf("%s\n", strerror(errno));
      exit(0);
    }

    printf("semaphore removed\n");
    
  }

  else {
    printf("HEY! Give me something to work with...\n");
    printf("Maybe try -c N, -v, or -r\n");
    exit(0);
  }

}
