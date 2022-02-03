#include <stdio.h>
#include <stdlib.h> 
#include <sys/utsname.h>
#include <utmp.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <string.h>

// INITIALIZING functionS SO THEY CAN BE USED //
void setValues(int *num_repetitions, int *delay, char *arg1, char *arg2, char **argv, int argc);
void printFirstLine(int *num_repetitions, int *delay);
void systemFlag(int *num_repetitions, int *delay);
void systemGraphicFlag(int *num_repetitions, int *delay);
void userFlag(int *num_repetitions, int *delay);
void userGraphicFlag(int *num_repetitions, int *delay);
void noFlags(int *num_repetitions, int *delay);
void graphicsFlag(int *num_repetitions, int *delay);
void printSystemInfo();
void printSessionsUsers(int *numUser);
int getNumCores();
void printCores();
void printMemory(double *memory);
double calculateCpuUsage(double frstWorkJiffy, double scndWorkJiffy, double frstTotalJiffy, double scndTotalJiffy);
void calculateWorkandTotalJiffies(double *workJiffy, double *totalJiffy);
void printTotalCpuUse(double frstWorkJiffy, double scndWorkJiffy, double frstTotalJiffy, double scndTotalJiffy);
void getMemoryGraphic(double *prevMem, double *currMem);
void getCpuGraphic(double *prevCpu, double *currCpu);
void goDown(int len);
void goUp(int len);


//main function that takes in the comand line arguments and calls
//the according functions depending what the user would like to be displayed
int main(int argc, char **argv){

    //if statement which checks if the user inputs too many arguments
    if (argc > 5){
        printf("Too many arguments provided");
    }//end if
    else {

        int num_repetitions = -1; //set to -1 to tell the program it hasn't been set yet
        int delay = -1; //set to -1 to tell the program it hasn't been set yet

        char *arg1 = malloc(sizeof(char *));
        strcpy(arg1, "NOT SET"); //set to "NOT SET" to tell the program it hasn't been set yet

        char *arg2 = malloc(sizeof(char *));
        strcpy(arg2, "NOT SET"); //set to "NOT SET" to tell the program it hasn't been set yet


        //this function sets our values accordingly
        setValues(&num_repetitions, &delay, arg1, arg2, argv, argc);

        //checking if the flag is for system output
        if (strcmp(arg1, "--system") == 0|| strcmp(arg2, "--system") == 0){

            //checking if the graphics flag is included
            if (strcmp(arg1, "--graphics") == 0 || strcmp(arg2, "--graphics") == 0 || strcmp(arg1, "-g") == 0 || strcmp(arg2, "-g") == 0){

                //calling the function that deals with the system and graphics flags
                systemGraphicFlag(&num_repetitions, &delay); 

            }//end if
            else if (strcmp(arg1, "NOT SET") == 0 || strcmp(arg2, "NOT SET") == 0){

                //calling the function that deals with the system flag
                systemFlag(&num_repetitions, &delay);

            }//end else
            else{

                //one argument isn't valid
                printf("One or more of your arguments aren't valid\n");

            }//end else
            

        }//end if
        else if (strcmp(arg1, "--user") == 0 || strcmp(arg2, "--user") == 0){ //checking if the flag is for user output

            //checking if the graphics flag is included
            if (strcmp(arg1, "--graphics") == 0 || strcmp(arg2, "--graphics") == 0 || strcmp(arg1, "-g") == 0 || strcmp(arg2, "-g") == 0){

                //calling the function that deals with user and graphics flags
                printf("There is no graphical element to the user flag\n");

            }//end if
            else if (strcmp(arg1, "NOT SET") == 0|| strcmp(arg2, "NOT SET") == 0){

                //calling the function that deals with the user flag
                userFlag(&num_repetitions, &delay);

            }//end else
            else{

                //one argument isn't valid
                printf("One or more of your arguments aren't valid\n");

            }//end else

        }//end if
        else if (strcmp(arg1, "NOT SET") == 0 && strcmp(arg2, "NOT SET") == 0){ //checking if neither arguments were set
            noFlags(&num_repetitions, &delay);
        }//end else if
        else if(strcmp(arg1, "--graphics") == 0 || strcmp(arg2, "--graphics") == 0 || strcmp(arg1, "-g") == 0 || strcmp(arg2, "-g") == 0){
            graphicsFlag(&num_repetitions, &delay);
        }//end else if
        else{ //none of the arguments are valid
            printf("One or more of your arguments aren't valid\n");
        }//end else
        
        free(arg1);
        free(arg2);
    }//end else
    
}//end main function

