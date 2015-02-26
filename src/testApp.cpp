#include "testApp.h"
#include <iostream>
#include <fstream>
#include "faButton.h"
#include "faScreen.h"
#include "faSlider.h"
#include "faBox.h"
#include "faTimer.h"
using namespace std;

//descriptively-titled global functions are prototyped
char* strcopy(const char* orig, char* &copy);
char* replaceChar(char* orig, char to_replace, char insert);
void setupGraphics();
void checkCamMovement(ofEasyCam &cam);
void startTimer();
void drawAvatar(ofEasyCam &cam);
void drawRestartText();
void loadAndPlayMusic();

//global variables are declared
bool is_hit; //tells if avatar has hit an enemy or not
move_key strafing; //tells which way, if any, the camera should be strafing
faTimer timer; //tracks and displays time
faScreen SCREEN; //contains button, slider, fractal, and box arrays; draws pretty much everything
ofSoundPlayer background_music; //contains music and methods for loading, playing, changing it

//--------------------------------------------------------------
void testApp::setup(){
	setupGraphics();
	cam.disableMouseInput();//disables mouse control of the camera orientation
	SCREEN.load();//loads title screen, buttons, opponents
	loadAndPlayMusic();//loads and plays music

	is_hit = false;//setup globals variables to start
	strafing = NONE;
	timer.load();//setup timer, initialize speed value
}

//--------------------------------------------------------------
void testApp::update(){
		if(is_hit==false) {
			cam.move(0,0,timer.speed); //if you haven't lost, keep moving at speed set by timer
		}
		else {
			cam.setPosition(0, cam.getY(), 500);//if you lost, set the camera/avatar back and reset fractals
			SCREEN.resetFractals();
		}
	if((int)strafing) checkCamMovement(cam);//mediates camera/avatar movement if you press 'a' or 'd'
	if(!is_hit) SCREEN.checkFractals(cam);//if you haven't lost, resets fractal position if they go off screen
}

//--------------------------------------------------------------
void testApp::draw(){

	ofBackground(0,0,0); //background is black
	cam.begin();//start 3d camera
	SCREEN.drawFractals();//draws opponents
	/*when you press Play, the screen mode changes to GAME*/
	if(SCREEN.getMode()==GAME) {
		drawAvatar(cam); //avatar draws in position relative to the camera
		if(SCREEN.checkHit(cam))//if avatar hits an opponent, is_hit is set to true
			is_hit = true;
		if(is_hit==true) { //if you hit something, stop everything and prompt to restart
			timer.stop();
			cam.end();
			drawRestartText();
		}
	}
	cam.end(); //end 3d camera
	if(SCREEN.getMode()==GAME)//if you're in game, draw the timer
		timer.draw(); 
	else
		SCREEN.draw();//if you're not in game, draw the buttons for your current screen

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(SCREEN.getMode()==GAME){ //if you're in game
		if(key==97) strafing = LEFT; //and you press 'a', tells camera to move LEFT during update
		if(key==100) strafing = RIGHT; //or RIGHT if you pressed 'd'
		if(key==(int)'q') { //pressing 'q' at any time in game sends you back to the title screen
			SCREEN.changeScreen(0);
			is_hit=false;
		}
	}
	if(is_hit==true) {
		if(key==(int)'r') { //if you lost, pressing 'r' resets your position and timer
			cam.move(0,0,25);
			is_hit=false; //now you can go again!
			timer.start();
		}
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if(key == 97 || key == 100) strafing = NONE; //if you released 'a' or 'd', 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	SCREEN.isOver(x,y); //checks for hovering over buttons
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if(SCREEN.getMode()==SOUNDOPS){ //if you're in the sound options screen
		SCREEN.isDragged(x,y); //and you are dragging the music volume slider
		background_music.setVolume(SCREEN.getMusicVolume());//set music volume based on slider position
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	SCREEN.isClicked(x,y); //checks for clicking of buttons
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	SCREEN.wasClicked(x,y); //responds to clicking of buttons
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

char* strcopy(const char* orig, char* &copy){
//dynamically copies a const char* to a char* location
	int len = 0; for(;orig[len]!='\0'; len++){};
	copy = new char[len+1];
	for(int i=0; i<len+1; i++) copy[i] = orig[i];
	return copy;
}

char* replaceChar(char* orig, char to_replace, char insert){
//replaces a specified character in a char* with another specified character
	int len = 0; for(;orig[len]!='\0'; len++){};
	char *copy = new char[len+1];
	for(int i=0; i<len+1; i++) copy[i] = orig[i];
	len = 0; while(copy[len]!= to_replace) len++;
	copy[len] = insert;
	return copy;
}

void setupGraphics(){
//stuff for setting up 3d
	ofEnableAlphaBlending();//enable transparency on png images
	ofSetVerticalSync(true);
	glEnable(GL_DEPTH_TEST);
	ofEnableNormalizedTexCoords();
	ofSetLineWidth(2);
}

void checkCamMovement(ofEasyCam &cam){
//moves camera if you've set the strafing variable by pressing 'a' or 'd'
	if(strafing==LEFT) cam.move(-3.5,0,0);
	else if(strafing==RIGHT) cam.move(3.5,0,0);
}

void startTimer(){ timer.start();} //starts timer

void drawAvatar(ofEasyCam &cam){
//draws your avatar, which always moves with the camera
	//moving the camera is equivalent to moving the avatar!
	ofSetColor(0,255,0); ofNoFill();
	ofBox(cam.getX(), cam.getY()-15, cam.getZ()-50, 5);
}

void drawRestartText(){
//called when you lose; draws text prompting for a restart
		ofFill();
		ofSetColor(255, 255, 255);
		ofTrueTypeFont restart;
		restart.loadFont("bigmacca.ttf", 40);
		restart.drawString("R to restart", 512-restart.stringWidth("R to restart")/2 , 200);
		restart.drawString("Q to quit", 512-restart.stringWidth("Q to quit")/2, 300);

}

void loadAndPlayMusic(){
//loads and plays and loops music
	background_music.loadSound("django.mp3");
	background_music.play(); background_music.setLoop(true);
}