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
	return (r<<vinfo.red.offset) | (g<<vinfo.green.offset) | (b<<vinfo.blue.offset);
}
	
void FrameBuffer::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	long location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel / 8) + (y + vinfo.yoffset) * finfo.line_length;
	*((uint32_t*)(back_buffer + location)) = getColor(r, g, b);
}
	
void FrameBuffer::swapBuffers() {;
		memcpy(front_buffer, back_buffer, screen_size);
}
