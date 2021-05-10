p, q =23, 53
r = 251
e = 16
A = [0]*30
B = [0]*30
i = 0

a, b = e, r
A[i], B[i] = a, b

while(B[i] != 0):
    i+=1
    A[i] = B[i-1]
    B[i] = A[i-1] % B[i-1]
    
p = A[i]
x, y = 1, 0
while(i > 0):
    i-=1
    t = x
    x = y
    y = int(t -  A[i]/B[i] * y)

print(x+r)
