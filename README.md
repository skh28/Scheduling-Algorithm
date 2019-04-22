# Scheduling-Algorithm
This Project implements four OS scheduling algorithms.
There are 2 Source files: Main.cpp, Tuple.cpp and 1 Header file: Tuple.h
Since the files are read from my desktop, when running the program from a different computer, the source of the file names will have to be changed.
In the Main class Line 29 "C:\\Users\\Scott\\Desktop\\testdata1.txt", etc.. will have to be changed to the respected location of the test data file. 
An alteration must be made pertaining to the value of the first input of the "substr(31, )" command (Line 59)
Since the length of the string being read in will be changed based on the location of test data files, the number "31" will have to be changed to the value which corresponds to the length of the string of the new location data set, up to the numbered set you are testing. 
For example "C:\Users\John\testdata1.txt" will make the change to "substr(22, )"
This will be done for each of the four classes (Lines 59, 95, 138, 206)
Also before running, change the "rawname" for each class to the desired output location (Lines 65, 100, 154, 221)
Once completed, simply run the program and the output will be a CSV file of the chosen location. 
There will be 20 files, 4 for each algorithm. 
