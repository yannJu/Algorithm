/*
쿠민이는 귀농 후 사과 농사를 시작했다. 요즘 사과는 시장에 팔리는 시점에 최상의 상태를 만들기 위해
덜 익은 사과를 수확한 후 에틸렌 가스로 후숙하는 방법을 사용한다. 쿠민이는 비용을 줄이기 위해 에틸렌
가스를 사용하는 대신 아직 익지 않은 사과와 잘 익은 사과를 한 상자에 넣어 숙성하려고 한다. 과일 상자는 격자 모양으로, 한 칸에 사과 하나씩 들어가며, 잘 익은 사과는 주변(상/하/좌/우) 사과를 숙성시킨다. 이때, 익지 않은 사과가 잘 익은 사과의 영향으로 숙성되는데 필요한 시간이 하루라면 상자 내 모든 사과가 익는데 필요한 시간을 계산하는 프로그램을 작성하시오. 입력
입력은 표준입력(standard input)을 사용한다. 첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤30)가 입력된다. 두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 각 테스트 케이스의 첫 번째 줄에는 상자의 행과 열의 크기를 나타내는 n, m (3 ≤ n, m ≤ 500) 이 공백을
기준으로 순서대로 주어진다. 두 번째 줄부터 이후 n개 줄에 걸쳐 각 줄에 m 개씩 상자 안에 담겨있는 사과의 정보 (-1, 0, 1) 가 입력된다. 이때, 0은 익지 않은 사과, 1은 익은 사과, -1은 사과가 들어있지 않은
칸을 나타낸다. 출력
출력은 표준출력(standard output)을 사용한다. 입력 테스트 케이스의 순서대로 결과를 출력한다. 각 테스트 케이스에 대해 모든 사과가 익는데 걸리는 시간을 출력한다. 이때, 상자 내 익지 않은 사과가 1개라도 존재하는 경우 –1을 출력한다. 입출력 예
입력 출력
3
4 6
1 -1 0 0 0 0
0 -1 0 0 0 0
0 -1 0 -1 -1 0
0 0 0 0 -1 1
4 6
0 -1 0 0 0 0
-1 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 1
3 3
1 -1 -1
-1 -1 -1
-1 -1 1
6
-1
0
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#define vii vector<vector<int> > 
using namespace std;

vii DIR(4, vector<int>(2, 0));
int main() {
    int testC;

    cin >> testC;

    DIR[0][0] = -1; DIR[0][1] = 0; // Up
    DIR[1][0] = 1; DIR[1][1] = 0; // Down
    DIR[2][0] = 0; DIR[2][1] = -1; // Left
    DIR[3][0] = 0; DIR[3][1] = 1; // Right
    while(testC--) {
        int n, m, allApple = 0, result = 0;
        queue<pair<int, int> > q;

        cin >> n >> m;
        vii map(n, vector<int>(m, 0)), ck(n, vector<int>(m, INT_MAX));

        // Setting Map
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int tmp;

                cin >> tmp;
                map[i][j] = tmp;

                if (tmp == 1) {
                    q.push(make_pair(i, j)); 
                    ck[i][j] = 0;
                }
                else if (tmp == 0) allApple += 1;
            }
        }

        while(!q.empty() && allApple > 0) {
            pair<int, int> now = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nextY = DIR[i][0] + now.first, nextX = DIR[i][1] + now.second;
                if ((nextY >= 0 && nextY < n) && (nextX >= 0 && nextX < m)) {
                    if (map[nextY][nextX] == 0 && ck[nextY][nextX] == INT_MAX) {
                        ck[nextY][nextX] = min(ck[nextY][nextX], ck[now.first][now.second] + 1);
                        result = max(result, ck[nextY][nextX]);
                        q.push(make_pair(nextY, nextX));
                        allApple -= 1;
                    }
                }
            }
        }

        // for (int i = 0; i < n ; i++) {
        //     for (int j = 0; j < m; j++) cout << ck[i][j] << " ";
        //     cout << endl;
        // }
        if (allApple > 0) result = -1;
        cout << result << endl;
    }
}