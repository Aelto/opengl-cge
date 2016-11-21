#version 430

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;

uniform sampler2D image;

void main() {
    
    vec4 textureColor = texture(image, fragmentUV);
    
    color = fragmentColor * textureColor;
}