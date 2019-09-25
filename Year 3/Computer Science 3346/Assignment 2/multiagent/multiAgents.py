# multiAgents.py
# --------------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

"""
CS3346A Assignment 2
Jameel Kaba (jkaba) 250796017
"""

from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
  """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
  """


  def getAction(self, gameState):
    """
    You do not need to change this method, but you're welcome to.

    getAction chooses among the best options according to the evaluation function.

    Just like in the previous project, getAction takes a GameState and returns
    some Directions.X for some X in the set {North, South, West, East, Stop}
    """
    # Collect legal moves and successor states
    legalMoves = gameState.getLegalActions()

    # Choose one of the best actions
    scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
    bestScore = max(scores)
    bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
    chosenIndex = random.choice(bestIndices) # Pick randomly among the best

    "Add more of your code here if you want to"

    return legalMoves[chosenIndex]

  def evaluationFunction(self, currentGameState, action):
    """
    Design a better evaluation function here.

    The evaluation function takes in the current and proposed successor
    GameStates (pacman.py) and returns a number, where higher numbers are better.

    The code below extracts some useful information from the state, like the
    remaining food (oldFood) and Pacman position after moving (newPos).
    newScaredTimes holds the number of moves that each ghost will remain
    scared because of Pacman having eaten a power pellet.

    Print out these variables to see what you're getting, then combine them
    to create a masterful evaluation function.
    """
    # Useful information you can extract from a GameState (pacman.py)
    successorGameState = currentGameState.generatePacmanSuccessor(action)
    newPos = successorGameState.getPacmanPosition()
    oldFood = currentGameState.getFood()
    newGhostStates = successorGameState.getGhostStates()
    newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

    "*** YOUR CODE HERE ***"
    
    # Set the total score to 0
    totalScore = 0.0
    
    # for the ghost in the new ghost states
    for ghost in newGhostStates:
        
      # set the value of distance to be the manhattan distance of the ghost position
      # and the new pacman position
      distance = manhattanDistance(ghost.getPosition(), newPos)
      
      # If the distance is 1 or less
      if distance <= 1:
          
        # If the scared timer for the ghost is not 0
        if ghost.scaredTimer != 0:
            
          # Add 2000 points to the score
          totalScore = totalScore + 2000
        
        # Else the scared timer is 0 so take away 200 points from the score
        else:
          totalScore = totalScore - 200

    # For the capsules in the current game state
    for capsule in currentGameState.getCapsules():
        
      # Set the distance to be the manhattan distance between pacman and a capsule
      distance = manhattanDistance(capsule, newPos)
      
      # If distance is 0, then add 100 to the total score
      if distance == 0:
        totalScore = totalScore + 100
     
      # If distance is not 0, then add 10/distance to the score
      else:
        totalScore = totalScore + (10.0/distance)

    # Search the map for the remaining food positions
    for x in range(oldFood.width):
      for y in range(oldFood.height):
          
        # If the old food is in position x, y
        if oldFood[x][y]:
            
          # Set the distance to be the manhattan distance between the food at x, y
          # And pacman's new position
          distance = manhattanDistance((x,y),newPos)
          
          # If distance = 0 then add 100 to the total score
          if distance == 0:
            totalScore = totalScore + 100
          
          # If distance is not 0, then add 1/(distance*distance) to the score
          else:
            totalScore = totalScore + (1.0/(distance*distance))

    # Return the value of total score
    return totalScore

