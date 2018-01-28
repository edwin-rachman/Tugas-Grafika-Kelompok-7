#ifndef DRAWMAP_H
#define DRAWMAP_H

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

class DrawMap {
private:
	const int width;
	const int height;
	int x_scale = 3;
	int y_scale = 3;
	int x_offset = 0;
	int y_offset = 0;
	std::vector<bool> map;
	
public:
	DrawMap(int width, int height, DrawMap char_map, std::string char_map_seq, int char_map_cols, int char_width, int char_height, const char *display_text_path);
	DrawMap(int width, int height, const char* charmap_path);
	int getDrawnY(int x, int y);
	void setXOffset (int x_offset);
	void setYOffset (int y_offset);
	int getXOffset ();
	int getYOffset ();
};

#endif
