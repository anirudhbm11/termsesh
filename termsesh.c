#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void record_pwd(char[]);
void saveSession(char *);
char* get_current_shell();
FILE* run_shell_command();

int main(int argc, char *argv[]){
	//Flag used to record name of the session which is to be saved
	char* saveFlag;
	//Flag used to record name of the session which is to be loaded
	char* loadFlag;
	int c;

	// Parsing argument paramters. Currently only save session option.
	while ((c = getopt (argc, argv, "s:")) != -1)
		switch (c)
		{
		case 's':
			saveFlag = optarg;
			saveSession(optarg);
			break;
		
		default:
			abort();
		}

	return 0;	
}

void saveSession(char* sessionName){
	/*
	Function used to store sesisons.
	*/
	FILE *fp;
	char dir_path[50] = "./sessions/";
	char util_file_path[100];
	char *shell;

	strcat(dir_path,sessionName);
	int create_session = mkdir(dir_path, 0777);
	if(create_session != -1){
		printf("Unable to create directory\n");
        exit(1);
	}

	strcpy(util_file_path, dir_path);
	strcat(util_file_path, "/util.txt");

	// Used to record present working directory
	record_pwd(util_file_path);

	// Get the current used shell
	shell = get_current_shell();
	
	if(shell == NULL){
		printf("Unimplemented shell....");
		exit(1);
	}else if(strcmp(shell, "zsh") == 0){
		printf("ZSH shell\n");
	}else{
		printf("Unimplemented shell....");
		exit(1);
	}

}

FILE* run_shell_command(FILE* commandFP, char* command){
	commandFP = popen(command, "r");

	return commandFP;
}

char* get_current_shell(){
	char *shell = getenv("SHELL");

	if(strcmp(shell, "/bin/zsh") == 0){
		return "zsh";
	}else if(strcmp(shell, "/bin/bash") == 0){
		return "bash";
	}else{
		return NULL;
	}
}


void record_pwd(char util_file_path[]){
	/*
	params:
	util_file_path(char []): File path used to store present working directory
	*/
	FILE *pwdfp; //Used to read the present working directory using pwd command
	FILE *util_file; // Used to store the output to file
	char buffer[300];
	char pwdfile[300];

	pwdfp = run_shell_command(pwdfp, "pwd");

	util_file = fopen(util_file_path, "w");
	if(util_file == NULL) {
        printf("File couldn't be opened\n");
        exit(1);
    }

	// Reading present working directory and printing it in file. 
	while(fgets(buffer, sizeof(buffer), pwdfp) != NULL){
		strcpy(pwdfile, buffer);
		fputs(buffer, util_file);
	}

	printf("%s", pwdfile);

	pclose(pwdfp);
	fclose(util_file);
}
