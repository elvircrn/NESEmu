#ifndef NESEMU_IO_H
#define NESEMU_IO_H

#include <array>
#include "SDL.h"

class IO {
	enum Joypad { JOYPAD_ONE, JOYPAD_TWO };

	SDL_Event &evt;
	std::array<u8, 2> buttonBuffers{};

	const std::array<int, 8> keyMappings = {
			SDL_SCANCODE_RIGHT,
			SDL_SCANCODE_LEFT,
			SDL_SCANCODE_DOWN,
			SDL_SCANCODE_UP,
			SDL_SCANCODE_KP_ENTER,
			SDL_SCANCODE_SPACE,
			SDL_SCANCODE_B,
			SDL_SCANCODE_A
	};

public:
	explicit IO(SDL_Event &_evt) : evt(_evt) {}

	void write4016(const u8 &val) {

	}

	void write4017(const u8 &val) {
	}

	u8 read4016() {
		return 0;
	}

	u8 read4017() {
		return 0;
	}

	void fillBuffer(const Joypad &joypad) {
		auto keystates = SDL_GetKeyboardState(nullptr);

		u8 mask{};
		for (size_t i = 0; i < 8; i++) {
			mask |= ((keystates[keyMappings[i]] > 0) << i);
		}

		buttonBuffers[joypad] = mask;
	}
};

#endif //NESEMU_IO_H
