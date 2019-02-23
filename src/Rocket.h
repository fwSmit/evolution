#pragma once
#include <armadillo>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Rocket{
	float mass, radius;
	arma::fvec2 pos, vel;
public:
	//class sf::CircleShape getSfObject();
	Rocket();
	float getRadius();
	void setRadius(float _radius);
	float getMass();
	void setMass(float mass);
	arma::fvec2 getPos();
	void setPos(arma::fvec2 _pos);
	arma::fvec2 getVel();
	void setVel(arma::fvec2 _vel);
	void travel(float time); // moves the object by time * velocity
	void applyForce(arma::fvec2 force, float time);
	void draw(sf::RenderWindow& window);
};
