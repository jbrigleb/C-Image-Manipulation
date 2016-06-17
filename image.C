#include <image.h>
#include <PNMreader.h>
#include <stdio.h>
#include <stdlib.h>

Image::Image(void){
	//fprintf(stderr,"instantiating img");

	height = 0;
	width = 0;
	maxval = 0;
	data = NULL;
	
}
void
Image::resetSize(int h, int w){
	if(data!=NULL){
		delete data;
	}
	height = h;
	width = w;
	data = new unsigned char[h*w*3];

	
}

Image::~Image(){
	if (data!=NULL){
		delete data;
	}
}

void
Image::Update() const{
	//fprintf(stderr,"IMAGE UPDATE\n");
	src->Update();
	
	
}