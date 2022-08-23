#include <windows.h>		
#include <gl\gl.h>			
#include <gl/glu.h>			
#include <glaux.h>	
#include <math.h>
#include <texture.h>
#include "camera.h"
#include "unit.cpp"
#include "Cupe.cpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include <Model_3DS.h>
#include <3DTexture.h>
#include <set>
#include <queue>
#include "sound.h"
#include "SoccerBall.h"
#include "BallLogic.h"
using namespace std;
#define PI 3.141592653589

HDC			hDC = NULL;
HGLRC		hRC = NULL;
HWND		hWnd = NULL;
HINSTANCE	hInstance;

bool	keys[256];
bool	active = TRUE;
bool	fullscreen = TRUE;

GLfloat LightPos[] = { 0.0f, 190.0f, 0.0f, 150.0f };
GLfloat LightAmp[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiff[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightSpec[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat MatAmb[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat MatDiff[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat MatSpec[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat Matshn[] = { 128.0f };

struct mousePair
{
	GLfloat X, Y;
} MousePt;

bool isClicked = false;
bool isRClicked = false;
bool isDragging = false;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)
	{
		height = 1;
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000000000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GLfloat lastX = 0;
GLfloat lastY = 0;

Model_3DS theBall , goal;
vector<unit> allUnits;
Cupe skyBox;
INIT initializer = INIT();
Sound sound1, sound2,sound3;
SoccerBall *ball;
BallLogic *logic;
Camera MyCamera(0,0,0);

bool reset = false , start = false;// for start rendering after entering first force and angle
bool enterPressedOnce = false;//for ensure that enter button pressed just one time
int arrowUp = 0.0, arrowRight = 0.0; // for the angles
int Fi = 200.0;// initial force
bool scoreSound = false ;



// textures for SkyBox
int Cupe::skyBoxTexture1Id[6], forceTexture[11];
void LoadTexturId()
{
	Cupe::skyBoxTexture1Id[0] = LoadTexture((char*)"images//stadium//up.bmp");
	Cupe::skyBoxTexture1Id[1] = LoadTexture((char*)"images//stadium//down.bmp");
	Cupe::skyBoxTexture1Id[2] = LoadTexture((char*)"images//stadium//north.bmp");
	Cupe::skyBoxTexture1Id[3] = LoadTexture((char*)"images//stadium//south.bmp");
	Cupe::skyBoxTexture1Id[4] = LoadTexture((char*)"images//stadium//right.bmp");
	Cupe::skyBoxTexture1Id[5] = LoadTexture((char*)"images//stadium//left.bmp");

	forceTexture[0] = forceTexture[1] = forceTexture[2] = LoadTexture((char*)"images//force//1.bmp");
	forceTexture[3] = forceTexture[4] = LoadTexture((char*)"images//force//2.bmp");
	forceTexture[5] = forceTexture[6] = LoadTexture((char*)"images//force//3.bmp");
	forceTexture[7] = forceTexture[8] = LoadTexture((char*)"images//force//4.bmp");
	forceTexture[9] = forceTexture[10] = LoadTexture((char*)"images//force//5.bmp");

}


double ballX = 0.0, ballY = 0.0 ;
double Fx, Fy, Fz;

double mass , density , airSpeedX , airSpeedZ , radios , ballZ , vis , Wx , Wy , Wz , frictionFactor,bouncingFactor;


// input file
double str_to_double(const string& str) {
stringstream input(str);
string num ;
input >> num;

return std::stod(num);
}

void getInput()
{
fstream file;
string line;
file.open("input.txt", ios::in);

	getline(file, line);  mass = str_to_double(line);
	getline(file, line);  density= str_to_double(line);
	getline(file, line);  airSpeedX= str_to_double(line);
	getline(file, line);  airSpeedZ= str_to_double(line);
	getline(file, line);  radios= str_to_double(line);
	getline(file, line);  ballZ= str_to_double(line);
	getline(file, line);  vis= str_to_double(line);
	getline(file, line);  Wx= str_to_double(line);
	getline(file, line);  Wy= str_to_double(line);
	getline(file, line);  Wz= str_to_double(line);
	getline(file, line);  frictionFactor= str_to_double(line);
	getline(file, line);  bouncingFactor= str_to_double(line);


file.close();
}

void stadiume()
{
	LoadTexturId();
	Cupe temp(-750, -750, 1500, 700, 0);  // sky Box
	skyBox = temp;
	skyBox.allocate(allUnits);
}

void sound(){
	initializer.InitOpenAL();
	sound1 = Sound((char*)"wave//daraj.wav");
	sound2 = Sound((char*)"wave//back.wav");
	sound3 = Sound((char*)"wave//goal.wav");
	sound2.Play();
}

void Ball(){
	theBall.Load((char*)"images/ball/ball.3ds");
	GLTexture ballImage1, ballImage2;
	ballImage1.LoadBMP((char*)"images/ball/ball1.bmp");
	ballImage2.LoadBMP((char*)"images/ball/ball2.bmp");
	theBall.Materials[0].tex = ballImage1;
	theBall.Materials[1].tex = ballImage2;

	// ball initialization
	ball = new SoccerBall(mass, radios , ballX, ballY, ballZ, Wx,Wy,Wz,theBall);
	logic = new BallLogic(ball,density,vis,frictionFactor,bouncingFactor,airSpeedX,airSpeedZ);
}

void Goal(){

	goal.Load((char*)"images/goal/goal.3ds");
	goal.pos.x = 0;
	goal.pos.y = 15;
	goal.pos.z = -510;
	goal.scale = 0.3;
	goal.rot.y = 90 ;
}

void initialForce(){
	double Up, Right;

	Up = (arrowUp * PI) / 180;
	Right = (arrowRight * PI) / 180;

	Fz = (Fi * cos(Up)) * cos(Right);
	Fx = (Fi * cos(Up)) * sin(Right);
	Fy = Fi * sin(Up);
}

int InitGL(GLvoid)
{
	getInput();
	sound();
	stadiume();
	Ball();
	Goal();
	MyCamera.setter(ballX, ballY , ballZ + 70);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	return TRUE;										// Initialization Went OK
}

void Key(bool* keys, float speed)
{
	// reset
	if (keys[VK_ESCAPE]) reset = true;

	// for camera look at vector
	if (keys[VK_UP]) MyCamera.RotateX(2 * speed);
	if (keys[VK_DOWN]) MyCamera.RotateX(-2 * speed);
	if (keys[VK_RIGHT]) MyCamera.RotateY(-2 * speed);
	if (keys[VK_LEFT]) MyCamera.RotateY(2 * speed);

	// for moving
	if (keys['I']) MyCamera.MoveForward(1 * speed, allUnits);
	if (keys['K']) MyCamera.MoveForward(-1 * speed, allUnits);
	if (keys['L']) MyCamera.MoveRight(1 * speed, allUnits);
	if (keys['J']) MyCamera.MoveRight(-1 * speed, allUnits);

	// speed
	if (keys[VK_SHIFT]) MyCamera.MoveForwardWitout(1 * speed);

	// for initial force & angles & start 
	if (keys[13]&&!start)
	{
		start = true;
		logic->applyInitialForce(Vector3d(Fx,Fy,-Fz));
	}
	if (keys['W']) if (arrowUp<45) arrowUp += 1;
	if (keys['S']) if (arrowUp>0) arrowUp -= 1;
	if (keys['D']) if (arrowRight<45) arrowRight += 1;
	if (keys['A']) if (arrowRight>-45) arrowRight -= 1;
	if (keys['E']) if (Fi<2000) Fi += 200.0;
	if (keys['Q']) if (Fi>200) Fi -= 200.0;

	// optional music
	bool EnableSound = false;
	bool soundRuning = true;
	if (keys['Z'])
	{
		if (soundRuning){
			if (EnableSound)
			{
				sound1.Stop();
				EnableSound = false;
			}
			else
			{
				sound1.Play();
				EnableSound = true;
			}
		}
	}

	// mouse
	if (!isDragging)
	{
		if (isRClicked || isClicked)
		{
			isDragging = true;
			lastX = MousePt.X;
			lastY = MousePt.Y;
		}
	}
	else
	{
		if (isRClicked || isClicked)
		{
			if (lastY > MousePt.Y)
			{
				MyCamera.RotateX(2 * speed);
			}
			if (lastY < MousePt.Y)
			{
				MyCamera.RotateX(-2 * speed);
			}
			if (lastX > MousePt.X)
			{
				MyCamera.RotateY(2 * speed);
			}
			if (lastX < MousePt.X)
			{
				MyCamera.RotateY(-2 * speed);
			}
		}
		else
		{
			isDragging = false;
		}
		lastX = MousePt.X;
		lastY = MousePt.Y;
	}
}

void Force(int y){

	glPushMatrix();

	glTranslated(ballX + 7, y, ballZ + 3);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, forceTexture[y]);

	y = y * 2;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(2, y, 10);   // Bottom Left Of The Quad 
	glTexCoord2f(1.0, 0.0); glVertex3f(10, y, 10);    // Bottom Right Of The Quad
	glTexCoord2f(1.0, 1.0); glVertex3f(10, y + 2, 10);    // Top Right Of The Quad 
	glTexCoord2f(0.0, 1.0); glVertex3f(2, y + 2, 10);   // Top Left Of The Quad 
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glTranslated(0, 0, 0);

	glPopMatrix();
}

void arrow(){

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, forceTexture[10]);

	glTranslated(ballX, 5, ballZ);

	glRotated(arrowUp, 1, 0, 0);
	glRotated(arrowRight, 0, -1, 0);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 1, 0);   // Bottom Left Of The Quad 
	glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 1, 0);    // Bottom Right Of The Quad
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 1, -30);    // Top Right Of The Quad 
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 1, -30);   // Top Left Of The Quad 
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 1, -34);   // Top Middle Of The Quad 
	glTexCoord2f(1.0, 1.0); glVertex3f(-1.5, 1, -30);   // Top Left Of The Quad 
	glTexCoord2f(1.0, 0.0); glVertex3f(1.5, 1, -30);    // Top Right Of The Quad 
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glTranslated(0, 0, 0);

	glPopMatrix();
}

