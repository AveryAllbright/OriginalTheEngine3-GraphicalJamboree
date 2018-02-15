#include "Game.h"
#include "Vertex.h"

// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		   // The application's handle
		"DirectX Game",	   // Text for the window's title bar
		1920,			   // Width of the window's client area
		1080,			   // Height of the window's client area
		true)			   // Show extra stats (fps) in title bar?
{
	// Initialize fields
	vertexShader = 0;
	pixelShader = 0;

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.");
#endif
	
}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	// Delete our simple shader objects, which
	// will clean up their own internal DirectX stuff
	delete vertexShader;
	delete pixelShader;
	delete Triangle;
	delete Square;
	delete Octogon;
	delete baseMat;
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	LoadShaders();
	CreateMatrices();
	CreateBasicGeometry();

	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Game::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device, context);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, context);
	pixelShader->LoadShaderFile(L"PixelShader.cso");
}

// --------------------------------------------------------
// Initializes the matrices necessary to represent our geometry's 
// transformations and our 3D camera
// --------------------------------------------------------
void Game::CreateMatrices()
{
	// Set up world matrix
	// - In an actual game, each object will need one of these and they should
	//    update when/if the object moves (every frame)
	// - You'll notice a "transpose" happening below, which is redundant for
	//    an identity matrix.  This is just to show that HLSL expects a different
	//    matrix (column major vs row major) than the DirectX Math library
	XMMATRIX W = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W)); // Transpose for HLSL!

	// Create the View matrix
	// - In an actual game, recreate this matrix every time the camera 
	//    moves (potentially every frame)
	// - We're using the LOOK TO function, which takes the position of the
	//    camera and the direction vector along which to look (as well as "up")
	// - Another option is the LOOK AT function, to look towards a specific
	//    point in 3D space
	XMVECTOR pos = XMVectorSet(0, 0, -5, 0);
	XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMMATRIX V = XMMatrixLookToLH(
		pos,     // The position of the "camera"
		dir,     // Direction the camera is looking
		up);     // "Up" direction in 3D space (prevents roll)
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!

	Cam.SetProjection(height, width);
	SetCursorPos(width / 2, height / 2);
}

// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{

	//Triangle Geometry!
	
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
		
	Vertex vertices[] =
	{
		{ XMFLOAT3(-3.0f, +1.0f, +0.0f), red },
		{ XMFLOAT3(-1.f, -1.0f, +0.0f), blue },
		{ XMFLOAT3(-3.f, -1.0f, +0.0f), green },
	};
		
	int indices[] = { 0, 1, 2 };
	
	Triangle = new Mesh(vertices, 3, indices, 3, device);

	//Square Geometry!
	Vertex squareVerts[] = 
	{
		{ XMFLOAT3(1.50f, .0f, .0f), red },
		{ XMFLOAT3(2.5f, .0f, +0.0f), blue },
		{ XMFLOAT3(+2.5f, -1.0f, +0.0f), green },
		{ XMFLOAT3(1.5f, -1.0f, +0.0f), blue },
	};

	int squareIndices[] = { 0, 1, 2, 0, 2, 3 };

	Square = new Mesh(squareVerts, 4, squareIndices, 6, device);

	//Eight Awesome Angles

	Vertex OctVerts[]
	{
		{XMFLOAT3(0.f, 0.f, 0.f), red},

		{ XMFLOAT3(0.f, 1.f, 0.f), blue },
		{ XMFLOAT3(.7f, .7f, 0.f), green },

		{ XMFLOAT3(1.f, 0.f, 0.f), red },
		{ XMFLOAT3(.7f, -.7f, 0.f), blue },

		{ XMFLOAT3(0.f, -1.f, 0.f), green },
		{ XMFLOAT3(-.7f, -.7f, 0.f), red },

		{ XMFLOAT3(-1.f, 0.f, 0.f), blue },
		{ XMFLOAT3(-.7f, .7f, 0.f), green },
	};

	int OctIndices[] = 
	{ 
		0, 1, 2,
		0, 2, 3,
		0, 3, 4, 
		0, 4, 5, 
		0, 5, 6, 
		0, 6, 7, 
		0, 7, 8, 
		0, 8, 1 
	};

	Octogon = new Mesh(OctVerts, 9, OctIndices, 24, device);

	XMFLOAT3 standRot = XMFLOAT3(0, 0, 0);
	XMFLOAT3 standScale = XMFLOAT3(1, 1, 1);

	baseMat = new Material(vertexShader, pixelShader);

	Entities.push_back(Entity(Triangle, baseMat, worldMatrix, XMFLOAT3(0, 0, 0), standRot, standScale));
	Entities.push_back(Entity(Square, baseMat, worldMatrix, XMFLOAT3(0,0,0), standRot, standScale));

	for (UINT i = 0; i < 3; i++)
	{
		Entities.push_back(Entity(Octogon, baseMat, worldMatrix, XMFLOAT3(0,0,0), standRot, XMFLOAT3(.5f, .5f, .5f)));
	}
}

// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	// Update our projection matrix since the window size changed
	Cam.SetProjection(height, width);
	SetCursorPos(width / 2, height / 2);
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();
	
	Entities[0].Move(XMFLOAT3(sin(deltaTime), 0, 0));
	Entities[1].Move(XMFLOAT3(0, sin(deltaTime), 0));
	Entities[2].Move(XMFLOAT3(0, 0, sin(deltaTime)));
	Entities[3].RotateBy(XMFLOAT3(sin(deltaTime), 0, 0));
	Entities[4].Move(XMFLOAT3(sin(deltaTime), 0, 0));

	for (int i = 0; i < 5; i++)
	{
		Entities[i].UpdateWorldView();
	}	

	Cam.Update(deltaTime);
	Cam.Rotate(0, 0, width, height);
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	ID3D11Buffer* vert;

	for (UINT i = 0; i < Entities.size(); i++)
	{

		Entities[i].PrepareMaterial(Cam.GetViewMat(), Cam.GetProjMat());

		// Set buffers in the input assembler
		//  - Do this ONCE PER OBJECT you're drawing, since each object might
		//    have different geometry.
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		vert = Entities[i].GetMesh()->GetVertexBuffer();

		context->IASetVertexBuffers(0, 1, &vert, &stride, &offset);
		context->IASetIndexBuffer(Entities[i].GetMesh()->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

		context->DrawIndexed(
			Entities[i].GetMesh()->GetIndexCount(),     // The number of indices to use (we could draw a subset if we wanted)
			0,     // Offset to the first index we want to use
			0);    // Offset to add to each index when looking up vertices
	}
	
	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);
}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	
	// Add any custom code here...
	//Cam.Rotate(x - prevMousePos.x, y - prevMousePos.y);
	// Save the previous mouse position, so we have it for the future
	
	prevMousePos.x = x;
	prevMousePos.y = y;
	
	//Attempting to recenter the mouse like in previous versions, but the way I am currently passing information about makes it lock
	//In previous iterations, the mouse position was captured, transformations applied, and then the mouse was reset to center
	//Here, the mouse pos being moved back to center IS a mouseMove, meaning the rotation gets called again as the mouse moves back by -n units the direction it just traveled.  

	/*
	float fSens = .001f;
	float yRot = fSens * (x - width * .5f);
	float xRot = fSens * (y - height * .5f);
	Cam.Rotate(xRot, yRot);
	SetCursorPos(width / 2.f, height / 2.f);
	*/

	//So, currently, I'm just passing in the screen size to the camera waaaay too often, its on my TODO I swear
	//And just ripping the data out manually even when I don't need it.
	//I know, its trash. But things were getting all.... stuck-like.
	//This is my third (fourth) major engine (re)build, and I have yet to make a camera I actually like.
	//So that's on my TODO too. 
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion