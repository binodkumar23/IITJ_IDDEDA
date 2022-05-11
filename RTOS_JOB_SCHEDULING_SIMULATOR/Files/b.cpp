#include <bits/stdc++.h>
#include "fcfs.h"
#include "sjfnp.h"
#include "sjfp.h"
#include "priority.h"
#include "rr.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc <2 )
    {
        int n;
        int quantum = 2;
        ifstream file_input;
        file_input.open("out.txt");
        int temp;
        vector<int> cpu_burst, arrival_time, priorities;
        int pro = 0;
        while (file_input >> temp)
        {
            file_input >> temp;
            cpu_burst.push_back(temp);
            file_input >> temp;
            arrival_time.push_back(temp);
            file_input >> temp;
            priorities.push_back(temp);
            pro++;
        }
        n = pro;


        
        vector<double> final_fcfs, final_sjfnp, final_sjfp, final_rr, final_priority;
        final_fcfs = fcfs(cpu_burst, arrival_time,0);
        final_sjfnp = sjfnp(cpu_burst, arrival_time,0);
        final_sjfp = sjfp(cpu_burst, arrival_time,0);
        final_rr = rr(cpu_burst, arrival_time, quantum,0);
        final_priority = priority(cpu_burst, arrival_time, priorities,0);

        cout << "Algorithm used  \t Average Waiting time \t  Average Turnaround time \t  Average Response time" << endl;
        cout << "FCFS\t\t\t\t\t" << final_fcfs[0] << "\t\t\t" << final_fcfs[1] << "\t\t\t" << final_fcfs[2] << "\t\t\t" << endl;
        cout << "Shortest job first np\t\t\t" << final_sjfnp[0] << "\t\t\t" << final_sjfnp[1] << "\t\t\t" << final_sjfnp[2] << "\t\t\t" << endl;
        cout << "Shortest job first p\t\t\t" << final_sjfp[0] << "\t\t\t" << final_sjfp[1] << "\t\t\t" << final_sjfp[2] << "\t\t\t" << endl;
        cout << "Round robin\t\t\t\t" << final_rr[0] << "\t\t\t" << final_rr[1] << "\t\t\t" << final_rr[2] << "\t\t\t" << endl;
        cout << "Priority Scheduler\t\t\t" << final_priority[0] << "\t\t\t" << final_priority[1] << "\t\t\t" << final_priority[2] << "\t\t\t" << endl;
    }
    else if(argc==3)
    {
        int a = stoi(argv[1]);
        int b = stoi(argv[2]);
        vector<double> maxi_art(5, INT_MIN), mini_art(5, INT_MAX), avg_art(5, 0);
        vector<double> maxi_att(5, INT_MIN), mini_att(5, INT_MAX), avg_att(5, 0);
        vector<double> maxi_awt(5, INT_MIN), mini_awt(5, INT_MAX), avg_awt(5, 0);

        for (int k = 0; k < 10; k++)
        {
            string x = "./a " + to_string(a) + " >out.txt";
            const char *cmd = x.c_str();
            // cout << cmd << endl;
            system(cmd);

            int n;
            int quantum = 2;
            ifstream file_input;
            file_input.open("out.txt");
            int temp;
            vector<int> cpu_burst, arrival_time, priorities;
            int pro = 0;
            while (file_input >> temp)
            {
                file_input >> temp;
                cpu_burst.push_back(temp);
                file_input >> temp;
                arrival_time.push_back(temp);
                file_input >> temp;
                priorities.push_back(temp);
                pro++;
            }
            n = pro;

            vector<double> final_fcfs, final_sjfnp, final_sjfp, final_rr, final_priority;
            final_fcfs = fcfs(cpu_burst, arrival_time,1);
            final_sjfnp = sjfnp(cpu_burst, arrival_time,1);
            final_sjfp = sjfp(cpu_burst, arrival_time,1);
            final_rr = rr(cpu_burst, arrival_time, quantum,1);
            final_priority = priority(cpu_burst, arrival_time, priorities,1);
            //FCFS maxi awt art att

            maxi_awt[0] = max(maxi_awt[0], final_fcfs[0]);
            maxi_art[0] = max(maxi_art[0], final_fcfs[2]);
            maxi_att[0] = max(maxi_att[0], final_fcfs[1]);
            maxi_awt[1] = max(maxi_awt[1], final_sjfnp[0]);
            maxi_art[1] = max(maxi_art[1], final_sjfnp[2]);
            maxi_att[1] = max(maxi_att[1], final_sjfnp[1]);
            maxi_awt[2] = max(maxi_awt[2], final_sjfp[0]);
            maxi_art[2] = max(maxi_art[2], final_sjfp[2]);
            maxi_att[2] = max(maxi_att[2], final_sjfp[1]);
            maxi_awt[3] = max(maxi_awt[3], final_rr[0]);
            maxi_art[3] = max(maxi_art[3], final_rr[2]);
            maxi_att[3] = max(maxi_att[3], final_rr[1]);
            maxi_awt[4] = max(maxi_awt[4], final_priority[0]);
            maxi_art[4] = max(maxi_art[4], final_priority[2]);
            maxi_att[4] = max(maxi_att[4], final_priority[1]);

            mini_awt[0] = min(mini_awt[0], final_fcfs[0]);
            mini_art[0] = min(mini_art[0], final_fcfs[2]);
            mini_att[0] = min(mini_att[0], final_fcfs[1]);
            mini_awt[1] = min(mini_awt[1], final_sjfnp[0]);
            mini_art[1] = min(mini_art[1], final_sjfnp[2]);
            mini_att[1] = min(mini_att[1], final_sjfnp[1]);
            mini_awt[2] = min(mini_awt[2], final_sjfp[0]);
            mini_art[2] = min(mini_art[2], final_sjfp[2]);
            mini_att[2] = min(mini_att[2], final_sjfp[1]);
            mini_awt[3] = min(mini_awt[3], final_rr[0]);
            mini_art[3] = min(mini_art[3], final_rr[2]);
            mini_att[3] = min(mini_att[3], final_rr[1]);
            mini_awt[4] = min(mini_awt[4], final_priority[0]);
            mini_art[4] = min(mini_art[4], final_priority[2]);
            mini_att[4] = min(mini_att[4], final_priority[1]);

            avg_awt[0] += final_fcfs[0];
            avg_art[0] += final_fcfs[2];
            avg_att[0] += final_fcfs[1];
            avg_awt[1] += final_sjfnp[0];
            avg_art[1] += final_sjfnp[2];
            avg_att[1] += final_sjfnp[1];
            avg_awt[2] += final_sjfp[0];
            avg_art[2] += final_sjfp[2];
            avg_att[2] += final_sjfp[1];
            avg_awt[3] += final_rr[0];
            avg_art[3] += final_rr[2];
            avg_att[3] += final_rr[1];
            avg_awt[4] += final_priority[0];
            avg_art[4] += final_priority[2];
            avg_att[4] += final_priority[1];
        }

        ofstream fout; // Create Object of Ofstream
        ifstream fin;

       

        fin.open("ATT.txt");
        fout.open("ATT.txt", ios::app); // Append mode
        // vector<int> v1(3, 2);

        if (fin.is_open())
        {
            fout << a<<" ";
            for (int r = 0; r < 5; r++)
            {
                fout << maxi_att[r] << " ";
            }
            fout << " " << endl; // Writing data to file
            fout << a<<" ";
            for (int r = 0; r < 5; r++)
            {
                fout << mini_att[r] << " ";
            }
            fout << " " << endl;
            fout << a<<" ";
            for (int r = 0; r < 5; r++)
            {
                fout << avg_att[r] << " ";
            }
            fout << " " << endl;
        }

        // cout << "\n Data has been appended to file";
        fin.close();
        fout.close();

        ///////////////////////////////////////////////////////////////////// ART
        fin.open("ART.txt");
        fout.open("ART.txt", ios::app); // Append mode
        // vector<int> v1(3, 2);

        if (fin.is_open())
        {
            fout << a<<" ";
            for (int r = 0; r < 5; r++)
            {
                fout << maxi_art[r] << " ";
            }
            fout << " " << endl; // Writing data to file
            fout << a<<" ";
            for (int r = 0; r < 5; r++)
            {
                fout << mini_art[r] << " ";
            }
            fout << " " << endl;
            fout << a<<" ";
            for (int r = 0; r < 5; r++)
            {
                fout << avg_art[r] << " ";
            }
            fout << " " << endl;
        }

        // cout << "\n Data has been appended to file";
        fin.close();
        fout.close();

        /////////////////////////////////////////////////////////AWT

        fin.open("AWT.txt");
        fout.open("AWT.txt", ios::app); // Append mode
        // vector<int> v1(3, 2);

        if (fin.is_open())
        {
            fout << a<<" ";
            for (int r = 0; r < 5; r++)
            {
                fout << maxi_awt[r] << " ";
            }
            fout << " " << endl; // Writing data to file
            fout << a<<" ";
            for (int r = 0; r < 5; r++)
            {
                fout << mini_awt[r] << " ";
            }
            fout << " " << endl;
            fout << a<<" ";
            for (int r = 0; r < 5; r++)
            {
                fout << avg_awt[r] << " ";
            }
            fout << " " << endl;
        }

        // cout << "\n Data has been appended to file";
        fin.close();
        fout.close();
        cout << a << " " << b << endl;
    }
    return 1;
}