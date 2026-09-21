#include <linux/limits.h>
#include<stdio.h>
#include <strings.h>
#include<time.h>
#include<stdlib.h>
#include<limits.h>



// man here the PATH_MAX is just representing the size of the possible file 
char FILE_PATH[PATH_MAX];

//  get a timestamp && string to a presistant file 
void init_path(void);
char *get_time(void);
int write(const char *str);
char *help(void);
int format_write(char *data);


int main(int argc , char *argv[]){
    
    init_path();
    if ( argc >1){    
        
        format_write(argv[1]);

        printf(" Noted 👍 \n");
        return 0;

    }

    else{
       printf(" No arguments found.\n");
       return 0;

   } 

}

void init_path(void){

    const char *home = getenv("HOME");
    snprintf(FILE_PATH, PATH_MAX ,"%s/.qnote",home);
    
}
    

int format_write(char *data){
        
    char *now = get_time();
        
    write("\n");
    write(now);
    write(data);        
    write("\n");

}

char *get_time(void){

    // here fetching time 
    time_t current_time = time(NULL);           // now current_time has a int time from eposh ( jan 1, 1970 )
    return ctime(&current_time);                // now were returning a string time from the time.h lib

}

int write(const char *str){
    
    FILE *fckin_file;
    fckin_file = fopen(FILE_PATH, "a+");

    if (fckin_file == NULL){
        printf("ERROR opening file \n");
        return 1;
    }

    if (fputs(str, fckin_file)== EOF)  // it doesnt return a newline char in the end 
    {    
        // here checking any trouble making char s

        fclose(fckin_file);
        return 1;

    }
    
    fclose(fckin_file);
    return 0;
    

}



