#include "textures.h"
#include <SFML/Graphics.hpp>

namespace sf {

	void loadTextures(Texture textures[], std::string filenames[], int len) {
		for (int i = 0; i < len; i++) {
			textures[i].loadFromFile(filenames[i]);
			textures[i].setSmooth(true);
		}
	}
}
