#include <bits/stdc++.h>
using namespace std;

vector<double> sjfnp(vector<int> &cpu_burst, vector<int> &arrival_times, int mode)
{

    int n = cpu_burst.size();
    vector<int> wait_time(n, 0), turnaround_time(n, 0), response_time(n), completion_time(n, 0);
    vector<vector<int> > table(n, vector<int>(6));

    table[0][0] = arrival_times[0];
    table[0][1] = cpu_burst[0];
    table[0][5] = 0;
    for (int i = 1; i < n; i++)
    {
        table[i][0] = arrival_times[i];
        table[i][1] = cpu_burst[i];
        table[i][2] = completion_time[i];
        table[i][3] = wait_time[i];
        table[i][4] = turnaround_time[i];
        table[i][5] = i;
    }
    sort(table.begin(), table.end());
    table[0][2] = table[0][1] + table[0][0];
    table[0][4] = table[0][2] - table[0][0];
    table[0][3] = table[0][4] - table[0][1];

    for (int i = 1; i < n; i++)
    {
        int ct = table[i - 1][2];
        int burst = table[i][1];
        int row = i;
        bool inside = false;
        for (int j = i; j < n; j++)
        {
            if (ct >= table[j][0] && burst >= table[j][1])
            {
                burst = table[j][1];
                row = j;
            }
        }
        if (ct < table[i][0])
            ct = table[i][0];
        table[row][2] = ct + table[row][1];
        table[row][4] = table[row][2] - table[row][0];
        table[row][3] = table[row][4] - table[row][1];

        for (int k = 0; k < 5; k++)
        {
            swap(table[row][k], table[i][k]);
        }
        // completion_time[i]=wait_time[i]+cpu_burst[i]-;
    }
    if (mode == 0)
    {
        cout << "----------------------------------------------------------------------" << endl;

        cout << "Shortest job first Non premptive" << endl;
        vector<pair<int, pair<int, int> > > rq;

        for (int j = 0; j < n; j++)
        {
            rq.push_back(make_pair(table[j][0], make_pair(0, table[j][5])));
            rq.push_back(make_pair(table[j][3], make_pair(1, table[j][5])));
        }
        sort(rq.begin(), rq.end());
        for (int j = 0; j < rq.size(); j++)
        {

            if (rq[j].second.first == 0)
            {
                cout << "Process " << rq[j].second.second+1 << " entering the ready queue" << endl;
            }
            else
            {
                cout << "Process " << rq[j].second.second+1 << " leaving the ready queue" << endl;
            }
        }
        cout << "----------------------------------------------------------------------" << endl;
    }

    double average_waiting_time = 0, average_turnaround_time = 0, average_response_time = 0;

    for (int i = 0; i < n; i++)
    {
        average_waiting_time += table[i][3];
        average_turnaround_time += table[i][4];
        // average_response_time+=response_time[i];
    }
    // cout<<average_turnaround_time<<" "<<average_waiting_time<<endl;
    // average_response_time/=n;
    average_turnaround_time /= n;
    average_waiting_time /= n;

    vector<double> final(3);
    final[0] = average_waiting_time;
    final[1] = average_turnaround_time;
    final[2] = average_waiting_time;
    return final;
}