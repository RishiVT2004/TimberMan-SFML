#include<iostream>
#include<SFML/Graphics.hpp>
#include<cstdlib> // for clock , rand , srand 
using namespace sf;

// input , update and draw part are 3 part of game 

int main(){

	// INPUT SECTION 
	
	VideoMode vm(1366,768);
	RenderWindow window(vm,"Timber!!!");
	
	// create texture object 
	Texture textureBackground;
	
	//Load Graphic to texture 
	textureBackground.loadFromFile("graphics/background.png");
	
	// Using view class helps to improve the display of the window 
	// view(x,y,height,width) -> syntax

	View view(FloatRect(0,0,1920,1080));
	window.setView(view);
		
	Sprite spriteBackground; // create sprite 
	spriteBackground.setTexture(textureBackground); // set sprite to texture background
	
	spriteBackground.setPosition(0,0); // set sprite position 
	
	// Make a Tree texture 
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree; // tree sprite 
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810,0);
	
	// Make Bee texture
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0,800);
	bool beeActive = false; // is bee moving 
	float beeSpeed = 0.0f; // speed of bee 
	
	// Make Cloud texture 
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1,spriteCloud2,spriteCloud3;
	
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	
	spriteCloud1.setPosition(0,0);// cloud position 
	spriteCloud2.setPosition(0,400);
	spriteCloud3.setPosition(0,800);
	
	bool cloud1Active = false; // cloud activity 
	bool cloud2Active = false;
	bool cloud3Active = false;
	
	float cloud1Speed = 0.0f; // cloud speed 
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;
	
	Clock clock; // clock object;
	
	
	while(window.isOpen()){
		//UPDATE SECTION 	
		/*
		Window event is used to remove force shutdown of window screen
		*/
		Event event1; // create an event 
		while(window.pollEvent(event1)){ // select the event 
			if(event1.type == event1.Closed){ // if event1 is closed , window shuts/closes
				window.close();
			}
		}
	
		if(Keyboard::isKeyPressed(Keyboard::Escape)){
			window.close();
		}
		
		// ADDING MOVEMENT TO THE BEE 	
		Time dt = clock.restart(); // time object 
		if(!beeActive){
			srand((int)time(0)*10); //  set random speed range 
			beeSpeed = (rand()%200)+200; // speed is b/w 200 and 400 
			
			/*
			srand - In essence, this line initializes the random number generator with a seed based on the current time, modified slightly. This makes the random number generation vary from one execution of the program to the next.
			
			*/
			// setup srand range for height 
			srand((int)time(0)*10);
			float height = (rand()%500)+500;// height is b/w 500 to 1000
			spriteBee.setPosition(2000,height); //The reason the bee's initial position is set to an x-coordinate of 2000, which is likely off-screen to the right, is to create the visual effect of the bee flying into the screen
			beeActive = true; // Sets beeActive to true, indicating that the bee is now active and moving.
		}else{
		// Move the bee 
		spriteBee.setPosition(
			spriteBee.getPosition().x - beeSpeed*dt.asSeconds() , spriteBee.getPosition().y);//(curr x position,y position)
		
			// Has the bee reached the left-hand edge of the screen?
			if(spriteBee.getPosition().x < -100){
			beeActive = false;// Set it up ready to be a whole new bee next frame
			}
			
		}
		
		// ADDING MOVEMENT TO CLOUD 1 
		
		if(!cloud1Active){
		// cloud 1 speed
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 200);
		// cloud 1 height 
			srand((int)time(0)*10);
			float height = (rand() % 150);
		spriteCloud1.setPosition(-200,height);// starts initially of screen to the left size 
		cloud1Active = true; // Sets cloud1Active to true, indicating that the cloud is now active and moving.
		}else{
		
		spriteCloud1.setPosition(
			spriteCloud1.getPosition().x + (cloud1Speed*dt.asSeconds()),spriteCloud1.getPosition().y
		); // we add cloud1speed*dt.asSecond here as cloud is moving from left to right
		
		// if cloud1 has reached end of screen 
		if(spriteCloud1.getPosition().x > 1920){
			// set it up to be ready for next frame 
			cloud1Active = false;	
		}
	}
	
	if(!cloud2Active){
		srand((int)time(0)*15);
		cloud2Speed = (rand() % 300);
		
		srand((int)time(0)*15);
		float height = (rand() % 350);
		spriteCloud2.setPosition(-200,height);
		cloud2Active = true;
	
	}else{
		spriteCloud2.setPosition(
			spriteCloud2.getPosition().x + (cloud2Speed*dt.asSeconds()),spriteCloud2.getPosition().y
		); 
		if(spriteCloud2.getPosition().x > 1920){
			cloud2Active = false;
		}
	}
	
	if(!cloud3Active){
		srand((int)time(0)*20);
		cloud3Speed = (rand() % 100);
		
		srand((int)time(0)*200);
		float height = (rand() % 500);
		spriteCloud3.setPosition(-200,height);
		cloud3Active = true;
	
	}else{
		spriteCloud3.setPosition(
			spriteCloud3.getPosition().x + (cloud3Speed*dt.asSeconds()),spriteCloud3.getPosition().y
		); 
		if(spriteCloud3.getPosition().x > 1920){
			cloud3Active = false;
		}
	
	}
		
		// DRAW SECTION 
		// clear everything from last frame
		window.clear();
		
		// load sprite 
		window.draw(spriteBackground); // background
		window.draw(spriteTree); // tree 
		window.draw(spriteBee); // bee			
		window.draw(spriteCloud1); // clouds 
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		
		// show everything we just draw
		window.display();
	}
}
