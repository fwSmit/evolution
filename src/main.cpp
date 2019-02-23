#include <SFML/Graphics.hpp>
#include <iostream>
#include <armadillo>
#include "Rocket.h"

int n_rockets = 11;
float speed = 100.f;

arma::fvec2 getRandomVel(float speed);
arma::fvec2 rotationToVel(float rotation, float speed);

std::vector<std::vector<float>> vels;
int n_vels = 3;
int framesPerVel = 60;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Evolution");
	arma::arma_rng::set_seed_random();
	window.setVerticalSyncEnabled(true);
	std::vector<Rocket> rockets;
	arma::fvec2 targetPlace{200, 50};
	sf::CircleShape target(30);
	target.setPosition(targetPlace[0], targetPlace[1]);
	target.setOrigin(target.getRadius()/2, target.getRadius()/2);
	target.setFillColor(sf::Color::Red);
	// rocket.setRadius(100);
	// rocket.setVel(getRandomVel(speed));
	rockets.resize(n_rockets);	
	vels.resize(n_rockets);
	std::cout << "Fine up until here" << std::endl;
	for(size_t i = 0; i < rockets.size(); i++){
		rockets[i].setPos(arma::fvec2{400, 400});
		
		vels[i].resize(n_vels);
		for(size_t j = 0; j < vels[i].size(); j++){
			vels[i][j] = arma::randu()*arma::Datum<float>::pi * 2;
		}
	}
	
	int count = 0;
	int vel_number = 0;
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type){
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}

		window.clear();
		for(size_t i = 0; i < rockets.size(); i ++){
			float deltaRot = vels[i][vel_number + 1] - vels[i][vel_number];
			rockets[i].setVel(rotationToVel(vels[i][vel_number] + deltaRot * float(count)/float(framesPerVel), speed));
			rockets[i].travel(1.f/60.f);
			rockets[i].draw(window);
		}
		window.draw(target);
		window.display();
		count++;
		if(count >= 60){
			count = 0;
			vel_number++;
			vel_number = vel_number % (n_vels-2);
		}
	}
}

arma::fvec2 getRandomVel(float speed){
	float rotation = arma::randu() * arma::datum::pi * 2;
	arma::fvec2 result = speed * arma::fvec2{static_cast<float>(cos(rotation)), static_cast<float>(sin(rotation))};
	return result;
}

arma::fvec2 rotationToVel(float rotation, float speed){
	arma::fvec2 result = speed * arma::fvec2{static_cast<float>(cos(rotation)), static_cast<float>(sin(rotation))};
	return result;
}
