#include <bits/stdc++.h>
using namespace std;
int mODe;
void find_wait_time_sjfp(vector<int> &wait_time, vector<int> &cpu_burst, vector<int> &arrival_time, vector<int> &response_time)
{
    int n = wait_time.size();
    // int service_time[n];
    vector<int> remaining_burst = cpu_burst;

    int processes_executed = 0;
    int time = 0;
    // int process_execution_time;
    vector<int> process_execution_time(n);
    int minimum_burst = INT_MAX;
    int current_shortest_process = 0;
    bool found = false;

    while (processes_executed != n)
    {
        /* code */
        for (int i = 0; i < n; i++)
        {
            if (arrival_time[i] <= time && remaining_burst[i] < minimum_burst && remaining_burst[i] > 0)
            {
                minimum_burst = remaining_burst[i];
                current_shortest_process = i;
                found = true;
            }
        }

        if (!found)
        {
            time++;
            continue;
        }
        if (response_time[current_shortest_process] == -1)
        {
            response_time[current_shortest_process] = time - arrival_time[current_shortest_process];
        }
        remaining_burst[current_shortest_process]--;

        minimum_burst = remaining_burst[current_shortest_process];

        if (minimum_burst == 0)
        {
            minimum_burst = INT_MAX;
            processes_executed++;
            found = false;

            process_execution_time[current_shortest_process] = time + 1;

            wait_time[current_shortest_process] = process_execution_time[current_shortest_process] - cpu_burst[current_shortest_process] - arrival_time[current_shortest_process];

            if (wait_time[current_shortest_process] < 0)
                wait_time[current_shortest_process] = 0;
        }

        time++;
    }
    if (mODe == 0)
    {

        cout << "----------------------------------------------------------------------" << endl;

        cout << "Shortest job first Premptive" << endl;
        vector<pair<int, pair<int, int> > > rq;

        for (int j = 0; j < n; j++)
        {
            rq.push_back(make_pair(arrival_time[j], make_pair(0, j)));
            rq.push_back(make_pair(process_execution_time[j], make_pair(1, j)));
        }
        sort(rq.begin(), rq.end());
        for (int j = 0; j < rq.size(); j++)
        {

            if (rq[j].second.first == 0)
            {
                cout << "Process " << rq[j].second.second +1<< " entering the ready queue" << endl;
            }
            else
            {
                cout << "Process " << rq[j].second.second +1<< " leaving the ready queue" << endl;
            }
        }
        cout << "----------------------------------------------------------------------" << endl;
    }
}

void find_turnaround_time_sjfp(vector<int> &turnaround_time, vector<int> &cpu_burst, vector<int> &wait_time)
{
    int n = cpu_burst.size();

    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = cpu_burst[i] + wait_time[i];
    }
}

vector<double> sjfp(vector<int> &cpu_burst, vector<int> &arrival_times, int mOde)
{
    mODe = mOde;
    int n = cpu_burst.size();
    vector<int> wait_time(n), turnaround_time(n), response_time(n, -1);
    // cout<<"here"<<endl;

    find_wait_time_sjfp(wait_time, cpu_burst, arrival_times, response_time);
    find_turnaround_time_sjfp(turnaround_time, cpu_burst, wait_time);

    double average_waiting_time = 0, average_turnaround_time = 0, average_response_time = 0;

    for (int i = 0; i < n; i++)
    {
        average_waiting_time += wait_time[i];
        average_turnaround_time += turnaround_time[i];
        average_response_time += response_time[i];
    }
    // cout<<average_waiting_time<<endl;
    average_response_time /= n;
    average_turnaround_time /= n;
    average_waiting_time /= n;

    vector<double> final(3);
    final[0] = average_waiting_time;
    final[1] = average_turnaround_time;
    final[2] = average_response_time;
    return final;
}