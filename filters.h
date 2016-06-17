#include<image.h>
#include<PNMreader.h>
#include<PNMwriter.h>
#include<logging.h>
#ifndef FILTERS_H
#define FILTERS_H
using namespace std;

class Filter: public Source, public Sink{
	
	public:
							Filter(void){};
		virtual void 		Update();
		virtual const char* SourceName();
		virtual	void		OneInputCheck();
		virtual int			InputCnt();
};

class Color: public Source{
		
	public:
							Color(int w, int h, int red, int green, int blue);
		virtual void		Execute(){};
		virtual const char*	SourceName();
		virtual void		Update(){};
};

class CheckSum: public Sink{
	
	public:
							CheckSum(void){};
		void				OutputCheckSum(const char* fname);	
		virtual const char*	SinkName();
	
};

class Shrinker:public Filter{
	
	public:
							Shrinker(void){};
		virtual void 		Execute();
		virtual void 		Update();
		virtual const char* SourceName();
		virtual int			InputCnt();

};


class LRConcat:public Filter{
	
	public:
							LRConcat(void){};
		virtual void 		Execute();
		virtual const char* SourceName();
};

class TBConcat:public Filter{
	
	public:
							TBConcat(void){};
		virtual void 		Execute();
		virtual const char* SourceName();	
};

class Blender:public Filter{
	float 					factor;
	
	public:
							Blender(void){factor = 0.0;};
		void 				SetFactor(float f){factor = f;};
		virtual void 		Execute();
		virtual const char* SourceName();
};

class Crop : public Filter
{
	private:
		int 				Istart, Istop, Jstart, Jstop;
	
	
	
	public:
							Crop()  { Istart = Istop = Jstart = Jstop = -1; };
		virtual const char *SourceName();
		virtual void   		Execute();
		virtual int			InputCnt();
		virtual void		Update();
	
		void           		SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
							{
								Istart = Istart_;
								Istop  = Istop_;
								Jstart = Jstart_;
								Jstop  = Jstop_;
							};

};


class Transpose : public Filter {
	
	
	public:
							Transpose(void){};
		virtual void 		Execute();
		virtual const char* SourceName();
		virtual int			InputCnt();
		virtual void		Update();
	
	
	
	
};

class Invert : public Filter {
	

	public:
							Invert(void){};
		virtual void 		Execute();
		virtual const char* SourceName();
		virtual int			InputCnt();
		virtual void		Update();
	
	
	
};

class Checkerboard : public Filter{
	
	public:
							Checkerboard(void){};
		virtual void		Execute();
		virtual const char*	SourceName();
	
	
};



#endif