def scoreEvaluationFunction(currentGameState):
  """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
  """
  return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
  """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
  """

  def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
    self.index = 0 # Pacman is always agent index 0
    self.evaluationFunction = util.lookup(evalFn, globals())
    self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
  """
    Your minimax agent (question 2)
  """

  def getAction(self, gameState):
    """
      Returns the minimax action from the current gameState using self.depth
      and self.evaluationFunction.

      Here are some method calls that might be useful when implementing minimax.

      gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

      Directions.STOP:
        The stop direction, which is always legal

      gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

      gameState.getNumAgents():
        Returns the total number of agents in the game
    """
    "*** YOUR CODE HERE ***"
    
    """
    This function will result in low scores if the ghost is moving randomly;
    Pacman may get stuck in a capsule spot and die
    This function works much better when using "-g DirectionalGhost"
    """
    
    # maxValue used to compute the max value for max nodes in minimax
    # Accepts a game state, depth, and number of ghosts as input
    def maxValue(gameState, depth, numGhosts):
        
      # If the game state is in either win or lose, or the depth is set to 0
      if gameState.isWin() or gameState.isLose() or depth == 0:
          
        # Then return the evaluation function of the game state
        return self.evaluationFunction(gameState)
      
      # Set value to negative infinity
      value = -(float("inf"))
      
      # Save the legal actions as a variable
      legalActions = gameState.getLegalActions(0)
      
      # For all actions that are legal
      for action in legalActions:
          
        # Set value to be the max between itself, and the value represented by the min node
        value = max(value, minValue(gameState.generateSuccessor(0, action), depth - 1, 1, numGhosts))
      
      # Return value
      return value

    # minValue used to find the value of the min node in a minimax tree
    # Acceots game state, depth, agent index, and number of ghosts as input
    def minValue(gameState, depth, agentIndex, numGhosts):

      # If the game state is in either win or lose, or depth is set to 0
      if gameState.isWin() or gameState.isLose() or depth == 0:
          
        # Then return the evaluation function of the game state
        return self.evaluationFunction(gameState)
      
      # Set Value to be infinity
      value = float("inf")

      # Save the legal actions as a variable
      legalActions = gameState.getLegalActions(agentIndex)

      # If the agent index is equal to the number of ghosts
      if agentIndex == numGhosts:
          
        # For all actions that are legal
        for action in legalActions:
            
          # Set the value to be the minimum between itself, and the value represented by the max node
          value = min(value, maxValue(gameState.generateSuccessor(agentIndex, action), depth - 1, numGhosts))
      
      # Else the agent index is not equal to the number of ghosts
      else:
          
        # For all actions that are legal
        for action in legalActions:
            
          # Set the value to be the minimum between itself, and the value represented by the min node
          value = min(value, minValue(gameState.generateSuccessor(agentIndex, action), depth, agentIndex + 1, numGhosts))
  
      # Return value
      return value

    # Save the legal actions as a variable
    legalActions = gameState.getLegalActions()
    
    # Set the number of ghosts to be the number of agents - 1
    numGhosts = gameState.getNumAgents() - 1
    
    # Set the initial score to negative infinity
    score = -(float("inf"))
    
    # For all legal actions
    for action in legalActions:
        
      # Set the next state to be the successor of the current state
      nextState = gameState.generateSuccessor(0, action)
      
      # Set oldScore to be a copy of the current score
      oldScore = score
      
      # Set the score to be the max between itself, and the value represented by the min nodw
      score = max(score, minValue(nextState, self.depth, 1, numGhosts))
      
      # If the new score is greater than the old score
      if score > oldScore:
          
        # Set the best action to be the current action
        bestAction = action

    # Return the best action
    return bestAction

