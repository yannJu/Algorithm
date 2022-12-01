/*
로봇청소기의 동작 방식과 n × n 크기의 격자로 표현된 방의 정보가 주어졌을 때, 로봇청소기 작동이 종료될 때까지 청소한 칸의 개수를 출력하는 프로그램을 작성하시오. 
격자의 각 칸은 1과 0으로 벽과 빈방을 나타낸다. 청소기는 바라보는 방향이 있으며, 이 방향은 동(1), 서(3), 남(2), 북(0) 중 하나이다. 로봇청소기가 동작하는 방식은 다음과 같다.
 1. 현재 위치를 청소.
 2. 현재 위치와 방향을 기준으로 왼쪽 방향부터 차례대로 탐색.
 2-1. 왼쪽 방향에 있는 공간이 아직 청소되지 않았다면, 왼쪽으로 회전하고 1칸을 전진한 다음 1번
규칙으로 이동.
 2-2. 왼쪽 방향에 있는 공간이 이미 청소가 됐다면, 왼쪽으로 회전 후 2번 규칙으로 이동.
 2-3. 네 방향 확인결과 청소할 곳이 없다면, 방향을 유지한 상태에서 1칸 후진 후 2번 규칙으로 이동.
 2-3. 네 방향 모두 확인결과 청소할 곳이 없고 뒤쪽 방향이 벽인 경우 작동 종료.
 ※ 로봇청소기는 벽을 통과할 수 없으며, 같은 곳을 두 번 이상 반복해서 청소하지 않는다. 입력
입력은 표준입력(standard input)을 사용한다. 첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤30)가 입력된다. 
두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 각 테스트 케이스의 첫 번째 줄에는 정사각 격자의 크기 n 과 로봇청소기의 방향 d (5 ≤ n ≤ 50, m ∈{0,
1, 2, 3}) 이 공백을 기준으로 순서대로 주어진다. 두 번째 줄에는 로봇청소기가 청소를 시작하는 격자의
행과 열 (1 ≤ r, c < n ) 이 공백을 기준으로 순서대로 입력된다. 세 번째 줄부터 이후 n개 줄에 걸쳐 격자 정보(0 또는 1)가 공백을 기준으로 순서대로 입력된다. 출력
출력은 표준출력(standard output)을 사용한다. 입력 테스트 케이스의 순서대로 결과를 출력한다. 각 테스트 케이스에 대해 로봇청소기가 청소한 격자 칸의 개수를 출력한다.
입출력 예
입력 출력 
2
4 0
1 1
1 1 1 1
1 0 1 1
1 0 0 1
1 1 1 1
10 0
7 4
1 1 1 1 1 1 1 1 1 1
1 0 0 0 0 0 0 0 0 1
1 0 0 0 1 1 1 1 0 1
1 0 0 1 1 0 0 0 0 1
1 0 1 1 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 1 0 1
1 0 0 0 0 0 1 1 0 1
1 0 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 1 1 1 
3
16
*/

#include <iostream>
#include <vector>
#define vii vector<vector<int> >
using namespace std;

vii DIR(4, vector<int>(3, 0));
void dfs(vii MAP, vii* CK, int* result, int nowY, int nowX, int dir, int isClean);
int main() {
    int testC;

    cin >> testC;
    while(testC--) {
        int n, m, nowX, nowY; // m : 북 -> 동 -> 남 -> 서 (0, 1, 2, 3)
        int result = 0;

        cin >> n >> m >> nowY >> nowX;
        vii map(n, vector<int>(n, 0)), ck(n, vector<int>(n, -1));
        DIR[0][0] = -1; DIR[0][1] = 0; DIR[0][2] = 3; // 북의 왼쪽은 서
        DIR[1][0] = 0; DIR[1][1] = 1; DIR[1][2] = 0; // 동의 왼쪽은 북
        DIR[2][0] = 1; DIR[2][1] = 0; DIR[2][2] = 1; // 남의 왼쪽은 동
        DIR[3][0] = 0; DIR[3][1] = -1; DIR[3][2] = 2; // 서의 왼쪽은 남

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cin >> map[i][j];
        }

        dfs(map, &ck, &result, nowY, nowX, m, 1);
        cout << result << endl;
    }
}

void dfs(vii MAP, vii* CK, int* result, int nowY, int nowX, int dir, int isClean) {
    vii ck = *CK;
    int ckAble = 0;
    
    if (isClean == 1 && ck[nowY][nowX] < 0) {
        result[0] += 1;
        ck[nowY][nowX] = 1; // 1. 청소한다. 
        CK = &ck;
    }

    int nowDir = dir, i = 0;
    for (i; i < 4; i++) {
        int nextDir = DIR[nowDir][2], nextY = nowY + DIR[nextDir][0], nextX = nowX + DIR[nextDir][1]; // 왼쪽으로 회전한 좌표값이 청소할 수 있는지 확인
        if ((nextY >= 0 && nextY < MAP.size()) && (nextX >= 0 && nextX < MAP.size())) {
            if (MAP[nextY][nextX] == 0 && ck[nextY][nextX] < 0) { // 빈공간이면서 청소를 아직 안한경우
                dfs(MAP, CK, result, nextY, nextX, nextDir, 1);
                break;
            }
            else if ((MAP[nextY][nextX] == 0 && ck[nextY][nextX] == 1) || (MAP[nextY][nextX] == 1)) { // 빈공간이면서 청소가 이미 된 경우 혹은 벽인경우 
                nowDir = nextDir;
            }
        }
        else nowDir = nextDir;
    }

    // 네 방향을 다 확인했으며, 청소를 할 수 없는 경우
    if (i == 4) {
        // 후진이 불가능한 경우
        int tmpY = nowY + (DIR[dir][0] * -1), tmpX = nowX + (DIR[dir][1] * -1);

        if ((tmpY >= 0 && tmpY < MAP.size()) && (tmpX >= 0 && tmpX < MAP.size())) {
            if (MAP[tmpY][tmpX] == 0) {
                dfs(MAP, CK, result, tmpY, tmpX, dir, 0);
            }
            else return;
        }
        else return;
    }
}