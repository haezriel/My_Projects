### Adapted from code in Artificial Intelligence: A Modern Approach, by
### Russell and Norvig

### Note to students: please do not use the AIMA code. Use this
### code instead. I've made some changes to the AIMA code to make it simpler
### and easier to work with. Using the AIMA code directly will just give you
#### headaches.

import random

### global variable holding all possible agent actions
agent_actions = ['Left', 'Right', 'Suck','Up','Down']

class Agent :
	"""An Agent is a subclass of Object with one required slot,
	.program, which should hold a function that takes one argument, the
	percept, and returns an action. (What counts as a percept or action
	will depend on the specific environment in which the agent exists.)"""

	def __init__(self):
		self.alive = True

	def program(self, percept):
		return raw_input('Percept=%s; action? ' % percept)


### In the 2 room environment, there are three actions: Left, Right and Suck

class RandomAgent(Agent):
	"An agent that chooses an action at random, ignoring all percepts."
	def __init__(self, actions):
		self.actions = actions

	def program(self, percept) :
		action = random.choice(self.actions)
		print "Percept: %s Action: %s" % (percept, action)
		return action


class SimpleReflexAgent(Agent):

	def __init__(self,actions):
		self.actions=actions

	def program(self, percept):
		action = {'Dirty' : self.actions[2],
					 (0,0) : self.actions[1],
					 (1,0) : self.actions[1],
                (2,0) : self.actions[3],
                (0,1) : self.actions[1],
                (1,1) : self.actions[4],
                (2,1) : self.actions[3],
                (0,2) : self.actions[4],
                (1,2) : self.actions[0],
                (2,2) : self.actions[0]}
		
		if percept[1]=='Dirty':
			action=action[percept[1]]
			print "Percept: %s Action: %s" % (percept, action)
			return action
		else:
			action=action[percept[0]]
			print "Percept: %s Action: %s" % (percept, action)
			return action
		
		return action[percept[0]]

class ModelReflexAgent(Agent):
		
	def __init__(self,actions):
		self.actions=actions
		rooms ={(0,0):'Unknown',
				(0,1):'Unknown',
				(0,2):'Unknown',
				(1,0):'Unknown',
				(1,1):'Unknown',
				(1,2):'Unknown',
				(2,0):'Unknown',
				(2,1):'Unknown',
				(2,2):'Unknown'}
		self.rooms=rooms
		self.flag=0

	def program(self,percept):

		val=percept[0]
		x=val[0]
		y=val[1]

		if cmp(val,(1,1))==0:
			self.flag=1
		
		if self.flag==0:		
			if x>1:
				action='Left'
				print "Percept: %s Action: %s" % (percept, action)
				return action
			if y>1:
				action='Down'
				print "Percept: %s Action: %s" % (percept, action)
				return action
			if x<1:
				action='Right'
				print "Percept: %s Action: %s" % (percept, action)
				return action
			if y<1:
				action='Up'
				print "Percept: %s Action: %s" % (percept, action)
				return action

		if percept[1]=='Dirty':
			action=self.actions[2]
			self.rooms[percept[0]]='Clean'
			print "Percept: %s Action: %s" % (percept, action)
			return action
		else:
			if x<2:
				if self.rooms[(x+1,y)]!='Clean':
					action='Right'
					self.rooms[percept[0]]='Clean'
					print "Percept: %s Action: %s" % (percept, action)
					return action
			if y<2:
				if self.rooms[(x,y+1)]!='Clean':
					action='Up'
					self.rooms[percept[0]]='Clean'
					print "Percept: %s Action: %s" % (percept, action)
					return action
			if x>0:
				if self.rooms[(x-1,y)]!='Clean':
					action='Left'
					self.rooms[percept[0]]='Clean'
					print "Percept: %s Action: %s" % (percept, action)
					return action
			if y>0:
				if self.rooms[(x,y-1)]!='Clean':
					action='Down'
					self.rooms[percept[0]]='Clean'
					print "Percept: %s Action: %s" % (percept, action)
					return action
		print("Completed cleaning")
