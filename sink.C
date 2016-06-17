#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sink.h>

Sink::Sink(void){
	input = NULL;
	input2 = NULL;
}

const char*
Sink::SinkName(){
	
	return "Sink";	
}


void Sink::SetInput(Image* a){
	input = a;
	//printf("width is %d \n height is %d \n", a->getWidth(),a->getHeight());
	
}

void Sink::SetInput2(Image* a){
	input2 = a;
	
}