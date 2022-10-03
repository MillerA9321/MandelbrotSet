// Include important C++ libraries/User defined header files here
#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>
#include <sstream>
#include <thread>
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

	float aspectRatio = resolution.y/resolution.x;

	// Construct the window
	VideoMode vm(resolution.x, resolution.y);
	RenderWindow window(vm, "Mandelbrot", Style::Fullscreen);

	// Construct an object of type ComplexPlane(this is after we do the ComplexPlane file)
	ComplexPlane plane(aspectRatio);

	// Construct Font and Text objects
	Font font;
	if (!font.loadFromFile("font/KOMIKAP_.ttf"))
	{
		cout << "Error: Font File" << endl;
	}

	Text text;
	text.setCharacterSize(35);
	text.setFont(font);
	text.setPosition(12, 12);

	// Construct a VertexArray, this is used for drawing each pixels color
	VertexArray verArray;
	verArray.setPrimitiveType(Points);
	verArray.resize(resolution.x * resolution.y);

	// Create an enum class with CALCULATING and DISPLAYING, initialize to CALCULATING
	enum State {
		CALCULATING,
		DISPLAYING
	};
	State currentState = CALCULATING;

	// Begin the main loop
	while (window.isOpen())
	{

		/*-------------------
		*****HandleInput*****
		---------------------*/
		Event handleEvent;
		while (window.pollEvent(handleEvent))
		{
			// Handle the closing of the window
			if (handleEvent.type == Event::Closed)
			{
				window.close();
			}
			// Handle Event::MouseButtonPressed for zooming in and out
			if (handleEvent.type == Event::MouseButtonPressed)
			{
				// Zoom in
				Vector2f getClickLoc = window.mapPixelToCoords(Mouse::getPosition(window), plane.getView());
				if (handleEvent.mouseButton.button == Mouse::Left)
				{
					plane.zoomIn();
					plane.setCenter(getClickLoc);
				}
				// Zoom out
				if (handleEvent.mouseButton.button == Mouse::Right)
				{
					plane.zoomOut();
					plane.setCenter(getClickLoc);
				}
				// Set current state so that it doesn't keep rendering and make the program explode
				currentState = CALCULATING;
			}
			// Handle Event::MouseMoved
			if (handleEvent.type == Event::MouseMoved)
			{
				Vector2f getMouseLoc = window.mapPixelToCoords(Mouse::getPosition(window), plane.getView());
				plane.setMouseLocation(getMouseLoc);
			}
		}

		// Check if escape is pressed to exit the window
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*-------------------
		*****UpdateScene*****
		---------------------*/
		// If the state is CALCULATING
		if (currentState == CALCULATING)
		{
			// Number of threads
			const int THREAD_COUNT = 16;
			// Prep the threads
			thread thr[THREAD_COUNT];
			// Run the program within the set number of threads using a for loop
			for (int i = 0; i < THREAD_COUNT; i++)
			{
				thr[i] = thread(&ComplexPlane::genSet, plane, resolution, &verArray, &window, plane, THREAD_COUNT, i);
			}
			// For loop to join the work (I still only vaguely understand what this does, but it works)
			for (int i = 0; i < THREAD_COUNT; i++)
			{
				thr[i].join();
			}
			// Set the state to DISPLAYING
			currentState = DISPLAYING;
		}
		
		// Call loadText from the ComplexPlane object
		plane.loadText(text);
		
		/*-------------------
		******DrawScene******
		---------------------*/
		// Clear the window
		window.clear();
		// Draw VertexArray
		window.draw(verArray);
		// Draw Text
		window.draw(text);
		// Display
		window.display();
	}

	return 0;
}