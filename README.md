## bashmyshell
A lofty attempt to recreate some linux utility programs on my own. Effectively my own recreation of coreutils. The executable names and functionality will likely match, but my intention is to avoid influences from coreutils when it comes to implemention.

#### configure
Bash script which outputs the project Makefile. Two variables in the script (FIRST and SECOND) are base64 encoded portions of the desired Makefile. The script then reads from the Targets file and generates the make variables for each target. Template for the Makefile exists in Makefile.template. The variables are seperated by the ### section.  

#### targets
This file describes each of the executables and their opject file dependencies. Target and dependencies must be colon seperated without space. Problem: this Target system prevents duplicate executable names regardless of location.  
New executables can be added by appending the above info to the Targets file and running the configure scripts.
