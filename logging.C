#include<stdio.h>
#include<logging.h>


FILE *Logger::logger = fopen("logger","w");

void
Logger::LogEvent(const char* event){
	fprintf(logger,"%s\n",event);
	
	
	
}

void
Logger::Finalize(){
	fclose(logger);
	
	
	
}

DataFlowException::DataFlowException(const char *type, const char *error){
	sprintf(msg,"Throwing exception:(%s):%s",type,error);
	fprintf(stderr,"Throwing exception:(%s):%s\n",type,error);
	Logger::LogEvent(msg);
	
}