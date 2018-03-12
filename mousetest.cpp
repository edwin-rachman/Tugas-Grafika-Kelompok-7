#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

int main () {
  int device = open("/dev/input/mice", O_RDONLY | O_NONBLOCK);
  if (device == -1) {
    std::cout << "Cannot read mouse\n";
    return -1;
  }
  
  int readBytes;
  int x, y, left, middle, right;
  char data[3];
  for (;;) {
    readBytes = read(device, data, sizeof(data));
    
    if (readBytes > 0) {
      left = data[0] & 0x1;
      right = data[0] & 0x2;
      middle = data[0] & 0x4;
      x = data[1];
      y = data[2];
      
      std::cout << x << ", " << y << (left ? " left" : "") << (middle ? " middle" : "") << (right ? " right" : "") << "\n";
    }
  }
}
