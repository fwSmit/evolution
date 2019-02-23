#include "Rocket.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace arma;
using namespace std;

Rocket::Rocket(){
	setRadius(30);
	setPos(fvec2{100, 100});
	setVel( fvec2{100,10} );
}

arma::fvec2 Rocket::getPos(){
	return pos;
}

fvec2 Rocket::getVel(){
	return vel;
}

void Rocket::setVel(fvec2 _vel){
	//std::cout << "new vel set to: "  << _vel << std::endl;
	vel = _vel;
}

void Rocket::setPos(fvec2 _pos){
	pos = _pos;
	//cout << pos << endl;
}

float Rocket::getRadius(){
	return radius;
}

void Rocket::setRadius(float _radius){
	radius = _radius;
	setMass(4/3 * arma::datum::pi * pow( _radius, 3));
}

float Rocket::getMass(){
	return mass;
}

void Rocket::setMass(float _mass){
	mass = _mass;
}

void Rocket::travel(float time){
	pos += vel * time;
}

void Rocket::applyForce(arma::fvec2 force, float time){
	fvec2 acceleration = force / getMass();
	setVel(getVel() + acceleration * time);
}

void Rocket::draw(sf::RenderWindow& window){
	sf::CircleShape circle(getRadius());
	circle.setPosition(getPos()[0], getPos()[1]);
	circle.setOrigin(getRadius()/2, getRadius()/2);
	circle.setFillColor(sf::Color::Blue);
	window.draw(circle);
}
