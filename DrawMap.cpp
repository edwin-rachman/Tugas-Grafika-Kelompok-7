#include "DrawMap.h"

DrawMap::DrawMap(int width, int height, DrawMap char_map, std::string char_map_seq, int char_map_cols, int char_width, int char_height, const char *display_text_path) 
 : width(width), height(height), map(width * height, false) {
	
	std::ifstream is(display_text_path);
	char c;
	int x = 0;
	int y = 0;
	while (is.get(c)) {
		if (c == '\n') {
			x = 0;
			++y;
		}
		else {
			int char_map_pos = char_map_seq.find(c);
			if (char_map_pos < 0) {
				std::stringstream err_msg;
				err_msg << "Character '" << c << "' not found in charmap";
				throw std::runtime_error(err_msg.str());
			}
			int char_map_x = char_map_pos % char_map_cols;
			int char_map_y = char_map_pos / char_map_cols;
			
			for (int copy_y = 0; copy_y < char_height; ++copy_y) {
				for (int copy_x = 0; copy_x < char_width; ++copy_x) {
					map[(y * char_height + copy_y) * width + x * char_width + copy_x] = char_map.map[(char_map_y * char_height + copy_y) * width + char_map_x * char_width + copy_x];
				}
			}
			
			++x;
		}
	}
}

DrawMap::DrawMap(int width, int height, const char* charmap_path)
 : width(width), height(height), map(width * height, false) {
	
	std::ifstream is(charmap_path);
	char c;
	int x = 0;
	int y = 0;
	while (is.get(c)) {
		if (c == '\n') {
			if (y < height - 1) {
				x = 0;
				++y;
			}
			else {
				break;
			}
		}
		else {
			if (c != ' ') {
				map[y * width + x] = true;
			}	
			if (x < width - 1) {
				++x;
			}
			else {
				x = 0;
				++y;
			}
		}
	}
}
	
int DrawMap::getDrawnY(int x, int y) {
	int draw_x = x - x_offset;
	int draw_y = y - y_offset;
	
	if (draw_x >= 0 && draw_y >= 0 && draw_x < width && draw_y < height && map[draw_y / y_scale * width + draw_x / x_scale]) {
		return draw_y / y_scale;
	}
	else {
		return -1;
	}
}
	
void DrawMap::setXOffset (int x_offset) {
	this->x_offset = x_offset;
}
	
void DrawMap::setYOffset (int y_offset) {
	this->y_offset = y_offset;
}
	
int DrawMap::getXOffset () {
	return x_offset;
}
	
int DrawMap::getYOffset () {
	return y_offset;
}
