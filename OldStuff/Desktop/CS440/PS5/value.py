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

delta=1
err=0
count=1
while 1:
	delta=0
	print 'Iteration #{}:'.format(count)
	for x in range (1,5):
		for y in range (1,4):
			if (x,y) in board:
				U=board[(x,y)]
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
				a=.8*up + .1*left + .1*right
				b=.8*left + .1*up +.1*down
				c=.8*down +.1*left + .1*right
				d=.8*right+.1*up +.1*down
				if board[(x,y)]==1 or board[(x,y)]==-1:
					pass
				else:
					board[(x,y)]=-.04+ max(a,b,c,d)
				print 'U({},{}): {}'.format(x,y,board[(x,y)])
				if (abs(board[(x,y)]) - abs(U)) > delta:
					delta=abs(board[(x,y)]) - abs(U)
	if delta < .0001:
		break
	else:
		count=count+1
