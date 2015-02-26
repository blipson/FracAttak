#include "faSlider.h"
#include <iostream>

const char* null = "";

faSlider::faSlider(const char* flname, ofPoint loc) : 
	  faButton(null, flname, loc, null, 0){
//Slider constructor; essentially a faButton without any text or font associated.
		  val = 0.8;//Default value of sliders is at 80%...
		  line_start = loc; line_end.set(loc.x+400, loc.y); //define starting and ending point of the slider...
		  location = ofPoint(loc.x+(line_end.x-loc.x)*val,loc.y); //and create line.
	  }

faSlider::~faSlider(){}

void faSlider::draw(){
//Draws slider; both the image and the line.
		  current_image->setAnchorPercent(0.5, 0.5);
		  current_image->draw(location);
		  ofLine(line_start, line_end);
}

void  faSlider::setVal(float v){ val = v; }

float faSlider::getVal() { return val; }

bool faSlider::isOver(int x, int y){
		  float dist = ofDist(x, y, location.x, location.y);
			if (dist <= half_image_width)//If you are hovering over the button...
				{
					if (b_hover==false) { //and you weren't before...
						current_image++; image_ct++; b_hover = true;//point to the next button image and set b_hover to true...
					}
				return true;//and return that you are hovering over.
			}
			else {//But if you aren't hovering over the button...
				if (b_hover) {//and you just were...
					current_image--; image_ct--;//then decrement the button image pointer...
					b_hover = false;//and set b_hover to false...
				}
			}
			return false;//and return that you are not hovering over.
}

bool faSlider::isDragged(int x, int y){
//Tells whether slider is being dragged. And, if so, what new value that slider has.
		  if(b_hover && (x < line_end.x) && (x > line_start.x)){
			  location.x = x;
			  val = (x-line_start.x)/(line_end.x - line_start.x);
			  return true;
		  }
		  else return false;
}