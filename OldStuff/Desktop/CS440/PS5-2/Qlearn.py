"""
	Michael Allen-Bond
	CS440 Artificial Intelligence
	Dr. Scott Wallace
"""

import random
random.seed(0)


def ChooseAction(Q,n,i,x,y):
	seq=['left','right','up','down']
	a=Q[(x,y,'left')]
	b=Q[(x,y,'right')]
	c=Q[(x,y,'up')]
	d=Q[(x,y,'down')]
	if i<n/2:
		if random.randint(0,9) < 3:
			action = random.choice(seq)
		else:
			if a ==max(a,b,c,d):
				action='left'
			if b ==max(a,b,c,d):
				action='right'
			if c ==max(a,b,c,d):
				action='up'
			if d ==max(a,b,c,d):
				action='down'
	else:
		if a ==max(a,b,c,d):
			action='left'
		if b ==max(a,b,c,d):
			action='right'
		if c ==max(a,b,c,d):
			action='up'
		if d ==max(a,b,c,d):
			action='down'
	return action

"""if 8 or 9, does .1 probability behavior"""
def PerformAction(x,y,action,board):
	key=random.randint(0,9) 
	if key == 8:	
		if action=='left' or action =='right':
			action='down'
		if action == 'up' or action == 'down':
			action='left'
	if key == 9:
		if action=='left' or action =='right':
			action='up'
		if action == 'up' or action == 'down':
			action='right'
	if action=='left':
		if (x-1,y) in board:
			return (x-1,y)
		else:
			return (x,y)
	if action=='right':
		if (x+1,y) in board:
			return (x+1,y)
		else:
			return (x,y)
	if action=='up':
		if (x,y+1) in board:
			return (x,y+1)
		else:
			return (x,y)
	if action=='down':
		if (x,y-1) in board:
			return (x,y-1)
		else:
			return (x,y)

board ={(1,1):-.04,
		(1,2):-.04,
		(1,3):-.04,
		(2,1):-.04,
		(2,3):-.04,
		(3,1):-.04,
		(3,2):-.04,
		(3,3):-.04,
		(4,1):-.04,
		(4,2):-1,
		(4,3):1}

action ={(1,1):None,
		(1,2):None,
		(1,3):None,
		(2,1):None,
		(2,3):None,
		(3,1):None,
		(3,2):None,
		(3,3):None,
		(4,1):None,
		(4,2):'term',
		(4,3):'term'}

Nsa = {(1,1,'left'):0,
		(1,1,'right'):0,
		(1,1,'up'):0,
		(1,1,'down'):0,
		(1,2,'left'):0,
		(1,2,'right'):0,
		(1,2,'up'):0,
		(1,2,'down'):0,
		(1,3,'left'):0,
		(1,3,'right'):0,
		(1,3,'up'):0,
		(1,3,'down'):0,
		(2,1,'left'):0,
		(2,1,'right'):0,
		(2,1,'up'):0,
		(2,1,'down'):0,
		(2,3,'left'):0,
		(2,3,'right'):0,
		(2,3,'up'):0,
		(2,3,'down'):0,
		(3,1,'left'):0,
		(3,1,'right'):0,
		(3,1,'up'):0,
		(3,1,'down'):0,
		(3,2,'left'):0,
		(3,2,'right'):0,
		(3,2,'up'):0,
		(3,2,'down'):0,
		(3,3,'left'):0,
		(3,3,'right'):0,
		(3,3,'up'):0,
		(3,3,'down'):0,
		(4,1,'left'):0,
		(4,1,'right'):0,
		(4,1,'up'):0,
		(4,1,'down'):0,
		(4,2,'None'):0,
		(4,3,'None'):0
		}

Q = {(1,1,'left'):0,
		(1,1,'right'):0,
		(1,1,'up'):0,
		(1,1,'down'):0,
		(1,2,'left'):0,
		(1,2,'right'):0,
		(1,2,'up'):0,
		(1,2,'down'):0,
		(1,3,'left'):0,
		(1,3,'right'):0,
		(1,3,'up'):0,
		(1,3,'down'):0,
		(2,1,'left'):0,
		(2,1,'right'):0,
		(2,1,'up'):0,
		(2,1,'down'):0,
		(2,3,'left'):0,
		(2,3,'right'):0,
		(2,3,'up'):0,
		(2,3,'down'):0,
		(3,1,'left'):0,
		(3,1,'right'):0,
		(3,1,'up'):0,
		(3,1,'down'):0,
		(3,2,'left'):0,
		(3,2,'right'):0,
		(3,2,'up'):0,
		(3,2,'down'):0,
		(3,3,'left'):0,
		(3,3,'right'):0,
		(3,3,'up'):0,
		(3,3,'down'):0,
		(4,1,'left'):0,
		(4,1,'right'):0,
		(4,1,'up'):0,
		(4,1,'down'):0,
		(4,2,None):0,
		(4,3,None):0
		}
i=0
n=2000
alpha=.1
while i<n:
	(x,y)=(1,1)
	(x_old,y_old)=(0,0)
	a_old=None
	r_old=0
	while 1:	
		r=board[(x,y)]
		if (x_old,y_old) in board:
			Nsa[(x_old,y_old,a_old)]=Nsa[(x_old,y_old,a_old)]+1
			if (x,y) == (4,3):
				f=1
			elif (x,y) == (4,2):
				f=-1
			else:
				a=Q[(x,y,'left')]
				b=Q[(x,y,'right')]
				c=Q[(x,y,'up')]
				d=Q[(x,y,'down')]
				f=max(a,b,c,d)
			Q[(x_old,y_old,a_old)]=Q[(x_old,y_old,a_old)]+alpha*(r_old+f-Q[(x_old,y_old,a_old)])
		if (x,y) in board and action[(x,y)]=='term':
			Q[(x,y,None)]=board[(x,y)]
			break
		direction=ChooseAction(Q,n,i,x,y)
		(x_old,y_old)=(x,y)
		(x,y)=PerformAction(x,y,direction,board)
		a_old=direction
		r_old=r
	i=i+1

a='left'
b='right'
c='up'
d='down'
for x in range (1,5):
	for y in range (1,4):
		if (x,y,a) in Q:
			print 'State({},{}): left Qvalue: {}, left Frequency: {}'.format(x,y,Q[(x,y,a)],Nsa[(x,y,a)])
		if (x,y,b) in Q:
			print 'State({},{}): right Qvalue: {}, right Frequency: {}'.format(x,y,Q[(x,y,b)],Nsa[(x,y,b)])
		if (x,y,c) in Q:
			print 'State({},{}): up Qvalue: {}, up Frequency: {}'.format(x,y,Q[(x,y,c)],Nsa[(x,y,c)])
		if (x,y,d) in Q:
			print 'State({},{}): down Qvalue: {}, down Frequency: {}'.format(x,y,Q[(x,y,d)],Nsa[(x,y,d)])

for x in range (1,5):
	for y in range (1,4):
		if (x,y,a) in Q and (x,y,b) in Q and (x,y,c) in Q and (x,y,d) in Q:
			f=max(Q[(x,y,a)],Q[(x,y,b)],Q[(x,y,c)],Q[(x,y,d)])
			if Q[(x,y,a)]==f:
				e=a
			if Q[(x,y,b)]==f:
				e=b
			if Q[(x,y,c)]==f:
				e=c
			if Q[(x,y,d)]==f:
				e=d
			print 'State({},{}): Highest Qvalue: {}, Direction: {} '.format(x,y,Q[(x,y,e)],e)			