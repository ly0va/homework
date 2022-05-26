#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
  int mice_fd = open("/dev/input/mice", O_RDONLY);

  if (mice_fd == -1) {
    printf("Could not open device file\n");
    exit(1);
  }

  char buf[3];
  while (1) {
      read(mice_fd, buf, 3);
      char left = buf[0] & 0x1;
      char right = buf[0] & 0x2;
      char middle = buf[0] & 0x4;
      if (buf[1] || buf[2]) {
          printf("Mouse moved: (dx, dy) = (%d, %d)\n", buf[1], buf[2]);
      } else {
          if (left) puts("Left button pressed");
          else if (right) puts("Right button pressed");
          else if (middle) puts("Middle button pressed");
          else puts("Button released");
      }
  }

  return 0;
}
