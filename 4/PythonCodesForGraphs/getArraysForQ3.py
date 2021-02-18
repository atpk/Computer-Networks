ages=[]
f=open("./q3_n.txt","r")
for x in range(0,1001,1):
	y=f.readline().split(' ')[-2][5:]
	if(x>=1):
		ages.append(float(y))

f.close()
fp=open("a.txt", "w")
for i in ages:
  fp.write(str(i))
  fp.write(", ")
fp.close()
