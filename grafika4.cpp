#include <iostream>
#include <ctime>
#include "Line.h"
#include "FloodFillDrawing.h"

const float pi = std::acos(-1);

int main() {
  std::cout << "\e[?25l" << std::flush;
  FrameBuffer frameBuffer("/dev/fb0");

  timespec delay, rem;
  delay.tv_sec = 0;
  delay.tv_nsec = 3333333L;

  Drawing bullets_center(frameBuffer.getWidth() / 2, frameBuffer.getHeight());
  Drawing bullets_left(frameBuffer.getWidth() / 2, frameBuffer.getHeight());
  Drawing bullets_right(frameBuffer.getWidth() / 2, frameBuffer.getHeight());
  for (int i = 0; i < 1; ++i) {
    bullets_center.add(new Line(0, i * 50, 0, i * 50 + 14, 0xFF, 0x00, 0x00));
    bullets_left.add(new Line(i * 40, i * 40, i * 40 + 10, i * 40 + 10, 0xFF, 0x00, 0x00));
    bullets_right.add(new Line(-i * 40, i * 40, -i * 40 - 10, i * 40 + 10, 0xFF, 0x00, 0x00));
  }

  Drawing rotor(0, 0);
  rotor.add(new Line(-2, 0, 2, 0, 0x00, 0xFF, 0x00));
  rotor.add(new Line(0, -2, 0, 2, 0x00, 0xFF, 0x00));
  rotor.add(new Line(-2, 0, -1.5f, 0.5f, 0x00, 0xFF, 0x00));
  rotor.add(new Line(-1.5f, 0.5f, 0, 0.5f, 0x00, 0xFF, 0x00));
  rotor.add(new Line(2, 0, 1.5f, -0.5f, 0x00, 0xFF, 0x00));
  rotor.add(new Line(1.5f, -0.5f, 0, -0.5f, 0x00, 0xFF, 0x00));
  rotor.add(new Line(0, -2, -0.5f, -1.5f, 0x00, 0xFF, 0x00));
  rotor.add(new Line(-0.5f, -1.5f, -0.5f, 0, 0x00, 0xFF, 0x00));
  rotor.add(new Line(0, 2, 0.5f, 1.5f, 0x00, 0xFF, 0x00));
  rotor.add(new Line(0.5f, 1.5f, 0.5f, 0, 0x00, 0xFF, 0x00));

  Drawing plane(0, 0);
  plane.add(new Line(-9, 1, -2, 1, 0x00, 0xFF, 0x00));
  plane.add(new Line(-2, 1, -1, 3, 0x00, 0xFF, 0x00));
  plane.add(new Line(-1, 3, 1, 3, 0x00, 0xFF, 0x00));
  plane.add(new Line(1, 3, 2, 1, 0x00, 0xFF, 0x00));
  plane.add(new Line(2, 1, 9, 1, 0x00, 0xFF, 0x00));
  plane.add(new Line(9, 1, 2, -1, 0x00, 0xFF, 0x00));
  plane.add(new Line(2, -1, 0, -4, 0x00, 0xFF, 0x00));
  plane.add(new Line(0, -4, -2, -1, 0x00, 0xFF, 0x00));
  plane.add(new Line(-2, -1, -9, 1, 0x00, 0xFF, 0x00));
  plane.add(&rotor);
  //FloodFillDrawing planeFill(7, 6, 0, 0, 20, 20, plane, 0x00, 0xFF, 0x00); 
  float height = 0;
  plane.translate(frameBuffer.getWidth()/2, frameBuffer.getHeight()/2);
  rotor.translate(0, - height / 2);
  
  float pilot_height = 1.6f;
  Drawing pilot(0, 0);
  pilot.add(new Line(-0.5f, 0, 0, -0.65f, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(0.5f, 0, 0, -0.65f, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(0, -0.65f, 0, -1.15f, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(-0.5f, -1, 0.5f, -1, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(-0.2f, -1.2f, 0.2f, -1.2f, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(-0.2f, -1.2f, -0.2f, -1.6f, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(-0.2f, -1.6f, 0.2f, -1.6f, 0xFF, 0xFF, 0xFF));
  pilot.add(new Line(0.2f, -1.2f, 0.2f, -1.6f, 0xFF, 0xFF, 0xFF));
  pilot.scale(10, 10);
  
  Drawing parachute(0, -pilot_height); 
  parachute.add(new Line(0, 0, -0.3f, -1.7f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(0, 0, 0.3f, -1.7f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(0, 0, 0.9f, -1.2f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(0, 0, -0.9f, -1.2f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(0.9f, -1.2f, 0.3f, -1.7f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(-0.9f, -1.2f, -0.3f, -1.7f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(-0.3f, -1.7f, 0.3f, -1.7f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(0.3f, -1.7f, 0.9f, -1.2f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(-0.9f, -1.2f, -1.2f, -1.5f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(0.9f, -1.2f,1.2f, -1.5f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(-1.2f, -1.5f, -1.0f, -1.9f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(-1.0f, -1.9f, -0.6f, -2.2f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(-0.6f, -2.2f, 0, -2.3f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(0, -2.3f, 0.6f, -2.2f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(0.6f, -2.2f, 1.0f, -1.9f, 0xFF, 0xFF, 0xFF)); 
  parachute.add(new Line(1.0f, -1.9f, 1.2f, -1.5f, 0xFF, 0xFF, 0xFF)); 
  parachute.scale(10, 10);
  
  Drawing wheel(0, 0);
  int segments = 18;
  float pos[segments][2];
  for (int i = 0; i < segments; i++) {
	pos[i][0] = std::cos(2 * pi * i / segments);
	pos[i][1] = std::sin(2 * pi * i / segments);
  }
  for (int i = 0; i < segments; i++) {
	int n = i + 1;
	if (n == segments) {
      n = 0;
	}
	wheel.add(new Line(pos[i][0], pos[i][1], pos[n][0], pos[n][1], 0xFF, 0xFF, 0xFF));
	float factor = 0.6f;
	wheel.add(new Line(pos[i][0] * factor, pos[i][1] * factor, pos[n][0] * factor, pos[n][1] * factor, 0xFF, 0xFF, 0xFF));
  }
  wheel.scale(10, 10);
  
  wheel.translate(frameBuffer.getWidth()/2, frameBuffer.getHeight()/2);
  pilot.translate(frameBuffer.getWidth()/2, frameBuffer.getHeight()/2 - pilot_height * 2);
  parachute.translate(frameBuffer.getWidth()/2, frameBuffer.getHeight()/2 - pilot_height * 2);

  float w_x = frameBuffer.getWidth() / 2;
  float w_y = frameBuffer.getHeight() / 2 + 5;
  float w_v_x = 7;
  float w_v_y = -6;

  float land_y_pos = frameBuffer.getHeight();
  float bounciness = 0.6f;
  float drag = 0.03f;
  float velocity = -10;
  float accel = 3;
  float deccel = 0.7f;
  float terminal = 10;
  float y_pos = frameBuffer.getHeight() / 2 - pilot_height * 2;

  int time = 0;

  do {
    frameBuffer.fill(frameBuffer.getColor(0x00, 0x00, 0x00));
	
	if (time <= 21) {
		bullets_center.draw(frameBuffer);
	} else {
		wheel.draw(frameBuffer);
		w_v_x = (1 - drag) * w_v_x;
		w_v_y += (1 - deccel) * accel;
		w_x += w_v_x;
		w_y += w_v_y;
		wheel.translate(w_v_x, w_v_y);
		if (w_y > land_y_pos) {
			w_v_y *= -1 * bounciness;
			wheel.translate(0, land_y_pos - w_y);
			w_y = land_y_pos;
		}
	}
    bullets_left.draw(frameBuffer);
    bullets_right.draw(frameBuffer);
    if (time > 19) {
		pilot.draw(frameBuffer);
		velocity += (1 - deccel) * accel;
		if (velocity > terminal) {
			velocity = terminal;
		}
		if (y_pos < land_y_pos) {
			parachute.draw(frameBuffer);
			y_pos += velocity;
			pilot.translate(0, velocity);
			parachute.translate(0, velocity);
		} else if (y_pos > land_y_pos) {
			pilot.translate(0, land_y_pos - y_pos);
			y_pos = land_y_pos;
		}
	}
	if (time < 100) {
		plane.draw(frameBuffer);
	}
    frameBuffer.swapBuffers();
    nanosleep(&delay, &rem);

    bullets_center.translate(0, -14);
    bullets_left.translate(-10, -10);
    bullets_right.translate(10, -10);
    plane.translate(-frameBuffer.getWidth()/2, -frameBuffer.getHeight()/2 - height/2);
    rotor.translate(0, height);
    rotor.rotate(pi / 3);
    rotor.translate(0, - height);
    plane.scale(1.04, 1.04);
	plane.translate(frameBuffer.getWidth()/2, frameBuffer.getHeight()/2 + height/2);
    height *= 1.08;
    ++time;
  }
  while (time < 200);

  std::cout << "\e[?25h" << std::flush;
  return 0;
}
