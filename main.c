
#include<stdio.h>
#include <string.h>
#include<time.h>
#include<stdlib.h>
#include<limits.h>
#include <sys/stat.h>
#include<sys/types.h>



// man here the PATH_MAX is just representing the size of the possible file 

char FILE_PATH[PATH_MAX];

char HOME[PATH_MAX];     // here home is the home for the tool ( i,e. /home/user/QNote/ - for linux )

char FILE_NAME[256]="QNote";     // represents the name of the file its wrinting ( here we call project )

//  get a timestamp && string to a presistant file 
void init_path(void);
char *get_time(void);
int write(const char *str);
char *help(void);
int format_write(char * data);
int mk_dir(char *name);
int dir_check(const char * path);




int main(int argc , char *argv[]){
    init_path();
    if ( argc >1){    
        
        if (strcmp(argv[1],"--locate") == 0 || strcmp(argv[1], "-l")==0){

            printf("%s\n",FILE_PATH);
        }
        
        else if (strcmp(argv[1],"--new-project")==0 || strcmp(argv[1],"-n")==0){
            if (argc>2){
                strcpy(FILE_NAME,argv[2]);
                printf("Done the file is set to %s.\n",FILE_NAME);
            }
            else{
                printf("please enter a Name for the project.\n");
                return 0;
            }
        }

        else{

            format_write(argv[1]);

            printf(" Noted 👍 \n");
            return 0;
        }

    }

    else{
       printf(" No arguments found.\n");
       return 0;

   } 

}

void init_path(void){

    // here we're using std posix tool to get the home dir 
    const char * home=getenv("HOME");

    snprintf(HOME, PATH_MAX, "%s/QNote",home);
    /* here it got merged to HOME */

    if (dir_check("~/QNote")==0){
        mk_dir(HOME);        // checking wether the dir exist , if not found create one 
    }
    snprintf(FILE_PATH, PATH_MAX ,"%s/QNote/%s",home,FILE_NAME);
    // merging the whole (absolute) path for the HOME/FILENAME 
    
}
    
int format_write(char *data){

        // just formating 

    char *now = get_time();
        
    write("\n");
    write(now);
    write(data);        
    write("\n"); 
    return 0;
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

int mk_dir(char *name){
    if (mkdir(name,0755)==0){
        return 0;
    }   

    /* which gives; 

     *       user * permissions  -rwx
     *       for grps            -rx
     *       other users         -rx
     
     */

    else{
        perror("mkdir");  // gives the default err (Inc in the mkdir doc)
    }
}


int dir_check(const char * path){

    // checks the file exists or not 

    struct stat pathStat;
    stat(path, &pathStat);
    return S_ISDIR(pathStat.st_mode);
}
