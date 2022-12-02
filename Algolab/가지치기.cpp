/*
실전프로젝트-가지치기
트리에서 리프 노드는 자식의 개수가 0인 노드를 말한다. 
현재 트리 구조와 삭제할 노드 하나가 주어질 때, 남은 리프 노드의 개수를 구하는 프로그램을 작성하시오. 
이때, 입력되는 트리는 1개 이상이며, 노드를 지우면 그 노드와 노드의 모든 자손이 트리에서 제거된다. 
아래 그림은 노드 삭제 시 사라지는 리프 노드의 예이다.
왼쪽 그림의 리프 노드 수는 총 3개이다. 
이때, 1번 노드를 삭제하면 2번 노드를 포함한 자식 노드(3, 4)까지 제거돼 리프 노드는 ‘2’ 1개만 남게 된다. 

입력
입력은 표준입력(standard input)을 사용한다. 첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤30)가 입력된다. 
두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 
각 테스트 케이스의 첫 번째 줄에는 전체 노드의 수 n (3 ≤ n ≤ 50) 과 삭제할 노드 번호가 주어진다. 
두 번째 줄에는 각 노드의 상위 노드 정보 n 개가 공백을 기준으로 순서대로 주어진다. 

출력
출력은 표준출력(standard output)을 사용한다. 입력 테스트 케이스의 순서대로 결과를 출력한다. 
각 테스트 케이스에 대해 입력된 노드 삭제 후 리프 노드의 수를 출력한다. 

입출력 예
입력 출력
2
5 2
-1 0 0 1 1
5 1
-1 0 0 1 1
5 0
-1 0 0 1 1

2
1
0
*/

#include <iostream>
#include <vector>
#define vii vector<vector<int> >
using namespace std;

void removeNode(vii* TREE, int node);
int main() {
    int testC;

    cin >> testC;
    while(testC--) {
        int n, eraseN;

        cin >> n >> eraseN;
        vii Tree(n, vector<int>(2, 0));// isLeaf (=0 is False, 1 is True), parent Node

        Tree[0][1] = -1;
        // Setting Tree
        for (int i = 0; i < n; i++) {
            int tmp;

            // i == self
            cin >> tmp; // parent Node
            if (tmp >= 0) {
                Tree[tmp].push_back(i);
                Tree[tmp][0] += 1;
                Tree[i][1] = tmp;
            }
        }

        removeNode(&Tree, eraseN);
        int parentNode = Tree[eraseN][1], j = 2;
        while(1) {
            if (Tree[parentNode][j] == eraseN) {
                Tree[parentNode][j] = -1;
                Tree[parentNode][0] -= 1; // 자식 Node 의 수를 -1
                break;
            }
            j += 1;
        }

        int result = 0;
        for (int i = 0; i < Tree.size(); i++) {
            if (Tree[i][0] == 0 && Tree[i][1] > -2) {cout << i << endl; result += 1;}
        }
        cout << result << endl;
    }
}

void removeNode(vii* TREE, int node) {
    vii Tree = *TREE;

    if (Tree[node][0] == 0) {
        Tree[node][1] = -2; // 부모노드를 없앰
        TREE = &Tree;
        return; // leaf node 인 경우 return;
    }

    for (int i = 2; i < Tree[node].size(); i++) {
        removeNode(&Tree, Tree[node][i]);
        Tree[node][i] = -1; // 자식 노드를 지우고
        Tree[node][0] -= 1; // 자식 노드의 수 -1
        Tree[node][1] = -2; // 부모노드를 없앰으로 삭제
    }
    TREE = &Tree;
}