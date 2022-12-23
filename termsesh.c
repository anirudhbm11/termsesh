#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	FILE *fp;
	FILE *pwdfp;
	char path[50] = "./sessions/";
	char pwdfile[100];
	int pid = fork();

	if(argc == 1){
		printf("Required: Session name\n");
		exit(0);
	}
	
	strcat(path,argv[1]);
	strcat(path, ".txt");
	fp = fopen(path,"w");
	
	//pwdfp = fopen("pwd","r");
	
	//printf("Printing pwd...");

	/*
	while(fgets(pwdfile, sizeof pwdfile, pwdfp) != NULL){
		printf("%s", pwdfile);
	}
	*/
	
	if(pid == 0){
		// char *args[]={"cd .. && &SHELL",NULL};
		// execvp(args[0],args);
		system("bash temp_bash.sh");
	}else{
		wait(NULL);
	}
	
	//int status = system("bash temp_bash.sh");
	//pclose(pwdfp);
	fclose(fp);

	return 0;	
}
