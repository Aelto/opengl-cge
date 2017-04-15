#include "Circle.h"

#include <iostream>
#include <cmath>
#include <math.h>

uni::Circle::Circle( float _radius, glm::vec2 _position, cge::Texture2D * _texture, glm::vec3 _color )
{

	setRadius( _radius );
	position = _position;
	color = _color;

	rotate = 0.0f;
	texture = _texture;


	velocity = glm::vec2( 0, 0 );
	acceleration = glm::vec2( 0, 0 );
}

void uni::Circle::setRadius( float _radius )
{

	radius = _radius;

	mass = radius * 10.0f;

}

void uni::Circle::updateRadius( float delta )
{

	setRadius( radius + delta );

}

void uni::Circle::draw( cge::Shader & spriteShader, cge::Camera & camera, GLuint quadVAO )
{
	spriteShader.Use();

	glm::mat4 model;
	model = glm::translate( model, glm::vec3( position, 0.0f ) );  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	 model = glm::translate(model, glm::vec3(-0.5f * radius, -0.5f * radius, 0.0f)); // Move origin of rotation to center of quad

	model = glm::rotate( model, rotate, glm::vec3( 0.0f, 0.0f, 1.0f ) ); // Then rotate

	model = glm::translate( model, glm::vec3( -0.5f * radius, -0.5f * radius, 0.0f ) ); // Move origin back

	model = glm::scale( model, glm::vec3( radius * 2, radius * 2, 1.0f ) ); // Last scale

	spriteShader.SetMatrix4( "model", model );

	// Camera
	spriteShader.SetMatrix4( "view", camera.view );

	// Render textured quad
	spriteShader.SetVector3f( "spriteColor", color );

	glActiveTexture( GL_TEXTURE0 );
	texture->Bind();

	glBindVertexArray( quadVAO );
	glDrawArrays( GL_TRIANGLES, 0, 6 );
	glBindVertexArray( 0 );
}

glm::vec2 uni::Circle::distanceTo( glm::vec2 pos )
{
	return glm::vec2( pos.x - position.x, pos.y - position.y );
}

bool uni::Circle::intersects( Circle obj )
{

	float sumRadius = this->radius + obj.radius;

	return std::abs( this->position.x - obj.position.x ) <= sumRadius
		|| std::abs( this->position.y - obj.position.y ) <= sumRadius;
}

void uni::Circle::calculateGravity( uni::Circle & planet )
{

	glm::vec2 distance = distanceTo( planet.position );

	float length = std::sqrt( distance.x * distance.x + distance.y * distance.y );

	acceleration.x += planet.mass * ( distance.x / length);
	acceleration.y += planet.mass * ( distance.y / length);
}

void uni::Circle::applyAcceleration( GLfloat delta )
{
	velocity.x += acceleration.x * delta;
	velocity.y += acceleration.y * delta;

	acceleration *= 0.0f;
}

void uni::Circle::applyVelocity( GLfloat delta )
{
	position.x += velocity.x * delta;
	position.y += velocity.y * delta;
}

