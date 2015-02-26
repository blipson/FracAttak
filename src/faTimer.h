#include <iostream>
#include <time.h>
#include "faScreen.h"

class faTimer {
	unsigned long begTime;
	ofTrueTypeFont timerFont;
public:
	int speed;
	int level;
	float score;
	bool stopper;

	void load(){
		timerFont.loadFont("bigmacca.ttf", 40);
		speed = -5;
	}

	void start(){
		begTime = clock();
		stopper = false;
		speed = -8;
		level = 1;
		score = 0;
	}

	void draw(){
		ofSetColor(255, 255, 255);
		timerFont.drawString(ofToString(10-elapsedTime()), 900, 100);
		timerFont.drawString("Level ", 50, 100);
		timerFont.drawString(ofToString(level), timerFont.stringWidth("Level ") + 75, 100);
		timerFont.drawString("Score ", 400, 100);
		timerFont.drawString(ofToString(score), timerFont.stringWidth("Score ") + 425, 100);
		if(((int)elapsedTime()==10) && (stopper==false)) levelUp();
		if(((int)elapsedTime()>=0) && (stopper==false)) scoreUp();
	}

	void stop(){
		stopper = true;
		speed = -5;
		level += 0;
		score += 0;
	}

	void scoreUp(){
		score += 1;
	}

	void levelUp(){
		begTime = clock();
		speed -= 2.5;
		level += 1;
	}

	unsigned long elapsedTime(){
		return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
	}

	bool isTimeOut(unsigned long seconds);




};