def checkPartition(partition, answer, size):
    dir = [(-1, 0), (0, 1), (1, 0), (0, -1)] #상우하좌
    answer.append(0)
    
    for i in range(size):
        for j in range(size):
            if (partition[i][j] == 'P'):
                for d in dir:
                    newI = i + d[0]
                    newJ = j + d[1] 
                    if ((0 <= newI < size) and (0 <= newJ < size)):
                        if (partition[newI][newJ] == 'P'): return answer
                        elif (partition[newI][newJ] == 'O'):
                            for d2 in dir:
                                if (0 <= newI + d2[0] < size and 0 <= newJ + d2[1] < size and (newI + d2[0] != i or newJ + d2[1] != j)):
                                    if (partition[newI + d2[0]][newJ + d2[1]] == 'P'): return answer
    
    answer[-1] = 1
    return answer                            

def solution(places):
    answer = []
    size = 5
    
    for i in places:
        #각 대기실 탐색
        P = list()
        for j in i:
            #각 대기실의 거리두기를 확인
            tmp = []
            #대기실 만들기
            for n in range(size):
                tmp.append(j[n])
            P.append(tmp)
        answer = checkPartition(P, answer, size)
    return answer