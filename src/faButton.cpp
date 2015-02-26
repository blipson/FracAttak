#include "faButton.h"
#include <iostream>

char* strcopy(const char* orig, char* &copy);
char* replaceChar(char* orig, char to_replace, char insert);

faButton::faButton(const char* txt, const char* flname, ofPoint loc, const char* ftname, int ftsize){
//Constructor for faButton that actually takes information.
		strcopy(txt, text); strcopy(flname, filename);//Copy passed info into variables.
		location = loc;
		strcopy(ftname, fontname);
		fontsize = ftsize;
		if(fontsize) has_text = true;//Clicky buttons have text. Sliders don't have text.
		else has_text = false;
		image_array = new ofImage*[3];//Allocate memory to store ofImage objects for the button images.
		image_array[0] = &image; image_array[1] = &hover_image; image_array[2] = &clicked_image;
		b_hover = false;//Set b_hover to false...
		image_ct = 0;//indexing of image array to 0...
		current_image = image_array[0];//and point current image to the first image in the image array.
		}

faButton::faButton(){
//Default constructor for faButton; initializes everything to 0.
	text = filename = fontname = '\0';
	fontsize = 0;
	image_array = 0; current_image = 0; 
	b_hover = has_text = false;
	image_ct = 0;
}

faButton::~faButton(){
	delete [] text; delete [] filename; delete [] fontname;
}

void faButton::load(){
//Loads all three images for the button. Loads font for text.
		image.loadImage(filename);
		hover_image.loadImage(replaceChar(filename,'0','1'));
		clicked_image.loadImage(replaceChar(filename,'0','2'));
		if(has_text) font.loadFont(fontname, fontsize);
		half_image_width=image.getWidth()/2;
		half_image_height=image.getHeight()/2;
}

void faButton::draw(){
//Draws text, which is a different color depending on whether the button is hovered or clicked over.
		ofSetColor(255,255,255);
		ofDisableAlphaBlending();
		switch( image_ct ){
			case 0:
				ofSetColor(255,255,255); break;
			case 1:
				ofSetColor(72,118,255); break;
			case 2:
				ofSetColor(220,20,60); break;
			default:;
		}
		font.drawString(text, location.x-font.stringWidth(text)/2, location.y+font.stringHeight(text)/2);
		ofEnableAlphaBlending();
		current_image->setAnchorPercent(0.5,0.5); 
}

bool faButton::isOver(int x, int y){
//Given mouse's current x and y positions, detects whether the mouse is over the button.
		if ((x > location.x-half_image_width) 
			&& (x < location.x+half_image_width) 
			&& (y > location.y-half_image_height) 
			&& (y < location.y+half_image_height))
			{
				if (b_hover==false) { 
					current_image++; image_ct++; b_hover = true;
				}
			return true;
		}
		else {
			if (b_hover) {
				current_image--; image_ct--;
				b_hover = false;
			}
		}
		return false;
}

void faButton::isClicked(int x, int y){
//Called when mouse is clicked. If the mouse is over this button, point to next image,
//which means that it will move from hover-blue to clicked-red.
		if(b_hover && (image_ct != 2)) { //The image_ct!=2 statement keeps the current_image pointer
			current_image++; image_ct++; // from pointing outside of the image_array.
		}
}

void faButton::resetImage(){
//Sets the current image to 1 (hover). This works to set the image back to unhovered.
//No, I don't know why it works that way, but it does.
	current_image = image_array[1];
	image_ct = 1;
}