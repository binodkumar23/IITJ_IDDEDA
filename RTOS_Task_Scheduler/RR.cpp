#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <string>
#include<iomanip>
using namespace std;

// task object
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
    // time quantum
    int time_quantum;

    // array to store number of process objects
    struct task task_list[10000];

    // open input file and read input values
    ifstream input_file("input/rr_input.txt");
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
            string s_time_quantum;
            getline(ss, s_num_task, ' ');
            num_task = stoi(s_num_task);
            getline(ss, s_time_quantum, ' ');
            time_quantum = stoi(s_time_quantum);
            
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

    // queue to store all tasks whose arrival time > current time
    queue<struct task> q;
    for(int i=0; i<num_task; i++){
        q.push(task_list[i]);
    }

    // queue to store taks whose arrival time is < current time and are not executed completetly
    queue<struct task> ready_q;
    // queue to store completed tasks
    queue<struct task> completed_q;

    // counter to track number of completed tasks
    int task_completed = 0;

    // counter for timer
    int time = 0;

    // vector for timeline
    vector<int> timeline;

    // run following loop until all tasks are not completed
    while(task_completed != num_task){
        // remove all tasks from waiting queue whose arrival time <= current time and move them to ready queue
        while(q.size()>0 && q.front().arrival_time <= time){
            struct task temp_ready_task = q.front();
            q.pop();
            ready_q.push(temp_ready_task);
        }

        // pop first task of ready queue and execute it for time = min(time_quantum, remaining_burst)
        struct task curr_task = ready_q.front();
        ready_q.pop();
        if(curr_task.burst_time == curr_task.burst_remaining){
            curr_task.start_time = time;
        }
        int temp_burst_time = curr_task.burst_remaining;
        for(int i=0; i<min(temp_burst_time, time_quantum); i++){
            timeline.push_back(curr_task.pid);
            curr_task.burst_remaining--;
            time++;
        }
        
        // check whether remaining burst is = 0 or not
        // if burst time remaining = 0 => task is completed
        // else add this task to ready queue again
        if(curr_task.burst_remaining == 0){
            curr_task.finish_time = time;
            completed_q.push(curr_task);
            task_completed++;
        }
        else{
            while(q.size()>0 && q.front().arrival_time <= time){
                struct task temp_ready_task = q.front();
                q.pop();
                ready_q.push(temp_ready_task);
            }
            ready_q.push(curr_task);
        }
        
    }

    // create output files
    // rr_output.txt => summary of execution
    // rr_timeline.txt => timeline
    ofstream output_file("output/rr_output.txt");
    ofstream timeline_file("output/rr_timeline.txt");
    int colWidth=20;
    output_file << setfill('*') << setw(7*colWidth) << "*" << endl;
    output_file << setfill(' ') << fixed;
    output_file << setw(colWidth) << "Process ID" << setw(colWidth) << "Arrival time" << setw(colWidth) << "Burst time" << setw(colWidth) << "Start time" << setw(colWidth) << "Completion time" << setw(colWidth) << "Turnaround time" << setw(colWidth) << "Waiting time"<< endl; 
    output_file << setfill('*') << setw(7*colWidth) << "*" << endl; 
    output_file << setfill(' ') << fixed; 
    while(completed_q.size()>0){
        struct task curr = completed_q.front();
        curr.turnaround_time = curr.finish_time - curr.arrival_time;
        curr.waiting_time = curr.turnaround_time - curr.burst_time;
        output_file << setw(colWidth) << curr.pid << setw(colWidth) << curr.arrival_time << setw(colWidth) << curr.burst_time << setw(colWidth) << curr.start_time << setw(colWidth) << curr.finish_time << setw(colWidth) << curr.turnaround_time << setw(colWidth) << curr.waiting_time << endl;
        output_file << setfill('-') << setw(7*colWidth) << "-" << endl; 
        output_file << setfill(' ') << fixed; 
        completed_q.pop();
    }
    output_file << endl;
    output_file << "Task Summary" << endl;
    for(int i=0; i<timeline.size(); i++){
        output_file << "For Time: " << i << " - " << i+1 << " ; Task running is : " << timeline[i] << endl;
        timeline_file << timeline[i] << " ";
    }
    // close output files
    output_file.close();
    timeline_file.close();
}