//this function sets the values needed accordingly
void setValues(int *num_repetitions, int *delay, char *arg1, char *arg2, char **argv, int argc){

    //checking if there are no arguments to set values to their default
    if (argc == 0){
        *num_repetitions = 10;
        *delay = 1;
    }//end if
    else{
        char *cur_arg = malloc(sizeof(char *)); //variable to set the current argument

        //for loop to go thorough each argument and set it accordingly
        for (int i = 1; i < argc; i++){
            strcpy(cur_arg, argv[i]);

            //checking if this argument starts with - to minimize the options
            if (cur_arg[0] == '-'){

                //checking if this argument starts has = to minimize the options
                if (strchr(cur_arg, '=') != NULL){

                    //checking if the argumet is for the number of samples
                    if (strchr(cur_arg, 's') != NULL){

                        //casting cur_arg to int and setting it to num_repitions
                        sscanf(cur_arg, "%d", num_repetitions); 

                    }//end if
                    else{

                        //casting cur_arg to int and setting it to delay
                        sscanf(cur_arg, "%d", delay); 

                    }//end else
                        
                }//end if
                else{

                    //checking arg1 has been set yet, if not then we set cur_arg to arg1
                    if (strcmp(arg1, "NOT SET") == 0){
                        strcpy(arg1, cur_arg);
                    }//end if
                    else{
                        strcpy(arg2, cur_arg);
                    }//end else
                        
                        
                }//end else
                    
            }//end if
            else{

                //checking if num_repetitions hasn't been set yet 
                //assuming the first number inputed in the CLA is the numer of repitions
                if (*num_repetitions == -1){

                    //casting cur_arg to int and setting it to num_repitions
                    sscanf(cur_arg, "%d", num_repetitions); 

                }//end if
                else{

                    //casting cur_arg to int and setting it to num_repitions
                    sscanf(cur_arg, "%d", delay); 

                }//end else
                    
            }//end else
                
        }//end for

        free(cur_arg);

    }//end else

    //checking if num_repitions wasn't set so we can set it to its default value
    if (*num_repetitions == -1){
        *num_repetitions = 10;
    }//end if

    //checking if delay wasn't set so we can set it to its default value
    if (*delay == -1){
        *delay = 1;
    }//end if
    
}//end setValues

//////////////////////////////////////////////////// functionS TO DEAL WITH FLAGS ////////////////////////////////////////////////////

// function that prints the generic first line that all flags use
void printFirstLine(int *num_repetitions, int *delay){
    printf("Nbr of samples: %d -- every %d secs\n", *num_repetitions, *delay);
}//end printFirstLine

