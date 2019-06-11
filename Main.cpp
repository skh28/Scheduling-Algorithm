//Scott Ha
//CS 4310

#include <iostream>
#include <fstream> //for file I/O
#include <cstdlib> //for exit() and random number generator
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <sstream> //for string streams
#include "Tuple.h"
using namespace std;
#define switch 3
#define QUANTA 40

//Function declaration for scheduling algorithms
void FirstComeFirstServe(ifstream& input, string fileName);
void ShortestJobFirst(ifstream& input, string fileName);
void RoundRobbin(ifstream& input, string fileName, int quanta = QUANTA);
void Lottery(ifstream& input, string fileName);


int main() {

ifstream input;
// 4 test data files entered in as an array Files[]
string Files[] = {"testdata1.txt", "testdata2.txt", "testdata3.txt", "testdata4.txt"};
//length refers to the number of elements in each File
int length = sizeof(Files)/sizeof(Files[0]);

//Loop to read in data sets for each Scheduler
for(int i = 0; i < length; i++) {
      
	input.open(Files[i].c_str()); //convert string to c-string
    if(!input)
   {
      cerr << "Unable to open file \n"; //standard error stream
      exit(1);
   }
      FirstComeFirstServe(input, Files[i]);
      ShortestJobFirst(input, Files[i]);
      RoundRobbin(input, Files[i], 20);
      RoundRobbin(input, Files[i]);
      Lottery(input, Files[i]);
	  input.close();  
}
system("PAUSE");
return 0;
}

void FirstComeFirstServe(ifstream& input, string fileName) {
int cputime = 0;
int pid = 0;
int completiontime = 0;
ofstream csv; //for reading file
int lastindex = fileName.find_last_of("a");
string rawname = fileName.substr(31, lastindex); //finds the test number
int burstTime = 0;
int temp;
int counter = 0;

//File creator based on test data number
rawname = "FirstComeFirstServe" + rawname + ".txt";
csv.open(rawname.c_str()); 
csv << "CPUTime,PID,StartingBurstTime,EndingBurstTime,CompletionTime,\n"; //Output Columns
while(input >> pid >> burstTime >> temp) //while loop function for FCFS 
    {
      csv << cputime << ",";
      csv << pid << ",";
      csv << burstTime << ",";
      csv << "0,";
      cputime += burstTime;
      completiontime += cputime;
      csv << cputime << ",\n";
      cputime += switch;
      ++counter;
    }
csv << "Average Completion Time: " << ((double)completiontime)/counter << "\n";
csv.close();

input.clear(); //clearing eof bit
input.seekg(input.beg); //seek to beginning of file
}

void ShortestJobFirst(ifstream& input, string fileName)
{
vector<Tuple> processes;
Tuple* filler;
int cputime = 0;
int completiontime = 0;
ofstream csv;
int lastindex = fileName.find_last_of("a");
string rawname = fileName.substr(31, lastindex);
int pid = 0;
int burstTime = 0;
int temp;

rawname = "ShortestJobFirst" + rawname + ".txt";
csv.open(rawname.c_str());
//takes pid and burst time from file and creating tuple objects then storing them into a vector of tuples
while(input >> pid >> burstTime >> temp)
    {
      filler = new Tuple(pid, burstTime, temp);
      processes.push_back(*filler);
    }
csv << "CPUTime,PID,StartingBurstTime,EndingBurstTime,CompletionTime,\n";
//sort the vector of Tuples in non-descending order by Burst Time
sort(processes.begin(), processes.end());

for(int i = 0; i < processes.size(); i++)
    {
      csv << cputime << ",";
      csv << (processes[i]).pid << ",";
      csv << (processes[i]).burst << ",";
      csv << "0,";
      cputime += (processes[i]).burst;
      completiontime += cputime;
      csv << cputime << ",\n";
      cputime += switch;
    }

csv << "Average Completion Time: " << ((double)completiontime)/processes.size() << "\n";
csv.close();

input.clear(); //clearing eof bit
input.seekg(input.beg); // seek to beginning of file

}

