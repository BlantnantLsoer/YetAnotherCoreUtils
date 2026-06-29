#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
  if(argc < 2 || strcmp(argv[1], "-") == 0) {
    while(1) {
      char c = getchar();
      putchar(c);
    }
  }


  for(int i = 1; i < argc; i++) {
    FILE* f = fopen(argv[i], "r");
    if(f == NULL) {
      perror("fopen");
      return 1;
    }


    fclose(f);
  }

  return 0;
}