// function to deal with only the system flag
void systemFlag(int *num_repetitions, int *delay){

    // SETTING/INITIALIZING VALUES //
    double prevWorkJiffy = 0;
    double prevTotalJiffy = 0;
    double currWorkJiffy = 0;
    double currTotalJiffy = 0;
    double currMemory = 0;

    printFirstLine(num_repetitions, delay); //prints the first line

    printf("---------------------------------------\n");

    printf("### Memory ### (Phys.Used/Tot -- Virtual Used/Tot)\n");

    //going down the amount of samples we're taking
    goDown(*num_repetitions);

    printf("---------------------------------------\n");

    calculateWorkandTotalJiffies(&currWorkJiffy,&currTotalJiffy); //getting the current values

    printCores();
    printTotalCpuUse(prevWorkJiffy, currWorkJiffy, prevTotalJiffy, currTotalJiffy); //calculating and printing the total cpu usage

    //swapping values
    prevWorkJiffy = currWorkJiffy;
    prevTotalJiffy = currTotalJiffy;

    printf("---------------------------------------\n");

    printSystemInfo(); //prints the system information

    printf("---------------------------------------\n");

    //going up to the memory section
    goUp(*num_repetitions + 11);

    //prints what is needed for the system flag
    for (int i = 0; i < *num_repetitions; i++){

        printMemory(&currMemory); //prints the memory sample at that time
        printf("\n");
        
        sleep(*delay); //'sleeps' for delay amount of time before taking another sample 

        //to get to the cpu percentage line
        goDown(*num_repetitions - i);

        calculateWorkandTotalJiffies(&currWorkJiffy,&currTotalJiffy); //getting the current values

        printCores();
        printTotalCpuUse(prevWorkJiffy, currWorkJiffy, prevTotalJiffy, currTotalJiffy); //calculating and printing the total cpu usage

        //swapping values
        prevWorkJiffy = currWorkJiffy;
        prevTotalJiffy = currTotalJiffy;

        //going up to the memory section
        goUp(*num_repetitions - i + 2);
        
    }//end for 

    //going down to the end
    goDown(11);

}//end systemFlag

// function to deal with system and graphics flags
void systemGraphicFlag(int *num_repetitions, int *delay){
    
    // SETTING/INITIALIZING VALUES // 
    double prevWorkJiffy = 0;
    double prevTotalJiffy = 0;
    double currWorkJiffy = 0;
    double currTotalJiffy = 0;

    double prevMemory = 0;
    double currMemory = 0;
    
    double currCpu = 0;
    double prevCpu = 0;

    printFirstLine(num_repetitions, delay); //prints the first line

    printf("---------------------------------------\n");

    printf("### Memory ### (Phys.Used/Tot -- Virtual Used/Tot)\n");

    //goes down the amount of samples that will be printed
    goDown(*num_repetitions);

    printf("---------------------------------------\n");

    calculateWorkandTotalJiffies(&currWorkJiffy,&currTotalJiffy); //getting the current values

    printCores();
    printTotalCpuUse(prevWorkJiffy, currWorkJiffy, prevTotalJiffy, currTotalJiffy); //calculating and printing the total cpu usage

    //spaces for graph output
    goDown(*num_repetitions);

    //swapping values
    prevWorkJiffy = currWorkJiffy;
    prevTotalJiffy = currTotalJiffy;

    printf("---------------------------------------\n");

    printSystemInfo(); //prints the system information

    printf("---------------------------------------\n");

    //going up to the memory section
    goUp((*num_repetitions)*2 + 11);

    //prints what is needed for the system flag
    for (int i = 0; i < *num_repetitions; i++){

        printMemory(&currMemory); //prints the memory sample at that time

        //if i is 0 there's no relative change
        if(i == 0){
            printf("   |o 0.00 (%.2f)\n", currMemory);
        }//end if 
        else{
            printf("   |");
            getMemoryGraphic(&prevMemory, &currMemory); //getting the string representing the change graphicaly 
            printf("* %.2f (%.2f)\n", currMemory - prevMemory, currMemory); //printing the graphical element
        }//end else

        //switch values
        prevMemory = currMemory;
        
        sleep(*delay); //'sleeps' for delay amount of time before taking another sample 

        //to get to the cpu percentage line
        goDown(*num_repetitions - i);

        calculateWorkandTotalJiffies(&currWorkJiffy,&currTotalJiffy); //getting the current values

        printCores(); //printing cores

        printTotalCpuUse(prevWorkJiffy, currWorkJiffy, prevTotalJiffy, currTotalJiffy); //calculating and printing the total cpu usage

        //goes down until we need to print the new cpu difference graphical output
        goDown(i);

        getCpuGraphic(&prevCpu, &currCpu);

        //swapping values
        prevWorkJiffy = currWorkJiffy;
        prevTotalJiffy = currTotalJiffy;
        prevCpu = currCpu;

        //going up to the memory section
        goUp(*num_repetitions + 2);

    }//end for 

    //goes to the bottom to end
    goDown(11 + *num_repetitions);

}//end systemGraphicFlag