void RoundRobbin(ifstream& input, string fileName, int quanta)
{
vector<Tuple> processes;
Tuple* filler;
int lastindex = fileName.find_last_of("a");
int firstindex = fileName.find_first_of(".");
string rawname = fileName.substr(31, lastindex);
int i = 0;
int pid = 0;
int burstTime = 0;
int temp;
int cputime = 0;
int completiontime = 0;
int length;
int initial;
long long sum = 0;
ofstream csv;
ostringstream str;
str << quanta;
string s = str.str();
bool flag = true;

rawname = "RoundRobbin" + s + "quanta" + rawname + ".txt";
csv.open(rawname.c_str());
//takes pid and burst time from file and creating tuple objects then storing them into a vector of tuples
while(input >> pid >> burstTime >> temp)
    {
      filler = new Tuple(pid, burstTime, temp);
      processes.push_back(*filler);
    }
csv << "CPUTime,PID,StartingBurstTime,EndingBurstTime,CompletionTime,\n";
length = processes.size();
initial = processes.size();
while(flag)
    {
      csv << cputime << ",";
      csv << (processes[i]).pid << ",";
      csv << (processes[i]).burst << ",";
      if(((processes[i]).burst - quanta) < 0)
   {
      completiontime = cputime + processes[i].burst;
      sum += completiontime;
      csv << "0" << ",";
      csv << completiontime << ",\n";
      cputime = cputime + processes[i].burst + switch;
      processes.erase(processes.begin() + i);
      if(i >= 0)
        --i;
   }
      else
   {
      processes[i].burst -= quanta; //Decrease burst time of process by quantum
      csv << processes[i].burst << ",";
      csv << "-" << ",\n";
      cputime = cputime + quanta + switch;
   }
      ++i;
      if(processes.size() == 0)
   flag = false;
      if(i == processes.size())
   i = 0;
    }
csv << "Average Completion Time: " << sum/(double)initial << "\n";
csv.close();

input.clear(); //clearing eof bit
input.seekg(input.beg); // seek to beginning of file
}

void Lottery(ifstream& input, string fileName)
{
vector<Tuple> processes;
Tuple* filler;
int lastindex = fileName.find_last_of("a");
string rawname = fileName.substr(31, lastindex);
int i = 0;
int pid = 0;
int burstTime = 0;
int priority;
int cputime = 0;
int completiontime = 0;
int totalPrioritySum = 0;
int sum=0;
ofstream csv;
int initial;
bool flag = true;
int ticket;
srand(time(NULL));

rawname = "Lottery" + rawname + ".txt";
csv.open(rawname.c_str());
//takes pid and burst time from file and creating tuple objects then storing them into a vector of tuples
while(input >> pid >> burstTime >> priority)
    {
      filler = new Tuple(pid, burstTime, priority);
      processes.push_back(*filler);
      totalPrioritySum += (*filler).priority;
    }

ticket = rand() % totalPrioritySum + 1; //random ticket number generator
csv << "CPUTime,PID,StartingBurstTime,EndingBurstTime,CompletionTime,\n";
initial = processes.size();

while(flag)
    {
      ticket -= (processes[i]).priority;
      if(ticket > 0)
   {
      ++i;
   }
      else
   {
      ticket = rand() % totalPrioritySum + 1;
      csv << cputime << ",";
      csv << (processes[i]).pid << ",";
      csv << (processes[i]).burst << ",";

      if(((processes[i]).burst - QUANTA) < 0)
        {
          completiontime = cputime + processes[i].burst;
          sum += completiontime;
          csv << "0" << ",";
          csv << completiontime << ",\n";
          cputime = cputime + processes[i].burst + switch;
          totalPrioritySum -= processes[i].priority;
          processes.erase(processes.begin() + i);
        }
      else
        {
          processes[i].burst -= QUANTA;
          csv << processes[i].burst << ",";
          csv << "-" << ",\n";
          cputime = cputime + QUANTA + switch;
        }
      i = 0;
   }
      if(processes.size() == 0)
   flag = false;
      if(i == processes.size())
   i = 0;
    }
csv << "Average Completion Time: " << ((double)sum)/initial << "\n";
csv.close();

input.clear(); //clearing eof bit
input.seekg(input.beg); // seek to beginning of file

}
