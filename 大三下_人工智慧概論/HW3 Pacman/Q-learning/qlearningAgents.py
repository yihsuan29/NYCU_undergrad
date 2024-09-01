# qlearningAgents.py
# ------------------
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


from game import *
from learningAgents import ReinforcementAgent
from featureExtractors import *

import random,util,math

"""
part 2-2 & part 2-3
"""

class QLearningAgent(ReinforcementAgent):
    """
      Q-Learning Agent

      Functions you should fill in:
        - computeValueFromQValues
        - computeActionFromQValues
        - getQValue
        - getAction
        - update

      Instance variables you have access to
        - self.epsilon (exploration prob)
        - self.alpha (learning rate)
        - self.discount (discount rate)

      Functions you should use
        - self.getLegalActions(state)
          which returns legal actions for a state
    """
    def __init__(self, **args):
        "You can initialize Q-values here..."
        ReinforcementAgent.__init__(self, **args)

        "*** YOUR CODE HERE ***"
        # Begin your code
        
        #紀錄QValue
        self.QValue = util.Counter()
        
        # util.raiseNotDefined()
        # End your code


    def getQValue(self, state, action):
        """
          Returns Q(state,action)
          Should return 0.0 if we have never seen a state
          or the Q node value otherwise
        """
        "*** YOUR CODE HERE ***"
        # Begin your code
        # util.raiseNotDefined()
        
        return self.QValue[(state, action)]
        # End your code


    def computeValueFromQValues(self, state):
        """
          Returns max_action Q(state,action)
          where the max is over legal actions.  Note that if
          there are no legal actions, which is the case at the
          terminal state, you should return a value of 0.0.
        """
        "*** YOUR CODE HERE ***"
        # Begin your code
        # util.raiseNotDefined()
        """
        公式
        isEnd(s):  V(s) = 0
        otherwise: V(s) = max_{a in actions} Q(s,a)
        """
        legalActions = self.getLegalActions(state)
        if len(legalActions)==0:
            return 0.0
        MaxAction = self.getPolicy(state)
        MaxValue = self.getQValue(state, MaxAction)
        return MaxValue
        # End your code

    def computeActionFromQValues(self, state):
        """
          Compute the best action to take in a state.  Note that if there
          are no legal actions, which is the case at the terminal state,
          you should return None.
        """
        "*** YOUR CODE HERE ***"
        # Begin your code
        # util.raiseNotDefined()
        """
        policy(s) = arg_max_{a in actions} Q(s,a)
        """
        legalActions = self.getLegalActions(state)
        if len(legalActions) == 0:
            return None
        ActionValue = util.Counter()
        for action in legalActions:
            ActionValue[action] = self.getQValue(state, action)
            
        #break ties randomly   
        MaxValue= ActionValue[ActionValue.argMax()]
        MaxActions = [action for action in ActionValue if ActionValue[action] == MaxValue]
        Action = random.choice(MaxActions) 
        return Action
        # End your code

    def getAction(self, state):
        """
          Compute the action to take in the current state.  With
          probability self.epsilon, we should take a random action and
          take the best policy action otherwise.  Note that if there are
          no legal actions, which is the case at the terminal state, you
          should choose None as the action.

          HINT: You might want to use util.flipCoin(prob)
          HINT: To pick randomly from a list, use random.choice(list)
        """
        # Pick Action
        legalActions = self.getLegalActions(state)
        action = None
        "*** YOUR CODE HERE ***"
        # Begin your code
        # util.raiseNotDefined()
        if len(legalActions) == 0:
            return None
        explore = util.flipCoin(self.epsilon)
        #硬幣擲到要隨機選action的話
        if explore:
            action =  random.choice(legalActions)
        #硬幣說要直接走
        else:
            action =  self.getPolicy(state)
        return action
        # End your code
        

    def update(self, state, action, nextState, reward):
        """
          The parent class calls this to observe a
          state = action => nextState and reward transition.
          You should do your Q-Value update here

          NOTE: You should never call this function,
          it will be called on your behalf
        """
        "*** YOUR CODE HERE ***"
        # Begin your code
        # util.raiseNotDefined()
        """
        Qopt(s,a) <- (1-eta)Qopt(s,a)+ eta(reward + discount* Vopt(s'))
        Qopt(s,a)為 prediction
        reward + discount* Vopt(s')為target
        """
        prediction = self.getQValue(state, action)
        prediction_ = (1-self.alpha)*prediction
        Value = self.getValue(nextState)
        target = reward + self.discount* Value
        target_ = self.alpha * target
        self.QValue[(state,action)] =  prediction_ + target_
        # End your code

    def getPolicy(self, state):
        return self.computeActionFromQValues(state)

    def getValue(self, state):
        return self.computeValueFromQValues(state)


class PacmanQAgent(QLearningAgent):
    "Exactly the same as QLearningAgent, but with different default parameters"

    def __init__(self, epsilon=0.05,gamma=0.8,alpha=0.2, numTraining=0, **args):
        """
        These default parameters can be changed from the pacman.py command line.
        For example, to change the exploration rate, try:
            python pacman.py -p PacmanQLearningAgent -a epsilon=0.1

        alpha    - learning rate
        epsilon  - exploration rate
        gamma    - discount factor
        numTraining - number of training episodes, i.e. no learning after these many episodes
        """
        args['epsilon'] = epsilon
        args['gamma'] = gamma
        args['alpha'] = alpha
        args['numTraining'] = numTraining
        self.index = 0  # This is always Pacman
        QLearningAgent.__init__(self, **args)

    def getAction(self, state):
        """
        Simply calls the getAction method of QLearningAgent and then
        informs parent of action for Pacman.  Do not change or remove this
        method.
        """
        action = QLearningAgent.getAction(self,state)
        self.doAction(state,action)
        return action


"""
part 2-4
"""

class ApproximateQAgent(PacmanQAgent):
    """
       ApproximateQLearningAgent

       You should only have to overwrite getQValue
       and update.  All other QLearningAgent functions
       should work as is.
    """
    def __init__(self, extractor='IdentityExtractor', **args):
        self.featExtractor = util.lookup(extractor, globals())()
        PacmanQAgent.__init__(self, **args)
        self.weights = util.Counter()

    def getWeights(self):
        return self.weights

    def getQValue(self, state, action):
        """
          Should return Q(state,action) = w * featureVector
          where * is the dotProduct operator
        """
        "*** YOUR CODE HERE ***"
        # Begin your code
        # get weights and feature
        # util.raiseNotDefined()
        featureVector = self.featExtractor.getFeatures(state, action)
        Q = 0
        for feature in featureVector.keys():
            Q += self.weights[feature]*featureVector[feature]
        return Q

        # End your code

    def update(self, state, action, nextState, reward):
        """
           Should update your weights based on transition
        """
        "*** YOUR CODE HERE ***"
        # Begin your code
        # util.raiseNotDefined()
        featureVector = self.featExtractor.getFeatures(state, action)
        correction = (reward +self.discount* self.getValue(nextState))-(self.getQValue(state, action))
        for feature in featureVector.keys():
            self.weights[feature] = self.weights[feature] + self.alpha* correction *featureVector[feature]

        # End your code


    def final(self, state):
        "Called at the end of each game."
        # call the super-class final method
        PacmanQAgent.final(self, state)