// function to deal with only the system flag
void userFlag(int *num_repetitions, int *delay){

    int numUsers = 0;

    // printFirstLine(num_repetitions, delay);
    printFirstLine(num_repetitions, delay);

    printf("---------------------------------------\n");

    printf("### Sessions/users ###\n");
    
    for (int i = 0; i < *num_repetitions; i++){

        printSessionsUsers(&numUsers);

        printf("---------------------------------------\n");
        printSystemInfo();
        printf("---------------------------------------\n");

        sleep(*delay);

        //going back up to print a new session
        goUp(8 + numUsers);

    }//end for

    //going back down to get to bottom
    goDown(8 + numUsers);
    

}//end userFlag

// function to deal with no flags
void noFlags(int *num_repetitions, int *delay){

    double prevWorkJiffy = 0;
    double prevTotalJiffy = 0;
    double currWorkJiffy = 0;
    double currTotalJiffy = 0;
    int numUsers = 0;

    double currMemory = 0;

    printFirstLine(num_repetitions, delay); //prints the first line

    printf("---------------------------------------\n");

    printf("### Memory ### (Phys.Used/Tot -- Virtual Used/Tot)\n");
    
    //going down the number of samples
    goDown(*num_repetitions);

    printf("---------------------------------------\n");

    printf("### Sessions/users ###\n");

    printSessionsUsers(&numUsers); //printing users and sessions

    printf("---------------------------------------\n");

    calculateWorkandTotalJiffies(&currWorkJiffy,&currTotalJiffy); //getting the current values

    printCores();
    printTotalCpuUse(prevWorkJiffy, currWorkJiffy, prevTotalJiffy, currTotalJiffy); //calculating and printing the total cpu usage

    //swapping values
    prevWorkJiffy = currWorkJiffy;
    prevTotalJiffy = currTotalJiffy;

    printf("---------------------------------------\n");

    printSystemInfo(); //prints the system information

    printf("---------------------------------------\n");

    //going up to the memory section
    goUp(*num_repetitions + 13 + numUsers);

    //prints what is needed for the system flag
    for (int i = 0; i < *num_repetitions; i++){

        printMemory(&currMemory); //prints the memory sample at that time
        printf("\n");
        
        sleep(*delay); //'sleeps' for delay amount of time before taking another sample 

        //to get to the cpu percentage line
        goDown(*num_repetitions - i + 1);

        printSessionsUsers(&numUsers); //printing users and sessions

        printf("\n");

        calculateWorkandTotalJiffies(&currWorkJiffy,&currTotalJiffy); //getting the current values

        printCores();
        printTotalCpuUse(prevWorkJiffy, currWorkJiffy, prevTotalJiffy, currTotalJiffy); //calculating and printing the total cpu usage

        //swapping values
        prevWorkJiffy = currWorkJiffy;
        prevTotalJiffy = currTotalJiffy;

        //going up to the memory section
        goUp(*num_repetitions - i + 4 + numUsers);
        

    }//end for 

    //going down to the bottom
    goDown(numUsers + 13);


}//end noFlages

