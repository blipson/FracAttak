#pragma once

#include "ofMain.h"
#include <iostream>
#include <math.h>
using namespace std;

#define field_width 600
#define h_field_width 300

class FTRectangle{ //individual rectangles in a fractal tree
	int itCounter;
	int iteration;
	float defSize;
	float size;
	float rotAngle; //keepts track of the angle each square is rotated at, so the squares in the next iteration have something to rotate from
	bool LorR; //keeps track of whether the block is the "left" (0) or "right" (1) one on the previous iteration's block
	float xPos;
	float yPos;
	float zPos;
public:
	FTRectangle (int, int);
	//~FTRectangle ();
	int getitCounter (){return itCounter;}
	int getiteration (){return iteration;}
	float getxPos (){return xPos;}
	float getyPos (){return yPos;}
	float getzPos (){return zPos;}
	float getsize (){return size;}
	float getrotAngle (){return rotAngle;}
	friend class FractalTree; //may or may not need this
	FTRectangle& operator = (const FTRectangle&);
};

class FractalTree{
	float xPos, yPos, zPos, zStart;
	static int posDivider; //this modifies the y position to give us the number of iterations we draw
	int iterations; //the number of iterations that given fractal tree should have, where 0 is the starting square (same as order)
	FTRectangle* iterationHolder; //array of dynamic iterations
	//dimension of order 0 square;
public:
	FractalTree (float xIn=60, float yIn=60, float zIn=200){
		yPos = yIn; xPos = xIn; zPos = zIn*50; zStart = zPos;
		iterations = 1; 
		iterate(); arrange();} /*constructor, 
												input should be the (non-adjusted, i.e. viewed from above) y position and x position.*/
	~FractalTree (){delete [] iterationHolder;}
	int returnNumIterations (){return iterations;} //returns the number of iterations given fractal tree is at
	void iterate (); //this actually manages how many and where squares are to be drawn (where will actually probably be taken care of by FTRectangle functions)
	void arrange ();
	void update (float); //obvious
	float getxPos (){return xPos;}
	void draw ();
	FTRectangle& operator [] (unsigned int i){return iterationHolder[i];}
	void reset(){ 
		zPos = zStart;
	}
	int check(float cam_z, float cam_x, int* rrxp, int rrxp_size){
		update(cam_z);
		if(cam_z < zPos) {
			zPos -= 900;
			iterations=1;
			bool good_pos_x = false; float temprand;
			while(true){
				temprand = (rand()%field_width) - h_field_width;
				if(goodPosX(temprand, rrxp, rrxp_size)) break;
			}
			xPos = temprand + cam_x;
			update(cam_z);
			return (int)temprand;
		}
		else return 0;
	}

	bool goodPosX(float t, int* rrxp, int rrxp_size){
		for(int i=0; i<rrxp_size; i++){
			int dist = abs(rrxp[i] - t);
			if(iterationHolder[0].defSize >= dist) return false;
		}
		return true;
	}
	bool is_hit(ofEasyCam &cam){
		int half_cube = (iterationHolder[0].defSize)/2;
		if((cam.getZ()-52.5 > zPos)) {
			if((cam.getZ()-52.5) < (zPos+half_cube)) {
				if((cam.getX()+2.5) > (xPos-half_cube)) {
					if((cam.getX()-2.5) < (xPos+half_cube)) {
						return true;
					}
				}
			}
		}
		return false;
	}


};
