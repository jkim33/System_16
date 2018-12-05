#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
  key_t key;
  int shmid;
  char *data;

  key = ftok("somefile", 'R');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *)0, 0);

  if(!data[0]) {
    printf("Segment Created.\n");
  }
  else {
    printf("Segment Contents: %s\n", data);
  }

  printf("Would like to change the data in the segment? (Y/N): ");
  char input[8];
  fgets(input, 8, stdin);
  if (strncmp(input, "Y", 1) == 0) {
    printf("Enter a new string: ");
    char new[200];
    fgets(new, 200, stdin);
    new[strlen(new)-1] = 0;
    strcpy(data, new);
  }

  printf("Would you like to delete the data in the segment? (Y/N): ");
  fgets(input, 8, stdin);
  if (strncmp(input, "Y", 1) == 0) {
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
  }
  
  return 0;
}
