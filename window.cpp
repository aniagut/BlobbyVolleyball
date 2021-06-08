#include "window.h"
#include <SFML/Graphics.hpp>

namespace sf {

	void setWindowProperties(RenderWindow& window, int width, int height, std::string title, int framerate_l, float scale) {
		window.create(VideoMode(width, height), title);
		window.setFramerateLimit(framerate_l);
		window.setSize(Vector2u(width * scale, height * scale));
	}
}
