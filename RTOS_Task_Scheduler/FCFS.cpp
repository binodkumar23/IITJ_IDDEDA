#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <string>
#include<iomanip>
using namespace std;

// task structure
struct task {
    int pid;
    int arrival_time;
    int burst_time;
    int burst_remaining;

    int start_time;
    int finish_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

// function to sort set of tasks according in the increasing order of arrival time
bool sort_by_arrival_time(task t1, task t2) 
{ 
    return t1.arrival_time < t2.arrival_time;
}

// main function
int main(){
    // read input from rr_input.txt
    // total number of tasks to be schedule 
    int num_task;

    // array to store number of process objects
    struct task task_list[10000];

    // open input file and read input values
    ifstream input_file("input/fcfs_input.txt");
    if(!input_file.is_open()){
        cout<<"File failed to open"<<endl;
        return 0;
    }
    int line_number = 0;
    string line;
    while(getline(input_file, line)){
        stringstream ss(line);
        if(line_number==0){
            string s_num_task;
            getline(ss, s_num_task, ' ');
            num_task = stoi(s_num_task);
        }
        else{
            string s_arrival_time;
            string s_burst_time;
            getline(ss, s_arrival_time, ' ');
            task_list[line_number-1].arrival_time = stoi(s_arrival_time);
            getline(ss, s_burst_time, ' ');
            task_list[line_number-1].burst_time = stoi(s_burst_time);
            task_list[line_number-1].burst_remaining = task_list[line_number-1].burst_time;
            task_list[line_number-1].pid = line_number;
        }
        line_number++;
    }
    // close input file
    input_file.close();

    // sort tasks in the increasing order of arrival time
    sort(task_list, task_list+num_task, sort_by_arrival_time);

    // counter for timer
    int time = 0;

    // create output files
    // fcfs_output.txt => summary of execution
    // fcfs_timeline.txt => timeline
    ofstream output_file("output/fcfs_output.txt");
    ofstream timeline_file("output/fcfs_timeline.txt");
    int colWidth=20;
    output_file << setfill('*') << setw(7*colWidth) << "*" << endl;
    output_file << setfill(' ') << fixed;
    output_file << setw(colWidth) << "Process ID" << setw(colWidth) << "Arrival time" << setw(colWidth) << "Burst time" << setw(colWidth) << "Start time" << setw(colWidth) << "Completion time" << setw(colWidth) << "Turnaround time" << setw(colWidth) << "Waiting time"<< endl; 
    output_file << setfill('*') << setw(7*colWidth) << "*" << endl; 
    output_file << setfill(' ') << fixed;

    // vector for timeline
    vector<int> timeline;
    for(int i=0; i<num_task; i++){
        // take ith task to execute
        struct task curr = task_list[i];
        curr.start_time = time;

        // execute this task till it completed
        while(curr.burst_remaining--){
            timeline_file << curr.pid << " ";
            timeline.push_back(curr.pid);
            time++;
        }

        // update its finish time
        curr.finish_time = time;

        // compute turnaround and waiting time
        curr.turnaround_time = curr.finish_time - curr.arrival_time;
        curr.waiting_time = curr.turnaround_time - curr.burst_time;

        // write result to output file
        output_file << setw(colWidth) << curr.pid << setw(colWidth) << curr.arrival_time << setw(colWidth) << curr.burst_time << setw(colWidth) << curr.start_time << setw(colWidth) << curr.finish_time << setw(colWidth) << curr.turnaround_time << setw(colWidth) << curr.waiting_time << endl; 

        output_file << setfill('-') << setw(7*colWidth) << "-" << endl; 
        output_file << setfill(' ') << fixed;
    }

    output_file << endl;
    output_file << "Task Summary" << endl;

    for(int i=0; i<timeline.size(); i++){
        output_file << "For Time: " << i << " - " << i+1 << " ; Task running is : " << timeline[i] << endl;
    }
    
    // close output files
    output_file.close();
    timeline_file.close();
}