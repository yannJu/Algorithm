/*
대전 성심당의 튀김소보로가 전국적으로 인기를 얻어 사람이 몰리자 빵을 구하기 힘들어졌습니다. 
대전의 명물이 된 성심당은 대전 곳곳에 직영점을 운영하기 시작했습니다. 이때, 빵을 구하고자 하는 m명의 사람이 있는데, 
1번 사람은 정확히 1분에, 2번 사람은 정확히 2분에, ..., m번 사람은 정확히 m 분에 각자의 숙소에서 출발하여 성심당 직영점으로 이동하기 시작합니다. 
숙소와 성심당의 위치를 나타내는 지도는 n×n 크기의 격자로 표현됩니다. 
사람들은 출발 시간이 되기 전까지 격자 밖에 나와 있으며, 사람들이 목표로 하는 성심당은 모두 다릅니다. 
성심당으로 이동하는 사람들은 다음과 같은 방법으로 움직입니다. 이 3가지 행동은 총 1분 동안 진행되며, 정확히 1, 2, 3 순서로 진행되어야 합니다.
 1. 격자에 있는 사람들이 본인이 가려고 하는 성심당 직영점 방향으로 1칸 움직입니다. 이동 방향은
최단거리로 움직이며, 이동 가능한 방향이 여러 가지인 경우 ↑, ←, →, ↓ 의 우선순위로 움직입니다.
 2. 성심당에 도착한다면 해당 위치에서 멈추게 되며, 이때부터 다른 사람들은 도착한 성심당이 있는
칸을 지나갈 수 없게 됩니다.
 3. 현재시간이 t 분이고 t ≤ m 를 만족한다면, t 번 사람은 자신이 가고 싶은 성심당과 가장 가까이 있는 숙소에 들어갑니다. 
 여기서 가장 가까이에 있다는 뜻 역시 최단거리를 의미합니다. 
 가장 가까운 숙소가 여러 가지인 경우, 그중 행이 작은 숙소, 행이 같다면 열이 작은 숙소로 들어갑니다. 
 이때, 사람이 숙소로 이동하는 시간은 고려하지 않습니다.
 사람이 숙소로 이동한 순간부터 해당 칸은 지나갈 수 없습니다. 
 t 번 사람이 성심당을 향해 움직이기 시작해 숙소를 비웠더라도 이동할 수 없습니다. 아래 그림은 5×5크기의 격자에, 숙소 3곳, 성심당 2곳인 경우의 예입니다. 
 1분에는 격자에 사람이 없기 때문에 1,2번 규칙에 의한 행동은 진행하지 않고 3번부터 진행됩니다.
3번 규칙에 따라 1분에는 1번 사람이 숙소에 들어갑니다. 
이때, 1번 사람이 가려고 하는 1번 성심당과 최단거리를 가지는 숙소는 2곳[(2, 1), (2, 5)]이지만, 열 번호가 더 작은 (2, 1)로 이동합니다.
2분에는 1번 규칙에 따라 1번 사람이 1번 성심당 방향으로 1칸 이동합니다. 그 다음 2번 사람이 2번 성심당과 최단거리를 가지는 숙소로 이동합니다. 
이때, 2번 성심당과 최단거리를 가지는 숙소는 2곳[(4, 2), (5,5)]이지만, 행 번호가 더 작은 (4, 2)로 이동합니다.
3분에는 1번 사람이 1번 성심당에 도착하게 되고, 2번 규칙에 따라 1번 성심당 위치는 이동 불가능한 지역이 됩니다. 
그 다음 2번 사람이 2번 성심당 방향으로 1칸 이동합니다.
4분에는 2번 사람이 2번 성심당에 도착하게 되며, 모든 사람이 성심당에 도착할 때까지 총 4분의 시간이 걸렸습니다.
위 예시와 같이 사람들이 움직일 때 총 몇 분 후에 모든 사람이 성심당에 도착하는지를 구하는 프로그램을 작성하시오. 

입력
입력은 표준입력(standard input)을 사용한다. 
첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤20)가 입력된다. 두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 
각 테스트 케이스의 첫 번째 줄에는 격자의 크기와 사람 수를 나타내는 자연수 n 과 m (3 ≤ n ≤ 15, 1 ≤m ≤ 30) 이 주어진다. 
두 번째 줄부터는 n 개 줄에 걸쳐 격자 정보(0 또는 1)가 각 줄에 n 개씩 공백을 기준으로 주어진다. 
격자 정보가 입력된 그 다음 줄부터 m 개 줄에 걸쳐 각 사람이 가고싶은 성심당의 위치가 행과 열(1 ≤ r, c ≤ n) 순서대로 공백을 기준으로 입력된다. 
이때, 격자 내 1의 수는 사람의 수보다 크거나 같다. 

출력
출력은 표준출력(standard output)을 사용한다. 
입력 테스트 케이스의 순서대로 모든 사람이 성심당에 도착하는데 걸리는 시간을 출력한다.
입출력 예
입력 출력 
2
5 2
0 0 0 0 0
1 0 0 0 1
0 0 0 0 0
0 1 0 0 0
0 0 0 0 1
2 3
4 4
5 3
0 0 0 0 1
1 0 0 0 0
0 0 0 0 0
0 1 0 0 0
0 0 0 1 0
2 3
4 3
5 1 

4
6
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#define vii vector<vector<int> >
using namespace std;

vii DIR(4, vector<int>(2, 0));
pair<int, int> findH(vii map, pair<int, int> market);
int main() {
    int testC;

    cin >> testC;
    DIR[3][0] = -1; DIR[3][1] = 0;
    DIR[2][0] = 0; DIR[2][1] = -1;
    DIR[1][0] = 0; DIR[1][1] = 1;
    DIR[0][0] = 1; DIR[0][1] = 0;

    while(testC--) {
        int n, m;
        int result = 0, people = 0;

        cin >> n >> m;
        vii map(n, vector<int>(n, 0));
        vector<pair<int, int> > markets, peoples(m, pair<int, int>(-1, -1));

        // Create Map (숙소 포함)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cin >> map[i][j];
        }

        int time = 0;
        while (m > people) {
            vector<pair<int, int> > tmp;
            cout << time << endl;
            // Create Markets XY
            if (time < m) {
                int y, x;
                cin >> y >> x;

                y -= 1; x -= 1;
                markets.push_back(make_pair(y, x));
            }
            for (int i = 0; i < markets.size(); i++) {
                if (peoples[i].first == markets[i].first && peoples[i].second == markets[i].second) {
                    tmp.push_back(make_pair(peoples[i].first, peoples[i].second));
                    people += 1;
                    peoples[i].first = -2; peoples[i].second = -2;
                }
                else if (peoples[i].first > -2) {
                    if (peoples[i].first == -1) {
                        pair<int, int> XY = findH(map, markets[i]);
                        peoples[i] = XY;
                    }
                    else {
                        int prevL = INT_MAX;
                        for (int j = 0; j < 4; j++) {
                            int nextY = DIR[j][0] + peoples[i].first, nextX = DIR[j][1] + peoples[i].second;

                            if ((nextY >= 0 && nextY < map.size()) && (nextX >= 0 && nextX < map.size())) {
                                if (abs(markets[i].first - nextY) + abs(markets[i].second - nextX) < prevL) {
                                    peoples[i].first = nextY;
                                    peoples[i].second = nextX;
                                }
                                else if (abs(markets[i].first - nextY) + abs(markets[i].second - nextX) == prevL) {
                                    if (nextY < peoples[i].first || (nextY == peoples[i].first && nextX < peoples[i].second)) {
                                        peoples[i].first = nextY;
                                        peoples[i].second = nextX;
                                    }
                                }
                            }
                        }
                    }
                }
                cout << " Time : " << time << " Y : " << peoples[i].first << " X : " << peoples[i].second << endl;
                if (time > 100) break;
            } 
            for (int j = 0; j < tmp.size(); j++) map[tmp[j].first][tmp[j].second] = -1;
            time += 1;
        }

        cout << time << endl;
    }
}

pair<int, int> findH(vii map, pair<int, int> market) {
    queue<pair<int, int>> q;
    pair<int, int> result = make_pair(-1, -1);
    vii Ck(map.size(), vector<int>(map.size(), INT_MAX));

    q.push(market);
    Ck[market.first][market.second] = 0;

    while(!q.empty()) {
        pair<int, int> now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nextY = now.first + DIR[i][0], nextX = now.second + DIR[i][1];

            if ((nextY >= 0 && nextY < map.size()) && (nextX >= 0 && nextX < map.size())) {
                if (map[nextY][nextX] == 1) {
                    if (result.first == -1 || result.first > nextY || (result.first == nextY && result.second > nextX)) {
                        result.first = nextY;
                        result.second = nextX;
                    }
                }
                else if (map[nextY][nextX] == 0) {
                    if (Ck[nextY][nextX] == INT_MAX) q.push(make_pair(nextY, nextX));
                    Ck[nextY][nextX] = min(Ck[nextY][nextX], Ck[now.first][now.second] + 1);
                }
            }
        }
    }        

    return result;
}