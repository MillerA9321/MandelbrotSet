#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>
#include <sstream>
#include "ComplexPlane.h"

using namespace sf;
using namespace std;

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
	double tempX, tempY;
	// Increment m_zoomCount
	m_zoomCount++;
	// Set a local variable for the x size to BASE_WIDTH * (BASE_ZOOM to the m_ZoomCount power)
	tempX = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	// Set a local variable for the y size to BASE_HEIGHT * m_aspectRatio * (BASE_ZOOM to the m_ZoomCount power)
	tempY = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	// setSize in m_view to the new size
	m_view.setSize(tempX, -tempY);
}

void ComplexPlane::zoomOut()
{
	double tempX, tempY;
	// Increment m_zoomCount
	m_zoomCount--;
	// Set a local variable for the x size to BASE_WIDTH * (BASE_ZOOM to the m_ZoomCount power)
	tempX = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	// Set a local variable for the y size to BASE_HEIGHT * m_aspectRatio * (BASE_ZOOM to the m_ZoomCount power)
	tempY = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	// setSize in m_view to the new size
	m_view.setSize(tempX, tempY);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	// setCenter for m_view to the given coordinate
	m_view.setCenter(coord);
}

View ComplexPlane::getView()
{
	// Return view
	return m_view;
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	// Store the given value in the m_mouseLocation variable
	m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text& text)
{
	/*
	Use a stringstream and the corresponding member variables to create the following output:
		Mandelbrot Set
		Center: (0,0)
		Cursor: (cursor posx, cursor posy)
		Left-click to Zoom in
		Right-click to Zoom out
	*/
	string firstString = "Mandelbrot Set \n",
		secondString = "Center: ",
		thirdString = "Cursor: ",
		fourthString = "Left-click to Zoom in\n",
		fifthString = "Right-click to Zoom out\n";

	string displayString;

	string displayCenter = "(" + to_string(m_view.getCenter().x) + ", " + to_string(m_view.getCenter().y) + ")\n";

	string displayMouseCoordinate = "(" + to_string(m_mouseLocation.x) + ", " + to_string(m_mouseLocation.y) + ")\n";

	displayString = firstString + secondString + displayCenter + thirdString + displayMouseCoordinate + fourthString + fifthString;

	text.setString(displayString);
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	// Count the number of iterations of the set for the given coordinate as specified above
	size_t iCount = 0;
	complex<double> z (0, 0);
	complex<double> c (coord.x, coord.y);
	for (int i = 0; i <= MAX_ITER; i++)
	{
		z = z * z + c;
		if (abs(z) <= 2.0)
		{
			iCount++;
		}
	}
	return iCount;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	// Map the given iteration count to an r,g,b color and assign the given reference variables
	if (count >= MAX_ITER)
	{
		r = 0,
			g = 0,
			b = 0;
	}
	else if (count <= MAX_ITER / 4.0)
	{
		r = count * 4,
			g = 0,
			b = 100 + (count * 10);
	}
	else if (count <= MAX_ITER / 2.0)
	{
		r = 0,
			g = 150 + (count * 10),
			b = 255 - (count * 12);
	}
	else if (count <= MAX_ITER / 1.5)
	{
		r = count * 2,
			g = 100 + (count * 10),
			b = 0;
	}
	else if (count <= MAX_ITER)
	{
		r = 140 + (count * 10),
			g = 10,
			b = 10;
	}
}

void ComplexPlane::genSet(Vector2f resolution, VertexArray* verArray, RenderWindow* window, ComplexPlane plane, int threadCount, int mainI)
{
	// Double for loop to loop through all pixels in screen height/width
	for (int i = mainI; i < resolution.y; i += threadCount)
	{
		for (int j = 0; j < resolution.x; j++)
		{
			// Use mapPixelToCoords to find the Vector2f coordinate in the ComplexPlane View
			(*verArray)[j + i * resolution.x].position = {(float)j, (float)i};
			Vector2f pixelCoordinates = (*window).mapPixelToCoords(Vector2i(j, i), plane.getView());
			// Call ComplexPlane::countIteraions for Vector2f coordinate in the ComplexPlane(+store interations)
			int iterations = plane.countIterations(pixelCoordinates);
			// Declare R G B as Uint8 local variables to store RGB values for current pixel
			Uint8 r, g, b;
			// Pass the number of iterations and the RGB values into ComplexPlane::iterationsToRGB
			plane.iterationsToRGB(iterations, r, g, b);
			// Set the color variable in the element of VertexArray that corresponds to the screen coordinate
			(*verArray)[j + i * resolution.x].color = { r, g, b };
		}
	}
}
