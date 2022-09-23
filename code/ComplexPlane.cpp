#include "ComplexPlane.h"
#include <math.h>

using namespace sf;

ComplexPlane::ComplexPlane(float aspectRatio)
{
	// Store the aspectRatio into m_aspectRatio
	m_aspectRatio = aspectRatio;
	// setSize of the m_view variable to BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);// Negative size for the height will invert the vertical axis
	// setCenter of the m_view variable to 0.0, 0.0
	m_view.setCenter(0.0, 0.0);
	// Set m_zoomCount to 0
	m_zoomCount = 0;

}

void ComplexPlane::zoomIn()
{
	// Increment m_zoomCount
	m_zoomCount += 1;
	// Set a local variable for the x size to BASE_WIDTH * (BASE_ZOOM to the m_ZoomCount power)
	float tempX = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	// Set a local variable for the y size to BASE_HEIGHT * m_aspectRatio * (BASE_ZOOM to the m_ZoomCount power)
	float tempY = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	// setSize in m_view to the new size
	m_view.setSize(tempX, tempY);
}

void ComplexPlane::zoomOut()
{
	// Decrement m_zoomCount
	m_zoomCount -= 1;
	// Set a local variable for the x size to BASE_WIDTH * (BASE_ZOOM to the m_ZoomCount power)
	float tempX = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	// Set a local variable for the y size to BASE_HEIGHT * m_aspectRatio * (BASE_ZOOM to the m_ZoomCount power)
	float tempY = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	// setSize in m_view to the new size
	m_view.setSize(tempX, tempY);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	// setCenter for m_view to the given coordinate
	m_view.setCenter(coord.x, coord.y);
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	// Store the given value in the m_mouseLocation variable
	m_mouseLocation.x = coord.x;
	m_mouseLocation.y = coord.y;
}

//void ComplexPlane::loadText(Text& text)
//{
	/*
	Use a stringstream and the corresponding member variables to create the following output:
		Mandelbrot Set
		Center: (0,0)
		Cursor: (cursor posx, cursor posy)
		Left-click to Zoom in
		Right-click to Zoom out
	*/
//}

//size_t ComplexPlane::countIterations(Vector2f coord)
//{
	// Count the number of iterations of the set for the given coordinate as specified above

//}

//void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
//{
	// Map the given iteration count to an r,g,b color and assign the given reference variables

	// You may want to start with gray scale, where r,g,b are always the same value in the range [0,255]
//}