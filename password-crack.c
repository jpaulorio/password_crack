//gcc password-crack.c -o password-crack -framework OpenCL
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define PASSWORD_SIZE (5)
#define FIRST_CHAR (0)
#define LAST_CHAR (127)

int main ()
{
  time_t t1;
  time_t t2;

  printf("Type a password: ");

  char password[PASSWORD_SIZE+1];
  char crackedPassword[PASSWORD_SIZE+1];

  int tempCrackPassword[PASSWORD_SIZE+1];
  for (int i = 0; i < PASSWORD_SIZE+1; i++) {
    tempCrackPassword[i] = 0;
  }

  scanf("%s", &password);

  time(&t1);
  printf("Cracking password\n");

  int cracked = 0;
  while (!cracked) {
    for (int i=0; i<PASSWORD_SIZE + 1; i++) {
      crackedPassword[i] = tempCrackPassword[i];
    }
    
    if (strcmp(password,crackedPassword) == 0) {
      cracked = 1;
      break;      
    }

    for (int i = 0; i < PASSWORD_SIZE; i++) {      
        if (tempCrackPassword[i] == (LAST_CHAR + 1)) {
          tempCrackPassword[i] = 0;
          tempCrackPassword[i+1]++;
        }        
    }

    tempCrackPassword[0]++;
  }

  for (int i=0; i<PASSWORD_SIZE + 1; i++) {
      crackedPassword[i] = tempCrackPassword[i];
  }

  printf("\nPassword is: %s\n", crackedPassword);

  time(&t2);
  printf("total time: %lu\n", t2-t1);

  return 0;
}