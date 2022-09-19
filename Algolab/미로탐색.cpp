/*
N×M 크기의 배열로 표현된 미로가 있을 때, 탈출에 필요한 최소 이동 거리를 계산하는 프로그램을 작성하시오. 
미로의 입구와 출구는 각각 (1, 1), (N, M)이며, ‘1’은 이동할 수 있는 칸을 나타내고, ‘0’은 이동할 수 없는 칸을 나타낸다. 
인접한 칸으로 한 칸씩 이동할 수 있으며, 이동한 거리를 계산할 때, 시작 위치와 도착
위치도 포함한다. 아래 그림은 배열로 표현된 미로의 예이다. 위 규칙에 따라 입구 (1, 1)에서 출구 (5, 5)까지 최단 이동 거리는 9 가 된다.

입력
첫 번째 줄에는 테스트 케이스 개수를 나타내는 t 가 입력된다. 두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 
각 테스트 케이스의 첫 번째 줄에는 미로의 크기 N 과 M (3 ≤ N, M ≤ 100)이 주어진다. 다음 N 개의 줄에는 M 개의 정수(0 또는 1)로 미로가 주어진다. 

출력
입력되는 테스트 케이스 순서대로 출력의 첫 줄에 입구에서 출구까지 최소이동 거리를 출력한다. 입출력 예

입력 출력
2
5 5
10000
10000
10000
11110
00011
3 6
101111
101010
111011

9
12
*/

#include <iostream>
#include <queue>
using namespace std;

struct DIR {
    int x;
    int y;
};
DIR dir[4];

void bfs(int ***ck, int ***map, int n, int m) ;
int main() {
    int testC;

    dir[0].x = -1; dir[0].y = 0; //좌
    dir[1].x = 1; dir[1].y = 0; //우
    dir[2].x = 0; dir[2].y = -1; //상
    dir[3].x = 0; dir[3].y = 1; //하

    cin >> testC;
    while(testC--) {
        int N, M, **map, **ck;
        string tmpRow;

        cin >> N >> M;
        map = new int*[N]; //map 2차원 배열
        ck = new int*[N]; //ck배열
        for (int i = 0; i < N; i++) {
            int *tmp = new int[M];
            int *ckTmp = new int[M];
            cin >> tmpRow;

            for (int j = 0 ; j < M; j++) {
                tmp[j] = tmpRow[j] - '0'; //map setting
                ckTmp[j] = 9999; //ck 를 9999로 setting
            }

            map[i] = tmp;
            ck[i] = ckTmp;
        }

        ck[0][0] = 1;
        bfs(&ck, &map, N, M);

        cout << ck[N - 1][M - 1] << endl;
    }
}

void bfs(int ***ck, int ***map, int n, int m) {
    int **CK = *ck;
    int ** MAP = *map;
    queue<pair<int, int> > q;

    q.push(make_pair(0, 0));

    while(!q.empty()) {
        pair<int, int> tmp = q.front();
        int row = tmp.first, col = tmp.second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            if ((row + dir[i].y > -1 && row + dir[i].y < n) && (col + dir[i].x > -1 && col + dir[i].x < m)) {
                if (MAP[row + dir[i].y][col + dir[i].x] == 1) {
                    if (CK[row + dir[i].y][col + dir[i].x] == 9999) q.push(make_pair(row + dir[i].y, col + dir[i].x)); // 한번도 ck 된적 없을 경우만 q에 삽입
                    CK[row + dir[i].y][col + dir[i].x] = min(CK[row + dir[i].y][col + dir[i].x], CK[row][col] + 1); //최소값을 setting
                }
            }
        }
    }

    ck = &CK;
}