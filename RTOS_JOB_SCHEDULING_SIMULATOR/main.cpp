#include <bits/stdc++.h>


using namespace std;


struct val
{
    float awt;
    float att;
    float art;
};

typedef struct val Struct;


Struct fcfs(int n, int process[], int bt[], int at[]){
    int wt[n], tat[n], service_time[n];

    queue <int> q;

    q.push(process[0]);
    // cout << "Process 0 entered the queue"<<endl;
    // cout << "Computing service time for process 0"<<endl;
    service_time[0] = at[0];
    // cout << "Computing waiting time for process 0"<<endl;
    wt[0] = 0;
    // cout << "Computing turn around time for process 0"<<endl;
    tat[0] = bt[0] + wt[0];
    q.pop();
    // cout << "Process 0 exied the queue";

    for (int i = 1; i < n ; i++)
    {   
        q.push(process[i]);
        // cout << "Process "<< q.front() <<" entered the queue"<<endl;
        // cout << "Computing service time for process "<<q.front()<<endl;
        service_time[i] = service_time[i-1] + bt[i-1];
        // cout << "Computing waiting time for process "<<q.front()<<endl;
        wt[i] = service_time[i] - at[i];
        if (wt[i] < 0) wt[i] = 0;
        // cout << "Computing turnaround time for process "<<q.front()<<endl;
        tat[i] = bt[i] + wt[i];
        // cout << "Process "<< q.front() <<" exited the queue"<<endl;
    }
        

    int total_wt = 0, total_tat = 0;
    for (int i = 0 ; i < n ; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        int compl_time = tat[i] + at[i];
    }

    Struct s;
    s.awt = (float)total_wt / (float)n;
    s.art = (float)total_wt / (float)n;
    s.att = (float)total_tat / (float)n;
    // cout<<"FCFS"<<endl;
    // cout << "Average waiting time = " << s.awt<<endl;
    // cout << "Average turn around time = " << s.att<<endl;
    // cout << "Average Response time = " << s.art<<endl;

    return s;
}

Struct sjf_np(int n, int process[], int burst_time[], int arrival_time[]){
    int bt[n], p[n], wt[n], tat[n], res[n], at[n]; 

    for(int i=0; i<n; i++){
        p[i] = process[i];
        bt[i] = burst_time[i];
        at[i] = arrival_time[i];
    }

    for(int i=0; i<n; i++)
    {
    	int pos = i;
    	for(int j=i+1; j<n; j++)
    	{
    		if(bt[j] < bt[pos])
    		{
    			pos = j;
    		}
    	}
    	int temp = bt[i];
    	bt[i] = bt[pos];
    	bt[pos] = temp;

    	temp = p[i];
    	p[i] = p[pos];
    	p[pos] = temp;

        temp = p[i];
    	at[i] = at[pos];
    	at[pos] = temp;
    }

    wt[0] = 0;
    tat[0] = bt[0];
    res[0] =0;
    for(int i=1; i<n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1];
        tat[i] = wt[i] + bt[i];
        res[i] = tat[i-1] + at[i-1] - at[i];
        
    }
    int total_wt = 0, total_tat = 0 , total_res =0;
    for(int i=0; i<n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        total_res += res[i]; 
    }

    Struct s;
    s.awt = (float)total_wt / (float)n;
    s.art = (float)total_res / (float)n;
    s.att = (float)total_tat / (float)n;
    // cout<<"SFJ_NP"<<endl;
    // cout << "Average waiting time = " << s.awt<<endl;
    // cout << "Average turn around time = " << s.att<<endl;
    // cout << "Average Response time = " << s.art<<endl;

    return s;

}

Struct sjf_p(int n, int process[], int burst_time[], int arrival_time[]){
    int bt[n], p[n], wt[n], tat[n], ct[n], res[n]; 

    for(int i=0; i<n; i++){
        p[i] = process[i];
        bt[i] = burst_time[i];
    }

    int current_time = 0;
    while(true){
        int shortest = -1;
        int rem_time = numeric_limits<int>::max();
        bool completed = true;

        for(int i=0;i<n;i++){
            if(bt[i] > 0){
                completed = false;
            
                if(arrival_time[i] <= current_time){
                    if(bt[i] < rem_time){
                        rem_time = bt[i];
                        shortest = i;
                    }
                }
            }
        }

        if(completed){
    		break;
    	}

        if(bt[shortest] == burst_time[shortest]){
            res[shortest] = current_time; 
        }

        bt[shortest]--;
        current_time++;

        if(bt[shortest] == 0){
			ct[shortest] = current_time;
		} 
    }

    for(int i=0; i<n; i++){
        tat[i] = ct[i] - arrival_time[i];
        wt[i] = tat[i] - burst_time[i];
    }

    int total_wt = 0, total_tat = 0 , total_res =0;
    for(int i=0; i<n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        total_res += res[i]; 
    }

    // cout<<endl<<total_res<<endl;
    // cout<<"SJF_P"<<endl;
    Struct s;
    s.awt = (float)total_wt / (float)n;
    s.art = (float)total_res / (float)n;
    s.att = (float)total_tat / (float)n;
    // cout << "Average waiting time = " << s.awt <<endl;
    // cout << "Average turn around time = " << s.att<<endl;
    // cout << "Average Response time = " << s.art<<endl;

    return s;
}


