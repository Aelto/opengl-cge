#pragma once

#include <GL/glew.h>

namespace cge {

	struct Position {
		float x;
		float y;
	};

	struct ColorRGBA8 {
		ColorRGBA8() : r( 0 ), g( 0 ), b( 0 ), a( 0 ) { }
		ColorRGBA8( GLubyte R, GLubyte G, GLubyte B, GLubyte A ) :
			r( R ), g( G ), b( B ), a( A ) { }
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV {
		float u;
		float v;
	};

	//The vertex definition
	struct Vertex {

		Position position;

		//4 bytes for r g b a color.
		ColorRGBA8 color;

		//UV texture coordinates.
		UV uv;

		void setPosition( float x, float y ) {
			position.x = x;
			position.y = y;
		}

		void setColor( GLubyte r, GLubyte g, GLubyte b, GLubyte a ) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV( float u, float v ) {
			uv.u = u;
			uv.v = v;
		}
	};

}