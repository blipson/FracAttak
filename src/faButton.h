#pragma once

#include "testApp.h"


class faButton
{
protected:
	char *filename;
	ofPoint location;
	ofImage image;
	ofImage hover_image;
	ofImage clicked_image;
	ofImage **image_array;
	ofImage *current_image;
	int image_ct;
	bool has_text;
	char *fontname;
	ofTrueTypeFont font;
	int fontsize;
	char *text;
	bool b_hover;
	float half_image_width;
	float half_image_height;
public:
	faButton(const char* txt, const char* flname, ofPoint loc, const char* ftname, int ftsize);
	faButton();
	~faButton();
	void load();
	void draw();
	bool isOver(int x, int y);
	void isClicked(int x, int y);
	void resetImage();
};


