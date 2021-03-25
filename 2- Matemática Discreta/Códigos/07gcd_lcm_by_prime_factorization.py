# Algoritmo que determina o MDC e o MMC entre dois número com base em seus fatores primos. Embora por Euclides o cálculo seja mais eficiente, esse algoritmo é interessante quando obtemos os números na forma fatorada

def merge(n1, n2):

    len1 = len(n1)
    len2 = len(n2)

    index1 = index2 = 0

    n = []

    while index1 < len1 and index2 < len2:
        if n1[index1][0] <= n2[index2][0]:
            n.append(n1[index1])
            index1 += 1
        else:
            n.append(n2[index2])
            index2 += 1

    while index1 < len1:
        n.append(n1[index1])
        index1 += 1
    
    while index2 < len2:
        n.append(n2[index2])
        index2 += 1
    
    return n


def merge_min(n1, n2):

    n = merge(n1, n2)

    last = len(n) - 1

    m = []

    for i in range(0, last):
        if n[i][0] == n[i+1][0]:
            m.append([n[i][0], min(n[i][1], n[i+1][1])])
    
    del n
            
    return m


def merge_max(n1, n2):

    n = merge(n1, n2)

    last = len(n)

    m = []

    for i in range(0, last):
        if i < last - 1 and n[i][0] == n[i+1][0]:
            m.append([n[i][0], max(n[i][1], n[i+1][1])])
        elif i > 0 and n[i][0] == n[i-1][0]:
            pass
        else:
            m.append(n[i])

    del n
            
    return m


def fact2int(n):

    integer = 1

    for fact in n:
        integer *= fact[0] ** fact[1]
    
    return integer


def gcd(n1, n2):

    n = merge_min(n1, n2)

    integer_n1 = fact2int(n1)
    integer_n2 = fact2int(n2)
    integer_gcd = fact2int(n)

    print(f'GCD({integer_n1},{integer_n2}) = {integer_gcd}') 
    

def lcm(n1, n2):

    n = merge_max(n1, n2)

    integer_n1 = fact2int(n1)
    integer_n2 = fact2int(n2)
    integer_lcm = fact2int(n)

    print(f'LCM({integer_n1},{integer_n2}) = {integer_lcm}') 


def main():

    n1 = [[2,2], [3,2], [5,1], [11,1]] # n1 = 2² * 3² * 5¹ * 11¹ = 1980
    n2 = [[2,3], [3,1], [7,1], [11,1]] # n2 = 2³ * 3¹ * 7¹ * 11¹ = 1848
    
    gcd(n1, n2)
    lcm(n1, n2)


if __name__ == '__main__':
    main()
