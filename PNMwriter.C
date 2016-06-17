#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<PNMwriter.h>

PNMwriter::PNMwriter(void){
	SetInput(NULL);
	SetInput2(NULL);
	
}

const char*
PNMwriter::SinkName(){
	return "PNMwriter";

	
}


void
PNMwriter::Write(char* filename){
	//fprintf(stderr,"we're writing!\n filename is %s\n", filename);
	FILE *f = fopen(filename, "w");
	
	fprintf(f, "P6\n%d %d\n255\n",input->getWidth(),input->getHeight());
	fwrite(input->getData(),3*sizeof(unsigned char)*input->getHeight()*input->getWidth(),1,f);
	//fprintf(stderr,"%s\n%d %d\n%d\n", img->magicNum,img->width,img->height,img->maxval);
	fclose(f);
	
	
}