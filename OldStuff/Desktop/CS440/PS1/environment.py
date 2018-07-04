### Adapted from code in Artificial Intelligence: A Modern Approach, by
### Russell and Norvig

### Note to students: please do not use the AIMA code. Use this
### code instead. I've made some changes to the AIMA code to make it simpler
### and easier to work with. Using the AIMA code directly will just give you
### headaches.


import random

class Environment:
    """Abstract class representing an Environment.  'Real' Environment classes
    inherit from this. Your Environment will typically need to implement:
        percept:           Define the percept that an agent sees.
        execute_action:    Define the effects of executing an action.
                           Also update the agent.performance slot.
    The environment keeps a list of .objects and .agents (which is a subset
    of .objects). Each agent has a .performance slot, initialized to 0.
    Each object has a .location slot, even though some environments may not
    need this."""

    def __init__(self,):
        self.objects = []
        self.agents = []

        object_classes = [] ## List of classes that can go into environment

    def percept(self, agent):
        "Return the percept that the agent sees at this point. Override this."
        abstract()

    def execute_action(self, agent, action):
        "Change the world to reflect this action. Override this."
        abstract()

    def default_location(self, object):
        "Default location to place a new object with unspecified location."
        return None

    def exogenous_change(self):
        "If there is spontaneous change in the world, override this."
        pass

    def is_done(self):
        "By default, we're done when we can't find a live agent."
        return False

    def step(self):
        """Run the environment for one time step. If the
        actions and exogenous changes are independent, this method will
        do.  If there are interactions between them, you'll need to
        override this method."""
        if not self.is_done():
            actions = [agent.program(self.percept(agent))
                       for agent in self.agents]
            for (agent, action) in zip(self.agents, actions):
                self.execute_action(agent, action)
            self.exogenous_change()

    def run(self, steps=1000):
        """Run the Environment for given number of time steps."""
        self.print_initial_state()
        for step in range(steps):
            if self.is_done():
                self.print_final_state()
                return
            self.step()
        self.print_final_state()

    def print_initial_state(self) :
        """ SHow the initial problem state """
        pass

    def print_final_state(self) :
        """ SHow the final problem state """
        pass

    def add_object(self, object, location=None):
        """Add an object to the environment, setting its location. Also keep
        track of objects that are agents.  Shouldn't need to override this."""
        object.location = location or self.default_location(object)
        self.objects.append(object)
        if isinstance(object, Agent):
            object.performance = 0
            self.agents.append(object)
        return self

    def add_agent(self, ag, location=None) :
        """Add an agent to the environment"""
        ag.location = location or self.default_location(ag)
        ag.performance = 0
        self.agents.append(ag)
        return self
    


class VacuumEnvironment (Environment) :
    def __init__(self):
        Environment.__init__(self)
        self.status = {	(0,0):random.choice(['Clean', 'Dirty']),
							(0,1):random.choice(['Clean', 'Dirty']),
							(0,2):random.choice(['Clean', 'Dirty']),
							(1,0):random.choice(['Clean', 'Dirty']),
							(1,1):random.choice(['Clean', 'Dirty']),
							(1,2):random.choice(['Clean', 'Dirty']),
							(2,0):random.choice(['Clean', 'Dirty']),
							(2,1):random.choice(['Clean', 'Dirty']),
							(2,2):random.choice(['Clean', 'Dirty'])}
    def percept(self, agent):
        "Returns the agent's location, and the location status (Dirty/Clean)."
        return (agent.location, self.status[agent.location])

    def print_initial_state(self) :
        """ Show the initial problem state """
        print "Initial room config: ", self.status

    def print_final_state(self) :
        """ Show the final problem state """
        print "Final room config: ", self.status




    def execute_action(self, agent, action):
        """Change agent's location and/or location's status; track performance.
        Score 10 for each dirt cleaned; -1 for each move."""
        if action == 'Right':			
			if agent.location[0] < 2:
				agent.location=(agent.location[0]+1,agent.location[1])
	  			agent.performance -= 1
        elif action == 'Left':
			if agent.location[0] > 0:			
				agent.location=(agent.location[0]-1,agent.location[1])
	  			agent.performance -= 1
        elif action == 'Up':
			if agent.location[1] < 2:				
				agent.location=(agent.location[0],agent.location[1]+1)
	  			agent.performance -= 1
        elif action == 'Down':
			if agent.location[1] > 0:		
				agent.location=(agent.location[0],agent.location[1]-1)
	  			agent.performance -= 1
        elif action == 'Suck':
            if self.status[agent.location] == 'Dirty':
                agent.performance += 10
            self.status[agent.location] = 'Clean'

    def default_location(self, object):
        "Agents start in either location at random."
        return random.choice([(0,0), (1,0),(2,0),(0,1),(0,2),(1,1),(1,2),(2,1),(2,2)])


    
