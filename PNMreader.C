#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<PNMreader.h>
#include<image.h>
#include<errno.h>

PNMreader::PNMreader(char* arg){
	filename = new char[strlen(arg)+1];
	//memcpy(filename,arg,strlen(arg)*sizeof(char));
    strcpy(filename, arg);
	
}

PNMreader::~PNMreader(){
	delete filename;
	
}

void
PNMreader::Execute(){
	//fprintf(stderr, "PNMREADER IS HAPPENING\n");
	if(GetOutput()->getData() != NULL){
		return;
	}
	
	Image* tim;
	tim = GetOutput();
	int h;
	int w;
	int maxval;
	char magicNum[2];
	unsigned char *temp;
	//fprintf(stderr,"filename is equal to: %s\n",filename);
	FILE * f = fopen(filename, "r");
	
	
	//fprintf(stderr, "This after the open\n");
	fscanf(f, "%s\n%d %d\n%d\n",magicNum, &w, &h, &maxval);
	//fprintf(stderr, "This after the scan\n");
	
	//printf("%d   %d\n",h,w);
	//Image *r = malloc(sizeof(Image));
	temp = (unsigned char *)malloc(h*w*sizeof(unsigned char)*3);
	//output.setHeight(h);
	//output.setWidth(w);
	tim->setMax(maxval);
	tim->setSpec(magicNum);
	fread(temp,h*w*sizeof(unsigned char)*3,1,f);
	fseek(f,0,SEEK_SET);
	fclose(f);
	tim->resetSize(h, w);
	//output.setData(temp);
	memcpy(tim->getData(),temp,h*w*3*sizeof(unsigned char));
	//printf("width is %d \nheight is %d \n", tim->getWidth(),tim->getHeight());
	free(temp);
	
	
}

const char*
PNMreader::SourceName(){
	//srcnm = new char[20];
	//sprintf(srcnm,"PNMreader");
	return "PNMreader";
	
}

void
PNMreader::Update(){
	//fprintf(stderr,"READING THE FILE");
	char msg[128];
	

	sprintf(msg, "%s: About to execute.",SourceName());
	//fprintf(stderr,"%s: About to execute.\n",SourceName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg, "%s: Done executing.",SourceName());
	//fprintf(stderr,"%s: Done executing.\n",SourceName());
	Logger::LogEvent(msg);
	
	
	
}
