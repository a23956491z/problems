test_input =  [
    [[ "a"] , ["a"]] ,
    [ ["a", "cb"],["ac", "b"]],
    [ ["a", "bc"],["ac", "b"]],
    [ ["a", "b", "c"], ["ab", "c"]],
    [ ["a", "b"], ["a", "bc"]],
    [ ["ab", "c"], ["ab"]],
]


# This is O(1) Space
class Solution:
    def arrayStringsAreEqual(self, word1: list, word2: list) -> bool:

        w1 = len(word1)
        w2 = len(word2)

        pw1a, pw1b = 0, 0
        pw2a, pw2b = 0, 0

        done_w1, done_w2 = False, False
        while True:

            ww1 = len(word1[pw1a])
            ww2 = len(word2[pw2a])

            if word1[pw1a][pw1b] != word2[pw2a][pw2b]:
                return False

            pw1b+=1
            pw2b+=1
            if pw2b == ww2:
                if pw2a == w2-1:
                    done_w2 = True
                pw2b = 0
                pw2a +=1

            if pw1b == ww1:
                if pw1a == w1-1:
                    done_w1 = True
                pw1b = 0
                pw1a += 1
            if done_w1 or done_w2 :
                break


        return done_w1 and done_w2
CURRENT_CASE = 0


for i in test_input:
    sol = Solution()
    print(sol.arrayStringsAreEqual(i[0], i[1]   )  )