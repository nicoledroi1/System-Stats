# System-Stats
C program to to monitor different resources

**How to run/use this program:**

This program can be used through linux (run through a virtual machine if one doesn't have imediate access to linux). It can be accessed through the terminal by using gcc and accessing the file outputted to run it. 

A couple notes: the terminal must be open far enough for the first line which is printed to be visible otherwise the output will write over itself, the flags accepted are as provided in the assignment information, the flags and values can be inputed in any order (E.g., –graphics 10 —system 3, -g 9 8, 1 —user, etc.), the flags must start with two of these symbols ‘--’ (special case is -g), if only one number is provided then it will be considered the number of sessions and the order in which the numbers are inputed by the user are important because the first number will be the number of sessions while the second is the delay time in seconds. 

**Overview of functions:**

*Note these are overviews of the functions. There are comments provided in the code to clarify what is being done in each step*

main function:

* The purpose of this function is 1) to deal with arguments that are not valid 2) to call the right functions depending on the user's input.
* Accesses setValues to set the variables to call the functions properly.
* Has two parameters 1) argc - the number of arguments the user provided 2) argv - an array storing the arguments that the user provided (also the name of the file, but it’s not used).

setValues:

* The purpose of this function is to set the variables created in the main function.
* Has six parameters 1) num_repetitions - a pointer to the variable to be pointed to the number of samples 2) delay - a pointer to the variable to be pointed to the delay in seconds 3) arg1 - a pointer to the variable to be pointed to the first argument 4) - a pointer to the variable to be pointed to the second argument 5) argv - the array of arguments provided by the user 6) argc - the number of arguments provided by the user.

printFirstLine:

* A function that’s used to print the common first line that every function has.
* Has two parameters 1) num_repetitions - a pointer to the variable to be pointed to the number of samples 2) delay - a pointer to the variable to be pointed to the delay in seconds.
    * Both of these parameters are needed to print in the first line.
* Calls goUp and goDown to alter the output as wanted.

systemFlag:

* The goal of this function is to print the information needed to display what the system flag displays. It displays the memory information (by accessing printMemory), cores and cpu usage (by accessing calculateWorkandTotalJiffies, printCores, printTotalCpuUse) and system information (by accessing printSystemInfo).
* Has two parameters 1) num_repetitions - a pointer to the variable to be pointed to the number of samples 2) delay - a pointer to the variable to be pointed to the delay in seconds
    * Both of these parameters are crucial and needed to properly display the information based on the user's wants.
* Calls goUp and goDown to alter the output as wanted.

systemGraphicFlag:

* The goal of this function is to print the information needed to display what the system along with the graphics flag displays. It displays the memory information (by accessing printMemory), cores and cpu usage (by accessing calculateWorkandTotalJiffies, printCores, printTotalCpuUse) and system information (by accessing printSystemInfo). Graphics wise for memory it accesses getMemoryGraphic and for cores getCpuGraphic.
* Has two parameters 1) num_repetitions - a pointer to the variable to be pointed to the number of samples 2) delay - a pointer to the variable to be pointed to the delay in seconds.
    * Both of these parameters are crucial and needed to properly display the information based on the user's wants.
* Calls goUp and goDown to alter the output as wanted.

userFlag:

* The goal of this function is to print the information needed to display what the user flag displays. It displays the sessions and users currently on the machine (by accessing printSessionsUsers) and system information (by accessing printSystemInfo).
* Has two parameters 1) num_repetitions - a pointer to the variable to be pointed to the number of samples 2) delay - a pointer to the variable to be pointed to the delay in seconds.
    * Both of these parameters are crucial and needed to properly display the information based on the user's wants.
* Calls goUp and goDown to alter the output as wanted.

noFlag:

* The goal of this function is to print the information needed to display what happens if the user does not provide any flags.It displays the memory information (by accessing printMemory), cores and cpu usage (by accessing calculateWorkandTotalJiffies, printCores, printTotalCpuUse), sessions and users currently on the machine (by accessing printSessionsUsers) and system information (by accessing printSystemInfo).
    * Note there are no flags so there’s no graphics. Graphics are printed only if the graphics flag is provided.
* Has two parameters 1) num_repetitions - a pointer to the variable to be pointed to the number of samples 2) delay - a pointer to the variable to be pointed to the delay in seconds.
    * Both of these parameters are crucial and needed to properly display the information based on the user's wants.
* Calls goUp and goDown to alter the output as wanted.

graphicsFlag:

* The goal of this function is to print the information needed to display what happens if the user provides only the graphics flags.It displays the memory information (by accessing printMemory), cores and cpu usage (by accessing calculateWorkandTotalJiffies, printCores, printTotalCpuUse), sessions and users currently on the machine (by accessing printSessionsUsers) and system information (by accessing printSystemInfo). Graphics wise for memory it accesses getMemoryGraphic and for cores getCpuGraphic.
* Has two parameters 1) num_repetitions - a pointer to the variable to be pointed to the number of samples 2) delay - a pointer to the variable to be pointed to the delay in seconds.
    * Both of these parameters are crucial and needed to properly display the information based on the user's wants.
* Calls goUp and goDown to alter the output as wanted.

goDown:

* The goal of this function is to go down the output depending on the amount passed in the parameter.
* There is one parameter for this function. len - an integer that stores how far the cursor should move down.

goUp:

* The goal of this function is to go up the output depending on the amount passed in the parameter.
* There is one parameter for this function. len - an integer that stores how far the cursor should move up.

printSystemInfo:

* The goal of this function is to print the system information needed to print in the system info section of the output. 
* Uses the utsname.h library to access the utsname struct. Through this struct and the uname function we receive all the information needed to print the different aspects of the system information.

printSessionsUser:

* The goal of this function is to print the sessions of each user that is using the machine currently being used.
* Uses the utmp.h library to access the utmp struct. Through this struct and the utmp file we receive the information needed to print the users and their corresponding sessions. 
* This function has one parameter. numUser - a pointer to an integer which stores the number of users connected.
    * In this function we calculate the number of users currently connected. This is used mainly for dealing with output display.

getNumCores:

* The purpose of this function is to return the number of cores. 
* Uses the sys/sysinfo.h library to use the get_nprocs function to access the number of cores.

printCores: 

* This function is used to print the number of cores.
* Calls getNumCores to get the number of cores needed to print.

printTotalCpuUse:

* The goal of this function is to calculate and print the total cpu usage in percent.
    * Uses the calculateCpuUsage function to calculate the percent of cpu usage.
* Has four parameters 1) frstWorkJiffy - a double which stores the value of the first work jiffy 2) scndWorkJiffy - a double which stores the value of the second work jiffy 3) frstTotalJiffy - a double which stores the value of the first total jiffy 4) scndTotalJiffy - a double which stores the value of the second total jiffy.

calculateWorkandTotalJiffies:

* The purpose of this function is to read from the /proc/stat file and acquire the work jiffy value and the total value.
* Has two parameters 1) workJiffy - a pointer to the work jiffy that we’re setting the value too 2) totalJiffy - a pointer to the total jiffy that we’re setting the value too.

calculateWorkandTotalJiffies:

* This function calculates and returns the total cpu usage in percent depending on the parameters passed.
* This function has four parameters 1) frstWorkJiffy - a double which stores the value of the first work jiffy 2) scndWorkJiffy - a double which stores the value of the second work jiffy 3) frstTotalJiffy - a double which stores the value of the first total jiffy 4) scndTotalJiffy - a double which stores the value of the second total jiffy.

getCpuGraphic:

* This function is used to print the graphical elements of the cpu usage differences.
* Has two parameters 1) prevCpu - a pointer to a double that stores the previous cpu percentage 2) curr Cpu - a pointer to a double that stores the current cpu percentage.

getVirtualMemoryTotal:

* The purpose of this function is to return and calculate the total virtual memory in the machine. 
* Accesses the sys/info.h library to use the struct sysinfo.
* Has one parameter. memoryInfo - a sysinfo struct that holds the information needed for the calculations in this function.

getVirtualMemoryCurr:

* The purpose of this function is to return and calculate the current virtual memory being used in the machine. 
* Accesses the sys/info.h library to use the struct sysinfo.
* Has one parameter. memoryInfo - a sysinfo struct that holds the information needed for the calculations in this function.

getPhysicalMemoryTotal:

* The purpose of this function is to return and calculate the total physical memory in the machine. 
* Accesses the sys/info.h library to use the struct sysinfo.
* Has one parameter. memoryInfo - a sysinfo struct that holds the information needed for the calculations in this function.

getPhysicalMemoryCurr:

* The purpose of this function is to return and calculate the current physical memory being used in the machine. 
* Accesses the sys/info.h library to use the struct sysinfo.
* Has one parameter. memoryInfo - a sysinfo struct that holds the information needed for the calculations in this function.

printMemory:

* The purpose of this function is to print the memory information needed for the memory lines being printed to the terminal.
* Has one parameter. memory - a pointer to a double that stores the average memory. 
* Uses the sys/sysinfo.h library to use the sysinfo struct and initialize it using sysinfo.
* Calls getVirtualMemoryTotal, getVirtualMemoryCurr, getPhysicalMemoryTotal and getPhysicalMemoryCurr to get the respective values.
* This function also calculates the average memory at that time.

getMemoryGraphic:

* This function is used to print the graphical output for memory depending on the parameters passed to the function.
* Has two parameters 1) prevMem - a double pointer that points to the value of the previous memory value 2)  currMem - a double pointer that points to the value of the current memory value.
