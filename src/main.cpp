#include <SFML/Graphics.hpp>
#include <iostream>
#include <armadillo>
#include "Rocket.h"

int n_rockets = 1000;
float speed = 100.f;

arma::fvec2 getRandomVel(float speed);
arma::fvec2 rotationToVel(float rotation, float speed);
int selectRandomRocket(std::vector<float>& distribution);

std::vector<std::vector<float>> vels;
int n_vels = 10;
int framesPerVel = 60;
bool stop = false;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Evolution");
	arma::arma_rng::set_seed_random();
	window.setVerticalSyncEnabled(true);
	std::vector<Rocket> rockets;
	arma::fvec2 targetPlace{200, 50};
	arma::fvec2 startingPos{400, 400};
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
		rockets[i].setPos(startingPos);
		
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
			if(!stop){
				float deltaRot = vels[i][vel_number + 1] - vels[i][vel_number];
				rockets[i].setVel(rotationToVel(vels[i][vel_number] + deltaRot * float(count)/float(framesPerVel), speed));
				rockets[i].travel(1.f/60.f);
			}
				rockets[i].draw(window);
		}
		window.draw(target);
		window.display();
		if(!stop)
		{
			count++;
		}
		if(count >= 60){
			count = 0;
			vel_number++;
			if(vel_number > (n_vels - 2)){
				float totalScore = 0;
				std::vector<float> scores;
				scores.resize(rockets.size());
				for(size_t i = 0; i < rockets.size(); i++){
					float distance_sq = arma::accu(arma::pow(rockets[i].getPos() - targetPlace, 2));
					scores[i] = 1/distance_sq;
					totalScore += scores[i];
					std::cout << "Distance " << i << ": " << distance_sq << std::endl;
				}	
				for(size_t i = 0; i < scores.size(); i++){
					scores[i] = scores[i]/totalScore;
				}
				std::vector<std::vector<float>> newVels;
				newVels.resize(n_rockets);
				for(size_t i = 0; i < newVels.size(); i++){
					int parent1 = selectRandomRocket(scores), parent2 = selectRandomRocket(scores);
					int cuttingPoint = arma::randi<int>(arma::distr_param(0, n_vels));
					newVels[i].resize(n_vels);
					for(int j = 0; j < n_vels; j++){
						if(j < cuttingPoint){
							newVels[i][j] = vels[parent1][j];
						}
						else{
							newVels[i][j] = vels[parent2][j];
						}
					}
					rockets[i].setPos(startingPos);
				}
				vels = newVels;
				count = 0;
				vel_number = 0;
			}
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

int selectRandomRocket(std::vector<float>& distribution){
	float number = arma::randu();
	for(size_t i = 0; i < distribution.size(); i++){
		if(number < distribution[i]){
			return int(i);
		}
		else{
			number -= distribution[i];
		}
	}
	return distribution.size() - 1;
}