class AlphaBetaAgent(MultiAgentSearchAgent):
  """
    Your minimax agent with alpha-beta pruning (question 3)
  """

  def getAction(self, gameState):
    """
      Returns the minimax action using self.depth and self.evaluationFunction
    """
    "*** YOUR CODE HERE ***"
    
    """
    This function will result in low scores if the ghost is moving randomly;
    Pacman may get stuck in a capsule spot and die
    This function works much better when using "-g DirectionalGhost"
    """
    
    # maxValue used to compute the max value of a max node in minimax using alpha/beta pruning
    # Takes game state, alpha value, beta value, and depth as input
    def maxValue(gameState, alpha, beta, depth):
        
      # If the game state is in either win or lose state, or depth = 0
      if gameState.isWin() or gameState.isLose() or depth == 0:
          
        # Then return the evaluation function of the game state
        return self.evaluationFunction(gameState)
      
      # Set value to equal negative infinity
      value = -(float("inf"))
      
      # Save the legal actions in a variable
      legalActions = gameState.getLegalActions(0)
      
      # For all legal actions
      for action in legalActions:
          
        # Get the next state by generating the successor of the current state
        nextState = gameState.generateSuccessor(0, action)
        
        # Set value to be the max between itself, and the value of the min node
        value = max(value, minValue(nextState, alpha, beta, gameState.getNumAgents() - 1, depth))
        
        # If value is greater than or equal to beta; then return value
        if value >= beta:
          return value
        
        # Set alpha to be the max between itself and value
        alpha = max(alpha, value)
        
      # Return value
      return value
        
    # minValue used to compute the min value of a min node in minimax using alpha/beta pruning
    # Takes game state, alpha value, beta value, agent index, and depth as input
    def minValue(gameState, alpha, beta, agentIndex, depth):
        
      # Set the number of ghosts to be the number of agents in the current state - 1
      numGhosts = gameState.getNumAgents() - 1
      
      # If the game state is either in win or lose state, or depth = 0
      if gameState.isWin() or gameState.isLose() or depth == 0:
          
        # Then return the evaluation function of the game state
        return self.evaluationFunction(gameState)
      
      # Set value to equal infinity
      value = float("inf")
      
      # Save legal actions as a variable
      legalActions = gameState.getLegalActions(agentIndex)
      
      # For all legal actions
      for action in legalActions:
          
        # Set the successor of the gamestate to be the nextState
        nextState = gameState.generateSuccessor(agentIndex, action)
        
        # If agent index = number of ghosts
        if agentIndex == numGhosts:
            
          # Set value to be the min between itself, and the value of the max node
          value = min(value, maxValue(nextState, alpha, beta, depth - 1))
          
          # If value is smaller or equal to alpha; then return value
          if value <= alpha:
            return value
          
          # Set beta to be the min between itself, and value
          beta = min(beta, value)
      
        # If agent index does not equal the number of ghosts
        else:
            
          # Set value to be the min between itself, and the value of the min node
          value = min(value, minValue(nextState, alpha, beta, agentIndex + 1, depth))
          
          # If value is less than or equal to alpha; then return value
          if value <= alpha:
            return value
          
          # Set beta to be the min between itself, and value
          beta = min(beta, value)
  
      # Return value
      return value
        
    # Save the legal actions as a variable
    legalActions = gameState.getLegalActions(0)
    
    # Set score and alpha to be negative infinity; Set beta to infinity
    score = -(float("inf"))
    alpha = -(float("inf"))
    beta = float("inf")
    
    # For all legal actions
    for action in legalActions:
        
      # Set the successor of the game state to be the nextState
      nextState = gameState.generateSuccessor(0, action)
      
      # Set old score to be a copy of score
      oldScore = score
      
      # Set score to be the max between itself, and the value of the min node
      score = max(score, minValue(nextState, alpha, beta, 1, self.depth))
      
      # If score is greater than the old score; Then set the best action to be the current one
      if score > oldScore:
        bestAction = action
      
      # If score is greater than or equal to beta; Then return the best action
      if score >= beta:
        return bestAction
    
      # Set alpha to be the max between itself, and score
      alpha = max(alpha, score)
        
    # Return the best action
    return bestAction

class ExpectimaxAgent(MultiAgentSearchAgent):
  """
    Your expectimax agent (question 4)
  """

  def getAction(self, gameState):
    """
      Returns the expectimax action using self.depth and self.evaluationFunction

      All ghosts should be modeled as choosing uniformly at random from their
      legal moves.
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

def betterEvaluationFunction(currentGameState):
  """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
  """
  "*** YOUR CODE HERE ***"
  util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction

class ContestAgent(MultiAgentSearchAgent):
  """
    Your agent for the mini-contest
  """

  def getAction(self, gameState):
    """
      Returns an action.  You can use any method you want and search to any depth you want.
      Just remember that the mini-contest is timed, so you have to trade off speed and computation.

      Ghosts don't behave randomly anymore, but they aren't perfect either -- they'll usually
      just make a beeline straight towards Pacman (or away from him if they're scared!)
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

