import random

# from utils import get_legal_actions
# import xxx    # Here may be other package you want to import
from .utils import *
from datetime import datetime, timedelta

KILLING_VALUE = 500000

class Player(): # please do not change the class name

    def __init__(self, side: str):
        """
        Variables:
            - self.side: specifies which side your agent takes. It must be "red" or "black".
            - self.history: records history actions.
            - self.move and self.move_back: when you do "search" or "rollout", you can utilize these two methods 
                to simulate the change of the board as the effect of actions and update self.history accordingly.
            - self.name : for you to set a name for your player. It is "Player" by default.

        Methods:
            - policy: the core method for you to implement. It must return a legal action according to the input 
                board configuration. Return values must be a four-element tuple or list in the form 
                of (old_x, old_y, new_x, new_y), with the x coordinate representing the column number 
                and the y coordinate representing the row number.
            - move: simulating movement, moving a piece from (old_x, old_y) to (new_x, new_y) 
                and eating a piece when overlap happens.
            - move_back: restoring the last move. You need to use it when backtracing along a path during a search,
                 so that both the board and self.history are reverted correctly.
        """

        self.side = side    # don't change
        self.history = []   # don't change
        self.name = "Player"    # please change to your group name
        self.timeOver = False
        self.timeCounter = 0
        self.maxThinkTime = 0
        self.nodeSearched = 0
        self.maxQuiescentDepth = 0
        self.searchStep = 0
        self.attackActions = []
        self.historySortDict = {}

    def policy(self, board: tuple): # the core method for you to implement
        """
        You should complement this method.

        Args:
            - board is a 10×9 matrix, showing current game state.
                board[i][j] > 0 means a red piece is on position (i,j)
                board[i][j] < 0 means a black piece is on position (i,j)
                board[i][j] = 0 means position (i,j) is empty.

        Returns:
            - Your return value is a four-element tuple (i,j,x,y), 
              which means your next action is to move your piece from (i,j) to (x,y).
            Note that your return value must be illegal. Otherwise you will lose the game directly.
        """          
        def negamax(board, depth, alpha, beta, side, best_action):
            # if self.time_up():
            #     return alpha
            candidate = get_legal_actions(board, side, self.history)
            if depth <= 0:
                return self.quiescent_search(board, alpha, beta, side)
                # return self.evaluate(board)
            

            # History heuristic sort
            # candidate.sort(key=self.compareHistory, reverse=True)

            pv = False
            # best_value = -KILLING_VALUE
            # best_history_move = None

            for action in candidate:
                sub_best_action = best_action
                self.move(board, action[0], action[1], action[2], action[3])
                if pv:
                    value = -negamax(board, depth - 1, -alpha - 1, -alpha, side2Str[not side2Bool[side]], sub_best_action)
                    if value > alpha and value < beta:
                        value = -negamax(board, depth - 1, -beta, -alpha, side2Str[not side2Bool[side]], sub_best_action)
                else:
                    value = -negamax(board, depth - 1, -beta, -alpha, side2Str[not side2Bool[side]], sub_best_action)
                # print(f"depth: {depth}, value: {negavalue}")
                self.move_back(board, action[0], action[1], action[2], action[3])

                if value > alpha:
                    alpha = value
                    # if side != self.side and action is not None:
                    best_action[0] = action
                    # best_history_move = action
                    pv = True

                if alpha > beta:
                    return alpha
                
            # if best_value == -KILLING_VALUE:
            #     # Killing step
            #     return -KILLING_VALUE
            # if best_history_move is not None:
            #     if best_history_move not in self.historySortDict:
            #         self.historySortDict[best_history_move] = depth * depth
            #     else:
            #         self.historySortDict[best_history_move] += depth * depth
            # return best_value
            return alpha
        
        # self.searchStep = depth

        alpha = float('-inf')
        beta = float('inf')
        for depth in range(1, 3):
            
            self.maxQuiescentDepth = 0
            self.timeOver = False
            startTime = datetime.now()
            self.maxThinkTime = datetime.now() + timedelta(seconds=9.5)

            print(f"Searching at depth {depth}")            
            best_action = [None]

            value = negamax(board, depth, alpha, beta, self.side, best_action)
            print(f"End with value: {value}, action: {best_action[0]}")
            if self.time_up():
                print(f"Time is up! Done in time: {(datetime.now() - startTime).seconds}.{(datetime.now() - startTime).microseconds}s")
                break
        return best_action[0]
        
  
    
    # Only generate node killing or catching king
    # side=True(red), False(black)
    def quiescent_search(self, board, alpha, beta, side, qDepth=1):
        if self.time_up():
            return alpha
        
        # For debug: record depth of quiescent search
        self.maxQuiescentDepth = max(qDepth, self.maxQuiescentDepth)
        self.nodeSearched += 1

        value = self.evaluate(board, side)
        alpha = max(value, alpha)
        if alpha >= beta:
            return alpha

        # Generate candidate actions
        safe = check_King_safe(board, side)
        if safe:
            # Append killing actions
            candidate = get_attacking_actions(board, side)
            if candidate == []:
                return value
        else:
            # Only append safe actions to ensure safety
            candidate = []
            action_list = get_legal_actions(board, side, self.history)
            for action in action_list:
                self.move(board, action[0], action[1], action[2], action[3])
                if check_King_safe(board, side):
                    candidate.append(action)
                self.move_back(board, action[0], action[1], action[2], action[3])
            if candidate == []:
                return alpha
            
        for action in candidate:
            self.move(board, action[0], action[1], action[2], action[3])
            sub_value = -self.quiescent_search(board, -alpha - 1, -alpha, side2Str[not side2Bool[side]], qDepth + 1)
            if alpha < sub_value and sub_value < beta:
                sub_value = -self.quiescent_search(board, -beta, -alpha, side2Str[not side2Bool[side]], qDepth + 1)
            self.move_back(board, action[0], action[1], action[2], action[3])

            alpha = max(alpha, sub_value)
            if alpha >= beta:
                break

        return alpha

    def evaluate(self, eboard, side):
        overall_value = 0
        conflict_list = get_conflict_count(eboard)
        for i in range(10):
            for j in range(9):
                action_list = get_one_piece_action(eboard, eboard[i][j], i , j)
                moveLength = len(action_list)
                if side == "red":
                    if eboard[i][j] > 0:
                        overall_value = overall_value + chessValue[eboard[i][j]] + positionRedValue[eboard[i][j]][i][j] + (moveLength << moveShiftValue[eboard[i][j]])
                        if(conflict_list[i][j] < 0):
                            overall_value = overall_value - chessConflictValue[eboard[i][j]]
                    elif eboard[i][j] < 0:
                        overall_value = overall_value - chessValue[-eboard[i][j]] - positionBlackValue[-eboard[i][j]][i][j] - (moveLength << moveShiftValue[-eboard[i][j]])
                        if(conflict_list[i][j] < 0):
                            overall_value = overall_value + chessConflictValue[-eboard[i][j]]
                else:
                    if eboard[i][j] > 0:
                        overall_value = overall_value - chessValue[eboard[i][j]] - positionRedValue[eboard[i][j]][i][j] - (moveLength << moveShiftValue[eboard[i][j]])
                        if(conflict_list[i][j] < 0):
                            overall_value = overall_value + chessConflictValue[eboard[i][j]]
                    elif eboard[i][j] < 0:
                        overall_value = overall_value + chessValue[-eboard[i][j]] + positionBlackValue[-eboard[i][j]][i][j] + (moveLength << moveShiftValue[-eboard[i][j]])
                        if(conflict_list[i][j] < 0):
                            overall_value = overall_value - chessConflictValue[-eboard[i][j]]
    
        return overall_value
    
    def compareHistory(self, action):
        return self.historySortDict.get(action, 0)


    # For time limited search
    def time_up(self):
        if self.timeOver:
            return True
        if datetime.now() > self.maxThinkTime:
            self.timeOver = True
            return True
        return False
    
    def search(self, board, depth, alpha, beta, side):
        if self.time_up():
            return alpha
        
        # For repeated cases: TODO

        if depth <= 0:
            return self.quiescent_search(board, alpha, beta, side)
        
        # Hash pre-determination: TODO

        # Candicate actions
        safe = check_King_safe(board, side)
        action_list = get_legal_actions(board, side, self.history)
        if safe:
            cutDepth = 4 if depth > 6 else 3
            value = -self.search(board, depth - cutDepth - 1, -beta, -beta + 1, side2Str[not side2Bool[side]])
            if value >= beta:
                depth -= 4
            candidate = action_list
        else:
            candidate = []
            for action in action_list:
                self.move(board, action[0], action[1], action[2], action[3])
                if check_King_safe(board, side):
                    candidate.append(action)
                self.move_back(board, action[0], action[1], action[2], action[3])
            if candidate == []:
                return alpha
        
        value = alpha
        pv = False

        # For debug
        num_steps = 0
        action_searched = 0

        while not candidate == []:
            action = take_best_action()
            action_searched += 1

            self.move(board, action[0], action[1], action[2], action[3])
            if pv:
                if safe and action_searched > 5 and depth > 3: # TODO and getCoverType(action) != None
                    value = -self.search(board, 3, -alpha - 1, -alpha, side2Str[not side2Bool[side]])
                else:
                    value = -self.search(board, depth - 1, -alpha - 1, -alpha, side2Str[not side2Bool[side]])

                if alpha < value and value < beta:
                    value = -self.search(board, depth - 1, -beta, -alpha, side2Str[not side2Bool[side]])
            
            else:
                value = -self.search(board, depth - 1, -beta, -alpha, side2Str[not side2Bool[side]])
            self.move_back(board, action[0], action[1], action[2], action[3])

            if alpha >= beta:
                break

        if self.time_up():
            return alpha
            
        if not pv:
            ## TODO: Update upperbound in hashtable
            pass
        else:
            if alpha >= beta:
                pass
                # TODO: Update lowerbound in hashtable
                # add attacking actions
            else:
                pass
                # TODO: Update PV in hashtable
                # add attacking actions  
            
        return alpha
        

            
    def move(self, board, old_x, old_y, new_x, new_y):  # don't change
        """utility function provided by us: simulate the effect of a movement"""
        eaten_id = board[new_x][new_y]
        board[new_x][new_y] = board[old_x][old_y]
        board[old_x][old_y] = 0
        self.history.append((old_x,old_y,new_x,new_y,eaten_id))

    def move_back(self, board, old_x, old_y, new_x, new_y): # don't change
        """utility function provided by us: restore or reverse the effect of a movement"""
        board[old_x][old_y] = board[new_x][new_y]
        board[new_x][new_y] = self.history[-1][4]
        self.history.pop()

    def update_history(self, current_game_history: list): 
        """to refresh your self.history after each actual play, which is taken care externally"""

        self.history = current_game_history
        
    def get_name(self):
        """used by the external logger"""

        return self.name
