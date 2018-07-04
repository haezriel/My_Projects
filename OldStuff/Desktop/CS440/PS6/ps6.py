"""
	Michael Allen-Bond
	CS440 Artificial Intelligence
	Dr. Scott Wallace
"""

import os, glob
import random
from canonicalize import * 
import operator
import sys

#These are just code snippets from the web that I copied for  use.
'''canonicalize("data/DR")
foo = "blahblahblah"
bar = "somethingblahblahblahmeep"
if foo in bar:
print("I just printed {0} pages to the printer {1}".format(num, printer))
import sys

orig_stdout = sys.stdout
f = file('out.txt', 'w')
sys.stdout = f

sys.stdout = orig_stdout
f.close()

'''


"""PROBLEM 2"""

def strawman(d):
	"""Output(with intput="data")"""
	"""         DR(Guessed)	|  DT(Guessed)	|  L(Guessed)
	DR(Actual)	|	3		|		70		|	2 
	DT(Actual)	|	9		|		63		|	3 
	 L(Actual)	|	0		|		1		|	74 
	"""
	os.chdir(d)
	ct=0
	strdt="deed of trust"
	strdr="reconveyance"
	c_matrix={(0,0):0,
				(0,1):0,
				(0,2):0,
				(1,0):0,
				(1,1):0,
				(1,2):0,
				(2,0):0,
				(2,1):0,
				(2,2):0}
	for dir in glob.glob("TEST-*"):
		os.chdir(dir)
		for file in glob.glob("*.txt"):
			tr=canonicalize(file)
			if strdt in tr:
				c_matrix[(ct,1)]=c_matrix[(ct,1)]+1
			elif strdr in tr:
				c_matrix[(ct,0)]=c_matrix[(ct,0)]+1
			else:
				c_matrix[(ct,2)]=c_matrix[(ct,2)]+1
		ct=ct+1
		os.chdir("..")
	print "                   DR(Guessed)\t|  DT(Guessed)\t|  L(Guessed)"
	print "DR(Actual)\t|\t{0}\t|\t{1}\t|\t{2} ".format(c_matrix[(0,0)],c_matrix[(0,1)],c_matrix[(0,2)])
	print "DT(Actual)\t|\t{0}\t|\t{1}\t|\t{2} ".format(c_matrix[(1,0)],c_matrix[(1,1)],c_matrix[(1,2)])
	print " L(Actual)\t|\t{0}\t|\t{1}\t|\t{2} ".format(c_matrix[(2,0)],c_matrix[(2,1)],c_matrix[(2,2)])
	os.chdir("..")
strawman("data")

"""PROBLEM 3"""

def readdir(dir):
	words={}
	os.chdir(dir)
	for file in glob.glob("*.txt"):
		tr=canonicalize(file)
		for i in tr.split():
			if i in words:
				words[i]=words[i]+1
			else:
				words[i]=1
	os.chdir("..")
	return words

def freqword(d):
	os.chdir(d)
	orig_stdout = sys.stdout
	dr = file('DR.words', 'w')
	dt = file('DT.words', 'w')
	l = file('L.words', 'w')
	wordsdr=readdir("DR")
	wordsdt=readdir("DT")
	wordsl=readdir("L")
	sorted_dr = sorted(wordsdr.items(), key=operator.itemgetter(1))
	sorted_dt = sorted(wordsdt.items(), key=operator.itemgetter(1))
	sorted_l = sorted(wordsl.items(), key=operator.itemgetter(1))
	sorted_dr.reverse()
	sorted_dt.reverse()
	sorted_l.reverse()
	os.chdir("..")
	sys.stdout = dr
	for i in range(200):
		print sorted_dr[i]
	sys.stdout = dt
	for i in range(200):
		print sorted_dt[i]

	sys.stdout = l
	for i in range(200):
		print sorted_l[i]

	sys.stdout = orig_stdout
	dr.close()
	dt.close()
	l.close()

freqword("data")

"""PROBLEM 4"""

def bernoulli_fv(f):
	"""
	data/TEST-DR/OR_Coos_2008-04-03__08003323.txt :
	['beneficiary', 'county', 'deed', 'described', 'entitled', 'executed', 'instrument', 'property', 'recorded', 'recording', 'state', 'trust', 'trustee']

	data/TEST-DT/OR_Coos_2008-04-03__08003293.txt :
	['beneficiary', 'county', 'deed', 'described', 'entitled', 'executed', 'instrument', 'lien', 'notice', 'property', 'reconveyance', 'recorded', 'recording', 'state', 'trust', 'trustee']

	data/TEST-L/OR_Coos_2008-04-07__08003406.txt :
	['county', 'lien', 'notice', 'property', 'recording', 'state']
	"""
	tr=canonicalize(f)
	print f,":"
	wl=["beneficiary","county","deed","described",
		"entitled","executed","instrument","lien",
		"notice","property","reconveyance","recorded",
		"recording","state","trust","trustee"]
	match=[]
	j=0
	for i in range(16):
		if wl[i] in tr:
			match.append(wl[i])
			j=j+1
	match=sorted(match)
	print match
	return match


#bernoulli_fv("data/TEST-DR/OR_Coos_2008-04-03__08003323.txt")
#bernoulli_fv("data/TEST-DT/OR_Coos_2008-04-03__08003293.txt")
#bernoulli_fv("data/TEST-L/OR_Coos_2008-04-07__08003406.txt")