Struct rr(int n, int process[], int burst_time[], int arrival_time[]){
    int bt[n], p[n], wt[n], tat[n], ct[n], res[n];
    int quantum = 2; 

    for(int i=0; i<n; i++){
        p[i] = process[i];
        bt[i] = burst_time[i];
        wt[i] =0;
        res[i] =0;
        tat[i] =0;
    }

    int current_time = arrival_time[0];
    int rem_process = n;

     for(int i=0;i<n;i=(i+1)%n){

         if(bt[i] > 0 && arrival_time[i] <=current_time){
             if(bt[i] == burst_time[i]){
                 res[i] = current_time;
             }

             if(bt[i] <= quantum){
                 current_time += bt[i];
                 ct[i] = current_time;
                 bt[i] =0;
                 rem_process--;
             }
             else{
                current_time += quantum;
                bt[i] -= quantum;
             }
         }

         if(rem_process ==0) break;
     }

    for(int i=0; i<n; i++){
        tat[i] = ct[i] - arrival_time[i];
        wt[i] = tat[i] - burst_time[i];
    }


    int total_wt = 0, total_tat = 0 , total_res =0;
    for(int i=0; i<n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        total_res += res[i]; 
    }

    // cout<<"Round Robin"<<endl;
    Struct s;
    s.awt = (float)total_wt / (float)n;
    s.art = (float)total_res / (float)n;
    s.att = (float)total_tat / (float)n;
    // cout << "Average waiting time = " << s.awt<<endl;
    // cout << "Average turn around time = " << s.att<<endl;
    // cout << "Average Response time = " << s.art<<endl;

    return s;

}


Struct pbs(int n, int process[], int burst_time[], int arrival_time[], int priority[]){
    int bt[n], ct[n], res[n], wt[n], tat[n];

    for(int i=0; i<n; i++){
        bt[i] = burst_time[i];
    }

    int current_time =0;

    while (true)
    {
        int curr_index = -1;
    	int curr_priority = INT_MAX;

        bool completed = true;

        for(int i=0;i<n;i++){
            if(bt[i] > 0) {
                completed = false;

                if(arrival_time[i] <= current_time){
                    if(priority[i] < curr_priority){
                        curr_priority = priority[i];
                        curr_index = i;
                    }
                }
            }
        }

        if(completed){
    		break;
    	}

        if(bt[curr_index] == burst_time[curr_index]){
            res[curr_index] = current_time;
        }

        bt[curr_index]--;
        current_time++;

        if(bt[curr_index] ==0){
            ct[curr_index] = current_time;
        }
    }

    for(int i=0; i<n; i++){
        tat[i] = ct[i] - arrival_time[i];
        wt[i] = tat[i] - burst_time[i];
    }


    int total_wt = 0, total_tat = 0 , total_res =0;
    for(int i=0; i<n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        total_res += res[i]; 
    }

    // cout<<"Priority Based"<<endl;
    Struct s;
    s.awt = (float)total_wt / (float)n;
    s.art = (float)total_res / (float)n;
    s.att = (float)total_tat / (float)n;
    // cout << "Average waiting time = " << s.awt<<endl;
    // cout << "Average turn around time = " << s.att<<endl;
    // cout << "Average Response time = " << s.art<<endl;

    return s;
    
}


