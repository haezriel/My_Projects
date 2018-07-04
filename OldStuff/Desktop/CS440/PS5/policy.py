"""
	Michael Allen-Bond
	CS440 Artificial Intelligence
	Dr. Scott Wallace
"""


board ={(1,1):0,
		(1,2):0,
		(1,3):0,
		(2,1):0,
		(2,3):0,
		(3,1):0,
		(3,2):0,
		(3,3):0,
		(4,1):0,
		(4,2):-1,
		(4,3):1}

policy ={(1,1):'left',
		(1,2):'left',
		(1,3):'left',
		(2,1):'left',
		(2,3):'left',
		(3,1):'left',
		(3,2):'left',
		(3,3):'left',
		(4,1):'left',
		(4,2):'term',
		(4,3):'term'}
counter=1

while 1:
	unchanged=1
	count=0
	while count<5:
		count=count+1
		for x in range (1,5):
			for y in range (1,4):
				if (x,y) in board:
					if (x+1,y) in board:
						right=board[(x+1,y)]
					else:
						right=board[(x,y)]
					if (x-1,y) in board:
						left=board[(x-1,y)]
					else:
						left=board[(x,y)]
					if (x,y+1) in board:
						up=board[(x,y+1)]
					else:
						up=board[(x,y)]
					if (x,y-1) in board:
						down=board[(x,y-1)]
					else:
						down=board[(x,y)]
					if policy[(x,y)]=='left':
						board[(x,y)]=-.04+.8*left + .1*up +.1*down
					if policy[(x,y)]=='right':
						board[(x,y)]=-.04+.8*right+.1*up +.1*down
					if policy[(x,y)]=='up':
						board[(x,y)]=-.04+.8*up + .1*left + .1*right
					if policy[(x,y)]=='down':
						board[(x,y)]=-.04+.8*down +.1*left + .1*right
	for x in range (1,5):
		for y in range (1,4):
			if (x,y) in board:
				if (x+1,y) in board:
					right=board[(x+1,y)]
				else:
					right=board[(x,y)]
				if (x-1,y) in board:
					left=board[(x-1,y)]
				else:
					left=board[(x,y)]
				if (x,y+1) in board:
					up=board[(x,y+1)]
				else:
					up=board[(x,y)]
				if (x,y-1) in board:
					down=board[(x,y-1)]
				else:
					down=board[(x,y)]
				a=.8*left + .1*up +.1*down
				b=.8*right+.1*up +.1*down
				c=.8*up + .1*left + .1*right
				d=.8*down +.1*left + .1*right
				f=max(a,b,c,d)
				if board[(x,y)]==1 or board[(x,y)]==-1:
					pass
				else:
					if (-.04+f)>board[(x,y)]:
						board[(x,y)]= -.04+f
						if a==f and policy[(x,y)] != 'left':
							policy[(x,y)]='left'
							unchanged=0
						if b==f and policy[(x,y)] != 'right':
							policy[(x,y)]='right'
							unchanged=0
						if c==f and policy[(x,y)] != 'up':
							policy[(x,y)]='up'
							unchanged=0
						if d==f and policy[(x,y)] != 'down':
							policy[(x,y)]='down'
							unchanged=0
	if unchanged==1:
		break
	else:
		print 'Iteration #{}'.format(counter)
		counter=counter+1
		for x in range(1,5):
			for y in range(1,4):
				if (x,y) in board:
					print 'S({},{}): {}, {}'.format(x,y,board[(x,y)], policy[(x,y)])
