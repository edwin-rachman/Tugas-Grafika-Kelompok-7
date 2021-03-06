#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <fcntl.h>
#include <vector>
#include <cstring>

class FrameBuffer {
private:
	int file_desc;
	fb_fix_screeninfo finfo;
	fb_var_screeninfo vinfo;
	
	long screen_size;
	uint8_t *front_buffer;
	uint8_t *back_buffer;
	
public:
	FrameBuffer(const char *file_desc_path);
	~FrameBuffer();
	int getWidth();
	int getHeight();
	uint32_t getColor(uint8_t r, uint8_t g, uint8_t b);
	void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
  void fill(uint8_t r, uint8_t g, uint8_t b);
	void swapBuffers();
};

#endif
