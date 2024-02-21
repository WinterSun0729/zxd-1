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
        self.name = "Player_6"    # please change to your group name
        self.timeOver = False
        self.timeCounter = 0
        self.maxThinkTime = 0
        self.nodeSearched = 0
        self.maxQuiescentDepth = 0
        self.searchStep = 0
        self.attackActions = []
        self.historySortDict = {}
        board = init_board()
        hash = 0
        for i in range(10):
            for j in range(9):
                if board[i][j] > 0:
                    hash ^= redHash[board[i][j]][i][j]
                elif board[i][j] < 0:
                    hash ^= blackHash[-board[i][j]][i][j]
        self.rootHash = hash
        self.hash_table = {}
    
    def updataRootHash(self, board, action):
        hash = self.rootHash
        if board[action[2]][action[3]] != 0:
            if board[action[2]][action[3]] > 0:
                hash ^= redHash[board[action[2]][action[3]]][action[2]][action[3]]
            else:
                hash ^= blackHash[-board[action[2]][action[3]]][action[2]][action[3]]
        if board[action[0]][action[1]] > 0:
            hash ^= redHash[board[action[0]][action[1]]][action[0]][action[1]]
            hash ^= redHash[board[action[0]][action[1]]][action[2]][action[3]]
        else:
            hash ^= blackHash[-board[action[0]][action[1]]][action[0]][action[1]]
            hash ^= blackHash[-board[action[0]][action[1]]][action[2]][action[3]]
        self.rootHash = hash
    
    def updateRootHashBack(self, board, action):
        hash = self.rootHash
        if board[action[2]][action[3]] > 0:
            hash ^= redHash[board[action[2]][action[3]]][action[0]][action[1]]
            hash ^= redHash[board[action[2]][action[3]]][action[2]][action[3]]
        else:
            hash ^= blackHash[-board[action[2]][action[3]]][action[0]][action[1]]
            hash ^= blackHash[-board[action[2]][action[3]]][action[2]][action[3]]
        tmp = self.history[-1][4]
        if(tmp > 0):
            hash ^= redHash[tmp][action[2]][action[3]]
        elif tmp < 0:
            hash ^= blackHash[-tmp][action[2]][action[3]]
        self.rootHash = hash

    def updateRootHashOther(self, board):
        hash = self.rootHash
        action = self.history[-1]
        if board[action[2]][action[3]] > 0:
            hash ^= redHash[board[action[2]][action[3]]][action[0]][action[1]]
            hash ^= redHash[board[action[2]][action[3]]][action[2]][action[3]]
        else:
            hash ^= blackHash[-board[action[2]][action[3]]][action[0]][action[1]]
            hash ^= blackHash[-board[action[2]][action[3]]][action[2]][action[3]]
        if(action[4] > 0):
            hash ^= redHash[action[4]][action[2]][action[3]]
        elif(action[4] < 0):
            hash ^= blackHash[-action[4]][action[2]][action[3]]
        self.rootHash = hash


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
            # if self.rootHash not in self.hash_table:
            #     self.hash_table[self.rootHash] = 1
            # else:
            #     return -20000000
            # if self.rootHash in self.hash_table:
            #     return -20000000
            
            candidate = get_legal_actions(board, side, self.history)
            if depth <= 0:
                return self.quiescent_search(board, alpha, beta, side)
                # return self.evaluate(board)
            
            candidate.sort(key=self.compareHistory, reverse=True)

            pv = False

            for action in candidate:
                sub_best_action = [None]
                self.updataRootHash(board, action)
                self.move(board, action[0], action[1], action[2], action[3])
                # if side == self.side and self.rootHash in self.hash_table:
                if self.rootHash in self.hash_table:
                    print(f"{self.rootHash} is repeated!")
                    self.updateRootHashBack(board, action)
                    self.move_back(board, action[0], action[1], action[2], action[3])
                    continue
                if pv:
                    value = -negamax(board, depth - 1, -alpha - 1, -alpha, side2Str[not side2Bool[side]], sub_best_action)
                    if value > alpha and value < beta:
                        value = -negamax(board, depth - 1, -beta, -alpha, side2Str[not side2Bool[side]], sub_best_action)
                else:
                    value = -negamax(board, depth - 1, -beta, -alpha, side2Str[not side2Bool[side]], sub_best_action)
                # print(f"depth: {depth}, value: {negavalue}")
                self.updateRootHashBack(board, action)
                self.move_back(board, action[0], action[1], action[2], action[3])


                if value > alpha:
                    alpha = value
                    # if side != self.side and action is not None:
                    best_action[0] = action
                    pv = True

                if alpha > beta:
                    return alpha
                
            if best_action[0] is not None:
                # self.updataRootHash(board, best_action[0])
                if best_action[0] not in self.historySortDict:
                    self.historySortDict[best_action[0]] = depth * depth
                    # print(f"Add action {best_action[0]} to historySortDict with value {depth * depth}")
                else:
                    self.historySortDict[best_action[0]] += depth * depth
                    # print(f"Update action {best_action[0]} in historySortDict with value {self.historySortDict[best_action[0]]}")
                
            return alpha
        
        # self.searchStep = depth

        if self.history:
            # print(f"self.history = {self.history[-1]}")
            self.updateRootHashOther(board)
            print(f"Begin rootHash = {self.rootHash}")
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
            if depth == 2:
                self.hash_table[self.rootHash] = 1  #push the other's step rootHash into hash_table
                self.updataRootHash(board, best_action[0])  
                self.hash_table[self.rootHash] = 1  #push the my step rootHash into hash_table
                print(f"rootHash = {self.rootHash}")
                # print(f"hash_table[{self.rootHash}] = {self.hash_table[self.rootHash]}")
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
                # self.updataRootHash(board, action)
                self.move(board, action[0], action[1], action[2], action[3])
                if check_King_safe(board, side):
                    candidate.append(action)
                # self.updateRootHashBack(board, action)
                self.move_back(board, action[0], action[1], action[2], action[3])
            if candidate == []:
                return alpha
            
        for action in candidate:
            # self.updataRootHash(board, action)
            self.move(board, action[0], action[1], action[2], action[3])
            sub_value = -self.quiescent_search(board, -alpha - 1, -alpha, side2Str[not side2Bool[side]], qDepth + 1)
            if alpha < sub_value and sub_value < beta:
                sub_value = -self.quiescent_search(board, -beta, -alpha, side2Str[not side2Bool[side]], qDepth + 1)
            # self.updateRootHashBack(board, action)
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
