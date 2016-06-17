#include<filters.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<math.h>



Color::Color(int w, int h, int red, int green, int blue){
	
	GetOutput()->resetSize(h, w);
	
	int dim = h*w*3;
	
	for(int i = 0; i < dim ; i+=3){
		GetOutput()->getData()[i] = (unsigned char)red;
		GetOutput()->getData()[i+1] = (unsigned char)green;
		GetOutput()->getData()[i+2] = (unsigned char)blue;
	}
}

const char*
Color::SourceName(){
	//srcnm = new char[20];
	//sprintf(srcnm,"Color");
	return "Color";
	
}

void
CheckSum::OutputCheckSum(const char* fname){
	if(input == NULL){
			char msg[1024];
			sprintf(msg,"%s: No input1!",SinkName());
			DataFlowException e(SinkName(),msg);
			throw e;
			
		}
	int dim = input->getHeight()*input->getWidth()*3;
	unsigned char rsum;
	unsigned char gsum;
	unsigned char bsum;
	
	for(int i=0;i<dim;i+=3){
		rsum+=input->getData()[i];
		gsum+=input->getData()[i+1];
		bsum+=input->getData()[i+2];
	}
	
	FILE *f = fopen(fname, "w");
	fprintf(f, "CHECKSUM: %u, %u, %u\n",rsum,gsum,bsum);
	
	fclose(f);
	
}

const char*
CheckSum::SinkName(){
	return "CheckSum";
}


void
Shrinker::Execute(){
	OneInputCheck();
	int h = floor(input->getHeight()/2);
	//printf("h is %d", h);
	int w = floor(input->getWidth()/2);
	GetOutput()->resetSize(h, w);
	//printf("w is %d", w);
	/*
	unsigned char *temp = new unsigned char[h*w*3];
	int i;
	int j = 0;
	int b = 0;
	for (i=0;i<h*w*3;i+=3){
		temp[i]= input->getData()[j];
		temp[i+1]=input->getData()[j+1];
		temp[i+2]=input->getData()[j+2];
		j+=6;
		b += 3;
		if((b+3) == w*3){
			j+=input->getWidth()*3;
			b=0;
		}
		//b += 3;
		
	}
	*/
	
	int rw = w*3;
	//fprintf(stderr,"new height is %d original is %d\nnew width is %d original is %d\n", h,input->getHeight(),w,input->getWidth());
	//fprintf(stderr,"input dimensions %d, calc to %d\n", input->getHeight()*input->getWidth()*3, 4*(h-1)*rw+2*(rw-1)+2);
	for(int i = 0; i<h;i++){
		for(int j = 0; j < rw;j+=3){
			//fprintf(stderr, "modifying point H: %d out %d  W: %d out of %d\n",i,h,j/3,w);
			//fprintf(stderr,"hitting point H: %d out %d  W: %d out of %d\n",i*2,input->getHeight(),2*(j/3),input->getWidth());
			GetOutput()->getData()[i*rw+j] = input->getData()[2*input->getWidth()*i*3+j*2];
			GetOutput()->getData()[i*rw+j+1] = input->getData()[2*input->getWidth()*i*3+j*2+1];
			GetOutput()->getData()[i*rw+j+2] = input->getData()[2*input->getWidth()*i*3+j*2+2];	
		}
		
	}
	/*
	int rh = h*2;
	rw= rw*2;
	
	for(int i = 0; i<rh;i+=2){
		for(int j = 0; j < rw;j+=3){
			//fprintf(stderr, "modifying point H: %d out %d  W: %d out of %d\n",i,h,j/3,w);
			//fprintf(stderr,"hitting point H: %d out %d  W: %d out of %d\n",i*2,input->getHeight(),2*(j/3),input->getWidth());
			GetOutput()->getData()[i*rw+j] = input->getData()[4*i*rw+j*2];
			GetOutput()->getData()[i*rw+j+1] = input->getData()[4*i*rw+j*2+1];
			GetOutput()->getData()[i*rw+j+2] = input->getData()[4*i*rw+j*2+2];	
		}
		
	}
	*/
	
	//memcpy(GetOutput()->getData(),temp,h*w*3*sizeof(unsigned char));
	
	//delete temp;
}

