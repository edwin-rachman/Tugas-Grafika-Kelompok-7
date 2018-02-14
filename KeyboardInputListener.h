#ifndef KEYBOARDINPUTLISTENER_H
#define KEYBOARDINPUTLISTENER_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

class KeyboardInputListener {
private:
  timeval delay;
  static termios oldTermios;
  static termios newTermios;
  
public:
  KeyboardInputListener(long delaySeconds, long delayMicroseconds);
  static void start();
  static void stop();
  int receivedInput();
  int getInput();
}; 

#endif
