#include "text.h"
#include <SFML/Graphics.hpp>

namespace sf {

	void changeDisplayedText(Text& text, std::string textToDisplay) {
		text.setString(textToDisplay);
	}

	void setFont(Font& font, std::string filename) {
		font.loadFromFile(filename);
	}

	void setTextProperties(Text& text, Color color, Uint32 style, int width, int height) {
		text.setFillColor(color);
		text.setStyle(style);
		text.setPosition(Vector2f(width, height));
	}
}