void 
Shrinker::Update(){
	//fprintf(stderr,"updating a shrinker %s\n", SourceName());
	if(GetOutput()->getData() != NULL){
		return;
	}
	
	char msg[128];
	
	OneInputCheck();
	
	sprintf(msg, "%s: About to update input1.",SourceName());
	//fprintf(stderr,"%s: About to update input1.\n",SourceName());
	Logger::LogEvent(msg);
	
	input->Update();
	
	sprintf(msg, "%s: Done updating input1.",SourceName());
	//fprintf(stderr,"%s: Done updating input1.\n",SourceName());
	Logger::LogEvent(msg);
	
	
	sprintf(msg, "%s: About to execute.",SourceName());
	//fprintf(stderr,"%s: About to execute.\n",SourceName());
	Logger::LogEvent(msg);
	
	Execute();
	
	sprintf(msg,"%s: done executing.",SourceName());
	//fprintf(stderr,"%s: done executing.\n",SourceName());
	Logger::LogEvent(msg);
}

const char*
Shrinker::SourceName(){
	//srcnm = new char[20];
	//sprintf(srcnm,"Shrinker");
	return "Shrinker";
	
}

int
Shrinker::InputCnt(){
	return 1;
	
}


void
LRConcat::Execute(){
	OneInputCheck();
	if(input->getHeight()!=input2->getHeight()){
		char msg[1024];
		sprintf(msg,"%s: Heights must match: %d, %d",SourceName(),input->getHeight(),input2->getHeight());
		DataFlowException e(SourceName(),msg);
		throw e;		
	}
	
	int nw = input->getWidth()+input2->getWidth();
	int h = min(input->getHeight(),input2->getHeight());
	GetOutput()->resetSize(h,nw);
	unsigned char* temp = new unsigned char[h*nw*3];
	
	//printf("the input has height: %d, width %d\n",h,leftInput.getWidth());
	//printf("this image is %d pixels height, and %d pixels wide\n",h,nw);
	
	int i;
	int j;
	
	
	
	for(i=0;i<h;i++){
		for(j=0;j<input->getWidth()*3;j++){
			temp[j+i*nw*3] = input->getData()[j+i*input->getWidth()*3];
		}
		for(j=0;j<input2->getWidth()*3;j++){
			temp[j+i*nw*3+input->getWidth()*3] = input2->getData()[j+i*input2->getWidth()*3];
		}
		
	}
	memcpy(GetOutput()->getData(),temp,h*nw*3*sizeof(unsigned char));
	
	delete temp;
}

const char*
LRConcat::SourceName(){
	//srcnm = new char[20];
	//sprintf(srcnm,"LRConcat");
	return "LRConcat";
	
}


