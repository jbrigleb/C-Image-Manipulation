#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<source.h>

Source::Source(void){
	//img = new Image();
	img.setSource(this);
	
	
}

//Source::~Source(){
	//if(img!=NULL){
		//fprintf(stderr,"in %s img isnt null:freeing\n ", SourceName());
	//	delete img;
	//}
	//if(srcnm!=NULL){
		//fprintf(stderr,"in %s srcnm isnt null:freeing\n", SourceName());
	//	delete srcnm;
	//}	
//}

const char*
Source::SourceName(){
	//srcnm = new char[20];
	//sprintf(srcnm,"Source");
	return "Source";
	
}