void Reset(){
	start = false;
	sound2.Play();
	scoreSound = false ;
	sound3.Stop();
	arrowUp = 0.0;
	arrowRight = 0.0;
	Fi = 200.0;
	getInput();
	logic->reset(density,vis,frictionFactor,bouncingFactor,airSpeedX,airSpeedZ,mass,radios,Wx,Wy,Wz,ballX, ballY, ballZ);
	MyCamera.setter(ballX,ballY,ballZ+70);
	reset = false;
}

void scored (){
	scoreSound = true;
	sound3.Play(); 
}

void DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Key(keys, 2);
	MyCamera.Render();
	skyBox.Draw();
	// goal
	glPushMatrix();
	glTranslated(0,0,0);
	glScaled(1.25,1,0.7);
	glTranslated(goal.pos.x , goal.pos.y , goal.pos.z );
	goal.Draw();
	glPopMatrix();


	if( ( ball->getZ() <= -695 ) && ( ball->getY()<=60 ) && ( ball->getX() >= -107 && ball->getX() <= 107 ) && !scoreSound) {
		 scored();
	}


	if (reset) Reset();
	if(ball->getZ() <= -600 && ball->getX() >= 0){
	  MyCamera.setter(-100,25,-720); 
	  MyCamera.setView(1.0); 
	}
	if(ball->getZ() <= -600 && ball->getX() < 0){
	  MyCamera.setter(100,25,-720); 
	  MyCamera.setView(-1.0); 
	}
	if (!start)  {
		for (int i = 1; i <= (Fi / 200); i++) Force(i);
		arrow();
		initialForce();
	}

	if (start) logic->move();

	logic->draw();

	glFlush();
	SwapBuffers(hDC);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT		WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;

	fullscreen = fullscreenflag;

	hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OpenGL";

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

