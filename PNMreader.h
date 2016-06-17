#ifndef PNMreader_H
#define PNMreader_H
#include<image.h>
#include<source.h>
#include<logging.h>



class PNMreader: public Source{
	char* filename;
	
	
	public:
	
						PNMreader(void);
						virtual ~PNMreader();
						PNMreader(char* arg);
						PNMreader(PNMreader &p);
	virtual void 		Execute();
	virtual const char* SourceName();
	virtual void 		Update();
	
	
	
};


#endif