#include<filters.h>
#include<stdio.h>


void
Filter::Update(){
	//fprintf(stderr, "updating some filter...%s\n",SourceName());
	/*
	if((input->getSource()->GetInput() == self)||(input->getSource()->GetInput2() == self)||(input2->GetInput() == self)||(input2->GetInput2() == self)){
		char msg[1024];
		sprintf(msg,"%s: Looping data flow",SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}
	*/
	if(input == NULL){
		char msg[1024];
		sprintf(msg,"%s: No input1!",SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
		
	}
	char msg[128];
	
	sprintf(msg, "%s: About to update input1.",SourceName());
	//fprintf(stderr,"%s: About to update input1.\n",SourceName());
	Logger::LogEvent(msg);
	
	input->Update();
	
	sprintf(msg, "%s: Done updating input1.",SourceName());
	//fprintf(stderr,"%s: Done updating input1.\n",SourceName());
	Logger::LogEvent(msg);

	
	sprintf(msg, "%s: About to update input2.",SourceName());
	//fprintf(stderr,"%s: About to update input2.\n",SourceName());
	Logger::LogEvent(msg);
	if(input2 == NULL){
		char msg[1024];
		sprintf(msg,"%s: No input2!",SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}
	
	
	input2->Update();

	sprintf(msg, "%s: Done updating input2.",SourceName());
	//fprintf(stderr,"%s: Done updating input2.\n",SourceName());
	Logger::LogEvent(msg);
	
	
	
	sprintf(msg, "%s: About to execute.",SourceName());
	//fprintf(stderr,"%s: About to execute.\n",SourceName());
	Logger::LogEvent(msg);
	
	Execute();
	
	sprintf(msg, "%s: Done executing.",SourceName());
	//fprintf(stderr,"%s: Done executing.\n",SourceName());
	Logger::LogEvent(msg);
	
	
}

const char*
Filter::SourceName(){
	//srcnm = new char[20];
	//sprintf(srcnm,"Filter");
	return "Filter";
	
}

int
Filter::InputCnt(){
	return 2;	
}

void
Filter::OneInputCheck(){
	if(InputCnt()==2){
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
	}	
	else{
		if(input == NULL){
			if(input2 == NULL){
				char msg[1024];
				sprintf(msg,"%s: No input1!",SourceName());
				DataFlowException e(SourceName(),msg);
				throw e;
			}
			else{
				input = input2;
			}
		
		}		

	}
}

