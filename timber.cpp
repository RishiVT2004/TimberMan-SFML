#include<iostream>
#include<SFML/Graphics.hpp>
#include<cstdlib> // for clock , rand , srand 
#include<sstream> // for font based operations
#include<SFML/Audio.hpp> // for audio 

using namespace sf;

// input , update and draw part are 3 part of game 
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES]; // This declares an array named branches.
//The data type of the elements in the array is Sprite

enum class side{LEFT,RIGHT,NONE}; // possible positions of branch 
/*
This declares an enum class named side. An enum class is a strongly-typed enumeration, which means that the enumerators (the values within the curly braces) are scoped to the side enum and are not implicitly convertible to integers.

The enumerators defined within side are LEFT, RIGHT, and NONE. These likely represent the possible sides of the tree where a branch can appear (left, right, or not present on that particular "level" of the tree).
*/

side branchPositions[NUM_BRANCHES]; // stores positions of branches 

/*
This declares an array named branchPosition.
The data type of the elements in the array is the side enum class that you just defined.
*/

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
	
	Clock clock; // Variables to control time itself;
	
	// adding timebar 
	RectangleShape timeBar;
	float timeBarStartWidth = 400; // initial width of timebar 
	float timeBarHeight = 80;
	
	timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight)); // holds 2 floating (x,y) component 
	// x -> horizontal . y -> vertical 
	timeBar.setFillColor(Color::Blue);
	timeBar.setPosition((1920/2) - timeBarStartWidth /2 , 980); // x,y
	
	Time gameTimeTotal;
	float timeRemaining = 6.0f; // initial time 
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining; // time bar progression 
	
	bool paused = true; // tracks wether the game is paused or running 
	
	int score = 0; // declare score 
	// draw some text 
	Text messageText; // display message 
	Text scoreText; // display in game score 
	
	// choose a font 
	Font font;
	font.loadFromFile("font/KOMIKAP_.ttf");
	
	// set the selected font to our text 
	messageText.setFont(font);
	scoreText.setFont(font);
	
	// Assign words to the message for display 
	messageText.setString("Press Enter to Start :)");
	scoreText.setString("Score - 0");
	
	// set the size of message 
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	
	// choose a color 
	messageText.setFillColor(Color::Black);
	scoreText.setFillColor(Color::Red);
	
	// Create a box to add position to message 
	
	FloatRect textRect = messageText.getLocalBounds(); // returns dimension (left,top,width,height);
	
	// contains x,y cordinate of messageText
	// x = (left + width) / 2
	// y = (right + top) / 2
	messageText.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
	
	// set position to middle 	
	messageText.setPosition(1920/2.0f , 1080/2.0f);	
	
	//set position to score text 
	scoreText.setPosition(20,20);
	
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png"); // load branch texture 
	
	// assign texture and position to each branch 
	for(int i = 0;i<NUM_BRANCHES;i++){
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000,2000);
		branches[i].setOrigin(220,20);
	}
	
	// Prepare Player Sprite 
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580,720);
	
	
	// Player starts on left 
	side playerSide = side::LEFT;
	
	
	// Prepare Gravestone 
	
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(700,830);
	
	// Prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);
	
	// Line the axe up with the tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;
	
	// Prepare the flying log
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);
	
	// Some other useful log related variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;
	
	// Control the player input
	bool acceptInput = false;
	
	// set input for audio 
	SoundBuffer chopBuffer; // chopping 
	chopBuffer.loadFromFile("audio/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);
	
	
	SoundBuffer deathBuffer; // sound of death  
	deathBuffer.loadFromFile("audio/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);
	
	SoundBuffer ootBuffer; // out of time 
	ootBuffer.loadFromFile("audio/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer); 	
	
	// main game loop 
	while(window.isOpen()){
		//UPDATE SECTION 	
		/*
		Window event is used to remove force shutdown of window screen
		*/
		 // create an event 
		// select and checks pending event in the event queue 
		
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::KeyReleased && !paused){
				acceptInput = true;
				spriteAxe.setPosition(2000,spriteAxe.getPosition().y);
			}
		}
		
							
		// press escape to exit	
		if(Keyboard::isKeyPressed(Keyboard::Escape)){
			window.close();
		}
		
		// start the game 
		if(Keyboard::isKeyPressed(Keyboard::Enter)){
			paused = false;
			score = 0; // set initial score 
			timeRemaining = 6; // set initial time to 6 sec 
			
			// set all branches side none making them disappera when game is started
			for(int i = 0;i<NUM_BRANCHES;i++){
				branchPositions[i]=side::NONE;
			}
			// initally set the position of gravestone outside the screen 
			spriteRIP.setPosition(675,2000);
			// initially player is aet at the lest site of screen
			spritePlayer.setPosition(580,720);
			// set accept player input to true 
			acceptInput = true;
		}
		
		// Wrap the player controls to
		// Make sure we are accepting input	
		if (acceptInput){
		// when right key is pressed 
			if(Keyboard::isKeyPressed(Keyboard::Right)){
				// player moves to right side 
				// as score increses by chopping , increse time based on given equation 
				playerSide = side::RIGHT;
				score++;
				timeRemaining += (2/score) + 0.15;
				
				// set new position of axe and player based on right movement 
				spriteAxe.setPosition(AXE_POSITION_RIGHT,spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200,720);
				
				//update Branch 
				updateBranches(score);
				
				// set log position 
				spriteLog.setPosition(810,720);
				logSpeedX =- 5000;
				logActive = true;
				
				acceptInput = false;
				chop.play(); // implement chopping sound 
			}
			else if(Keyboard::isKeyPressed(Keyboard::Left)){
			
				playerSide = side::LEFT;
				score++;
				timeRemaining += (2/score) + 0.15;
				
				spriteAxe.setPosition(AXE_POSITION_LEFT,spriteAxe.getPosition().y);
				spritePlayer.setPosition(580,720);
				
				updateBranches(score);
				
				spriteLog.setPosition(810,720);
				logSpeedX = 5000;
				logActive = true;
				
				acceptInput = false;
				chop.play(); // implement chopping sound 
			}
		}
		
	if(!paused){
		// if pause == false , then game runs ...
		
		// ADDING MOVEMENT TO THE BEE 	
		Time dt = clock.restart(); // time object 
		
		timeRemaining -= dt.asSeconds(); // decrease time for every second 
		
		// set new timebar display 
		timeBar.setSize(Vector2f(timeRemaining * timeBarWidthPerSecond , timeBarHeight));
		
		// if time runs out 
		if(timeRemaining <= 0.0f){
			paused = true; // pause the game 
			messageText.setString("Out of Time"); // display message out of time 
			
			// set size and position of new message 
			FloatRect textRect = messageText.getLocalBounds();
			messageText.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f
			);
			messageText.setPosition(1920/2.0f,1080/2.0f);
			outOfTime.play(); // out of time sound 
				
		}
		
		// Bee Movement 
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
		
		spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed*dt.asSeconds()),spriteCloud1.getPosition().y
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
	
	// Update score text at the end of the game 
	std::stringstream ss;
	ss<< "Score=" <<score;
	scoreText.setString(ss.str());
	
	for(int i = 0;i<NUM_BRANCHES;i++){
		float height = i * 150;
		if(branchPositions[i] == side::LEFT){ // if branch enum type is left 
			branches[i].setPosition(610,height); // set position 
			branches[i].setRotation(180); // rotate branch by 180
			
		}else if(branchPositions[i] == side::RIGHT){  // if branch enum type is left 
			branches[i].setPosition(1330,height); // set position 
			branches[i].setRotation(0); //dont rotate branch 
			
		}else{
			branches[i].setPosition(3000,height); // hide branch is NONE , set it outside screen 
		}
	}// set logs flying 
		if(logActive){
			spriteLog.setPosition(spriteLog.getPosition().x +(logSpeedX * dt.asSeconds()) , 
					      spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));
			
			if(spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000){
				logActive = false;
				spriteLog.setPosition(810,720);
			}
		}
		
	// criteria for ending the game 
		if(branchPositions[5] == playerSide){
			paused = true; // pause the game 
			acceptInput = false; // no more input accepted 
			spriteRIP.setPosition(525,760); // implement gravestone
			spritePlayer.setPosition(2000,660); // remove player from screen 
			messageText.setString("SQUISHED!!!"); // ending message
			
			 // get local dimension of message  
			FloatRect textRect = messageText.getLocalBounds();
			messageText.setOrigin(textRect.left + textRect.width/2.0f , textRect.top + textRect.height/2.0);
			messageText.setPosition(1920/2.0f,1080/2.0f);
			death.play(); // death sound 
			
		}
		
	
	}
	
		
		// DRAW SECTION 
		// clear everything from last frame
		window.clear();
		
		// load sprite 
		window.draw(spriteBackground); // background
		
		window.draw(spriteCloud1); // clouds 
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		
		// drawing all branches 
		for(int i = 0;i<NUM_BRANCHES;i++){
			window.draw(branches[i]);
		}
		
		window.draw(spriteTree); // tree 
		window.draw(spriteBee); // bee			
		
		window.draw(scoreText);
		window.draw(timeBar);
		// draw message text if game is paused 
		if(paused){
			window.draw(messageText);
		}
		window.draw(spritePlayer);
		window.draw(spriteRIP);
		window.draw(spriteAxe);
		window.draw(spriteLog);
		
		// show everything we just draw
		window.display();
	}
}

void updateBranches(int seed){
	
	for(int j = NUM_BRANCHES ; j > 0 ; j--){
		branchPositions[j] = branchPositions[j-1];
	}
	
	// Spawn a new branch at position 0
	// LEFT, RIGHT or NONE
	srand((int)time(0)+seed);
	int r = (rand() % 5);
	
	switch(r){
		case 0: 
			branchPositions[0] = side::LEFT;
			break;
		case 1:
			branchPositions[0] = side::RIGHT;
			break;
		default:
			branchPositions[0] = side::NONE;
			break;
	}

}
