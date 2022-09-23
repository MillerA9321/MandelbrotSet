// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

// Begin program
int main()
{
	// Get desktop res and calculate aspect ratio (height/width)
	int windowWidth = VideoMode::getDesktopMode().width,
		windowHeight = VideoMode::getDesktopMode().height,
		aspectRatio = windowWidth/windowHeight;

	// Construct the window
	VideoMode vm(windowWidth, windowHeight);
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

		/*-------------------
		******DrawScene******
		---------------------*/

		window.clear();
		window.display();
	}

	return 0;
}