int main(int argc, char *argv[]){

    srand(time(0));
    ofstream MyFile("output.txt");

    if(argc != 2){
        cout<<"Enter number of process as argument";
        exit(1);
    }

    int n = stoi(argv[1]);
    MyFile << n <<endl;

    float total_awt[5] , mini_awt[5], maxi_awt[5];
    float total_att[5] , mini_att[5] , maxi_att[5];
    float total_art[5] , mini_art[5], maxi_art[5];

    for(int j=0; j<5 ; j++){
        total_awt[j] = 0.0;
        total_att[j] = 0.0;
        total_art[j] = 0.0;

        mini_awt[j] = numeric_limits<float>::max();
        mini_att[j] = numeric_limits<float>::max();
        mini_art[j] = numeric_limits<float>::max();


        maxi_awt[j] = numeric_limits<float>::min();
        maxi_att[j] = numeric_limits<float>::min();
        maxi_art[j] = numeric_limits<float>::min();
    }

    // for(int j=0; j<5 ; j++){
    //     cout<<mini_awt[j] << " ";
    // }
    // cout<<endl;

    // for(int j=0; j<5 ; j++){
    //     cout<<maxi_awt[j] << " ";
    // }

    for(int l=0; l<10; l++){
        int process[n], burst_time[n], arrival_time[n], priority[n];
        arrival_time[0] = 0;

        for(int i=0; i<n; i++){
            process[i] = i;
            burst_time[i] = (rand() % 20) + 1;
            priority[i] = (rand() % 10) + 1;
            if(i!=0){
                double x=rand()/(double) RAND_MAX;
                int t= (int)(-1.0/0.5)*log(x);
                arrival_time[i] = arrival_time[i-1] + t;
                MyFile << burst_time[i] << " " <<t<<" "<<priority[i] <<endl;
            }else{
                MyFile << burst_time[i] << " " <<0<<" "<<priority[i] <<endl;
            }
        }

        MyFile.close();


        Struct s[5];
        s[0] = fcfs(n, process, burst_time, arrival_time);
        s[1] = sjf_np(n, process, burst_time, arrival_time);
        s[2] = sjf_p(n, process, burst_time, arrival_time);
        s[3] = rr(n, process, burst_time, arrival_time);
        s[4] = pbs(n, process, burst_time, arrival_time, priority);



        for(int j=0; j<5 ; j++){
            total_awt[j] += s[j].awt;
            mini_awt[j] = min(mini_awt[j], s[j].awt);
            maxi_awt[j] = max(maxi_awt[j], s[j].awt);
            total_att[j] += s[j].att;
            mini_att[j] = min(mini_att[j], s[j].att);
            maxi_att[j] = max(maxi_att[j], s[j].att);
            total_art[j] += s[j].art;
            mini_art[j] = min(mini_art[j], s[j].art);
            maxi_art[j] = max(maxi_art[j], s[j].art);
        }
        
    }
    
    for(int j=0; j<5; j++){
        total_awt[j] = total_awt[j]/10;
        total_att[j] = total_att[j]/10; 
        total_art[j] = total_art[j]/10; 
    }

    
     
    ofstream fcfs_file("fcfs.txt");
    fcfs_file <<"Total\n"<< "AWT : " << total_awt[0] <<endl<< "ATT : " <<total_att[0] <<endl << "ART : "<<total_art[0] << endl << endl;
    fcfs_file <<"Minimum\n"<< "AWT : " << mini_awt[0] <<endl<< "ATT : " <<mini_att[0] <<endl << "ART : " <<mini_art[0] << endl << endl;
    fcfs_file <<"Maximum\n"<< "AWT : " << maxi_awt[0] <<endl<< "ATT : " << maxi_att[0] <<endl << "ART : " <<maxi_art[0];
    fcfs_file.close();


    ofstream sjf_np_file("sjf_np.txt");
    sjf_np_file << "Total\n"<< "AWT : " << total_awt[1] <<endl<< "ATT : " <<total_att[1] <<endl << "ART : "<<total_art[1] << endl << endl;
    sjf_np_file <<"Minimum\n"<< "AWT : " << mini_awt[1] <<endl<< "ATT : " <<mini_att[1] <<endl << "ART : " <<mini_art[1] << endl << endl;
    sjf_np_file <<"Maximum\n"<< "AWT : " << maxi_awt[1] <<endl<< "ATT : " << maxi_att[1] <<endl << "ART : " << maxi_art[1];
    sjf_np_file.close();


   
    ofstream sjf_p_file("sjf_p.txt");
    sjf_p_file << "Total\n"<< "AWT : " << total_awt[2] <<endl<< "ATT : " <<total_att[2] <<endl << "ART : "<<total_art[2] << endl << endl;
    sjf_p_file <<"Minimum\n"<< "AWT : " << mini_awt[2] <<endl<< "ATT : " <<mini_att[2] <<endl << "ART : " <<mini_art[2] << endl << endl;
    sjf_p_file <<"Maximum\n"<< "AWT : " << maxi_awt[2] <<endl<< "ATT : " << maxi_att[2] <<endl << "ART : " << maxi_art[2];
    sjf_p_file.close();
 
    ofstream rr_file("rr.txt");
    rr_file << "Total\n"<< "AWT : " << total_awt[3] <<endl<< "ATT : " <<total_att[3] <<endl << "ART : "<<total_art[3] << endl << endl;
    rr_file <<"Minimum\n"<< "AWT : " << mini_awt[3] <<endl<< "ATT : " <<mini_att[3] <<endl << "ART : " <<mini_art[3]<<endl<<endl;
    rr_file <<"Maximum\n"<< "AWT : " << maxi_awt[3] <<endl<< "ATT : " << maxi_att[3] <<endl << "ART : " << maxi_art[3];
    rr_file.close();


    ofstream pbs_file("pbs.txt");
    pbs_file << "Total\n"<< "AWT : " << total_awt[4] <<endl<< "ATT : " <<total_att[4] <<endl << "ART : "<<total_art[4] << endl << endl;
    pbs_file <<"Minimum\n"<< "AWT : " << mini_awt[4] <<endl<< "ATT : " <<mini_att[4] <<endl << "ART : " <<mini_art[4]<<endl<<endl;
    pbs_file <<"Maximum\n"<< "AWT : " << maxi_awt[4] <<endl<< "ATT : " << maxi_att[4] <<endl << "ART : " << maxi_art[4];
    pbs_file.close();
    
    
}