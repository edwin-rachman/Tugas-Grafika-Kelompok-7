#include <iostream>
#include <ctime>
#include "Line.h"
#include "FloodFillDrawing.h"
#include "KeyboardInputListener.h"

const float PI = std::acos(-1);

int main() {
  std::cout << "\e[?25l" << std::flush;
  FrameBuffer frameBuffer("/dev/fb0");

  KeyboardInputListener keyboardInputListener(0, 33333);
  keyboardInputListener.start();

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
  rotor.translate(0, 5);

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
  plane.translate(frameBuffer.getWidth() / 2, 100);

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
  pilot.scale(10, 10, 0, 0);

  Drawing parachute(0, -pilot_height);
  parachute.add(new Line(0, 0, -0.3f, -1.7f, 0xFF, 0xFF, 0xFF));
  parachute.add(new Line(0, 0, 0.3f, -1.7f, 0xFF, 0xFF, 0xFF));
  parachute.add(new Line(0, 0, 0.9f, -1.2f, 0xFF, 0xFF, 0xFF));
  parachute.add(new Line(0, 0, -0.9f, -1.2f, 0xFF, 0xFF, 0xFF));
  parachute.scale(10, 10, 0, 0);

  float land_y_pos = frameBuffer.getHeight();

  float velocity = -10;
  float accel = 3;
  float deccel = 0.7f;
  float terminal = 10;
  float y_pos = frameBuffer.getHeight() / 2 - pilot_height * 2;

  float bulletAngle = 0;
  Drawing bullet(0, 0);
  bullet.add(new Line(0, 0, 0, -20, 0xFF, 0x00, 0x00));
  bullet.translate(frameBuffer.getWidth() / 2, frameBuffer.getHeight());

  bool running = true;
  bool shooting = false;
  int rotorState = 0;

  int time = 0;
  while (running && time < 200) {
    ++time;
    if (keyboardInputListener.receivedInput()) {
      switch (keyboardInputListener.getInput()) {
        case 27:
          running = false;
        break;
        case 97:
          if (bulletAngle > -PI/3 && !shooting) {
            bulletAngle -= PI/18;
            bullet.rotate(-PI/18, bullet.getOrigin().getX(), bullet.getOrigin().getY());
          }
        break;
        case 100:
          if (bulletAngle < PI/3 && !shooting) {
            bulletAngle += PI/18;
            bullet.rotate(PI/18, bullet.getOrigin().getX(), bullet.getOrigin().getY());
          }
        break;
        case 98:
          shooting = true;
        break;
      }
    }
    if (shooting) {
      bullet.translate(std::sin(bulletAngle) * 10, -std::cos(bulletAngle) * 10);
      if (std::abs(bullet.getOrigin().getX() - rotor.getOrigin().getX()) < 20 && std::abs(bullet.getOrigin().getY() - rotor.getOrigin().getY()) < 20) {
        shooting = false;
        bullet.translate(frameBuffer.getWidth() / 2 - bullet.getOrigin().getX(), frameBuffer.getHeight() - bullet.getOrigin().getY());
        plane.remove(&rotor);
        rotorState = 1;
        pilot.translate(frameBuffer.getWidth()/2, rotor.getOrigin().getY() - pilot_height * 2);
        parachute.translate(frameBuffer.getWidth()/2, rotor.getOrigin().getY() - pilot_height * 2);
      }
      if (bullet.getOrigin().getY() < 0) {
        shooting = false;
        bullet.translate(frameBuffer.getWidth() / 2 - bullet.getOrigin().getX(), frameBuffer.getHeight() - bullet.getOrigin().getY());
      }
    }
    if (rotorState == 1) {
      if (rotor.getOrigin().getY() > land_y_pos) {
        rotorState = 2;
      }
    }

    frameBuffer.fill(frameBuffer.getColor(0x00, 0x00, 0x00));
    plane.draw(frameBuffer);
    bullet.draw(frameBuffer);
    if (rotorState > 0) {
      rotor.draw(frameBuffer);
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
      }
      else if (y_pos > land_y_pos) {
        pilot.translate(0, land_y_pos - y_pos);
        y_pos = land_y_pos;
      }
    }

    frameBuffer.swapBuffers();


    plane.scale(1.025, 1.025, plane.getOrigin().getX(), plane.getOrigin().getY());
    if (rotorState == 1) {
      rotor.translate(0, 10);
    }
    else if (rotorState == 2) {
      rotor.translate(4, -7);
    }
    else {
      rotor.rotate(PI / 24, rotor.getOrigin().getX(), rotor.getOrigin().getY());
    }
  }

  keyboardInputListener.stop();


  /*timespec delay, rem;
  delay.tv_sec = 0;
  delay.tv_nsec = 33333333L;

  Drawing bullets_center(frameBuffer.getWidth() / 2, frameBuffer.getHeight());
  Drawing bullets_left(frameBuffer.getWidth() / 2, frameBuffer.getHeight());
  Drawing bullets_right(frameBuffer.getWidth() / 2, frameBuffer.getHeight());
  for (int i = 0; i < 50; ++i) {
    bullets_center.add(new Line(0, i * 50, 0, i * 50 + 14, 0xFF, 0x00, 0x00));
    bullets_left.add(new Line(i * 40, i * 40, i * 40 + 10, i * 40 + 10, 0xFF, 0x00, 0x00));
    bullets_right.add(new Line(-i * 40, i * 40, -i * 40 - 10, i * 40 + 10, 0xFF, 0x00, 0x00));
  }

  //FloodFillDrawing planeFill(7, 6, 0, 0, 20, 20, plane, 0x00, 0xFF, 0x00);

  plane.translate(frameBuffer.getWidth() / 2, 100);
  //rotor.translate(100, 100);

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
		//planeFill.draw(frameBuffer);
	}
	if ((time >= 21) && (time <= 21)) {
		frameBuffer.fill(frameBuffer.getColor(0xFF, 0xCC, 0xFF));
	}
    frameBuffer.swapBuffers();
    nanosleep(&delay, &rem);

    bullets_center.translate(0, -14);
    bullets_left.translate(-10, -10);
    bullets_right.translate(10, -10);

    ++time;
  }
  while (time < 100);*/

  std::cout << "\e[?25h" << std::flush;
  return 0;
}
