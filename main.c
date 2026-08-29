#include <linux/limits.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>


//  get a timestamp && string to a presistant file 

const char *FILE_PATH = "/home/normie/.qnote/log";

char *get_time(void);
int write(const char *str);
char *help(void);

int main(int argc , char *argv[]){

    if ( argc >1){    
        char *now = get_time();
        
        write("\n");
        write(now);
        write(argv[1]);        
        write("\n");

        printf(" Noted 👍 \n");
        return 0;

    }

    else{
       printf(" No arguments found.\n");
       return 0;

   } 

}

char *get_time(void){

    // here fetching time 
    time_t current_time = time(NULL);           // now current_time has a int time from eposh ( jan 1, 1970 )
    return ctime(&current_time);                // now were returning a string time from the time.h lib

}

int write(const char *str){

    FILE *fckin_file;

    fckin_file = fopen(FILE_PATH, "a");

    if (fckin_file == NULL){
        printf("ERROR opening file \n");
        return 1;
    }

    if (fputs(str, fckin_file)== EOF)  // it doesnt return a newline char in the end 
    {    
        // here checking any trouble making char s

        fclose(fckin_file);
        return 1;}
    
    fclose(fckin_file);
    return 0;
    

}

