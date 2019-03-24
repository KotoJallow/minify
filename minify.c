#include <stdio.h>

#ifdef _WIN32
#define fileSeparator 92
#else
#define fileSeparator 47   
#endif

void minify(int argc,char **argv){
	if(argc < 2){
		fprintf(stderr,"File required\n");
		return;
	}
	FILE *fp = fopen(argv[1],"r");
	
	if(!fp){
		fprintf(stderr,"Error in opening file\n");
		return ;      
	}
	
	/**Create min file name**/
	int lastFileSeparator = 0;
	int point = 0;
	const char  * min = ".min.";
	char * s = argv[1];
	int i;
	for(i=0;*s;i++){
		if(*s == fileSeparator){
			lastFileSeparator = i+1;		
		}
		if(*s == '.') point = i;
		
		s++;
	}
	
	char * ext = s - (i-point-1);
	//now set a null terminator in place of the point
	*(s - (i-point)) = '\0';
	char * fileName = s - (i-lastFileSeparator);
	char minFileName[i-lastFileSeparator + 5];

	sprintf(minFileName,"%s%s%s",fileName,min,ext);
	/*****end min file name creation**/
	
	FILE *mfp = fopen(minFileName,"w");
	
	if(!mfp){
		perror("");return;
	}
	
	char temp;
	while(fscanf(fp,"%c",&temp) != -1){
		
		if(temp == 10) continue;
		
		fprintf(mfp,"%c",temp);
			
	}	
}

int main(int argc,char **argv){
	minify(argc,argv);
	return 0;
}
