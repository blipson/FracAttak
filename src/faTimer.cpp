#include "faTimer.h"

void faTimer::scoreUp() {
	score += 1;
}

bool faTimer::isTimeOut(unsigned long seconds) {
	return seconds >= elapsedTime();
}

//
//For some reason, including any of the following functions in the this cpp file
//instead of the faTimer.h file raises an exception like the following (which is for elapsedTime()):
//testApp.obj : error LNK2019: unresolved external symbol "public: unsigned long __thiscall faTimer::elapsedTime(void)" (?elapsedTime@faTimer@@QAEKXZ) referenced in function "public: void __thiscall faTimer::draw(void)" (?draw@faTimer@@QAEXXZ)

//I think it's some VC++ rule that we aren't following. Whoops.

/*void faTimer::start() {
	begTime = clock();
	stopper = false;
	speed = -8;
	level = 1;
	score = 0;
	return true
}

void faTimer::draw(){
	ofSetColor(255, 255, 255);
	timerFont.drawString(ofToString(10-elapsedTime()), 900, 100);
	timerFont.drawString("Level ", 50, 100);
	timerFont.drawString(ofToString(level), timerFont.stringWidth("Level ") + 75, 100);
	timerFont.drawString("Score ", 400, 100);
	timerFont.drawString(ofToString(score), timerFont.stringWidth("Score ") + 425, 100);
	if(((int)elapsedTime()==10) && (stopper==false)) levelUp();
	if(((int)elapsedTime()>=0) && (stopper==false)) scoreUp();
}

void faTimer::stop() {
	stopper = true;
	speed = -5;
	level += 0;
	score += 0;
}

void faTimer::load() {
	timerFont.loadFont("bigmacca.ttf", 40);
	speed = -5;
}

void faTimer::levelUp() {
	begTime = clock();
	speed -= 2.5;
	level += 1;
}

unsigned long faTimer::elapsedTime() {
	return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
}

*/