"""PROBLEM 5"""
def predict(wl, pt, dname,fp):
	orig_stdout = sys.stdout
	c_matrix={}
	os.chdir(dname)
	for files in glob.glob("*.txt"):
		tr=canonicalize(files)
		proddr=1/3.0
		proddt=1/3.0
		prodl=1/3.0
		for i in range (16):
			if wl[i] in tr:
				if pt[i][0]==0:
					proddr= proddr*.001
				elif pt[i][0]== 1:
					proddr= proddr*.999
				else:
					proddr=proddr*pt[i][0]
				if pt[i][1] == 0:
					proddt= proddt*.001
				elif pt[i][1]== 1:
					proddt= proddt*.999
				else:
					proddt=proddt*pt[i][1]
				if pt[i][2] == 0:
					prodl= prodl*.001
				elif pt[i][2]== 1:
					prodl= prodl*.999
				else:
					prodl=prodl*pt[i][2]
		if max(prodl,proddt,proddr) == proddr:
			c_matrix[files]="DR"
		elif max(prodl,proddt,proddr) == proddt:
			c_matrix[files]="DT"	
		else:
			c_matrix[files]="L"
	os.chdir("..")
	fpt = file(fp,'w')
	sys.stdout = fpt
	for key in c_matrix:
		print key, ":", c_matrix[key]
	sys.stdout = orig_stdout
	fpt.close()
	return c_matrix			



def MVB():
	wl=["beneficiary","county","deed","described",
	"entitled","executed","instrument","lien",
	"notice","property","reconveyance","recorded",
	"recording","state","trust","trustee"]
	os.chdir("data")
	"""0=DR, 1=DT, 2=L"""
	pt= [[0 for _ in range(3)] for _ in range(16)]

	for i in range (16):
		wc=0.0
		fc=0.0
		for files in glob.glob("DR/*.txt"):
			fc=fc+1.0
			tr=canonicalize(files)
			if wl[i] in tr:
				wc=wc+1.0
		pt[i][0]=wc/fc

	for i in range (16):
		wc=0.0
		fc=0.0
		for files in glob.glob("DT/*.txt"):
			fc=fc+1.0
			tr=canonicalize(files)
			if wl[i] in tr:
				wc=wc+1.0
		pt[i][1]=wc/fc

	for i in range (16):
		wc=0.0
		fc=0.0
		for files in glob.glob("L/*.txt"):
			fc=fc+1.0
			tr=canonicalize(files)
			if wl[i] in tr:
				wc=wc+1.0
		pt[i][2]=wc/fc

	dr='dr.results'
	dt='dt.results'
	l='l.results'
	dr_matrix=predict(wl,pt,"TEST-DR",dr)
	dt_matrix=predict(wl,pt,"TEST-DT",dt)
	l_matrix=predict(wl,pt,"TEST-L",l)
	c_matrix={(0,0):0,
				(0,1):0,
				(0,2):0,
				(1,0):0,
				(1,1):0,
				(1,2):0,
				(2,0):0,
				(2,1):0,
				(2,2):0}


	for dir in glob.glob("TEST-*"):
		os.chdir(dir)
		for files in glob.glob("*.txt"):
			if files in dr_matrix:
				if dr_matrix[files]=="DR":
					c_matrix[(0,0)]=c_matrix[(0,0)]+1
				elif dr_matrix[files]=="DT":
					c_matrix[(0,1)]=c_matrix[(0,1)]+1
				else:
					c_matrix[(0,2)]=c_matrix[(0,2)]+1
			elif files in dt_matrix:
				if dt_matrix[files]=="DR":
					c_matrix[(1,0)]=c_matrix[(1,0)]+1
				elif dt_matrix[files]=="DT":
					c_matrix[(1,1)]=c_matrix[(1,1)]+1
				else:
					c_matrix[(1,2)]=c_matrix[(1,2)]+1
			elif files in l_matrix:
				if l_matrix[files]=="DR":
					c_matrix[(2,0)]=c_matrix[(2,0)]+1
				elif l_matrix[files]=="DT":
					c_matrix[(2,1)]=c_matrix[(2,1)]+1
				else:
					c_matrix[(2,2)]=c_matrix[(2,2)]+1
		os.chdir("..")
	orig_stdout=sys.stdout

	fp= file('bernoulli.results','w')
	sys.stdout=fp
	print "                  DR(Guessed)\t|  DT(Guessed)\t|  L(Guessed)"
	print "DR(Actual)\t|\t{0}\t|\t{1}\t|\t{2} ".format(c_matrix[(0,0)],c_matrix[(0,1)],c_matrix[(0,2)])
	print "DT(Actual)\t|\t{0}\t|\t{1}\t|\t{2} ".format(c_matrix[(1,0)],c_matrix[(1,1)],c_matrix[(1,2)])
	print " L(Actual)\t|\t{0}\t|\t{1}\t|\t{2} ".format(c_matrix[(2,0)],c_matrix[(2,1)],c_matrix[(2,2)])

	sys.stdout = orig_stdout
	fp.close()
	#for i in range(16):
		#print wl[i], pt[i]


MVB()



'''if wc/fc==1:
	pt[i][1]=.999
elif wc/fc==0:
	pt[i][1]=.001
else:'''

