def exgcd(a, b):
    # y的值实际上控制的是解的情况，0的时候输出的是最小解
    # x的值是最后一次的系数，由于满足贝祖等式，所以最后剩下gcd系数应该为1
    # Your code
    return (d, x, y)


def qpod(x, a, mod):
    # Your code
    return res


if __name__ == "__main__":
    # 以下需要手动输入
    n = 14312918057165920501
    p = 3403789369
    q = 4204995229
    # Your code
    e = 65537
    c = 1736293171604281203
    print(""+str(n)+" "+str(p) + " "+str(q)+" "+str(lll)+" "+str(c))
    # Your code
    # d = (x + lll) % lll
    print(e*d % lll)
    print(str(d))
    print("Decrypt")
    print(pow(c, d, n))
    # gcd1, x1, y1 = exgcd(3, 5)
    # print("gcd1 = " + str(gcd1) + "  x1 = "+str(x1) + "  y1 = " + str(y1))