void CheckMouse(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		MousePt.X = (GLfloat)LOWORD(lParam);
		MousePt.Y = (GLfloat)HIWORD(lParam);
		isClicked = (LOWORD(wParam) & MK_LBUTTON) ? true : false;
		isRClicked = (LOWORD(wParam) & MK_RBUTTON) ? true : false;
		break;
	case WM_LBUTTONUP:
		isClicked = false;
		break;
	case WM_RBUTTONUP:
		isRClicked = false;
		break;
	case WM_LBUTTONDOWN:
		isClicked = true;
		break;
	case WM_RBUTTONDOWN:
		isRClicked = true;
		break;
	}
}

LRESULT CALLBACK WndProc(HWND	hWnd, UINT	uMsg, WPARAM	wParam, LPARAM	lParam)
{
	CheckMouse(uMsg, wParam, lParam);

	static PAINTSTRUCT ps;

	switch (uMsg)
	{
	case WM_PAINT:
		DrawGLScene();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		DrawGLScene();
		return 0;

	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
													if (!HIWORD(wParam))					// Check Minimization State
													{
														active = TRUE;						// Program Is Active
													}
													else
													{
														active = FALSE;						// Program Is No Longer Active
													}

													return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
													switch (wParam)							// Check System Calls
													{
													case SC_SCREENSAVE:					// Screensaver Trying To Start?
													case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
														return 0;							// Prevent From Happening
													}
													break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
													PostQuitMessage(0);						// Send A Quit Message
													return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
													keys[wParam] = TRUE;					// If So, Mark It As TRUE
													return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
													keys[wParam] = FALSE;					// If So, Mark It As FALSE
													return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
													ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
													return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = false;							// Windowed Mode
	}

	// Create Our OpenGL Window ( old:  640, 480, 16 )
	if (!CreateGLWindow((char*)"SoccerBall Simulation", 1280, 720, 56, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer = SetTimer(hWnd, 0, 20, (TIMERPROC)NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}