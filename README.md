# Introduction to system calls

## Task 1

Given a file, you need to reverse the contents of the file and store the result in a new file in the directory named “Assignment”.
The percentage of the file written should be printed on the console during file writing. The percentage of the file written should be overwritten each time (shouldn’t write multiple times).
The directory created should have read, write, and execute permissions for the user who created it. The new file created should have the read and write permissions for the user who created it.
The program will be tested on LARGE (>1GB) files which could be greater than RAM size.


The input file path would be given to you as an argument to your program: ```./a.out < input file path >```

The output file must be named:  ```1 < input file name >```

## Task 2

Write a program to reverse a specific portion of the file and store the result in a new file in the directory named “Assignment”.
The percentage of the file written should be printed on the console during file writing. The percentage of the file written should be overwritten each time (shouldn’t write multiple times).
The directory created should have read, write, and execute permissions for the user who created it. The new file created should have the read and write permissions for the user who created it.
The program will be tested on LARGE (>1GB) files which could be greater than RAM size.

The input file path would be given to you as an argument to your program along with the start and stop character, reverse the rest of the file and leave the portion of the file from the start character to the stop character untouched. In order to do this you will have to reverse the file in two parts, from 0 to the start character and from the end character to the end of the document. Assume the first character of the document to be 0:


The input file path would be given to you as an argument to your program: ```./a.out < input file path > start_char end_char```

The output file must be named: ```2 < input file name >```


## Task 3

1. Check the permissions for the two files and the directory.
2. Check whether the content in the new file are the reverse of the old file.

The input to this program has paths for newfile, oldfile, and the directory.
Example:
Directory is created: Yes
Whether file contents are reversed in newfile: Yes 
User has read permissions on newfile: Yes
User has write permission on newfile: Yes
User has execute permission on newfile: No 
Group has read permissions on newfile: No Group has write permission on newfile: No 
Group has execute permission on newfile: No 
Others has read permissions on newfile: No 
Others has write permission on newfile: No 
Others has execute permission on newfile: No

The above 9 should be printed for the old file and the directory too.
Path of newfile oldfile and directory will be passed as a command-line argument: ```./a.out < newfile >< oldfile >< directory >```
