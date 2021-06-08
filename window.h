#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

namespace sf {
	void setWindowProperties(RenderWindow& window, int width, int height, std::string title, int framerate_l, float scale);
}

#endif
