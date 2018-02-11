#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

/*--------
  Jen Yu
  P4 Graphics
  HW #02: Because it's time, you'll make a line
  2018-02-10
  --------*/

//draws a square
void draw_square(int x, int y, int l, int w, screen s, color c){
  draw_line(x, y, x+w, y, s, c);
  draw_line(x+w, y, x+w, y+l, s, c);
  draw_line(x, y+l, x, y, s, c);
  draw_line(x, y+l, x+w, y+l, s, c);
}

//returns a random number
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
  //draws random squares all over the screen
  for (i = 0; i < 15; i ++){
    r = rand_num();
    c.red = r%256;
    c.green = (r+50)%256;
    c.blue = (r+25)%256 + 25;
    x += r%150;
    y += r%200; 
    draw_square(x, y, 50 , 40, s, c);
    }
  
  //Mr. DW's test code
  //octants 1 and 5
  draw_line(0, 0, XRES-1, YRES-1, s, c);
  draw_line(0, 0, XRES-1, YRES / 2, s, c);
  draw_line(XRES-1, YRES-1, 0, YRES / 2, s, c);

  //octants 8 and 4
  c.blue = 255;
  draw_line(0, YRES-1, XRES-1, 0, s, c);
  draw_line(0, YRES-1, XRES-1, YRES/2, s, c);
  draw_line(XRES-1, 0, 0, YRES/2, s, c);

  //octants 2 and 6
  c.red = 255;
  c.green = 0;
  c.blue = 0;
  draw_line(0, 0, XRES/2, YRES-1, s, c);
  draw_line(XRES-1, YRES-1, XRES/2, 0, s, c);

  //octants 7 and 3
  c.blue = 255;
  draw_line(0, YRES-1, XRES/2, 0, s, c);
  draw_line(XRES-1, 0, XRES/2, YRES-1, s, c);

  //horizontal and vertical
  c.blue = 0;
  c.green = 255;
  draw_line(0, YRES/2, XRES-1, YRES/2, s, c);
  draw_line(XRES/2, 0, XRES/2, YRES-1, s, c);
  
  display(s);
  save_extension(s, "lines.png");
}
