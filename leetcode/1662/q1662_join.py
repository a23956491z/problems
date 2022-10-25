test_input =  [
    [ ["a", "cb"],["ac", "b"]],
    [ ["a", "bc"],["ac", "b"]],
    [ ["a", "b", "c"], ["ab", "c"]],
    [ ["a", "b"], ["a", "bc"]],
    [ ["ab", "c"], ["ab"]],
]


class Solution:
    def arrayStringsAreEqual(self, word1: list, word2: list) -> bool:

        c1 = 0
        for i in word1:
            c1 += len(i)
        c2 = 0
        for i in word2:
            c2 += len(i)
        if (c1 != c2):
            return False
        return "".join(word1) == "".join(word2)

CURRENT_CASE = 0


for i in test_input:
    sol = Solution()
    print(sol.arrayStringsAreEqual(i[0], i[1]   )  )