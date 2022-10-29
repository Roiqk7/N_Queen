using System;
    using System.Text.RegularExpressions;

    public class Constans
    {
        public const int QUEEN_NUM = 1;
        public const int EMPTY_NUM = 0;
        public const char QUEEN_CHAR = 'Q';
        public const char EMPTY_CHAR = '.';
    }


    public class NQueen
    {
        static void Main()
        {
            while (true)
            {
                string pos = System.String.Empty;
                Console.Write("Enter N: ");
                int n = Convert.ToInt32(Console.ReadLine());
                Console.Write("(optional) Enter starting position of the Queen: ");
                pos = Console.ReadLine();
                int[,] board = new int[n, n];
                assignPos(pos, n, board);
                var watch = System.Diagnostics.Stopwatch.StartNew();
                if (solveNQueen(0, n, board))
                {
                    watch.Stop();
                    double elapsedS = watch.ElapsedMilliseconds/1000.0;
                    Console.WriteLine("Finished in " + elapsedS + "s");
                    printOut(n, board);
                }
                else Console.WriteLine("No solutions found");
            }
        }


        static void assignPos(string pos, int n, int[,] board)
        {
            int col = (int) pos[0] - 97;
            int row = n - Convert.ToInt32(Regex.Match(pos, @"\d+").Value);
            if (isValid(row, col, n, board)) board[row, col] = Constans.QUEEN_NUM;
        }


        static bool isValid(int row, int col, int n, int[,] board)
        {
            for (int i = 0; i < n; i++) if (board[i, col] == Constans.QUEEN_NUM) return false;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (i + j == row + col || i - j == row - col)
                    {
                        if (board[i, j] == Constans.QUEEN_NUM) return false;
                    }
                }
            }
            return true;
        }


        static bool solveNQueen(int row, int n, int[,] board)
        {
            if (row == n) return true;
            for (int i = 0; i < n; i++) if (board[row, i] == Constans.QUEEN_NUM) return solveNQueen(row+1, n, board);
            for (int i = 0; i < n; i++)
            {
                if (isValid(row, i, n, board))
                {
                    board[row, i] = Constans.QUEEN_NUM;
                    if (solveNQueen(row + 1, n, board)) return true;
                }
                board[row, i] = Constans.EMPTY_NUM;
            }
            return false;
        }


        static void printOut(int n, int[,] board)
        {
            for (int i = 0; i < n; i++) Console.Write((char) ((int) 'a' + i % 26) + " ");
            Console.Write("\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (board[i, j] == Constans.QUEEN_NUM) Console.Write(Constans.QUEEN_CHAR + " ");
                    else Console.Write(Constans.EMPTY_CHAR + " ");
                }
                Console.Write("|" + (n - i) + "\n");
            }
            Console.WriteLine();
            returnf(n, board);
        }


        static void returnf(int n, int[,] board)
        {
            int count = 0;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (board[j, i] == Constans.QUEEN_NUM)
                    {
                        Console.Write((char) (97 + i % 26));
                        Console.Write(n - j);
                        count++;
                        if (count != n) Console.Write(", ");
                    }
                }
                if (count % (n / 2) == 0 && count > 0) Console.Write("\n");
            }
            Console.Write("\n\n");
        }
    }
