#pragma once
#include "testApp.h"
#include "faSlider.h"
#include "faBox.h"
#include "faFractalTree.h"

void startTimer();

class faScreen 
{
//MODE VARIABLES
	s_mode mode; //the screen mode--dictates which set of buttons is drawn
	opponent_mode opponents; //sets which opponent to draw--fractal trees or boxes
//SCREEN VARIABLES
	int num_screens; //number of screens, imported from buttons.txt
	int *num_buttons_array; //array containing the number of buttons for each screen
//BUTTON-RELEVANT VARIABLES
	faButton ***master_button_array; // pointers to the dynamic arrays that point to the buttons of screens
	faSlider **sound_slider_array; //points to pointer to dynamic array of sliders
//OPPONENT-RELEVANT VARIABLES
	int num_fractals; //number of opponents currently being drawn to screen
	faBox **box_array; //points to array containing box opponents
	FractalTree **fractal_array;//points to array containing fractal tree opponents
	int *recently_reset_x_positions;//hold the x-positions of the last several opponents to be reset; used to avoid visual overlap of opponents
	int rrxp_size;//size of recently_reset_x_positions array
	int rrxp_ct;//keeps track of the position of the last x-position inserted into rrxp array
public:
	faScreen() {
	//default constructor for faScreen object
		master_button_array = 0; num_buttons_array = 0; num_screens = 0;
		mode = TITLE;
		num_fractals = 14;
	}

	~faScreen(){
	//faScreen deconstructor
		for(int i=0; i<num_screens; i++){
			for(int j=0; j<num_buttons_array[i]; j++)
			{delete master_button_array[i][j];}
			delete [] master_button_array[i];}
		delete [] master_button_array;
		for(int i=0; i<1; i++) delete sound_slider_array[i];
		delete [] sound_slider_array;
		for(int i=0; i<num_fractals; i++){
			delete box_array[i]; delete fractal_array[i];
		}
		delete [] box_array; delete [] fractal_array;
	}


//LOADING-RELEVANT METHODS//
	void load(){
	//calls funcs to load buttons and opponents
		loadAllButtons();
		loadFractals();
}

	void loadAllButtons(){
	//loads buttons from file
		ifstream in("buttons.txt"); //Create a file stream and target a file...
		in >> num_screens; //read in the number of screens from targeted file...
		num_buttons_array = new int[num_screens]; //allocate memory for the array of the number of buttons on each screen...
		master_button_array = new faButton**[num_screens]; //you'll also need an array of faButtons for each screen.
		for(int i=0; i<num_screens; i++){ //Now, for each screen...
			in >> num_buttons_array[i]; //read in the number of faButtons it will have...
			master_button_array[i] = new faButton*[num_buttons_array[i]];//alloc for this screen's button array, place pointer in master array...
			loadFromFile(in, i);//and load the faButtons for this screen from targeted file.
		}
		 loadSliders();//Load the sliders.
	}

	void loadFromFile(ifstream &in, int i){
	//Loads faButtons from file, when given a filestream and the screen's position in num_buttons_array
		char in_text[20]; char in_image[20]; //Create variables for reading in text and filename...
		int in_x; int in_y;//... and position
		char in_fontname[20]; int in_fontsize;//and font and font size.
		for(int j=0; j<num_buttons_array[i]; j++){ //Now, for as many faButtons as this screen has...
			in >> in_text >> in_image >> in_x >> in_y >> in_fontname >> in_fontsize;//read the info into the variables...
			master_button_array[i][j] = new faButton(in_text, in_image, ofPoint(in_x, in_y), in_fontname, in_fontsize);
			master_button_array[i][j]->load();//create faButton with info, in proper place within its screen's faButton array, and load it.
		}
	}

	void loadSliders(){
	//Creates and loads the music volume slider.
		sound_slider_array = new faSlider*[1];
		sound_slider_array[0] = new faSlider("slider0.png", ofPoint(350, 300));
		for(int i=0; i<1; i++) sound_slider_array[i]->load();
	}

	void loadFractals(){
	//Creates arrays containing both types of opponents, and takes care of rrxp array.
		box_array = new faBox*[num_fractals];//First, boxes..
		for(int i=0; i<num_fractals; i++)//for as many opponents as there should be...
			box_array[i] = new faBox(rand()%200, -15, rand()%20,25);//create a box and store it in box_array.
		fractal_array = new FractalTree*[num_fractals];//Second, fractal trees..
		for(int i=0; i<num_fractals; i++)//for as many opponents as there should be...
			fractal_array[i] = new FractalTree(rand()%200, -15, rand()%20);//create a fractal tree and store it in fractal_array
		rrxp_size = (int)num_fractals/2;//We want to know the x position of the last half of opponents that were reset.
		recently_reset_x_positions = new int[rrxp_size];//So create an array that is that large...
		for(int i=0; i<rrxp_size; i++) //and fill it with zeros to begin.
			recently_reset_x_positions[i]=0;
		rrxp_ct = 0;//Start the indexing variable at 0.
	}


//SCREEN-RELEVANT METHODS
	void setMode(s_mode m){ mode = m; }

	s_mode getMode(){ return mode;}

