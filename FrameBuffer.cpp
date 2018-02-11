#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(const char *file_desc_path) {
	file_desc = open(file_desc_path, O_RDWR);
	ioctl(file_desc, FBIOGET_VSCREENINFO, &vinfo);
	vinfo.grayscale = 0;
	vinfo.bits_per_pixel = 32;
	vinfo.yres_virtual = vinfo.yres * 2;
	
	ioctl(file_desc, FBIOPUT_VSCREENINFO, &vinfo);
	ioctl(file_desc, FBIOGET_VSCREENINFO, &vinfo);
	ioctl(file_desc, FBIOGET_FSCREENINFO, &finfo);
	
	screen_size = vinfo.yres_virtual * finfo.line_length;
	front_buffer = (uint8_t *) mmap(0, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_desc, (off_t) 0);
	back_buffer = (uint8_t *) mmap(0, screen_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t) 0);
}
	
FrameBuffer::~FrameBuffer() {
	munmap(front_buffer, file_desc);
	munmap(back_buffer, -1);
}
	
int FrameBuffer::getWidth() {
	return vinfo.xres;
}
	
int FrameBuffer::getHeight() {
	return vinfo.yres;
} 
	
uint32_t FrameBuffer::getColor(uint8_t r, uint8_t g, uint8_t b) {
	return (r << vinfo.red.offset) | (g << vinfo.green.offset) | (b << vinfo.blue.offset);
}

uint32_t FrameBuffer::getPixel(int x, int y) {
  long location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel / 8) + (y + vinfo.yoffset) * finfo.line_length;
  return *((uint32_t *) (back_buffer + location));
}

uint32_t FrameBuffer::getPixel(uint8_t *buffer, int width, int height, int x, int y) {
  long location = (y * width + x) * (vinfo.bits_per_pixel / 8);
  return *((uint32_t *) (buffer + location));
}

void FrameBuffer::setPixel(int x, int y, uint32_t color) {
	if (x >= 0 && y >= 0 && x < getWidth() && y < getHeight()) {
		long location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel / 8) + (y + vinfo.yoffset) * finfo.line_length;
		*((uint32_t*) (back_buffer + location)) = color;
	}
}

void FrameBuffer::setPixel(uint8_t *buffer, int width, int height, int x, int y, uint32_t color) {
  if (x >= 0 && y >= 0 && x < width && y < height) {
		long location = (y * width + x) * (vinfo.bits_per_pixel / 8);
		*((uint32_t*) (buffer + location)) = color;
	}
}

void FrameBuffer::fill(uint32_t color) {
  for (int i = 0; i < screen_size; ++i) {
    *((uint32_t*)(back_buffer + i)) = color;
  }
}
	
void FrameBuffer::swapBuffers() {;
		memcpy(front_buffer, back_buffer, screen_size);
}
