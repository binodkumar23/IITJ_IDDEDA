import random
import time

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




v=''
literals= int(input("No. of literals: "))
clauses=int(input("No. of clauses: "))
start=time.time()
rint= random.sample(range(literals*10), literals)
for c in range(clauses):
  v+='('
  rlrange=random.randint(int(literals/2),literals)
  for l in  range(rlrange):
    randomBool=random.randint(0,2)
    if(randomBool==0):
      v+='!'
    #v+=random.choice(string.ascii_letters)
    v+=str(rint[l])
    if(l!=rlrange-1):
      v+='+'
  v+=')'
#v=input()
print(v)
v=v[1:len(v)-1]
k=v.split(')(')
x=[]
for i in k:
  x.append(set(i.split('+')))

print(dpll(x))
print(time.time()-start)

