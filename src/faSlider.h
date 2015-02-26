#pragma once
#include "faButton.h"

class faSlider: public faButton
{
	float val;
	ofPoint line_start;
	ofPoint line_end;
public:
	faSlider(const char* flname, ofPoint loc);
	~faSlider();
	 void draw();
	 void setVal(float v);
	 float getVal();
	 bool isOver(int x, int y);
	 bool isDragged(int x, int y);
	  
};