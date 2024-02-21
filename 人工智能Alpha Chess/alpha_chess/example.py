
from headless_game import play_headless_game
from player_1 import player_1
from player_6 import player_6

if __name__ == "__main__":    # for Windows OS
    for i in range(1, 101):  # 进行10次比赛
        if i%2 == 0:
            red = player_6.Player("red")
            black = player_1.Player("black")
            side = "red"
        else:
            red = player_1.Player("red")
            black = player_6.Player("black")
            side = "black"
        
        # 进行比赛
        winner, text, history = play_headless_game(red, black, timeout=True)
        
        # 保存比赛结果到文件
        filename = f"Player 1 VS Player 6/Game {i}.txt"
        with open(filename, "w") as file:
            file.write(f"Winner: {winner}\n")
            file.write(f"Win side: {side}\n")
            file.write(f"Text: {text}\n")
            file.write("History:\n")
            for move in history:
                file.write(f"{move}\n")

        # 打印提示
        print(f"Game {i} finished. Results saved to {filename}")

    print("All games finished.")



# from replay import replay_final_game
# # replay the fourth game between group 2 and group 3 with delay time 0.1s
# replay_final_game(player_1 = 1, player_2 = 6, game = 1, delta_time = 0.1) # this will automatically load the record of Game 4 in the "Player 2 VS Player 3" folder