// function that deals with only the graphics flag
void graphicsFlag(int *num_repetitions, int *delay){

    double prevWorkJiffy = 0;
    double prevTotalJiffy = 0;
    double currWorkJiffy = 0;
    double currTotalJiffy = 0;
    int numUsers = 0;

    double currCpu = 0;
    double prevCpu = 0;

    double prevMemory = 0;
    double currMemory = 0;

    printFirstLine(num_repetitions, delay); //prints the first line

    printf("---------------------------------------\n");

    printf("### Memory ### (Phys.Used/Tot -- Virtual Used/Tot)\n");

    //creating the space needed for the memory section
    goDown(*num_repetitions);

    printf("---------------------------------------\n");

    printf("### Sessions/users ###\n");

    printSessionsUsers(&numUsers); //printing users and sessions

    printf("---------------------------------------\n");

    calculateWorkandTotalJiffies(&currWorkJiffy,&currTotalJiffy); //getting the current values

    printCores();
    printTotalCpuUse(prevWorkJiffy, currWorkJiffy, prevTotalJiffy, currTotalJiffy); //calculating and printing the total cpu usage
    
    //spaces for graph output
    goDown(*num_repetitions);

    //swapping values
    prevWorkJiffy = currWorkJiffy;
    prevTotalJiffy = currTotalJiffy;
    prevCpu = currCpu;

    printf("---------------------------------------\n");

    printSystemInfo(); //prints the system information

    printf("---------------------------------------\n");

    //going up to the memory section
    goUp((*num_repetitions)*2 + 13 + numUsers);

    //prints what is needed for the system flag
    for (int i = 0; i < *num_repetitions; i++){

        printMemory(&currMemory); //prints the memory sample at that time
        
        //if i is 0 there's no relative change
        if(i == 0){
            printf("   |o 0.00 (%.2f)\n", currMemory);
        }//end if 
        else{
            printf("   |");
            getMemoryGraphic(&prevMemory, &currMemory); //getting the string representing the change graphicaly 
            printf("* %.2f (%.2f)\n", currMemory - prevMemory, currMemory); //printing the graphical element
        }//end else

        //switch values
        prevMemory = currMemory;
        
        sleep(*delay); //'sleeps' for delay amount of time before taking another sample 

        //to get to the cpu percentage line
        goDown(*num_repetitions - i + 1);

        printSessionsUsers(&numUsers); //printing users and sessions

        printf("\n");

        calculateWorkandTotalJiffies(&currWorkJiffy,&currTotalJiffy); //getting the current values

        printCores();

        printTotalCpuUse(prevWorkJiffy, currWorkJiffy, prevTotalJiffy, currTotalJiffy); //calculating and printing the total cpu usage

        //going down to print the new graphical output for the difference
        goDown(i);

        getCpuGraphic(&prevCpu, &currCpu);

        //swapping values
        prevWorkJiffy = currWorkJiffy;
        prevTotalJiffy = currTotalJiffy;

        prevCpu = currCpu;

        //going up to the memory section
        goUp(*num_repetitions + 4 + numUsers);
        
    }//end for 

    //go to the bottom
    goDown(numUsers + 13 + *num_repetitions);
    
}//end graphicsFlag

//a helper to reduce lines
//goes down len lines in the output
void goDown(int len){
    for(int i = 0; i < len; i++){
        printf("\n");
    }//end for
}//end goDown

//a helper to reduce lines
//goes up len lines in the output
void goUp(int len){
    for(int i = 0; i < len; i++){
        printf("\033[F");
    }//end for
}//end goDown

//////////////////////////////////////////////////// SYSTEM INFORMATION ////////////////////////////////////////////////////

//This function prints the system information of the current user by
//accessing the utsname.h library
void printSystemInfo(){

    struct utsname unameData; //using the utsname struct to access information about the currect system
    uname(&unameData); //utilizing the uname function to include the information needed for unameData
    
    //in the following lines I'm accessing unameData to print the information needed
    printf("### System Information ###\n");
    printf("System name = %s\n", unameData.sysname);
    printf("Machine name = %s\n", unameData.nodename); 
    printf("Version = %s\n", unameData.version);
    printf("Release = %s\n", unameData.release);
    printf("Architecture = %s\n", unameData.machine); 

}//end printSystemInfo function

//////////////////////////////////////////////////// SESSIONS/USERS ////////////////////////////////////////////////////

//This function prints the sessions and users using
//the utmp.h library
void printSessionsUsers(int *numUser){

    struct utmp *utmp_info; //using the utmp struct to access info on the users currently on the machine
    setutent(); //rewinding to the begining of the utmp file
    utmp_info = getutent(); //reads the firstline which was just rewinded too and setting utmo_info to point to the struct returned
    int num_users = 0; //variable to count the number of users

    while(utmp_info){ //staying in the while loop for each user

        if(utmp_info -> ut_type == USER_PROCESS){
            printf("%9s        %s (%s)\n", utmp_info -> ut_user, utmp_info -> ut_line, utmp_info -> ut_host); //prints the current user we're looking at and the session
            num_users++; //adding to the number of users
        }//end if

        utmp_info = getutent(); //reading the next line
    }//end while

    endutent(); //closing the file
    *numUser = num_users;

}//end printSessionsUsers function

