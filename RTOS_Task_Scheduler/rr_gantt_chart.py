from time import time
import matplotlib.pyplot as plt
def plot_gantt_chart():
    fileObj = open("output/rr_timeline.txt", "r") #opens the file in read mode
    timeline = fileObj.read().splitlines() #puts the file into an array
    fileObj.close()
    timeline = timeline[0].split(' ')
    timeline = timeline[0:len(timeline)-1]
    timeline = list(map(int, timeline))

    simultaion_time = len(timeline)+1
    task_schedule = {i:[] for i in timeline}
    for i in range(simultaion_time-1):
        task_schedule[timeline[i]].append((i,1))

    fig, gnt = plt.subplots()
    gnt.set_ylim(0, len(task_schedule)+1)
    gnt.set_xlim(0, simultaion_time + 10)

    gnt.set_xlabel('Time')
    gnt.set_ylabel('Tasks')

    gnt.set_yticks([i+1 for i in range(len(task_schedule))])
    gnt.set_yticklabels(task_schedule)

    gnt.grid(True)
    for i in range(len(task_schedule)):
        gnt.broken_barh(task_schedule[i+1],(i+0.9,0.2),facecolors=('tab:orange'))
    plt.savefig("output/RR.png")
    print("Gantt Chart generated successfully.")
plot_gantt_chart()