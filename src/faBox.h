#pragma once

#include "ofMain.h"
#include "testApp.h"

#define field_width 600
#define h_field_width 300

class faBox {
public:
	float posX;
	float posY;
	float posZ;
	float startZ;
	float size;
	faBox(float x, float y, float z, float n){
	//faBox constructor--sets up position and size of box.
		if(x > h_field_width) posX = -x + h_field_width;
		else posX = x;
		if(z > 10) posZ = (-z + 10)*50;
		else posZ = z*50;
		posY = y;
		startZ = posZ;
		size = n;
	}
	void draw(){
	//Draws unfilled ofBox with a random color at position x,y,z with size size.
		ofSetColor(rand()%255, rand()%255, rand()%255);
		ofNoFill();
		ofBox(posX, posY, posZ, size);
	}
	int check(float cam_z, float cam_x, int* rrxp, int rrxp_size){
	//Determines whether the camera has passed up this faBox.
		if(cam_z < posZ) { //If it has, then it needs to be reset.
			posZ -= 900; //So, set it back in the field...
			bool good_pos_x = false; float temprand;//grab a random x-value...
			while(true){
				temprand = rand()%field_width;//does the x-value make this box overlap with any other recently reset boxes?..
				if(goodPosX(temprand, rrxp, rrxp_size)) break;//if it doesn't, keep it... if it does, try again.

			}
			if(temprand > h_field_width) {
				posX = (temprand*(-1) + h_field_width) + cam_x;
			}
			else {
				posX = temprand + cam_x;
			}
			return (int)temprand;
		}
		else return 0; //If it's still in front of the camera, return 0.
	}

	bool goodPosX(float t, int* rrxp, int rrxp_size){
	//Checks recently reset x-positions to see whether there will be box overlap.
		for(int i=0; i<rrxp_size; i++){
			int dist = abs(rrxp[i] - t);
			if(size >= dist) return false;//If there's overlap, return false.
		}
		return true;//If there's no overlap, return true.
	}

	void reset(){
	//Set the fractal back to where it started on the z axis.
		posZ = startZ;
	}

	bool is_hit(ofEasyCam &cam){
	//Good old fashioned collision detection.
		if((cam.getZ()-52.5 > posZ)) {
			if((cam.getZ()-52.5) < (posZ+12.5)) {
				if((cam.getX()+2.5) > (posX-12.5)) {
					if((cam.getX()-2.5) < (posX+12.5)) {
						return true;
					}
				}
			}
		}
		return false;
	}
};