	void changeScreen(int i){
	//Based on current mode and the index of button that was pressed, screen mode is changed.
		switch(mode){
			case TITLE: //If you are in the title screen...
				if(i==0) {mode = GAME; startTimer();}//and you click Play, the game and timer are started...
				else if(i==1) mode = OPTIONS;//or if you click Options, you are sent to the Options screen...
				else if(i==2) ofExit(0);//or if you click Quit, the program is exited normally.
				break;
			case OPTIONS: //Likewise for all the other cases.
				if(i==0) mode = GAMEOPS;
				else if(i==1) mode = SOUNDOPS;
				else if(i==2) mode = TITLE;
				break;
			case GAMEOPS:
				if(i==0) mode = OPTIONS;
				else if(i==3) changeDifficulty(16);//These five call a method that changes num_fractals and reloads the fractal arrays.
				else if(i==4) changeDifficulty(28);
				else if(i==5) changeDifficulty(32);
				else if(i==7) {opponents = BOXES; changeDifficulty(28);}
				else if(i==8) {opponents = FRACTALS; changeDifficulty(28);}
				break;
			case SOUNDOPS:
				if(i==0) mode = OPTIONS;
				break;
			case GAME:
				mode = TITLE;
				break;
			default:;
		}
}

	void changeDifficulty(int n) {
	//Changes number of opponents based on selected difficulty, deletes current opponent array and re-allocates
	//with new number of opponents.
		switch(opponents){
			case FRACTALS: {
				n /= 2;
				for(int i=0; i<num_fractals; i++) delete fractal_array[i];
					delete [] fractal_array; break;}
			case BOXES: {
				for(int i=0; i<num_fractals; i++) delete box_array[i];
					delete [] box_array; break;}
			default:;
		};
		delete [] recently_reset_x_positions;
		num_fractals = n;
		loadFractals();
	}

//BUTTON-AND-SLIDER-RELEVANT METHODS//
	void draw(){
	//Draws all faButtons in the sub-master_button_array indicated by the screen mode variable.
	//Draws the volume slider if you're in the Sound Options screen.
		for(int i=0; i<num_buttons_array[(int)mode]; i++){
			master_button_array[(int)mode][i]->draw();}
		if(mode==SOUNDOPS){
			for(int i=0; i<1; i++)
			sound_slider_array[i]->draw();
		}
	}

	int isOver(int x, int y){
	//Checks all faButtons and faSliders in current screen for a mouseover.
		for(int i=0; i<num_buttons_array[(int)mode]; i++){
			if(master_button_array[(int)mode][i]->isOver(x,y))
				return i;}
		if(mode==SOUNDOPS){
			for(int i=0; i<1; i++)
			sound_slider_array[i]->isOver(x,y);		
		}
		return 0;
	}

	void isDragged(int x, int y){
	//Checks whether you are dragging any sliders in the Sound Options screen.
		for(int i=0; i<1; i++)
			sound_slider_array[i]->isDragged(x,y);
	}

	void isClicked(int x, int y){
	//Checks whether you just clicked over any of the buttons in the current screen.
		for(int i=0; i<num_buttons_array[(int)mode]; i++){
			master_button_array[(int) mode][i]->isClicked(x,y);
		}
}

	void wasClicked(int x,int y){
	//Checks whether you are just mouse-released over any of the buttons in the current screen.
		for(int i=0; i<num_buttons_array[(int)mode]; i++){
			if(master_button_array[(int) mode][i]->isOver(x,y)) {
				master_button_array[(int)mode][i]->resetImage();
				this->changeScreen(i);//If you did, pass the index of the clicked button to changeScreen!
				break;}
		}
}

	float getMusicVolume(){ return sound_slider_array[0]->getVal();}


//OPPONENT-RELEVANT METHODS
	void drawFractals(){
	//Draws all objects in the appropriate array of opponents.
		switch(opponents){
			case FRACTALS:
				for(int i=0; i<num_fractals; i++) fractal_array[i]->draw(); break;
			case BOXES:
				for(int i=0; i<num_fractals; i++) box_array[i]->draw(); break;
			default:;
		};
	}

	void checkFractals(ofEasyCam &cam){
	//Checks whether any objects in the current array of opponents is behind the camera and needs to be reset.
		for(int i=0; i<num_fractals; i++){
			int temp;
			switch(opponents){
			//These check methods return the new x-value of the opponent if it was reset, but return a 0 otherwise. 
				case FRACTALS:
					temp = fractal_array[i]->check(cam.getZ(), cam.getX(), recently_reset_x_positions, rrxp_size); break;
				case BOXES:
					temp = box_array[i]->check(cam.getZ(), cam.getX(), recently_reset_x_positions, rrxp_size); break;
				default:;
			};
			if(temp){ //If the opponent was reset, store its x-position and move the indexer of rrxp one forward.
				if(rrxp_ct==rrxp_size) rrxp_ct = 0;
				recently_reset_x_positions[rrxp_ct] = temp;
				rrxp_ct++;
			}
		}
	}

	bool checkHit(ofEasyCam &cam){
	//Calls collision-detecting methods of objects in the relevant opponent array.
		for(int i=0; i<num_fractals; i++) {
			switch(opponents){
			case FRACTALS:
				if (fractal_array[i]->is_hit(cam)) return true;
			case BOXES:
				if (box_array[i]->is_hit(cam)) return true;
			default:;
			};
		}
		return false;
	}

	void resetFractals(){
	//Resets opponents to original z-positions relative to the camera, is called if you hit an opponent (is_hit==true);
		switch(opponents){
			case FRACTALS:
				for(int i=0; i<num_fractals; i++) fractal_array[i]->reset(); break;
			case BOXES:
				for(int i=0; i<num_fractals; i++) box_array[i]->reset(); break;
			default:;
		};
	}
};