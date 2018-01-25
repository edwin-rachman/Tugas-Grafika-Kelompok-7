#include <iostream>

#include "FrameBuffer.h"
#include "DrawMap.h"
	
int main (int argc, char **argv) {
	if (argc < 3) {
		std::stringstream err_msg;
		err_msg << "Given " << argc - 1 << " argument(s), expected 2: charmap file, display text file";
		throw std::runtime_error(err_msg.str());
	}
	
	//initialize frame buffer
  FrameBuffer frameBuffer("/dev/fb0");
  
  //load pixel map for characters from text file (arg1)
  DrawMap charMap(frameBuffer.getWidth(), frameBuffer.getHeight(), argv[1]);
  
  //new pixel map for display text (arg2) based on charMap (7x8 pixels per character, newline every 13 characters)
  DrawMap drawMap(frameBuffer.getWidth(), frameBuffer.getHeight(), charMap, 
  "0123456789-  ABCDEFGHIJKLMabcdefghijklmNOPQRSTUVWXYZnopqrstuvwxyz", 13, 7, 8, argv[2]);
  
  //30fps : 1/30s delay per frame
  timespec delay, rem;
  delay.tv_sec = 0;
  delay.tv_nsec = 33333333L;
  
  //position text to bottom of screen
  drawMap.setXOffset(55);
  drawMap.setYOffset(frameBuffer.getHeight());
  
  //hide cursor
  std::cout << "\e[?25l" << std::flush;
  
  //loop until text at top of screen
  while (drawMap.getYOffset() > 0) {
		for (int y = 0; y < frameBuffer.getHeight(); ++y) {
			for (int x = 0; x < frameBuffer.getWidth(); ++x) {
				int drawnY = drawMap.getDrawnY(x, y);
				if (drawnY == -1) {
					frameBuffer.setPixel(x, y, 0x11, 0x11, 0x11);
				}
				else {
					switch (drawnY / 8) {
						case 0:
						case 1:
							frameBuffer.setPixel(x, y, 0xFF, 0xFF, 0xFF);
							break;
						case 2:
							frameBuffer.setPixel(x, y, 0xFF, 0x00, 0x00);
							break;
						case 3:
							frameBuffer.setPixel(x, y, 0xFF, 0x7F, 0x00);
							break;
						case 4:
							frameBuffer.setPixel(x, y, 0xFF, 0xFF, 0x00);
							break;
						case 5:
							frameBuffer.setPixel(x, y, 0x00, 0xFF, 0x00);
							break;
						case 6:
							frameBuffer.setPixel(x, y, 0x00, 0x00, 0xFF);
							break;
						case 7:
							frameBuffer.setPixel(x, y, 0x4B, 0x00, 0x82);
							break;
						case 8:
							frameBuffer.setPixel(x, y, 0x94, 0x00, 0xD3);
							break;
					}
				}
			}
		}
		//move text 5 pixels every frame
		drawMap.setYOffset(drawMap.getYOffset() - 3);
		
		//update frame buffer
		frameBuffer.swapBuffers();
		
		//delay
		nanosleep(&delay, &rem);
	}
	
	//show cursor
	std::cout << "\e[?25h" << std::flush;
  
  return 0;
}
