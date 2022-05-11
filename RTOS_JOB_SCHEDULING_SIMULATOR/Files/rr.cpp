#include <bits/stdc++.h>
using namespace std;
int mOdE_;
void find_wait_time_rr(vector<int> &wait_time, vector<int> &cpu_burst, vector<int> &arrival_time, vector<int> &response_time, queue<pair<int, pair<int, int> > > &q, int quantum)
{
    int n = wait_time.size();
    vector<int> process_completion_time(n);
    int time = 0;
    int flag = 0;
    while (q.size() != 0)
    {
        if (flag == q.size())
        {

            // cout << flag << endl;
            flag = 0;
            time++;
        }
        pair<int, pair<int, int> > current = q.front();
        q.pop();
        // cout<<time<<" "<<current.first<<" "<<current.second.second<<" "<<current.second.first<<endl;
        if (current.second.second <= time)
        {
            if (current.second.first == cpu_burst[current.first])
            {
                response_time[current.first] = time - current.second.second;
            }
            if (current.second.first <= quantum && current.second.first > 0)
            {
                time += current.second.first;
                process_completion_time[current.first] = time;
                wait_time[current.first] += (time - cpu_burst[current.first] - arrival_time[current.first]);
            }
            else if (current.second.first > quantum)
            {
                time += quantum;
                current.second.first -= quantum;
                q.push(current);
            }
        }
        else
        {
            flag++;
            q.push(current);
            // time++;
        }
    }
    if (mOdE_ == 0)
    {
        cout << "----------------------------------------------------------------------" << endl;

        cout << "The Round Robin scheduler" << endl;
        vector<pair<int, pair<int, int> > > rq;

        for (int j = 0; j < n; j++)
        {
            rq.push_back(make_pair(arrival_time[j], make_pair(0, j)));
            rq.push_back(make_pair(process_completion_time[j], make_pair(1, j)));
        }
        sort(rq.begin(), rq.end());
        for (int j = 0; j < rq.size(); j++)
        {

            if (rq[j].second.first == 0)
            {
                cout << "Process " << rq[j].second.second+ 1<< " entering the ready queue" << endl;
            }
            else
            {
                cout << "Process " << rq[j].second.second + 1<< " leaving the ready queue" << endl;
            }
        }
        cout << "----------------------------------------------------------------------" << endl;
    }
}

void find_turnaround_time_rr(vector<int> &turnaround_time, vector<int> &cpu_burst, vector<int> &wait_time)
{
    int n = cpu_burst.size();

    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = cpu_burst[i] + wait_time[i];
    }
}

vector<double> rr(vector<int> &cpu_burst, vector<int> &arrival_times, int quantum, int mOdE)
{
    mOdE_ = mOdE;
    // int quantum = 2;
    int n = cpu_burst.size();
    vector<int> wait_time(n), turnaround_time(n), response_time(n, -1);

    queue<pair<int, pair<int, int> > > q;
    for (int i = 0; i < n; i++)
    {
        q.push(make_pair(i, make_pair(cpu_burst[i], arrival_times[i])));
    }
    // cout << "here" << endl;
    find_wait_time_rr(wait_time, cpu_burst, arrival_times, response_time, q, quantum);
    find_turnaround_time_rr(turnaround_time, cpu_burst, wait_time);
    // cout << "here" << endl;
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