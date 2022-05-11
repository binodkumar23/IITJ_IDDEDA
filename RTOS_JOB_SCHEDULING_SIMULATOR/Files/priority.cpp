#include <bits/stdc++.h>
using namespace std;
int MOde_;
class compareBurst
{
public:
    int operator()(pair<int, pair<int, pair<int, int> > > const &p1, pair<int, pair<int, pair<int, int> > > const &p2)
    {
        return p1.second.second.first > p2.second.second.first;
    }
};

void find_wait_time_priority(vector<int> &wait_time, vector<int> &cpu_burst, vector<int> &arrival_time, vector<int> &response_time, vector<int> &priorities)
{
    int time = 0;
    priority_queue<pair<int, pair<int, pair<int, int> > >, vector<pair<int, pair<int, pair<int, int> > > >, compareBurst> pq;
    vector<int> process_completeion_time(cpu_burst.size());
    vector<pair<int, pair<int, pair<int, int> > > > process;

    int n = arrival_time.size();
    for (int i = 0; i < n; i++)
    {
        process.push_back(make_pair(priorities[i], make_pair(arrival_time[i], make_pair(i, cpu_burst[i]))));
    }

    pq.push(process[0]);

    // cout<<n<<endl;
    int i = 1;
    int flag=0;
    while (pq.size() > 0)
    {
        
        pair<int, pair<int, pair<int, int> > > top = pq.top();
        pq.pop();
        // cout << time << " " << top.first << " " << top.second.first << " " << top.second.second.first << " " << top.second.second.second << endl;
        wait_time[top.second.second.first] = time - top.second.first;
        time += top.second.second.second;
        process_completeion_time[top.second.second.first] = time;
        while (i < n && process[i].second.first <= time)
        {
            pq.push(process[i]);
            i++;
        }
        if (pq.size() == 0 && i < n)
        {
            int min = INT_MAX;
            int idx = -1;
            for (int j = 0; j < n; j++)
            {
                if (arrival_time[j] > time && arrival_time[j] < min)
                {
                    idx = j;
                    time = arrival_time[j];
                }
            }
            pq.push(make_pair(idx, make_pair(arrival_time[idx], make_pair(priorities[idx], cpu_burst[idx]))));
        }

        // cout<<pq.size()<<" size"<<endl;
    }
    // cout << endl;
    if (MOde_ == 0)     
    {
        cout << "----------------------------------------------------------------------" << endl;

        cout << "Priority Scheduling" << endl;
        vector<pair<int, pair<int, int> > > rq;

        for (int j = 0; j < n; j++)
        {
            rq.push_back(make_pair(arrival_time[j], make_pair(0, j)));
            rq.push_back(make_pair(process_completeion_time[j], make_pair(1, j)));
        }
        sort(rq.begin(), rq.end());
        for (int j = 0; j < rq.size(); j++)
        {

            if (rq[j].second.first == 0)
            {
                cout << "Process " << rq[j].second.second +1 << " entering the ready queue" << endl;
            }
            else
            {
                cout << "Process " << rq[j].second.second +1<< " leaving the ready queue" << endl;
            }
        }
        cout << "----------------------------------------------------------------------" << endl;
    }
}

void find_turnaround_time_priority(vector<int> &turnaround_time, vector<int> &cpu_burst, vector<int> &wait_time)
{
    int n = cpu_burst.size();

    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = cpu_burst[i] + wait_time[i];
    }
}

vector<double> priority(vector<int> &cpu_burst, vector<int> &arrival_times, vector<int> &priorities, int MOde)
{
    MOde_ = MOde;
    int n = cpu_burst.size();
    // cout<<n<<endl;
    vector<int> wait_time(n), turnaround_time(n), response_time(n);

    find_wait_time_priority(wait_time, cpu_burst, arrival_times, response_time, priorities);
    find_turnaround_time_priority(turnaround_time, cpu_burst, wait_time);

    double average_waiting_time = 0, average_turnaround_time = 0, average_response_time = 0;

    for (int i = 0; i < n; i++)
    {
        // cout<<wait_time[i]<<" ";
        average_waiting_time += wait_time[i];
        average_turnaround_time += turnaround_time[i];
        average_response_time += response_time[i];
    }
    // cout<<endl;
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