//////////////////////////////////////////////////// NUMBER OF CORES AND CPU USAGE ////////////////////////////////////////////////////

//This function returns the number of cores by
//accessing the sys/sysinfo.h library
int getNumCores(){
    return get_nprocs(); //get the number of processors available and returns it
}//end getNumCores

//This function prints the number of cores
void printCores(){
    printf("Number of cores: %d\n", getNumCores()); //prints the number of cores by using my getNumCores function
}//end printCores

//This function prints the current total cpu use 
void printTotalCpuUse(double frstWorkJiffy, double scndWorkJiffy, double frstTotalJiffy, double scndTotalJiffy){
    double totalCpuUsage = calculateCpuUsage(frstWorkJiffy, scndWorkJiffy, frstTotalJiffy, scndTotalJiffy);
    printf("total cpu use = %f%%\n", totalCpuUsage);
}//end printTotalCpuUse function

//This function accesses the /proc/stat file and sets the parameters accordingly
void calculateWorkandTotalJiffies(double *workJiffy, double *totalJiffy){
    FILE *procStatFile = fopen("/proc/stat", "r"); //opening the /proc/stat file
    char *cpuLine = malloc(sizeof(char *));
    char *arrLine = malloc(sizeof(char *));

    fscanf(procStatFile, "%[^\n]s", cpuLine); //reads the whole line and sets it to cpuLine
    arrLine = strtok(cpuLine, " "); //seperates cpuLine by spaces
    
    //for loop which itterates through the numbers in cpuLine
    for(int i = 0; arrLine != NULL; i++){
        
        int num = 0; 
        sscanf(arrLine, "%d", &num); //casting arrLine to int and setting it to num

        //checking for the first three numbers to add to workJiffy
        if(i <= 3 && i != 0){
            *workJiffy += num;
            // *totalJiffy += num;
        }//end if

        //if it's not 0 then add to totalJiffy
        if(i != 0){
            *totalJiffy += num;
        }//end else if

        arrLine = strtok(NULL, " "); //move on the the next char we're looking at

    }//end for

    free(cpuLine);
    free(arrLine);
    fclose(procStatFile);
}//end calculateWorkandTotalJiffies

//This function calculates the total CPU usage in percent
double calculateCpuUsage(double frstWorkJiffy, double scndWorkJiffy, double frstTotalJiffy, double scndTotalJiffy){
    double totalWorkJiffy = scndWorkJiffy - frstWorkJiffy; //calculating total work over the time period
    double totalJiffy = scndTotalJiffy - frstTotalJiffy; //calculating the total over the period
    return totalWorkJiffy/totalJiffy * 100; //returning the percentage over the period
}//end calculateCpuUsage

// function to get what to print for the graphic representation of cpu
void getCpuGraphic(double *prevCpu, double *currCpu){

    int num_lines = (int)(*currCpu - *prevCpu) + 3; //calculating the number of lines to print
    printf("\t");
    
    //printing the graphical output depending on num_lines
    for(int i = 0; i < num_lines; i++){
        printf("|");
    }//end for

    //printing the difference
    printf(" %.2f", *currCpu - *prevCpu);

}//end getMemoryGraphic

//////////////////////////////////////////////////// MEMORY ////////////////////////////////////////////////////

//This function returns the total virtual memory
//accessing sys/sysinfo.h
double getVirtualMemoryTotal(struct sysinfo memoryInfo){
    double virtualMemoryTotal = memoryInfo.totalram; //initializing the total usable main memory size
    
    //next we add other values so we don't have overflow 
    virtualMemoryTotal += memoryInfo.totalswap; //adding the total swap space size
    virtualMemoryTotal *= memoryInfo.mem_unit; //multiplying by the memory unit size in bites
    virtualMemoryTotal = virtualMemoryTotal / (1024*1024*1024); //converting to GB

    return virtualMemoryTotal;
}//end getVirtualMemoryTotal

