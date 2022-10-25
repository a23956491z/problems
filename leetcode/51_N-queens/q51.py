test_input =  [
    8
]


class Solution:

    def __init__(self):
        self.n = 0
        self.lim = 0
        self.visited = set()
        self.result = []

        self.BOARD_QUEEN = 1
        self.BOARD_EMPTY = 0
        self.BOARD_INVALID = -1

    def get_row(self, idx):
        i = (idx-1) // self.n
        ret = [v for v in range(i*self.n+1,  (i+1)*self.n+1 )]
        ret.remove(idx)
        return ret
    def get_col(self, idx):
        j = idx % self.n
        ret = [v for v in range(j, self.lim+1,self.n)]
        ret.remove(idx)
        return ret
    def get_dia(self, idx):
        start_point = idx % (self.n + 1)
        ret = [v for v in range(start_point, self.lim+1, self.n+1)]
        ret.remove(idx)

        ptr = idx
        while (ptr % self.n)  != 0:
            ptr -= self.n-1
            ret.append(ptr)
        ptr = idx
        while ((ptr-1) // self.n) != self.n-1:
            ptr += self.n-1
            ret.append(ptr)
        return ret

    def find_possible_move(self, queen, print_out=False):

        # 0 for empty
        # 1 for queen
        # -1 for not available

        current_board = [self.BOARD_EMPTY for _ in range(self.lim)]

        for q in queen:
            current_board[q-1] = self.BOARD_QUEEN
            invalid_pos = self.get_row(q) + self.get_col(q) + self.get_dia(q)
            for pos in invalid_pos:
                if current_board[pos-1] != self.BOARD_QUEEN:
                    current_board[pos-1] = self.BOARD_INVALID
        if print_out:
            self.visualize(current_board)
        ret = []
        for pos, value in enumerate(current_board):
            if value == self.BOARD_EMPTY:
                ret.append(pos+1)

        return ret


    def hash_list(self, lst):
        return "".join(str(i) for i in set(lst))



    def solveNQueens(self, n: int) -> list:

        self.n = n
        self.lim = n**2

        for i in range(1, self.lim+1):
            self.search([i])

        print(len(self.result))

        print(len(self.visited))
    def search(self, queen):

        iden = self.hash_list(queen)
        if iden in self.visited:
            return


        if len(queen) == self.n:
            self.result.append(queen)
            self.find_possible_move(queen, True)

        valid_move = self.find_possible_move(queen)

        # self.visited.append(iden)
        self.visited.add(iden)
        for vm in valid_move:
            self.search(queen + [vm])
    def visualize(self, board):

        print("****************")
        print("length: ",len(board))
        for idx, piece in enumerate(board):
            if piece == self.BOARD_QUEEN:
                print('#', end='')
            if piece == self.BOARD_EMPTY:
                print('-', end='')
            if piece == self.BOARD_INVALID:
                print('x', end='')

            if( (idx+1) % self.n == 0):
                print('|')
        print("****************")


for i in test_input:
    sol = Solution()
    sol.solveNQueens(i)
    # for a in sol.solveNQueens( i   ) :
    #
    #     for b in a:
    #         print(a)
    #     print("-----")