# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


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
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and child states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best
        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed child
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        childGameState = currentGameState.getPacmanNextState(action)
        newPos = childGameState.getPacmanPosition()
        newFood = childGameState.getFood()
        newGhostStates = childGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
        return childGameState.getScore()

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
    Your minimax agent (par1-1)
    """
    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.getNextState(agentIndex, action):
        Returns the child game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        # Begin your code
        # util.raiseNotDefined()
        legalMoves = gameState.getLegalActions(0) # 這一步是小精靈
        MaxScore=float('-inf')
        Move = None
        for move in legalMoves:
            nextState = gameState.getNextState(0, move)
            Score =self.Vminimax(nextState,0,1) #下一步是鬼
            if  Score>MaxScore:
                MaxScore = Score
                Move = move
        return Move
    
    def Vminimax (self,gameState,tmpDepth,agentIndex):
        #遞迴終止條件 不想了或玩完了
        """
        IsEnd(s): Vminimax(s) = Utility(s)
        """
        if tmpDepth== self.depth or gameState.isWin() or gameState.isLose():
            return self.evaluationFunction(gameState)
        #精靈 做max
        """
        Player = agent: Vminimax(s) = max_action{Vminmax(Succ(s,a))}
        """
        if agentIndex==0:
            MaxScore=float('-inf')
            legalMoves = gameState.getLegalActions(agentIndex)
            for move in legalMoves:
                nextState = gameState.getNextState(agentIndex, move)
                #預期下一步的鬼會做啥
                nextStateScore =self.Vminimax(nextState,tmpDepth,agentIndex+1)
                MaxScore = max(MaxScore,nextStateScore) #所有可選的之中挑最大
            return MaxScore
        #鬼 做min
        """
        Player = opp: Vminimax(s) = min_action{Vminmax(Succ(s,a))}
        """
        if agentIndex>0:        
            MinScore=float('inf')
            legalMoves = gameState.getLegalActions(agentIndex)
            for move in legalMoves:
                nextState = gameState.getNextState(agentIndex, move)
                if agentIndex < gameState.getNumAgents()-1: #還要讓下一隻鬼跑
                    nextStateScore =  self.Vminimax(nextState,tmpDepth,agentIndex+1) 
                else: #鬼都跑過一步了 換精靈
                    nextStateScore =  self.Vminimax(nextState,tmpDepth+1,0) 
                MinScore = min(MinScore,nextStateScore) #鬼就是故意要選最爛的給你
            return MinScore
        # End your code

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (part1-2)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        # Begin your code
        # util.raiseNotDefined()
        legalMoves = gameState.getLegalActions(0) # 這一步是小精靈
        MaxScore=float('-inf')
        Move = None
        for move in legalMoves:
            nextState = gameState.getNextState(0, move)
            Score =self.Vexptmax(nextState,0,1) #下一步是鬼
            if  Score>MaxScore:
                MaxScore = Score
                Move = move
        return Move
    
    def Vexptmax (self,gameState,tmpDepth,agentIndex):
        #遞迴終止條件 不想了或玩完了
        """
        IsEnd(s): Vexpectimax(s) = Utility(s)
        """
        if tmpDepth== self.depth or gameState.isWin() or gameState.isLose():
            return self.evaluationFunction(gameState)
        #精靈 做max
        """
        Player = agent: Vexptmax(s) = max_action{Vexptmax(Succ(s,a))}
        """
        if agentIndex==0:
            MaxScore=float('-inf')
            legalMoves = gameState.getLegalActions(agentIndex)
            for move in legalMoves:
                nextState = gameState.getNextState(agentIndex, move)
                #預期下一步的鬼會做啥
                nextStateScore =self.Vexptmax(nextState,tmpDepth,agentIndex+1)
                MaxScore = max(MaxScore,nextStateScore) #所有可選的之中挑最大
            return MaxScore
        #鬼做exp
        """
        Player = opp: Vexptmax(s) = sum_action{pi_opp(s,a)*Vexptmax(Succ(s,a))}
        """
        if agentIndex>0:
            Score=0
            legalMoves = gameState.getLegalActions(agentIndex)
            for move in legalMoves:
                nextState = gameState.getNextState(agentIndex, move)
                if agentIndex < gameState.getNumAgents()-1: #還要讓下一隻鬼跑
                    Score +=  self.Vexptmax(nextState,tmpDepth,agentIndex+1) 
                else: #鬼都跑過一步了 換精靈
                    Score +=  self.Vexptmax(nextState,tmpDepth+1,0) 
            ExpScore = Score/len(legalMoves)
            return ExpScore
        # End your code

better = scoreEvaluationFunction