//This function returns the virtual memory currently being used
//accessing sys/sysinfo.h
double getVirtualMemoryCurr(struct sysinfo memoryInfo){
    double currVirtualMemoryUsed = memoryInfo.totalram - memoryInfo.freeram; //calculating the memory being used by using the total ram and subtracting the ram which isn't currently being used
    
    //once again adding more values to reduce overflow
    currVirtualMemoryUsed += memoryInfo.totalswap - memoryInfo.freeswap; //similar to total virtual memory and the calculation is similar to the one previously done
    currVirtualMemoryUsed *= memoryInfo.mem_unit; //similar to before
    currVirtualMemoryUsed = currVirtualMemoryUsed / (1024*1024*1024); //converting to GB

    return currVirtualMemoryUsed;
}//end getVirtualMemoryTotal

//This function returns the total physical memory 
//accessing sys/sysinfo.h
double getPhysicalMemoryTotal(struct sysinfo memoryInfo){
    double physicalMemoryTotal = memoryInfo.totalram; //initializing the total uable main memory size
    
    //here we only need to multiply physical memory by the memory unit size 
    physicalMemoryTotal *= memoryInfo.mem_unit;
    physicalMemoryTotal = physicalMemoryTotal / (1024*1024*1024); //converting to GB

    return physicalMemoryTotal;
}//end getVirtualMemoryTotal

//This function returns the physical memory currently being used
//accessing sys/sysinfo.h
double getPhysicalMemoryCurr(struct sysinfo memoryInfo){
    double currPhyscialMemoryUsed = memoryInfo.totalram - memoryInfo.freeram; //calculating the memory being used by using the total ram and subtracting the ram which isn't currently being used
    
    //here we only need to multiply physical memory by the memory unit size 
    currPhyscialMemoryUsed *= memoryInfo.mem_unit;
    currPhyscialMemoryUsed = currPhyscialMemoryUsed / (1024*1024*1024); //converting to GB

    return currPhyscialMemoryUsed;
}//end getVirtualMemoryTotal

//This function prints the memory currently being used
//accessing sys/sysinfo.h
void printMemory(double *memory){

    struct sysinfo memoryInfo; //creating a struct to access memory information
    sysinfo(&memoryInfo); //populates memoryInfo with the information needed
    
    //calculating the total virtual memory 
    double virtualMemoryTotal = getVirtualMemoryTotal(memoryInfo);

    //calculating the current virtual memory being used
    double currVirtualMemoryUsed = getVirtualMemoryCurr(memoryInfo);

    //calculating the total physical memory 
    double physicalMemoryTotal = getPhysicalMemoryTotal(memoryInfo);

    //calculating the physical virtual memory being used
    double currPhyscialMemoryUsed = getPhysicalMemoryCurr(memoryInfo);

    // PRINTING INFO //
    printf("%.2f GB / %.2f GB -- %.2f GB / %.2f GB", currPhyscialMemoryUsed, physicalMemoryTotal, currVirtualMemoryUsed, virtualMemoryTotal); //printing the information needed

    *memory = (currVirtualMemoryUsed + currPhyscialMemoryUsed)/2;
}//end printMemory

// function to get what to print for the graphic representation of memory
void getMemoryGraphic(double *prevMem, double *currMem){

    //checking if the change is positive
    if(*currMem > *prevMem + 0.01){

        double temp = 0.01; //starts at 0.01 for rounding issues
        //while temp is less than the difference it prints the graphical output needed
        while(temp < *currMem - *prevMem){
            printf("#");
            temp += 0.01;
        }//end while

    }//end if
    else if(*currMem + 0.01 < *prevMem){ //checking if the change is negative

        double temp = 0.01; //starts at 0.01 for rounding issues
        //while temp is less than the difference it prints the graphical output needed
        while(temp < *prevMem - *currMem){
            printf(":");
            temp += 0.01;
        }//end while

    }//end else if

}//end getMemoryGraphic