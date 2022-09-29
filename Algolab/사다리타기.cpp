/*
쿠민이는 항상 내기에서 이기기 위해 사다리를 보자마자 목적지에 도착할 수 있는 번호를 알려주는 프로그램이 필요하다. 
프로그램은 ‘그림 1’과 같은 사다리를 입력받게 되며, 오직 ‘+’ 만 따라 이동할 수 있다. 
이동은 위에서 아래 이동하는 것을 기본으로 하며, 좌측 또는 우측으로 이동 가능한 경우 좌 / 우 이동이 더 높은 우선순위를 갖는다.
1 2 3 4 5 6
+ + + + + +
+ + + + + + + +
+ + + + + + +
+ + + + + + + +
+ + + + + +
+ + + + + + + +
+ + + + + + +
+ + + + + +
+ + + + + + + +
+ + + + + +
*
+
+
+ + +
+
+
그림 1 그림 2
위 규칙에 따라 그림에서 목적지에 도착할 수 있는 번호를 구해보면 ‘5’ 가 정답이 된다. 
단, ‘그림 2’와 같이 한 점을 기준으로 좌 / 우 모두 이동 가능한 경우는 존재하지 않는다. 

입력
입력은 표준입력(standard input)을 사용한다. 첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤25)가 입력된다. 
두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 
각 테스트 케이스의 첫 번째 줄에는 시작 번호의 개수 n 과 사다리의 크기 m , 
목적지의 위치 d (3 ≤ n ≤100, 10 ≤ m ≤ 200, 1 ≤ d ≤ n) 이 공백을 기준으로 순서대로 주어진다. 
두 번째 줄부터 m 개의 줄에 걸쳐 ‘m × (n * 2 - 1)’ 크기의 사다리가 입력으로 주어진다. 

출력
출력은 표준출력(standard output)을 사용한다. 출력의 첫 줄에 목적지에 도착할 수 있는 시작 번호를 출력한다.
입출력 예
입력 출력 
2
6 10 4
+ + + + + +
+ + +++ +++
+++ + + + +
+ +++ +++ +
+ + + + + +
+++ + + +++
+ + +++ + +
+ + + + + +
+++ + +++ +
+ + + + + +
4 10 2
+ + + +
+++ + +
+ + +++
+++ + +
+ +++ +
+ + + +
+++ +++
+ + + +
+ +++ +
+ + + + 

5
3
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct DIR {
    int x;
    int y;
};
DIR *dir;

void ladders(vector<int> **MAP, int n, int m, int *result, int x, int y);
int main() {
    int testC;

    dir = new DIR[3];
    dir[0].x = -1; dir[0].y = 0; //좌
    dir[1].x = 1; dir[1].y = 0; //우
    dir[2].x = 0; dir[2].y = -1; //상

    cin >> testC;
    while(testC--) {
        int n, m, d, result = -1;
        vector<int> *map;

        cin >> n >> m >> d;
        map = new vector<int>[m];
        cin.ignore();

        //creat Map
        for (int i = 0; i < m; i++) {
            string tmp;
            vector<int> vecTmp;

            getline(cin, tmp, '\n');
            for (int j = 0; j < tmp.length(); j++) {
                if (tmp[j] == '+') vecTmp.push_back(1);
                else vecTmp.push_back(0);
            }

            map[i] = vecTmp;
        }

        int nowX = (d - 1) * 2, nowY = m - 1;
        do {
            for (int k = 0; k < 3; k++) {
                if ((nowY + dir[k]. y >= 0 && nowY + dir[k].y < m) && (nowX + dir[k].x >= 0 && nowX + dir[k].x < 2 * n - 1)) {
                    if (map[nowY + dir[k].y][nowX + dir[k].x] == 1) {
                        nowX += dir[k].x;
                        nowY += dir[k].y;
                        map[nowY][nowX] = -1;
                    }
                }
            }
        } while(nowY > 0);
        
        cout << nowX / 2 + 1 << endl;
    }
}

void ladders(vector<int> **MAP, int n, int m, int *result, int x, int y) {
    vector<int> *map = *MAP;

    if (y == 0) {
        result[0] = x;
        return;
    }

    for (int i = 0; i < 3; i++) {
        if ((x + dir[i].x > -1 && x + dir[i].x < 2 * n - 1) && (y + dir[i].y > -1 && y + dir[i].y < m)) {
            if (map[y + dir[i].y][x + dir[i].x] == 1) ladders(&map, n, m, result, x + dir[i].x, y + dir[i].y);
        }
    }
}