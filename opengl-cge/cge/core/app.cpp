#include "app.h"

cge::app::app( GLuint _width, GLuint _height )
	: width(_width), height(_height)
{

	window = nullptr;

}


cge::app::~app()
{
	//cge::app::currentApp = nullptr;

	glfwTerminate();
}


void cge::app::open( int GL_major, int GL_minor, const char * name ) {

	glfwInit();

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, GL_major );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, GL_minor );

	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

	window = glfwCreateWindow( width, height, name, nullptr, nullptr );
	glfwMakeContextCurrent( window );

	cge::app::currentApp = this;
	glfwSetKeyCallback( window, cge::app::keyCallback_dispatch );

	glewExperimental = GL_TRUE;
	glewInit();
	// Call it once to catch glewInit() bug, all other errors are now from our application.
	glGetError(); 

	// OpenGL configuration
	glViewport( 0, 0, width, height);
	glEnable( GL_CULL_FACE );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

}

cge::app * cge::app::currentApp;

void cge::app::keyCallback_dispatch( GLFWwindow* window, int key, int scancode, int action, int mode ) {
	
	if ( cge::app::currentApp )
		cge::app::currentApp->keyCallback( window, key, scancode, action, mode );

}

void cge::app::keyCallback( GLFWwindow * window, int key, int scancode, int action, int mode )
{

	if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
		glfwSetWindowShouldClose( window, GL_TRUE );

	if ( key >= 0 && key < 1024 )
	{
		if ( action == GLFW_PRESS )
			keys[ key ] = GL_TRUE;
		else if ( action == GLFW_RELEASE )
			keys[ key ] = GL_FALSE;
	}

}

int cge::app::shouldClose() {

	return glfwWindowShouldClose( window );

}

void cge::app::startLoop()
{

	glfwPollEvents();

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}

void cge::app::endLoop()
{

	glfwSwapBuffers( window );

	if ( keys[ GLFW_KEY_ESCAPE ] )
		glfwSetWindowShouldClose( window, GL_TRUE );

}