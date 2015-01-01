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

#define PASSWORD_SIZE (100)
#define FIRST_CHAR (33)
#define LAST_CHAR (127)

int main ()
{
  time_t t1;
  time_t t2;
  time(&t1);

  printf("Type a password: ");

  char password[PASSWORD_SIZE];
  char crackedPassword[PASSWORD_SIZE];

  scanf("%s", &password);

  printf("Cracking password\n");

  int cracked = 0;
  while (!cracked) {
    printf("%s\n",crackedPassword);

    crackedPassword[0]++;
    for (int i = 0; i < PASSWORD_SIZE - 1; i++) {        
      if (crackedPassword[i] == LAST_CHAR) {
        crackedPassword[i] = FIRST_CHAR;
        if (crackedPassword[i+1] == 0) {
          crackedPassword[i+1] = FIRST_CHAR;
        } else {
          crackedPassword[i+1]++;
        }
      }        
    }

    if (strcmp(password,crackedPassword) == 0) {
      cracked = 1;
    }
  }

  printf("\nPassword is: %s\n", crackedPassword);

  time(&t2);
  printf("total time: %lu\n", t2-t1);

  return 0;
}