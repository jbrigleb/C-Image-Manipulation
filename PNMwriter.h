#ifndef PNMWRITER_H
#define PNMWRITER_H
#include<image.h>
#include<sink.h>

class PNMwriter:public Sink{
	
	public:
						PNMwriter(void);
	void 				Write(char* filename);
	virtual const char* SinkName();
	
};



#endif