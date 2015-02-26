#pragma once

#include "ofMain.h"

enum s_mode {TITLE = 0, OPTIONS, GAMEOPS, SOUNDOPS, CONTROLOPS, GAME};
enum move_key {NONE = 0, LEFT, RIGHT};
enum opponent_mode {BOXES = 0, FRACTALS = 1};

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofEasyCam cam;

};