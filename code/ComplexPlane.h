#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

// Implement the header file as specified in the UML diagram
class ComplexPlane
{
	private:
		Vector2f m_mouseLocation;
		View m_view;
		int m_zoomCount;
		float m_aspectRatio;

	public:
		ComplexPlane(float aspectRatio);

		void zoomIn(),
			zoomOut(),
			setCenter(Vector2f coord),
			setMouseLocation(Vector2f coord),
			loadText(Text& text);

		View getView();

		static size_t countIterations(Vector2f coord);
		static void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
};
/*
In addition to the variables in the diagram, declare the following global constants:
const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;
*/