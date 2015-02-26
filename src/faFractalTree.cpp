#include "faFractalTree.h"

//int iterations;


double two = 2;
//--------------------------------------------------------------

FTRectangle::FTRectangle (int itCounterIn=1, int iterationIn=0){
	xPos=0;
	yPos=0;
	zPos=0;
	rotAngle = 0; 
	iteration = iterationIn;
	itCounter = itCounterIn;
	defSize = 40; //SHOULD MAKE THESE STATIC
	size = defSize*(pow((1/(sqrt (two))),iterationIn));
	if ((itCounter%2) == 1)
		LorR = 0;
	else if ((itCounter%2) == 0)
		LorR = 1;
	xPos=yPos=0;
	//cout << "constructor itOut: " << iteration << endl;
}

FTRectangle& FTRectangle::operator = (const FTRectangle& param){
	itCounter = param.itCounter;
	iteration = param.iteration;
	defSize = param.defSize;  //NEED TO BASE ON YPOS STILL
	size = param.size;
	rotAngle = param.rotAngle;
	LorR = param.LorR;
	xPos = param.xPos;
	yPos = param.yPos;
	zPos = param.zPos;
	//cout << "assignment itOut: " << iteration << endl;
	return *this;
}

/*FTRectangle& FractalTree::operator [] (const FTRectangle&){

}*/

void FractalTree::update (float zIn){
	float deltaZ = 900-(zPos - zIn);
	int possIterations = (deltaZ/posDivider)+1;
	if (possIterations > iterations){
		iterations = possIterations;
		iterate ();
	}
	arrange ();
};

void FractalTree::iterate (){ //see header file for purpose
	int counter = 0; //keeps track of which array entry we are on
	//update (); //updates so that we have the correct number of iterations  PROB CAUSING MEMORY ISSUES
	//cout << "Iterations: " << iterations << endl;
	int arraySize = (pow(two,iterations)) - 1;
	//cout << "Array size: " << (int) arraySize << endl; system("PAUSE");
	iterationHolder = new FTRectangle[arraySize];  //this allocates the amount of memory needed for all the squares
	for (int i=0; i<arraySize; i++)
		iterationHolder[i] = 0;
	for (int i=0; i<iterations; i++){ 
		if (i==0){ //making the VERY FIRST SQUARE :)
			counter++;
			iterationHolder[0] = FTRectangle(counter, i);
			iterationHolder[0].xPos = xPos;
			iterationHolder[0].yPos = yPos;
			iterationHolder[0].zPos = zPos;
		}		
		else if (i != 0 ){ //iterating new squares off of previous iterations
			int iterationCounter = 1;
			for (int j=0; j<(pow(two,i)); j++){ //making boxes for each iteration	
				iterationHolder[counter] = FTRectangle(iterationCounter, i);   
				iterationHolder[counter].zPos = zPos;
				iterationCounter++;
				counter++;
			}
			iterationCounter++;
		}
	}
}

float pi = 3.141593;
float rad (float deg){
	float rad;
	rad = deg*pi/180;	
	return rad;
}

void FractalTree::arrange (){
	iterationHolder[0].xPos = xPos;
	iterationHolder[0].yPos = yPos;
	iterationHolder[0].zPos = zPos;
	for (int i=1; i<pow(two,(iterations)) -1; i++){
		int itNo = iterationHolder[i].iteration; //importing the variables to be used by more intuitive names
		int itCount = iterationHolder[i].itCounter; //same
		bool LorR = iterationHolder[i].LorR; //same
		int prevItNo = itNo-1;
		int prevItCount = (itCount-1)/2;
		int prevItHolderValue = pow(two,prevItNo)+prevItCount-1;    //still need to figure out whether iteration should start at 0 or 1
		//cout << prevItHolderValue << endl; system("PAUSE");
		float prevRotAngle = iterationHolder[prevItHolderValue].rotAngle;
		if (LorR == 0){   //remember, 0=L, positive angles are clockwise
			iterationHolder[i].rotAngle = prevRotAngle - 45;
			iterationHolder[i].xPos = iterationHolder[prevItHolderValue].xPos - iterationHolder[prevItHolderValue].size*(.5*cos(rad(iterationHolder[prevItHolderValue].rotAngle)) - sin(rad(iterationHolder[prevItHolderValue].rotAngle)));
			iterationHolder[i].yPos = iterationHolder[prevItHolderValue].yPos + iterationHolder[prevItHolderValue].size*(cos(rad(iterationHolder[prevItHolderValue].rotAngle)) + .5*sin(rad(iterationHolder[prevItHolderValue].rotAngle)));
		}
		else if (LorR ==1){
			iterationHolder[i].rotAngle = prevRotAngle + 45;
			iterationHolder[i].xPos = iterationHolder[prevItHolderValue].xPos + iterationHolder[prevItHolderValue].size*(.5*cos(rad(iterationHolder[prevItHolderValue].rotAngle)) + sin(rad(iterationHolder[prevItHolderValue].rotAngle)));
			iterationHolder[i].yPos = iterationHolder[prevItHolderValue].yPos + iterationHolder[prevItHolderValue].size*(cos(rad(iterationHolder[prevItHolderValue].rotAngle)) - .5*sin(rad(iterationHolder[prevItHolderValue].rotAngle)));
		}
	}
}

void FractalTree::draw (){
	ofNoFill(); ofSetColor(205,133,63);
	ofBox(iterationHolder[0].getxPos (), iterationHolder[0].getyPos (), iterationHolder[0].getzPos (), iterationHolder[0].getsize ());
	for (unsigned int i=1; i<pow(two, iterations)-1; i++){
		if (iterationHolder[i].iteration<2){
			ofNoFill();
			ofSetColor(205,133,63);}
		else if (iterationHolder[i].iteration>=2){
			ofFill();
			ofSetColor(0,200,0);}
		ofTranslate(iterationHolder[i].getxPos (), iterationHolder[i].getyPos (), 0);
		ofRotateZ(iterationHolder[i].getrotAngle ());
		ofBox(0, 0, iterationHolder[i].getzPos (), iterationHolder[i].getsize ());
		ofRotateZ(-iterationHolder[i].getrotAngle ());
		ofTranslate(-iterationHolder[i].getxPos (), -iterationHolder[i].getyPos (), 0);
	}
}


int FractalTree::posDivider = 400; //see in-class description
//--------------------------------------------------------------