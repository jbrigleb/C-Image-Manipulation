#ifndef SOURCE_H
#define SOURCE_H
#include<image.h>
#include<string>
using namespace std;

class Source{
	protected:
	
		Image 			img;
		//char* 			srcnm;
		virtual void 	Execute() = 0;
	
	public:
	
							Source(void);
		//virtual 			~Source();
	
		Image*				GetOutput(){return &img;};
		//void 				SetOutput(Image* i){img = i;};
		virtual const char* SourceName();
		virtual void		Update()=0;
	
};


#endif