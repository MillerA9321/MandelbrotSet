// Include important C++ libraries/User defined header files here
#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex.h>
#include "ComplexPlane.h"

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

// Begin program
int main()
{
	// Get desktop res and calculate aspect ratio (height/width)
	Vector2f resolution;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	float aspectRatio = resolution.x/resolution.y;

	// Construct the window
	VideoMode vm(resolution.x, resolution.y);
	RenderWindow window(vm, "Mandelbrot", Style::Fullscreen);

	// Construct an object of type ComplexPlane(this is after we do the ComplexPlane file)

	// Construct Font and Text objects

	// Construct a VertexArray, this is used for drawing each pixels color

	// Create an enum class with CALCULATING and DISPLAYING, initialize to CALCULATING

	// Begin the main loop
	while (window.isOpen())
	{

		/*-------------------
		*****HandleInput*****
		---------------------*/
		// Handle the closing of the window

		// Handle Event::MouseButtonPressed for zooming in and out

		// Handle Event::MouseMoved

		// Check if escape is pressed to exit the window
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*-------------------
		*****UpdateScene*****
		---------------------*/
		// If the state is CALCULATING

			// Double for loop to loop through all pixels in screen height/width
			
			// Use mapPixelToCoords to find the Vector2f coordinate in the ComplexPlane View

			// Call ComplexPlane::countIteraions for Vector2f coordinate in the ComplexPlane(+store interations)

			// Declare R G B as Uint8 local variables to store RGB values for current pixel
			
			// Pass the number of iterations and the RGB values into ComplexPlane::iterationsToRGB

			// Set the color variable in the element of VertexArray that corresponds to the screen coordinate

			// Set the state to DISPLAYING

			// Call loadText from the ComplexPlane object

		// End of for loop

		/*-------------------
		******DrawScene******
		---------------------*/
		// Clear the window
		window.clear();

		// Draw VertexArray

		// Draw Text

		// Display
		window.display();
	}

	return 0;
}