# search.py
# ---------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

"""
In search.py, you will implement generic search algorithms which are called 
by Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
  """
  This class outlines the structure of a search problem, but doesn't implement
  any of the methods (in object-oriented terminology: an abstract class).
  
  You do not need to change anything in this class, ever.
  """
  
  def getStartState(self):
     """
     Returns the start state for the search problem 
     """
     util.raiseNotDefined()
    
  def isGoalState(self, state):
     """
       state: Search state
    
     Returns True if and only if the state is a valid goal state
     """
     util.raiseNotDefined()

  def getSuccessors(self, state):
     """
       state: Search state
     
     For a given state, this should return a list of triples, 
     (successor, action, stepCost), where 'successor' is a 
     successor to the current state, 'action' is the action
     required to get there, and 'stepCost' is the incremental 
     cost of expanding to that successor
     """
     util.raiseNotDefined()

  def getCostOfActions(self, actions):
     """
      actions: A list of actions to take
 
     This method returns the total cost of a particular sequence of actions.  The sequence must
     be composed of legal moves
     """
     util.raiseNotDefined()
           

def tinyMazeSearch(problem):
  """
  Returns a sequence of moves that solves tinyMaze.  For any other
  maze, the sequence of moves will be incorrect, so only use this for tinyMaze
  """
  from game import Directions
  s = Directions.SOUTH
  w = Directions.WEST
  return  [s,s,w,s,w,w,s,w]


"""
Jameel Kaba (jkaba) 250796017
CS3346 Assignment 1
"""

class Node():
  """
  Node class is a container used to store the current state of a node,
  the list of directions that have to be followed from the start state
  in order to get to the current state and the specific problem in which
  the node will be used. Node also contains a cost, and heuristic value.
  """
  
  #Constructor
  def __init__(self, state, path, cost=0, heuristic=0, problem=None):
    self.state = state
    self.path = path
    self.cost = cost
    self.heuristic = heuristic
    self.problem = problem

  #Get Successor method to obtain a node's successor's
  def getSuccessors(self,heuristicFunction=None):
      
    #Create an array to store the children nodes
    children = []
    
    #For loop to get the successors from a node's state
    for successor in self.problem.getSuccessors(self.state):
        
      #Store the state into position 0
      state = successor[0]
      
      #Create a list that containes the path of a node
      path = list(self.path)
      
      #Append the object in position 1 of successor to the list
      path.append(successor[1])
      
      #Calculate the cost of the node's
      cost = self.cost + successor[2]
      
      #If it is a heuristic function then calculate the heuristic
      if heuristicFunction:
        heuristic = heuristicFunction(state,self.problem)
      
      #Else set the heuristic to 0
      else:
        heuristic = 0
      
      #Create a node based on the info obtained and append it to the children array
      node = Node(state, path, cost, heuristic, self.problem)
      children.append(node)
        
    #Return the array of children
    return children

def depthFirstSearch(problem):
  """
  Search the deepest nodes in the search tree first [p 85].
  
  Your search algorithm needs to return a list of actions that reaches
  the goal.  Make sure to implement a graph search algorithm [Fig. 3.7].
  
  To get started, you might want to try some of these simple commands to
  understand the search problem that is being passed in:
  
  print "Start:", problem.getStartState()
  print "Is the start a goal?", problem.isGoalState(problem.getStartState())
  print "Start's successors:", problem.getSuccessors(problem.getStartState())
  """
  "*** YOUR CODE HERE ***"
  
  #Create an empty set to store the visited nodes
  visited = set()
  
  #Frontier will be a stack
  frontier = util.Stack()
  
  #Create a node to store the initial info and push into the stack
  startNode = Node(problem.getStartState(), [], 0, 0, problem)
  frontier.push(startNode)
  
  #While loop
  while True:
      
    #If the frontier is empty return false (default case)
    if frontier.isEmpty():
      return False
    
    #Pop the next node off the stack
    node = frontier.pop()
    
    #If the node is the goal state then return it's path
    if problem.isGoalState(node.state):
      return node.path
    
    #If the node hasn't been visited then add it to the set
    if node.state not in visited:
      visited.add(node.state)
      
      #Push the node's children onto the stack
      for childNode in node.getSuccessors():
        frontier.push(childNode)

def breadthFirstSearch(problem):
  "Search the shallowest nodes in the search tree first. [p 81]"
  "*** YOUR CODE HERE ***"
  
  #Create an empty set to store the visited nodes
  visited = set()
  
  #Frontier will be a standard queue
  frontier = util.Queue()
  
  #Create a start node that stores the initial information and push it into the frontier
  startNode = Node(problem.getStartState(), [], 0, 0, problem)
  frontier.push(startNode)
  
  #While loop
  while True:
      
    #If the frontier is empty return false (default case)
    if frontier.isEmpty():
      return False
    
    #Pop the next node off the frontier
    node = frontier.pop()
    
    #If this node is the goal state then return it's path
    if problem.isGoalState(node.state):
      return node.path
    
    #If the node hasn't been visited then add it to the set
    if node.state not in visited:
      visited.add(node.state)
      
      #Push the node's children into the queue
      for childNode in node.getSuccessors():
        frontier.push(childNode)
      
def uniformCostSearch(problem):
  "Search the node of least total cost first. "
  "*** YOUR CODE HERE ***"
  
  #Create an empty set to store the visited nodes
  visited = set()
  
  #Frontier will be a priority Queue
  frontier = util.PriorityQueue()
  
  #Create a node to store initial information
  startNode = Node(problem.getStartState(), [], 0, 0, problem)

  #Push the starting node into the frontier
  frontier.push(startNode, startNode.cost)

  #While loop
  while True:
      
    #If the frontier is empty then return False (default case)
    if frontier.isEmpty():
      return False
    
    #Pop the next node off the queue
    node = frontier.pop()

    #If the node is the goal state then return the node's path
    if problem.isGoalState(node.state):
      return node.path

    #If the node hasn't been visited then add it to the set
    if node.state not in visited:
      visited.add(node.state)
      
      #Push the children nodes in the frontier while keeping a track of cost
      for childNode in node.getSuccessors():
        frontier.push(childNode, childNode.cost)

def nullHeuristic(state, problem=None):
  """
  A heuristic function estimates the cost from the current state to the nearest
  goal in the provided SearchProblem.  This heuristic is trivial.
  """
  return 0

def aStarSearch(problem, heuristic=nullHeuristic):
  "Search the node that has the lowest combined cost and heuristic first."
  "*** YOUR CODE HERE ***"
  
  #Create an empty set to keep track of visited nodes
  visited = set()
  
  #Frontier will be a priority queue
  frontier = util.PriorityQueue()
  
  #Create the starting node and push it into the frontier
  startNode = Node(problem.getStartState(), [], 0, 0, problem)
  frontier.push(startNode, startNode.cost + startNode.heuristic)
  
  #While loop
  while True:
      
    #If the frontier is empty then return false (default case)
    if frontier.isEmpty():
      return False
    
    #Pop the next node off the queue
    node = frontier.pop()

    #If the node is the goal state then return the path
    if problem.isGoalState(node.state):
      return node.path

    #If the node hasn't been visited then add it to the set
    if node.state not in visited:
      visited.add(node.state)
      
      #Push the children nodes into the frontier while keeping track of the heuristic
      for childNode in node.getSuccessors(heuristic):
        frontier.push(childNode, childNode.cost + childNode.heuristic)
  
# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch