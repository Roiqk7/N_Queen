from timeit import default_timer


times = []
QUEEN_CHAR = "Q"
EMPTY_CHAR = "."


def main():
    while True:
        try:
            n = int(input("Enter N: ").replace(" ", ""))
            times.clear()
            start_pos = " "
            while start_pos != "x" or start_pos != "":
                start_pos = input("(press [x] to reassign N) Enter position of the Queen: ").replace(" ", "").lower()
                print(queens(start_pos, n))
                print("\n")
        except ValueError:
            print("Value error. If you are unsure about entry format read `README.md`.")
            continue
        except IndexError:
            print("Index error. Your value is out of range.")
            continue


queen_positions = []


def queens(position: str, size: int) -> str:
    start = default_timer()
    board = [[0 for i in range(size)] for i in range(size)]
    if position != "":
        row = int(position[1:]) * -1
        col = int(ord(position[0])-97)
        board[row][col] = 1
    if solve_N_queens(board, 0):
        run_time = default_timer() - start
        times.append(run_time)
        print(f"\nFinihed in {run_time:.3f}s")
        print("Time average: " + str(sum(times)/len(times)))
        print_out(board)
        queen_positions.clear()
        return format_return(board)
    return "No solutions found"


def is_valid(board: list, row: int, col: int) -> bool:
    size = len(board)
    if 1 in board[row]:
        return False
    for i in range(size):
        if board[i][col] == 1:
            return False
    for i in range(0, size):
        for j in range(0, size):
            if (i + j == row + col) or (i - j == row - col):
                if board[i][j] == 1:
                    return False
    return True


def solve_N_queens(board: list, row: int):
    size = len(board)
    if row == size:
        return True
    if 1 in board[row]:
        return solve_N_queens(board, row+1)
    for col in range(size):
        if is_valid(board, row, col):
            board[row][col] = 1
            if solve_N_queens(board, row+1):
                return True
        board[row][col] = 0
    return False


def format_return(board: list) -> str:
    for i in range(len(board)):
        for j in range(len(board)):
            if board[i][j] != EMPTY_CHAR:
                queen_positions.append(chr(j+97) + str(len(board) - i))
    return ", ".join(sorted(queen_positions))


def print_out(board: list) -> print:
    print(" ".join([chr(i%26+97) for i in range(len(board))]))
    for i in range(len(board)):
        for j in range(len(board)):
            if board[i][j] == 0: board[i][j] = EMPTY_CHAR
            else: board[i][j] = QUEEN_CHAR
            print(board[i][j], end=" ")
        print("|" + str(len(board) - i))


if __name__ == "__main__":
    print(main())
