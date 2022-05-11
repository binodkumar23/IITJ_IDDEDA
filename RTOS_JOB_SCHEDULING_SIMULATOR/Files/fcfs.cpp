#include <bits/stdc++.h>
using namespace std;

int Mode;
void find_wait_time(vector<int> &wait_time, vector<int> &cpu_burst, vector<int> &arrival_time, vector<int> &response_time)
{
    int n = wait_time.size();
    // int service_time[n];
    response_time[0] = arrival_time[0];
    wait_time[0] = 0;
    if (Mode == 0)
    {
        cout << "----------------------------------------------------------------------" << endl;
        cout << "First come First serve ready queue" << endl;
        cout << "Process 1 entering the ready queue" << endl;
    }

    int start = 1;
    int end = 0;
    for (int i = 1; i < n; i++)
    {
        response_time[i] = response_time[i - 1] + cpu_burst[i - 1];
        for (; start < n; start++)
        {
            if (arrival_time[start] <= response_time[i])
            {
                if (Mode == 0)
                    cout << "Process " << start + 1 << " entering the ready queue" << endl;
            }
            else
                break;
        }

        if (Mode == 0)
            cout << "Process " << i << " leaving the ready queue" << endl;
        wait_time[i] = response_time[i] - arrival_time[i];

        if (wait_time[i] < 0)
        {
            wait_time[i] = 0;
            response_time[i] = arrival_time[i];
        }
        int time;
    }
    if (Mode == 0)
    {
        cout << "Process " << n << " leaving the ready queue" << endl;
        cout << "----------------------------------------------------------------------" << endl;
    }
}

void find_turnaround_time(vector<int> &turnaround_time, vector<int> &cpu_burst, vector<int> &wait_time)
{
    int n = cpu_burst.size();

    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = cpu_burst[i] + wait_time[i];
    }
}

vector<double> fcfs(vector<int> &cpu_burst, vector<int> &arrival_times, int mode)
{
    Mode = mode;
    int n = cpu_burst.size();
    vector<int> wait_time(n), turnaround_time(n), response_time(n);
    vector<vector<int> > table(n, vector<int>(2));
    for (int i = 0; i < n; i++)
    {
        table[i][1] = cpu_burst[i];
        table[i][0] = arrival_times[i];
        // table[i][2] = priorities[i];
    }
    sort(table.begin(), table.end());

    for (int i = 0; i < n; i++)
    {
        cpu_burst[i] = table[i][1];
        arrival_times[i] = table[i][0];
    }

    find_wait_time(wait_time, cpu_burst, arrival_times, response_time);
    // findTurnAroundTime(processes, n, bt, wt, tat);
    // for(int i=0;i<n;i++)
    // {
    //     cout<<wait_time[i]<<" ";
    // }
    // cout<<endl;
    find_turnaround_time(turnaround_time, cpu_burst, wait_time);

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
    final[2] = average_waiting_time;
    return final;
}