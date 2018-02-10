#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

void draw_square(int x, int y, int l, int w, screen s, color c){
  draw_line(x, y, x+w, y, s, c);
  draw_line(x+w, y, x+w, y+l, s, c);
  draw_line(x, y+l, x, y, s, c);
  draw_line(x, y+l, x+w, y+l, s, c);
}

int rand_num()
{
  int fd = open("/dev/random", O_RDONLY);
  int num;
  read(fd, &num, sizeof(num));
  close(fd);
  return num;
}

int main() {

  screen s;
  color c;

  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;

  clear_screen(s);
  int i, r;
  int x = 100; int y = 100;
  for (i = 0; i < 15; i ++){
    r = rand_num();
    c.red = r%256;
    c.green = (r+50)%256;
    c.blue = (r+25)%256 + 25;
    x += r%100;
    y += r%120; 
    draw_square(x, y, 50 , 40, s, c);
    }
  display(s);
  save_extension(s, "lines.png");
}
