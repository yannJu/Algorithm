/*
스포츠 클라이밍은 인공으로 만든 암벽에 설치된 홀드(손잡이)를 잡고 등반하는 스포츠이다. 
스포츠 클라이밍 종목 중 리드는 정해진 시간 내 누가 더 높이 올라가는지 겨루는 종목으로 정상까지 최적의 경로로 올라가는 것이 중요하다.
최적 경로 분석을 위해 시작 지점부터 암벽의 각 홀드까지 최소 이동 횟수룰 계산하려 한다. 
이를 위해 암벽 정보가 정사각형 형태의 격자로 주어졌을 때, 각 홀드까지 이동하는데 필요한 횟수를 계산하는 프로그램을 작성하시오. 
격자 내 정보는 홀드/이동불가/빈칸 3종류가 존재하며, 각각 ‘H’, ‘X’, ‘.’으로 표현된다. 
시작 위치는 항상 마지막 행 첫 번째 열이며, 이동할 수 있는 홀드 규칙은 다음과 같다.
 1. 상하좌우 인접한 지역에 홀드가 있는 경우 주변 지형과 상관없이 이동 가능.
 2. 다음 조건을 만족하는 경우 좌우로 2칸 또는 3칸 떨어진 홀드로 이동 가능.
 - 두 홀드의 바로 윗 칸이 빈칸일 때
 - 두 홀드를 직선으로 이었을 때 지나가는 칸들이 빈칸일 때
 - 두 홀드를 직선으로 이었을 때 지나가는 칸들의 윗 칸이 비었을 때
 3. 바로 윗 칸이 빈칸인 경우 위로 2칸 떨어진 홀드로 이동 가능.
 4. 왼쪽 칸과 윗 칸이 빈칸인 경우 좌상단에 있는 홀드로 이동 가능.
 5. 오른쪽 칸과 윗 칸이 빈칸인 경우 우상단에 있는 홀드로 이동 가능.
H <---> H
H <---- ----> H
2번 규칙에 의한 이동
H
↑
H
3번 규칙에 의한 이동
H
H
4번 규칙에 의한 이동
H
H
5번 규칙에 의한 이동
위 그림은 두 홀드를 이동하는 방법을 그림으로 나타낸 것으로, 노란색은 빈칸을 나타낸다. 
만약 노란색 칸 중 하나라도 빈칸이 아닌 경우 두 홀드 사이를 이동할 수 없다. 

입력
입력은 표준입력(standard input)을 사용한다. 
첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤20)가 입력된다. 
두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 
각 테스트 케이스의 첫 번째 줄에는 격자의 크기를 나타내는 자연수 n (3 ≤ n ≤ 500) 이 주어진다. 
두 번째 줄부터는 n 개 줄에 걸쳐 격자 정보(H 또는 . 또는 X)가 각 줄에 n 개씩 공백을 기준으로 주어진다. 

출력
출력은 표준출력(standard output)을 사용한다. 입력 테스트 케이스의 순서대로 각 홀드까지 최소 이동 횟수를 입력된 격자와 같은 형태로 출력한다. 이때, 빈칸은 0, 이동 불가능한 홀드는 –1을 출력한다.


입출력 예
입력 출력 
2
3
H . H
. H X
H . H 
6
H . . . . H
. . H . . .
. . H . X H
H . . H . .
. . . . H H
H . . H . H
----------
2 0 -1
0 2 0
1 0 -1
-1 0 0 0 0 6
0 0 5 0 0 0
0 0 4 0 0 5
2 0 0 3 0 0
0 0 0 0 3 4
1 0 0 2 0 5 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main() {
    int testC;
    vector<vector<int> > dir(4, vector<int>(2, 0));
    dir[0][0] = -1; dir[0][1] = 0; // up
    dir[2][0] = 0; dir[2][1] = -1; // left
    dir[1][0] = 1; dir[1][1] = 0; // down
    dir[3][0] = 0; dir[3][1] = 1; // right

    cin >> testC;
    while(testC--) {
        int n, nextX, nextY;
        queue<pair<int, int> > q;

        cin >> n;
        vector<vector<int> > result(n, vector<int>(n, INT_MAX)), ck(n, vector<int>(n, 0));
        vector<vector<char> > map(n, vector<char>(n, '1'));

        // create map
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cin >> map[i][j];
        }

        q.push(make_pair(n - 1, 0));
        result[n - 1][0] = 1;
        while(!q.empty()) {
            pair<int, int> pii = q.front();
            q.pop();
            ck[pii.first][pii.second] = 1;
            // 1번 규칙
            for (int i = 0; i < 4; i++) {
                nextY = pii.first + dir[i][0]; nextX = pii.second + dir[i][1];
                if ((nextY >= 0 && nextY < n) && (nextX >= 0 && nextX < n)) {
                    if (map[nextY][nextX] == 'H') {
                        result[nextY][nextX] = min(result[nextY][nextX], result[pii.first][pii.second] + 1);
                        if (ck[nextY][nextX] == 0) q.push(make_pair(nextY, nextX));
                    }
                }
            }

            // 2번 규칙 & 3번 규칙
            if (pii.first - 1 >= 0) {
                if (map[pii.first - 1][pii.second] == '.' && pii.first - 2 >= 0) {
                    if (map[pii.first - 2][pii.second] == 'H') {
                        result[pii.first - 2][pii.second] = min(result[pii.first - 2][pii.second], result[pii.first][pii.second] + 1);
                        if (ck[pii.first - 2][pii.second] == 0) q.push(make_pair(pii.first - 2, pii.second));
                    }
                }

                // 2번 규칙 (우)
                for (int i = 0; i <= 3; i++) {
                    if (pii.second + i > n || pii.first - 1 < 0) break;
                    if (map[pii.first][pii.second + i] == 'X') break;
                    if (map[pii.first - 1][pii.second + i] != '.') break;
                    
                    if (i == 3 && map[pii.first][pii.second + i] == 'H') {
                        result[pii.first][pii.second + i] = min(result[pii.first][pii.second + i], result[pii.first][pii.second] + 1);
                        if (ck[pii.first][pii.second + i] == 0) q.push(make_pair(pii.first, pii.second + i));
                    }
                    else if (i == 2) {
                        if (map[pii.first][pii.second + i] == 'H') {
                            result[pii.first][pii.second + i] = min(result[pii.first][pii.second + i], result[pii.first][pii.second] + 1);
                            if (ck[pii.first][pii.second + i] == 0) q.push(make_pair(pii.first, pii.second + i));
                            break;
                        }
                        else {
                            if (map[pii.first][pii.second + i] != '.') break;
                        }
                    }
                    else if (i == 1) {
                        if (map[pii.first][pii.second + i] != '.') break;
                    }
                }

                // 2번 규칙 (좌)
                for (int i = 0; i <= 3; i++) {
                    if (pii.second - i < 0 || pii.first - 1 < 0) break;
                    if (map[pii.first][pii.second - i] == 'X') break;
                    if (map[pii.first - 1][pii.second - i] != '.') break;
                    
                    if (i == 3 && map[pii.first][pii.second - i] == 'H') {
                        result[pii.first][pii.second - i] = min(result[pii.first][pii.second - i], result[pii.first][pii.second] + 1);
                        if (ck[pii.first][pii.second - i] == 0) q.push(make_pair(pii.first, pii.second - i));
                    }
                    else if (i == 2) {
                        if (map[pii.first][pii.second - i] == 'H') {
                            result[pii.first][pii.second - i] = min(result[pii.first][pii.second - i], result[pii.first][pii.second] + 1);
                            if (ck[pii.first][pii.second - i] == 0) q.push(make_pair(pii.first, pii.second - i));
                            break;
                        }
                        else {
                            if (map[pii.first][pii.second - i] != '.') break;
                        }
                    }
                    else if (i == 1) {
                        if (map[pii.first][pii.second - i] != '.') break;
                    }
                }
            }

            // 4번, 5번 규칙
            if (pii.first - 1 >= 0 && pii.second - 1 >= 0) {
                if (map[pii.first - 1][pii.second] == '.' && map[pii.first][pii.second - 1] == '.') {
                    if (map[pii.first - 1][pii.second - 1] == 'H') {
                        result[pii.first - 1][pii.second - 1] = min(result[pii.first - 1][pii.second - 1], result[pii.first][pii.second] + 1);
                        if (ck[pii.first - 1][pii.second - 1] == 0) q.push(make_pair(pii.first - 1, pii.second - 1));
                    }
                }
            }
            if (pii.first - 1 >= 0 && pii.second + 1 < n) {
                if (map[pii.first - 1][pii.second] == '.' && map[pii.first][pii.second + 1] == '.'){
                    if (map[pii.first - 1][pii.second + 1] == 'H') {
                        result[pii.first - 1][pii.second + 1] = min(result[pii.first - 1][pii.second + 1], result[pii.first][pii.second] + 1);
                        if (ck[pii.first - 1][pii.second + 1] == 0) q.push(make_pair(pii.first - 1, pii.second + 1));
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (result[i][j] == INT_MAX && map[i][j] == 'H') cout << -1 << " ";
                else if (result[i][j] == INT_MAX) cout << 0 << " ";
                else cout << result[i][j] << " ";
            }
            cout << endl;
        }
    }
}