#ifndef SINK_H
#define SINK_H
#include<image.h>
class Sink{
	protected:
	const Image*  		input;
	const Image*		input2;
	
	public:
						Sink(void);
						~Sink(){};
	void 				SetInput(Image* a);
	void 				SetInput2(Image* a);
	virtual const char* SinkName();
	
};


#endif