void
TBConcat::Execute(){
	if(input == NULL){
		char msg[1024];
		sprintf(msg,"%s: No input1!",SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
		
	}
	if(input2 == NULL){
		char msg[1024];
		sprintf(msg,"%s: No input2!",SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}
/*	if(input->getWidth()!=input2->getWidth()){
		char msg[1024];
		sprintf(msg,"%s: Widths must match: %d, %d",SourceName(),input->getWidth(),input2->getWidth());
		DataFlowException e(SourceName(),msg);
		throw e;		
	}
*/	
	
	
	
	int w = min(input->getWidth(),input2->getWidth());
	int nh = input2->getHeight()+input->getHeight();
	//fprintf(stderr,"input height/width: %d/%d, input2 height/width: %d/%d height/width we iterate to:%d/%d\n",input->getHeight(),input)
	GetOutput()->resetSize(nh, w);
	unsigned char* temp = new unsigned char[nh*w*3];
	
	int i;
	int odim = input->getHeight()*w*3;
	int bdim = input2->getHeight()*w*3;
	int iter = max(odim,bdim);
	
	for(i=0;i<iter;i++){
		if(i<odim){
			temp[i] = input->getData()[i];
		}
		if(i<bdim){
			temp[i+odim]=input2->getData()[i];
		}	
	}
	
	memcpy(GetOutput()->getData(),temp,nh*w*3*sizeof(unsigned char));
	
	delete temp;
}

const char*
TBConcat::SourceName(){
	//srcnm = new char[20];
	//sprintf(srcnm,"TBConcat");
	return "TBConcat";
	
}

void
Blender::Execute(){
	if(input == NULL){
		char msg[1024];
		sprintf(msg,"%s: No input1!",SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
		
	}
	if(input2 == NULL){
		char msg[1024];
		sprintf(msg,"%s: No input2!",SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}
	
	if(factor>(float)1||factor<(float)0){
		char msg[1024];
		sprintf(msg,"%s:Invalid factor for Blender: %f",SourceName(),factor);
		DataFlowException e(SourceName(),msg);
		throw e;
	}
	
	int dim = input->getHeight()*input->getWidth()*3;
	int i;
	GetOutput()->resetSize(input->getHeight(),input->getWidth());
	unsigned char* temp = new unsigned char[dim];
	for(i=0;i<dim;i++){
		temp[i]=(unsigned char)((float)input->getData()[i]*factor+(float)input2->getData()[i]*((float)(1)-factor));
	}
	memcpy(GetOutput()->getData(),temp,dim*sizeof(unsigned char));
	
	delete temp;
}

const char*
Blender::SourceName(){
	//srcnm = new char[20];
	//sprintf(srcnm,"Blender");
	return "Blender";
	
}


void
Crop::Execute(void)
{
    OneInputCheck();
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    if (Istart >= input->getWidth() || Istop >= input->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    if (Jstart >= input->getHeight() || Jstop >= input->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }

    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = input->getWidth();
    GetOutput()->resetSize(height, width);
    unsigned char *buffer = GetOutput()->getData();
    const unsigned char *buffer1 = input->getData();
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            buffer[3*idx]   = buffer1[3*idx1];
            buffer[3*idx+1] = buffer1[3*idx1+1];
            buffer[3*idx+2] = buffer1[3*idx1+2];
        }
}

void 
Crop::Update(){
	//fprintf(stderr,"updating a Crop %s\n", SourceName());
	char msg[128];
	

	sprintf(msg, "%s: About to update input1.",SourceName());
	//fprintf(stderr,"%s: About to update input1.\n",SourceName());
	Logger::LogEvent(msg);
	
	input->Update();
	
	sprintf(msg, "%s: Done updating input1.",SourceName());
	//fprintf(stderr,"%s: Done updating input1.\n",SourceName());
	Logger::LogEvent(msg);
	
	
	sprintf(msg, "%s: About to execute.",SourceName());
	//fprintf(stderr,"%s: About to execute.\n",SourceName());
	Logger::LogEvent(msg);
	
	Execute();
	
	sprintf(msg,"%s: done executing.",SourceName());
	//fprintf(stderr,"%s: done executing.\n",SourceName());
	Logger::LogEvent(msg);
}

int
Crop::InputCnt(){
	return 1;
}

const char*
Crop::SourceName(){
	//srcnm = new char[20];
	//sprintf(srcnm,"Crop");
	return "Crop";
	
}

void
Transpose::Execute(){
	OneInputCheck();
	int height = input->getWidth();
	int width = input->getHeight();
	GetOutput()->resetSize(height, width);
	int start;
	
	for(int i = 0;i<height;i++){
		start =i*3;
		for(int j = 0; j<width*3;j+=3){
			GetOutput()->getData()[i*width*3+j] = input->getData()[start];
			GetOutput()->getData()[i*width*3+j+1] = input->getData()[start+1];
			GetOutput()->getData()[i*width*3+j+2] = input->getData()[start+2];
			start+=height*3;
		}
	}
	
	
}

void 
Transpose::Update(){
	//fprintf(stderr,"updating a shrinker %s\n", SourceName());
	char msg[128];
	

	sprintf(msg, "%s: About to update input1.",SourceName());
	//fprintf(stderr,"%s: About to update input1.\n",SourceName());
	Logger::LogEvent(msg);
	
	input->Update();
	
	sprintf(msg, "%s: Done updating input1.",SourceName());
	//fprintf(stderr,"%s: Done updating input1.\n",SourceName());
	Logger::LogEvent(msg);
	
	
	sprintf(msg, "%s: About to execute.",SourceName());
	//fprintf(stderr,"%s: About to execute.\n",SourceName());
	Logger::LogEvent(msg);
	
	Execute();
	
	sprintf(msg,"%s: done executing.",SourceName());
	//fprintf(stderr,"%s: done executing.\n",SourceName());
	Logger::LogEvent(msg);
}

int
Transpose::InputCnt(){
	return 1;
}

const char*
Transpose::SourceName(){
	//srcnm = new char[20];
	//sprintf(srcnm,"Transpose");
	return "Transpose";
	
}


void
Invert::Execute(){
	OneInputCheck();
	int dim = input->getHeight()*input->getWidth()*3;
	GetOutput()->resetSize(input->getHeight(),input->getWidth());
	for(int i = 0;i<dim;i++){
		GetOutput()->getData()[i]=(unsigned char)(255-(int)input->getData()[i]);
	}
	
	
}

void 
Invert::Update(){
	//fprintf(stderr,"updating a shrinker %s\n", SourceName());
	char msg[128];
	

	sprintf(msg, "%s: About to update input1.",SourceName());
	//fprintf(stderr,"%s: About to update input1.\n",SourceName());
	Logger::LogEvent(msg);
	
	input->Update();
	
	sprintf(msg, "%s: Done updating input1.",SourceName());
	//fprintf(stderr,"%s: Done updating input1.\n",SourceName());
	Logger::LogEvent(msg);
	
	
	sprintf(msg, "%s: About to execute.",SourceName());
	//fprintf(stderr,"%s: About to execute.\n",SourceName());
	Logger::LogEvent(msg);
	
	Execute();
	
	sprintf(msg,"%s: done executing.",SourceName());
	//fprintf(stderr,"%s: done executing.\n",SourceName());
	Logger::LogEvent(msg);
}

int
Invert::InputCnt(){
	return 1;
}

const char*
Invert::SourceName(){
	//srcnm = new char[20];
	//sprintf(srcnm,"Invert");
	return "Invert";
	
}

void
Checkerboard::Execute(){
	OneInputCheck();
	if(input->getHeight()*input->getWidth() != input2->getWidth()*input2->getHeight()){
		char msg[1024];
		sprintf(msg,"%s: Images not same size!",SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;		
	}
	int h = input->getHeight();
	int w = input->getWidth();
	int rw = w*3;
	
	GetOutput()->resetSize(h,w);

	for(int i = 0; i< h; i++){
		
		for(int j=0;j<rw;j+=3){
			if((i/10+(j/3)/10)%2==0){
				GetOutput()->getData()[i*rw+j] = input->getData()[i*rw+j];
				GetOutput()->getData()[i*rw+j+1] = input->getData()[i*rw+j+1];
				GetOutput()->getData()[i*rw+j+2] = input->getData()[i*rw+j+2];
			}else{
				GetOutput()->getData()[i*rw+j] = input2->getData()[i*rw+j];
				GetOutput()->getData()[i*rw+j+1] = input2->getData()[i*rw+j+1];
				GetOutput()->getData()[i*rw+j+2] = input2->getData()[i*rw+j+2];
			}
			
			
		}
	}
	
}

const char*
Checkerboard::SourceName(){
	//srcnm = new char[20];
	//sprintf(srcnm,"Blender");
	return "Checkerboard";
	
}

