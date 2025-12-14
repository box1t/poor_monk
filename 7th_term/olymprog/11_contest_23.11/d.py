# https://chatgpt.com/c/6922d245-e97c-8332-84a7-a2c0f486b171 - d


# a, b, c, d = map(int, input().split())
# n, m = map(int, input().split())
# inf = 10**18

# frank_arts = []
# for _ in range(n):
#     p, q = map(int, input().split())
#     frank_arts.append((p, q))

# bull_arts = []
# for _ in range(m):
#     p, q = map(int, input().split())
#     bull_arts.append((p, q))

# def min_cost_to_reduce(init, lim, arts):
#     diff = init - lim
#     if diff <= 0:
#         return 0 
    
#     dp = [inf] * (diff + 1)
#     dp[0] = 0

#     for p, q in arts:
#         for x in range(diff, -1, -1):
#             nx = min(diff, x + p)
#             dp[nx] = min(dp[nx], dp[x] + q)

#     return dp[diff]

# frank_price = min_cost_to_reduce(c, b, frank_arts)
# bull_price = min_cost_to_reduce(d, a, bull_arts)

# if frank_price >= inf or bull_price >= inf:
#     print("NO")
# else:
#     print("YES")
#     print(frank_price + bull_price)

