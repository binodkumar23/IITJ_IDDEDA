from heapq import *
from tabulate import tabulate
import matplotlib.pyplot as plt

# class for doing heap operations
class minHeap:
    def __init__(self):
        self.hea = []
    
    def push_heap(self,ele):
        heappush(self.hea,ele)
    
    def pop_heap(self):
        return heappop(self.hea)

    def get_top(self):
        return self.hea[0]

    def get_heap(self):
        return self.hea

    def isEmpty(self):
        return len(self.hea) == 0

def plot_gantt_chart(summary,task,simultaion_time):
    task_schedule = {i:[] for i in task}
    task_schedule[""] = []
    for a,b,c in summary:
        task_schedule[a].append((b,1))

    fig, gnt = plt.subplots()
    gnt.set_ylim(0, len(task)+1)
    gnt.set_xlim(0, simultaion_time + 2)

    gnt.set_xlabel('Time')
    gnt.set_ylabel('Tasks')

    gnt.set_yticks([i+1 for i in range(len(task))])
    gnt.set_yticklabels(task)

    gnt.grid(True)

    for i in range(len(task)):
        gnt.broken_barh(task_schedule[task[i]],(i+0.9,0.2),facecolors=('tab:orange'))
    plt.savefig("output/RM.png")

# utility for checking if given taskset is schedulable or not
def utilization(ci,ti):
    return sum(ci[i]/ti[i] for i in range(len(ti)))

# Calculating GCD
def gcd(a,b):
    if b == 0:
        return a
    return gcd(b,a%b)

# Calculating LCM to know for how much time we need to simulate
def lcm(ti):
    x = 1
    for i in range(len(ti)):
        x = (x*ti[i])//gcd(x,ti[i])
    return x

# utitlity for releasing all the process according to release time
def intialise_heap(hea,timePeriod,processName,executionTime,table):
    for i in range(len(processName)):
        hea.push_heap( ( timePeriod[i],0,-executionTime[i],-table[processName[i]] ) )


# Input file reader
def input_file_reader():
    file = open("input/input.txt","r")
    for i in file.readlines():
        yield(i.strip())

# Rate Monotonic Algorithm

# input table
x = input_file_reader()
task = next(x).split(" ")
ci   = list(map(int,next(x).split(" ")))
di   = list(map(int,next(x).split(" ")))
ti   = list(map(int,next(x).split(" ")))

file1 = open("output/rm.txt", "w")

# Table for conversion task_name to integer
table0 = {
    task[i]:i+1 for i in range(len(task))
}

# Table for conversion integer to task_name
table1 = {
    i+1:task[i] for i in range(len(task))
}

# Checking if schedulable
U = utilization(ci,ti)
print(f"Utilization is : {U}")
n = len(ti)

if U <= n*((2**(1/n))-1):
    print("Uilization is less than Theoretical Bound thus we can use this scheduling algo here.")
elif n*((2**(1/n))-1) < U<=1:
    print("Uilization is more than Theoretical Bound but less than 1 thus we may use this scheduling algo here.")
else:
    print("Uilization is more than 1 thus we can't use this scheduling algo here.")
    exit()    

# intialising Heaps
heap1 = minHeap()
heap2 = minHeap()

# global time
time = 0
simultaion_time = lcm(ti)

# variable to store all results
summary = []

intialise_heap(heap1,ti,task,ci,table0)

# main logic
while time < simultaion_time:

    # checking if new process should be  added to heap or not 
    while (not heap2.isEmpty() and heap2.get_top()[0] <= time):
        x,x1,y,z = heap2.pop_heap()
        heap1.push_heap((x1,x,y,z))

    # if there are no process continue
    if heap1.isEmpty() : 
        summary.append(("",time,time+1))
        time+=1
        continue

    # sheduling a process according to time period
    x,x1,y,z = heap1.pop_heap()
    summary.append((table1[-z],time,time+1))
    y = y+1
    if y == 0:
        heap2.push_heap(( x1+ti[-z-1],x,-ci[-z-1],z ))
    else:
        heap1.push_heap((x,x1,y,z))
    
    time+=1

# Plot Chart

plot_gantt_chart(summary,task,simultaion_time)
# printing summary

head = ["Tasks","Execution Time(ci)","Deadline(di)","Time Period(ti)"]
data = []
for idx in range(len(task)):
    data.append([task[idx],ci[idx], di[idx], ti[idx]])

print("Real Time tasks Table is :- ",file=file1)
print(tabulate(data, headers=head, tablefmt="grid"),file=file1)
print("\nTask Summary\n",file=file1)
for a,b,c in summary:
    a = a if a != "" else "No Task"
    print("For Time {0:3} - {1:3} ; Task running is : {2:3}".format(b,c,a)  ,file=file1 )

