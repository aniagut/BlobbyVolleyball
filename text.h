#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>

namespace sf {

	void changeDisplayedText(Text& text, std::string textToDisplay);

	void setFont(Font& font, std::string filename);

	void setTextProperties(Text& text, Color color, Uint32 style, int width, int height);

}

#endif