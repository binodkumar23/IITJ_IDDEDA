import random
import time
l={}

def pickLiteral(input):
  for j in input:
    if(len(j)==1):
      return list(j)[0],1
    for k in j:
      if (k[0]!='!'):
        return k,0
      else:
        return k[1::],0 

def dpll(input, values={}):
  if(len(input)==0):
    return True,values
  if( any([len(k)==0 for k in input])):
    return False,None
  literal, isunit= pickLiteral(input)
  newInput=[]
  newInput2=[]
  if(literal[0]!='!'):
    for i in input:
      if(literal not in i):
        newInput.append(i)
    for i in newInput:
      newInput2.append(i.difference({'!'+literal}))
    if(isunit):
      return dpll(newInput2,{**values,**{literal:True}})
    result,value=dpll(newInput2,{**values,**{literal:True}})
    if(result):
      return result,value

  newInput=[]
  newInput2=[]
  if(literal[0]!='!'):
    newLiteral='!'+literal
  if(isunit):
    for i in input:
      if(literal not in i):
        newInput.append(i)
    for i in newInput:
      newInput2.append(i.difference({literal[1::]}))
    return dpll(newInput2,{**values,**{literal[1::]:False}})
  for i in input:
    if(newLiteral not in i):
      newInput.append(i)
  for i in newInput:
    newInput2.append(i.difference({literal}))
  result,value=dpll(newInput2,{**values,**{literal:False}})
  if(result):
    return result,value
  return False,None

def OR(a,c):
  x=[]
  s={'!'+c}
  for i in a:
    s.add(i)
  x.append(s)
  for i in a:
    x+=[{'!'+i,c}]

  return x

def ORO0(a):
  x=[]
  for i in a:
    x+=[{'!'+i}]
  return x

def ORO1(a):
  x=[]
  s=set()
  for i in a:
    s.add(i)
  x.append(s)
  return x

def AND(a,c):
  x=[]
  s={c}
  for i in a:
    s.add('!'+i)
  x.append(s)
  for i in a:
    x+=[{i,'!'+c}]
  
  return x

def ANDO1(a):
  x=[]
  for i in a:
    x+=[{i}]
  
  return x

def ANDO0(a):
  x=[]
  s=set()
  for i in a:
    s.add('!'+i)
  x.append(s)
  
  return x

def NAND(a,c):
  x=[]
  s={'!'+c}
  for i in a:
    s.add('!'+i)
  x.append(s)
  for i in a:
    x+=[{i,c}]
  
  return x

def NANDO1(a):
  x=[]
  s=set()
  for i in a:
    s.add('!'+i)
  x.append(s)
  
  return x

def NANDO0(a):
  x=[]
  for i in a:
    x+=[{i}]
  
  return x

def NOR(a,c):
  x=[]
  s={c}
  for i in a:
    s.add(i)
  x.append(s)
  for i in a:
    x+=[{'!'+i,'!'+c}]
  
  return x

def NORO1(a):
  x=[]
  for i in a:
    x+=[{'!'+i}]
  
  return x

def NORO0(a):
  x=[]
  s=set()
  for i in a:
    s.add(i)
  x.append(s)
  
  return x

def NOT(a,b):
  a=a[0]
  return [{a,b},{'!'+a,'!'+b}]

def NOTO1(a):
  a=a[0]
  return [{'!'+a}]

def NOTO0(a):
  a=a[0]
  return [{a}]


x=[]
unit0=[]
unit1=[]
inputFile=input("Enter the input file name: ")
k= open('circuits/'+inputFile,'r')
outputLit=int(input("Do you want to assign a value to the output literal yourself(else random output values will be assigned)?  Input 1 for yes and 0 for no: "))
for i in k.readlines():
  f=0
  i.replace('\n','')
  if(i[0:5]=='INPUT'):
    lit=''
    for c in i:
      if c=='(':
        f=1
      elif c==')':
        break
      elif(f==1):
        lit+=c
    l[lit]=lit
  elif(i[0:6]=='OUTPUT'):
    lit=''
    for c in i:
      if c=='(':
        f=1
      elif c==')':
        break
      elif(f==1 and c!=')'):
        lit+=c
    if(outputLit==0):
      l[lit]=random.randint(0,1)
    else:
      l[lit]=int(input("Enter the value of the output literal "+ lit + ": "))
  elif(i[0]!='#' and len(i)>2):
    lit=''
    func=''
    lit1=''
    j=0
    while(i[j]!='=' and i[j]!=' '):
      lit+=i[j]
      j+=1
    j+=3
    while(i[j]!='('):
      func+=i[j]
      j+=1
    j+=1
    while(i[j]!=')'):
        lit1+=i[j]
        j+=1
    lit1=lit1.split(', ')
    if(func=='AND'):
      if(lit in l.keys()):
        if(l[lit]==0):
          x+=ANDO0(lit1)
        elif(l[lit]==1):
          x+=ANDO1(lit1)
        else:
          x+=AND(lit1,lit)  
      else:
        x+=AND(lit1,lit)
    elif(func=='OR'):
      if(lit in l.keys()):
        if(l[lit]==0):
          x+=ORO0(lit1)
        elif(l[lit]==1):
          x+=ORO1(lit1)
        else:
          x+=OR(lit1,lit)  
      else:
        x+=OR(lit1,lit)
    elif(func=='NAND'):
      if(lit in l.keys()):
        if(l[lit]==0):
          x+=NANDO0(lit1)
        elif(l[lit]==1):
          x+=NANDO1(lit1)
        else:
          x+=NAND(lit1,lit)  
      else:
        x+=NAND(lit1,lit)
    elif(func=='NOR'):
      if(lit in l.keys()):
        if(l[lit]==0):
          x+=NORO0(lit1)
        elif(l[lit]==1):
          x+=NORO1(lit1)
        else:
          x+=NOR(lit1,lit)  
      else:
        x+=NOR(lit1,lit)
    elif(func=='NOT'):
      if(lit in l.keys()):
        if(l[lit]==0):
          x+=NOTO0(lit1)
          unit1.append(lit1[0])
        elif(l[lit]==1):
          x+=NOTO1(lit1)
          unit0.append(lit1[0])
        else:
          x+=NOT(lit1,lit)  
      else:
        x+=NOT(lit1,lit)

k={}
print(x)
x1=[]
x2=[]
for literal in unit1:
  k[literal]=True
  for i in x:
    if(literal not in i):
      x1.append(i)
  for i in x1:
    x2.append(i.difference({'!'+literal}))
  x=x2
  #print(x)
  x1=[]
  x2=[]
for literal in unit0:
  for i in x:
    if(('!'+literal) not in i):
      x1.append(i)
  for i in x1:
    x2.append(i.difference({literal}))
  x=x2
  x1=[]
  x2=[]
x.sort(key=len)
#print(x)
while(len(x[0])==1):
  literal=next(iter(x[0]))
  if(literal[0]!='!'):
    for i in x:
      if(literal not in i):
        x1.append(i)
    for i in x1:
      x2.append(i.difference({'!'+literal}))
    x=x2
    #print(x)
    x1=[]
    x2=[]
  else:
    for i in x:
      if((literal) not in i):
        x1.append(i)
    for i in x1:
      x2.append(i.difference({literal[1::]}))
    x=x2
    x1=[]
    x2=[]
  x.sort(key=len)

print(dpll(x))