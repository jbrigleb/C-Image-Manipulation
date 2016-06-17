#ifndef IMAGE_H
#define IMAGE_H





class Source;

class Image{
	protected:
		unsigned char 	*data;
		int				 height;
		int				 width;
		char 			*spec;
		int				 maxval;
		Source* 		 src;
	
	public:
						Image(void);
						Image(unsigned char *d,int w,int h,char *s, int m);
						Image(Image &);
						~Image();
		
		int 			getHeight() const{return height;};
		void 			setHeight(int h){height = h;};
		
		int 			getWidth() const{return width;};
		void 			setWidth(int w){width = w;};
		
		char 		   *getSpec() const{return spec;};
		void 			setSpec(char *s){spec = s;};
		
		int 			getMax() const{return maxval;};
		void 			setMax(int m){maxval = m;};
		
		void 			setData(unsigned char *d){data = d;};
		unsigned char  *getData()const{return data;};
		
		void 			resetSize(int h, int w);
		
		Source* 		getSource()const{return src;};
		void 			setSource(Source* s){src = s;};
		
		void 			Update() const;
};


#endif