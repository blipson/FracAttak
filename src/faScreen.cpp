#include "faScreen.h"
#include <iostream>

char* strcopy(const char* orig, char* &copy);
char* addSuffix(char* orig, char suff);

faScreen::faScreen(){
	num_buttons = 0; 
	button_array = 0; 
	mode = TITLE;
}

faScreen::~faScreen(){
	for(int i=0; i<num_buttons; i++) delete button_array[i];
	delete [] button_array;
}

void faScreen::displayMode(){ 
	cout << mode << endl;
}

void faScreen::load(){
		switch(mode){
			case TITLE:
				{num_buttons = 3;
				button_array = new faButton*[num_buttons];
				button_array[0] = new faButton("New Game", "long0.png", ofPoint(512, 384+30),"bigmacca.ttf", 50);
				button_array[1] = new faButton("Options", "long0.png", ofPoint(512, 384+200),"bigmacca.ttf", 50);
				button_array[2] = new faButton("Quit", "square0.png", ofPoint(900,300+170+170),"bigmacca.ttf", 30);
				for(int i=0; i<num_buttons; i++) button_array[i]->load(); 
				cout << "Loaded TITLE " << endl; break;}
			case OPTIONS:
				{num_buttons = 4;
				button_array = new faButton*[num_buttons];
				button_array[0] = new faButton("Game", "long0.png", ofPoint(512, 300),"bigmacca.ttf", 50);
				button_array[1] = new faButton("Sound", "long0.png", ofPoint(512, 300+170),"bigmacca.ttf", 50);
				button_array[2] = new faButton("Control", "long0.png", ofPoint(512, 300+170+170),"bigmacca.ttf", 50);
				button_array[3] = new faButton("Back", "square0.png", ofPoint(900,300+170+170),"bigmacca.ttf", 30);
				for(int i=0; i<num_buttons; i++) button_array[i]->load();
				cout << "Loaded OPTIONS" << endl; break;}
			case GAMEOPS:
				{num_buttons = 1;
				button_array = new faButton*[num_buttons];
				button_array[0] = new faButton("Back", "square0.png", ofPoint(900,300+170+170),"bigmacca.ttf", 30);
				for(int i=0; i<num_buttons; i++) button_array[i]->load(); break;
				}
			case SOUNDOPS:
				{num_buttons = 1;
				button_array = new faButton*[num_buttons];
				button_array[0] = new faButton("Back", "square0.png", ofPoint(900,300+170+170),"bigmacca.ttf", 30);
				for(int i=0; i<num_buttons; i++) button_array[i]->load(); break;
				}
			default: cout << "none" << endl;
		}
}

void faScreen::draw(){
		//cout << "in draw" << endl;
		for(int i=0; i<num_buttons; i++)
		//	cout << " drawing" << i << " " << button_array[i] << endl;}
			button_array[i]->draw();
		
}

int faScreen::isOver(int x, int y){
		for(int i=0; i<num_buttons; i++){
			if(button_array[i]->isOver(x,y))
				return i;}
		return 0;
}

void faScreen::isClicked(int x, int y){
		for(int i=0; i<num_buttons; i++){
			button_array[i]->isClicked(x,y);
		}
}

void faScreen::wasClicked(int x,int y){
		int i=0; while(!(button_array[i]->isOver(x,y))) {i++;}
		this->changeScreen(i);
}

void faScreen::changeScreen(int i){
		switch(mode){
			case TITLE:
				if(i==0) mode = GAME;
				else if(i==1) mode = OPTIONS;
				else if(i==2) ofExit(0);
				break;
			case OPTIONS:
				if(i==0) mode = GAMEOPS;
				else if(i==1) mode = SOUNDOPS;
				else if(i==2) mode = CONTROLOPS;
				else if(i==3) mode = TITLE;
				break;
			case GAMEOPS:
				if(i==0) mode = OPTIONS;
				break;
			case SOUNDOPS:
				if(i==0) mode = OPTIONS; 
				break;
			default:;
		}
		this->load();
}