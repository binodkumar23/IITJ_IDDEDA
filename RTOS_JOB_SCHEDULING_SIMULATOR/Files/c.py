
import os
# import matplotlib.pyplot as plt
import matplotlib.pyplot as plt
import numpy as np
file = open("AWT.txt",'w')
file.close()
file = open("ATT.txt",'w')
file.close()
file = open("ART.txt",'w')
file.close()
cmd = './final 10 10'
os.system(cmd)
cmd = './final 20 10'
os.system(cmd)
cmd = './final 30 10'
os.system(cmd)
cmd = './final 40 10'
os.system(cmd)
cmd = './final 50 10'
os.system(cmd)


x=np.arange(10,60,10)
y1max=[]
y1min=[]
y1avg =[]

y2max=[]
y2min=[]
y2avg =[]

y3max=[]
y3min=[]
y3avg =[]

y4max=[]
y4min=[]
y4avg =[]

y5max=[]
y5min=[]
y5avg=[]

flag=[0,0,0,0,0]
file = open("AWT.txt",'r')
Lines = file.readlines()
for line in Lines:
    if(line.startswith("10 ")):
        x=line.split(' ')
        if(flag[0]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[0]=1
        elif(flag[0]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[0]=2
        elif(flag[0]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))
                
                
    elif(line.startswith("20 ")):
        x=line.split(' ')
        if(flag[1]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[1]=1
        elif(flag[1]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[1]=2
        elif(flag[1]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))

    elif(line.startswith("30 ")):
        x=line.split(' ')
        if(flag[2]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[2]=1
        elif(flag[2]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[2]=2
        elif(flag[2]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))     
    
    elif(line.startswith("40 ")):
        x=line.split(' ')
        if(flag[3]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[3]=1
        elif(flag[3]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[3]=2
        elif(flag[3]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))


    elif(line.startswith("50 ")):
        x=line.split(' ')
        if(flag[4]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[4]=1
        elif(flag[4]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[4]=2
        elif(flag[4]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))        
  
x=np.arange(10,60,10)
# x=np.arange(10,60,10)
plt.plot(x, y1min, label="FCFS")
plt.plot(x, y2min, label="SJFNP")
plt.plot(x, y3min, label="SJFP")
plt.plot(x, y4min, label="RR")
plt.plot(x, y5min, label="PS")
# plt.legend(['FCFS','SJFNP','SJFP','RR','PS'])
plt.title("Minimum AWT vs N")
plt.legend(['FCFS','SJFNP','SJFP','RR','PS'])
plt.ylabel("Minimum AWT")
plt.xlabel("Value of N")
plt.savefig("graphs/minawt.png")
plt.show()

plt.plot(x, y1max, label="FCFS")
plt.plot(x, y2max, label="SJFNP")
plt.plot(x, y3max, label="SJFP")
plt.plot(x, y4max, label="RR")
plt.plot(x, y5max, label="PS")

plt.title("Maximum AWT vs N")
plt.legend(['FCFS','SJFNP','SJFP','RR','PS'])
plt.ylabel("Maximum AWT")
plt.xlabel("Value of N")
plt.savefig("graphs/maxawt.png")
plt.show()


plt.plot(x, y1avg, label="FCFS")
plt.plot(x, y2avg, label="SJFNP")
plt.plot(x, y3avg, label="SJFP")
plt.plot(x, y4avg, label="RR")
plt.plot(x, y5avg, label="PS")

plt.title("Average AWT vs N")
plt.legend(['FCFS','SJFNP','SJFP','RR','PS'])
plt.ylabel("Average AWT")
plt.xlabel("Value of N")
plt.savefig("graphs/avgawt.png")
plt.show()



file.close()


##########################################################ART

flag=[0,0,0,0,0]
y1max=[]
y1min=[]
y1avg =[]

y2max=[]
y2min=[]
y2avg =[]

y3max=[]
y3min=[]
y3avg =[]

y4max=[]
y4min=[]
y4avg =[]

y5max=[]
y5min=[]
y5avg=[]
file = open("ART.txt",'r')
Lines = file.readlines()
for line in Lines:
    if(line.startswith("10 ")):
        x=line.split(' ')
        if(flag[0]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[0]=1
        elif(flag[0]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[0]=2
        elif(flag[0]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))
                
                
    elif(line.startswith("20 ")):
        x=line.split(' ')
        if(flag[1]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[1]=1
        elif(flag[1]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[1]=2
        elif(flag[1]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))

    elif(line.startswith("30 ")):
        x=line.split(' ')
        if(flag[2]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[2]=1
        elif(flag[2]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[2]=2
        elif(flag[2]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))     
    
    elif(line.startswith("40 ")):
        x=line.split(' ')
        if(flag[3]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[3]=1
        elif(flag[3]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[3]=2
        elif(flag[3]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))


    elif(line.startswith("50 ")):
        x=line.split(' ')
        if(flag[4]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[4]=1
        elif(flag[4]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[4]=2
        elif(flag[4]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))        
  
x=np.arange(10,60,10)
# print(y1min)
plt.plot(x, y1min, label="FCFS")
plt.plot(x, y2min, label="SJFNP")
plt.plot(x, y3min, label="SJFP")
plt.plot(x, y4min, label="RR")
plt.plot(x, y5min, label="PS")

plt.title("Minimum ART vs N")
plt.legend(['FCFS','SJFNP','SJFP','RR','PS'])
plt.xlabel("Value of N")
plt.ylabel("Minimum ART")
plt.savefig("graphs/minart.png")
plt.show()

plt.plot(x, y1max, label="FCFS")
plt.plot(x, y2max, label="SJFNP")
plt.plot(x, y3max, label="SJFP")
plt.plot(x, y4max, label="RR")
plt.plot(x, y5max, label="PS")

plt.title("Maximum ART vs N")
plt.legend(['FCFS','SJFNP','SJFP','RR','PS'])
plt.xlabel("Value of N")
plt.ylabel("Maximum ART")
plt.savefig("graphs/maxart.png")
plt.show()


plt.plot(x, y1avg, label="FCFS")
plt.plot(x, y2avg, label="SJFNP")
plt.plot(x, y3avg, label="SJFP")
plt.plot(x, y4avg, label="RR")
plt.plot(x, y5avg, label="PS")

plt.title("Average ART vs N")
plt.legend(['FCFS','SJFNP','SJFP','RR','PS'])
plt.xlabel("Value of N")
plt.ylabel("Average ART")
plt.savefig("graphs/avgart.png")
plt.show() 


##################################################################################################ATT

flag=[0,0,0,0,0]
y1max=[]
y1min=[]
y1avg =[]

y2max=[]
y2min=[]
y2avg =[]

y3max=[]
y3min=[]
y3avg =[]

y4max=[]
y4min=[]
y4avg =[]

y5max=[]
y5min=[]
y5avg=[]

file = open("ATT.txt",'r')
Lines = file.readlines()
for line in Lines:
    if(line.startswith("10 ")):
        x=line.split(' ')
        if(flag[0]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[0]=1
        elif(flag[0]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[0]=2
        elif(flag[0]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))
                
                
    elif(line.startswith("20 ")):
        x=line.split(' ')
        if(flag[1]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[1]=1
        elif(flag[1]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[1]=2
        elif(flag[1]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))

    elif(line.startswith("30 ")):
        x=line.split(' ')
        if(flag[2]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[2]=1
        elif(flag[2]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[2]=2
        elif(flag[2]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))     
    
    elif(line.startswith("40 ")):
        x=line.split(' ')
        if(flag[3]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[3]=1
        elif(flag[3]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[3]=2
        elif(flag[3]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))


    elif(line.startswith("50 ")):
        x=line.split(' ')
        if(flag[4]==0):
            y1max.append(float(x[1]))
            y2max.append(float(x[2]))
            y3max.append(float(x[3]))
            y4max.append(float(x[4]))
            y5max.append(float(x[5]))
            flag[4]=1
        elif(flag[4]==1):
            y1min.append(float(x[1]))
            y2min.append(float(x[2]))
            y3min.append(float(x[3]))
            y4min.append(float(x[4]))
            y5min.append(float(x[5]))
            flag[4]=2
        elif(flag[4]==2):
            y1avg.append(float(x[1]))
            y2avg.append(float(x[2]))
            y3avg.append(float(x[3]))
            y4avg.append(float(x[4]))
            y5avg.append(float(x[5]))        
  
x=np.arange(10,60,10)
plt.plot(x, y1min, label="FCFS")
plt.plot(x, y2min, label="SJFNP")
plt.plot(x, y3min, label="SJFP")
plt.plot(x, y4min, label="RR")
plt.plot(x, y5min, label="PS")

plt.title("Minimum ATT vs N")
plt.legend(['FCFS','SJFNP','SJFP','RR','PS'])
plt.xlabel("Value of N")
plt.ylabel("Minimum ATT")
# plt.savefig("graphs/minatt.png")
plt.show() 

plt.plot(x, y1max, label="FCFS")
plt.plot(x, y2max, label="SJFNP")
plt.plot(x, y3max, label="SJFP")
plt.plot(x, y4max, label="RR")
plt.plot(x, y5max, label="PS")

plt.title("Maximum ATT vs N")
plt.legend(['FCFS','SJFNP','SJFP','RR','PS'])
plt.xlabel("Value of N")
plt.ylabel("Maximum ATT")
# plt.savefig("graphs/maxatt.png")
plt.show() 


plt.plot(x, y1avg, label="FCFS")
plt.plot(x, y2avg, label="SJFNP")
plt.plot(x, y3avg, label="SJFP")
plt.plot(x, y4avg, label="RR")
plt.plot(x, y5avg, label="PS")

plt.title("Average ATT vs N")
plt.legend(['FCFS','SJFNP','SJFP','RR','PS'])
plt.xlabel("Value of N")
plt.ylabel("Average ATT")
# plt.savefig("graphs/avgatt.png")
plt.show() 