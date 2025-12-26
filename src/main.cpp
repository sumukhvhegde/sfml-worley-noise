#include <SFML/Graphics.hpp>
#include "include/WorleyNoise.hpp"

#include <algorithm>
#include <cstdint>

constexpr unsigned int WIDTH = 512;
constexpr unsigned int HEIGHT = 512;

int main() {
	sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "Worley Noise", sf::Style::Close);

	WorleyNoise worley(218379801);

	sf::Image image({ WIDTH, HEIGHT }, sf::Color::Black);

	for (unsigned int y = 0; y < HEIGHT; ++y) {
		for (unsigned int x = 0; x < WIDTH; ++x) {
			float nx = static_cast<float>(x) / WIDTH;
			float ny = static_cast<float>(y) / HEIGHT;

			float d = worley.sample(nx, ny);

			float value = d * 12.f;
			value = std::clamp(value, 0.f, 1.f);

			std::uint8_t c = static_cast<std::uint8_t>(value * 255);

			image.setPixel({ x, y }, sf::Color(c, c, c));
		}
	}

	sf::Texture texture;
	texture.loadFromImage(image);

	sf::Sprite sprite(texture);

	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}