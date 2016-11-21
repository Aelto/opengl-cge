#version 430
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 view;

void main() {
    //Set the x,y position on the screen
    gl_Position = (view * vec4(vertexPosition, 0.0, 1.0));
    
    fragmentPosition = vertexPosition;
    
    fragmentColor = vertexColor;
    
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}