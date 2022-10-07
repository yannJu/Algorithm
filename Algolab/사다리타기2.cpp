/*
쿠민이가 사다리게임에서 목적지와 연결된 시작 번호 계산하는 프로그램을 만들어 사용하는 것을 친구들에게 걸리고 말았다. 
친구들은 특단의 조치로 사다리의 특정 행을 가리기로 했다. 
하지만 쿠민이도 이런 상황에 맞춰 프로그램을 개선하고 싶다. 
쿠민이를 위해 목적지에 도착할 가능성이 있는 시작 번호를 계산하는 프로그램을 만드시오. 
프로그램은 ‘그림 1’과 같은 사다리를 입력받게 된다. ‘+’는 사다리를, ‘0’은 이동할 수 없는 빈 공간을 나타낸다. 
그리고 ‘?’는 친구들이 가린 곳을 나타낸다. 사다리는 오직 ‘+’ 만 따라 이동할 수 있으며, 
이동은 위에서 아래 이동하는 것을 기본으로 한다. 
좌측 또는 우측으로 이동 가능한 경우 좌 / 우 이동이 더 높은 우선순위를 갖는다.

1 2 3 4 5
+ 0 + 0 + 0 + 0 +
+ 0 + 0 + + + 0 +
+ + + 0 + 0 + 0 +
+ 0 + + + 0 + + +
+ 0 + 0 + 0 + 0 +
? ? ? ? ? ? ? ? ?
+ 0 + 0 + + + 0 +
+ 0 + 0 + 0 + 0 +
+ + + 0 + 0 + + +
+ 0 + 0 + 0 + 0 +
*
+
+
+ + +
+
+
그림 1 그림 2

1 2 3 4 5
+ 0 + 0 + 0 + 0 +
+ 0 + 0 + + + 0 +
+ + + 0 + 0 + 0 +
+ 0 + + + 0 + + +
+ 0 + 0 + 0 + 0 +
? ? ? ? ? ? + 0 +
+ 0 + 0 + + + 0 +
+ 0 + 0 + 0 + 0 +
+ + + 0 + 0 + + +
+ 0 + 0 + 0 + 0 +
*
1 2 3 4 5
+ 0 + 0 + 0 + 0 +
+ 0 + 0 + + + 0 +
+ + + 0 + 0 + 0 +
+ 0 + + + 0 + + +
+ 0 + 0 + 0 + 0 +
? ? ? ? ? ? + + +
+ 0 + 0 + + + 0 +
+ 0 + 0 + 0 + 0 +
+ + + 0 + 0 + + +
+ 0 + 0 + 0 + 0 +
* 그림 3 그림 4
위 규칙에 따라 그림에서 목적지에 도착할 가능성이 있는 시작 번호는 3, 5 이 된다. 단, ‘그림 2’와 같이 한 점을 기준으로 좌 / 우 모두 이동 가능한 경우는 존재하지 않는다. 입력
입력은 표준입력(standard input)을 사용한다. 첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤25)가 입력된다. 
두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 각 테스트 케이스의 첫 번째 줄에는 시작 번호의 개수 n 과 사다리의 크기 m , 목적지의 위치 d (3 ≤ n ≤100, 10 ≤ m ≤ 200, 1 ≤ d ≤ n) 이 공백을 기준으로 순서대로 주어진다. 두 번째 줄부터 m 개의 줄에 걸쳐 ‘m × (n * 2 - 1)’ 크기의 사다리가 입력으로 주어진다. 출력
출력은 표준출력(standard output)을 사용한다. 출력의 첫 줄에 목적지에 도착할 가능성이 있는 시작 번호를 출력한다. 단, 시작 번호가 2개 이상일 때, 공백을 기준으로 작은 번호부터 순서대로 출력한다.
입출력 예
입력 출력 2
5 10 4
+0+0+0+0+
+0+0+++0+
+++0+0+0+
+0+++0+++
+0+0+0+0+
?????????
+0+0+++0+
+0+0+0+0+
+++0+0+++
+0+0+0+0+

4 10 2
+0+0+0+
+++0+0+
???????
+++0+0+
+0+++0+
+0+0+0+
+++0+++
+0+0+0+
+0+++0+
+0+0+0+

3 5
3 4
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct DIR {
    int x;
    int y;
};
DIR *dir;

void dfs(int nowX, int nowY, vector<int> **MAP, vector<int> **ckMAP, vector<int> *result, int m, int n, int ds);
int main() {
    int testC;

    cin >> testC;

    dir = new DIR[3];
    dir[0].x = -1; dir[0].y = 0;
    dir[1].x = 1; dir[1].y = 0;
    dir[2].x = 0; dir[2].y = -1;

    while(testC--) {
        int n, m, d;
        vector<int> *map, *ckMap, result;

        cin >> n >> m >> d;
        map = new vector<int>[m];
        ckMap = new vector<int>[m];
        cin.ignore();

        //create Map
        for (int i = 0; i < m; i++) {
            vector<int> tmp, ckTmp;
            string sTmp;

            getline(cin, sTmp, '\n');
            for (int j = 0; j < sTmp.length(); j++) {
                if (sTmp[j] == '+') {tmp.push_back(1); ckTmp.push_back(0);}
                else if (sTmp[j] == '0') {tmp.push_back(0); ckTmp.push_back(1);}
                else tmp.push_back(-1);
            }
            map[i] = tmp;
            ckMap[i] = ckTmp;
        }

        //check ladder
        ckMap[m - 1][2 * (d - 1)] = 1;
        dfs(2 * (d - 1), m - 1, &map, &ckMap, &result, m, n, d);
        sort(result.begin(), result.end());

        for (int i = 0; i < result.size(); i++) cout << result[i] << " ";
        cout << endl;
    }
}

void dfs(int nowX, int nowY, vector<int> **MAP, vector<int> **ckMAP, vector<int> *result, int m, int n, int d) {
        vector<int> *map = *MAP, *ckMap = *ckMAP;
        int nextY, nextX;

        if (nowY == 0) {
            result[0].push_back(nowX / 2 + 1);
            return;
        }
        
        for (int j = 0; j < 3; j++) {
            nextX = dir[j].x + nowX;
            nextY = dir[j].y + nowY;

            if ((nextX > -1 && nextX < 2 * n - 1) && (nextY > -1 && nextY < m)) {
                if (map[nextY][nextX] == 1 && ckMap[nextY][nextX] == 0) {
                    ckMap[nextY][nextX] = 1;
                    ckMAP = &ckMap;
                    dfs(nextX, nextY, MAP, ckMAP, result, m, n, d);
                    ckMap[nextY][nextX] = 0;
                    ckMAP = &ckMap;
                    break;
                }
                else if (map[nextY][nextX] == -1) {
                    if (nextX - 2 > -1) {
                        if (map[nextY - 1][nextX - 2] == 1 && ckMap[nextY - 1][nextX - 2] == 0) {
                            ckMap[nextY - 1][nextX - 2] = 1;
                            ckMAP = &ckMap;
                            dfs(nextX - 2, nextY - 1, MAP, ckMAP, result, m, n, d);
                            ckMap[nextY - 1][nextX - 2] = 0;
                            ckMAP = &ckMap;
                        }
                    }
                    if (nextX + 2 < 2 * n - 1) {
                        if (map[nextY - 1][nextX + 2] == 1 && ckMap[nextY - 1][nextX + 2] == 0) {
                            ckMap[nextY - 1][nextX + 2] = 1;
                            ckMAP = &ckMap;
                            dfs(nextX + 2, nextY - 1, MAP, ckMAP, result, m, n, d);
                            ckMap[nextY - 1][nextX + 2] = 0;
                            ckMAP = &ckMap;
                        }
                    }
                    if (map[nextY - 1][nextX] == 1 && ckMap[nextY - 1][nextX] == 0) {
                        ckMap[nextY - 1][nextX] = 1;
                        ckMAP = &ckMap;
                        dfs(nextX, nextY - 1, MAP, ckMAP, result, m, n, d);
                        ckMap[nextY - 1][nextX] = 0;
                        ckMAP = &ckMap;
                    }
                }
            }
        }
}