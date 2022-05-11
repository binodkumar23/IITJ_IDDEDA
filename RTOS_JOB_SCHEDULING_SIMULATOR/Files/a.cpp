#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair
#define fo(i, n) for (i = 0; i < n; i++)
#define foo(i, a, b) for (i = a; i < b; i++)

ll t, i, j, k, m, n, p, q;




double round_dob(double var)
{
    double value = (int)(var*100+.5);
    return (double)value/100;
}
int main(int argc, char* argv[])
{
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll mean=2;
    // cout << "Enter the number of processes : " << endl;
    if(argc==1)
    {
        cin >> n;
    }
    else
    {
        n= stoi(argv[1]);
    }
    vector<int> processes(n), cpu_burst(n), arrival_times(n), priorities(n);
    fo(i, n) processes[i] = i + 1;
    srand(time(0));
    unsigned seed1 = std::chrono::steady_clock::now().time_since_epoch().count();
    unsigned seed2 = std::chrono::steady_clock::now().time_since_epoch().count();
    default_random_engine gen(seed1),generator2(seed2);
    uniform_int_distribution<int> uni_dist1(1, 20),uni_dist2(1, 10);
    uniform_real_distribution<double> uni_dist3(0.0,1.0);
    // vector<int> at(n),bt(n),p(n);
    
    fo(i, n)
    {
        cpu_burst[i] = uni_dist1(gen);  
        priorities[i] = uni_dist2(gen);
        if (i == 0)
        {
            arrival_times[0] = 0;
        }
        else
        {
            double R = uni_dist3(gen);
            // double R = 0.0001;
            double val = round_dob(R);
            // cout<<R<<endl;
            double number = -((double)mean)*(double)log(R);
            arrival_times[i]=arrival_times[i-1]+number;
        }
    }
    // cout<<"Processes\t"<<"CPU Burst\t"<<"Arrival Time\t"<<"Priority\t"<<endl;
    fo(i,n)
    {
        cout<<processes[i]<<"\t\t"<<cpu_burst[i]<<"\t\t"<<arrival_times[i]<<"\t\t"<<priorities[i]<<"\t\t"<<endl;
    }

    return 0;
}