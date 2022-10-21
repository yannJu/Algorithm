/*
보물의 위치를 쉽게 알아채지 못하도록 특별한 방법으로 표시한 보물 지도가 있다. 
그 보물 지도에는 보물의 위치가 따로 표시돼 있지 않고 이동할 방향과 거리만 나타내고 있다. 
보물 지도의 모습은 아래와 같다.
0 1 2 3 4
0 B1 L1 R2 F1 R2
1 F2 R2 L2 R2 F2
2 B1 L1 R2 L1 R1
3 R3 R3 B1 R2 R1
4 R1 R2 B1 L3 R2
그리고 지도에 표시된 암호를 해독하는 방법은 아래와 같다. 전 이동 방향 지도에 표시된 방향 이동할 방향
F F F
F R R
F L L
F B B
R F R
R R B
R L F
R B L
L F L
L R F
L L B
L B R
B F B
B R L
B L R
B B F
- B: 행이 감소하는 방향, F: 행이 증가하는 방향, R: 열이 증가하는 방향, L: 열이 감소하는 방향 
- 이동 방향 = 전 이동 방향 + 지도에 표시된 방향
- 이동 거리 = 지도에 표시된 크기 (이동 가능한 거리보다 더 큰 거리가 표시된 경우는 없음) 
- 보물 위치 = 두 번 이상 같은 방향으로 이동한 곳
- 시작 위치는 (0, 0) 이며, 첫 이동 시 전 이동 방향은 ‘B’ 로 한다.
위 규칙을 토대로 앞의 지도를 해석하면 아래 그림과 같은 방향으로 이동하며, 보물의 위치는 (0, 3)인 것을 확인할 수 있다. 

그렇다면 위와 같이 정사각형 모양의 지도가 주어질 때 보물의 위치를 찾는 프로그램을 작성하시오. 

입력
입력은 표준입력(standard input)을 사용한다. 첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤20)가 입력된다. 
두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 각 테스트 케이스의 첫 번째 줄에는 지도의 크기를 나타내는 자연수 n (4 ≤ n ≤ 50) 이 주어진다. 두 번째
줄부터는 지도에 들어갈 방향과 위치 정보 ab (a ∈ (B, R, F, L), 1 ≤ b ≤ 9)가 n 줄에 걸쳐 n 개씩 입력된다. 
잘못된 정보가 입력되거나, 보물이 없는 지도가 입력되는 경우는 없다. 

출력
출력은 표준출력(standard output)을 사용한다. 입력 테스트 케이스의 순서대로 다음 줄에 이어서 각 테스트의 결과를 출력한다. 
각 테스트 케이스에 해당하는 출력의 첫 줄에 입력된 지도에서 보물이 있는 곳을
공백을 기준으로 행과 열로 출력한다.

2
5
B1 L1 R2 F1 R2
F2 R2 L2 R2 F2
B1 L1 R2 L1 R1
R3 R3 B1 R2 R1
R1 R2 B1 L3 R2
5
B3 B1 R2 L2 R2
B1 F3 B1 R2 B1
F2 F1 F2 B2 R3
R4 R1 F3 L2 R3
R1 F1 B3 R2 B2

1 3 
2 2 
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int testC, **DIR;
    DIR = new int*[4];
    for (int i = 0; i < 4; i++) DIR[i] = new int[4];

    //DIR[0] F
    DIR[0][0] = 0; DIR[0][1] = 1; DIR[0][2] = 2; DIR[0][3] = 3; 
    //DIR[1] R
    DIR[1][0] = 1; DIR[1][1] = 3; DIR[1][2] = 0; DIR[1][3] = 2; 
    //DIR[2] L
    DIR[2][0] = 2; DIR[2][1] = 0; DIR[2][2] = 3; DIR[2][3] = 1; 
    //DIR[3] B
    DIR[3][0] = 3; DIR[3][1] = 2; DIR[3][2] = 1; DIR[3][3] = 0;

    cin >> testC;
    while(testC--) {
        int n, prev = 3;
        vector<pair<int, int> > *map;
        vector<vector<int> > *ck;

        cin >> n;
        map = new vector<pair<int, int> >[n];
        ck = new vector<vector<int> >[n];

        // F, R, L, B순으로 인덱싱
        // Create Map
        for (int i = 0; i < n; i++) {
            vector<pair<int, int> > tmpV;
            vector<vector<int> > tmpC;
            for (int j = 0; j < n; j++) {
                string tmp;
                vector<int> tmpsC;
                cin >> tmp;

                if (tmp[0] == 'F') tmpV.push_back(make_pair(0, tmp[1] - '0'));
                else if (tmp[0] == 'R') tmpV.push_back(make_pair(1, tmp[1] - '0'));
                else if (tmp[0] == 'L') tmpV.push_back(make_pair(2, tmp[1] - '0'));
                else if (tmp[0] == 'B') tmpV.push_back(make_pair(3, tmp[1] - '0'));

                for (int i = 0; i < 4; i++) tmpsC.push_back(0);
                tmpC.push_back(tmpsC);
            }
            map[i] = tmpV;
            ck[i] = tmpC;
        }

        int nowX = 0, nowY = 0;
        while (1) {
            int dir = DIR[prev][map[nowY][nowX].first];
            ck[nowY][nowX][dir] += 1;
            cout << "Y : " << nowY << " X: " << nowX << " CK : " << ck[nowY][nowX][dir] << endl;
            if (ck[nowY][nowX][dir] > 1) break;

            if (dir == 0) nowY += map[nowY][nowX].second;
            else if (dir == 1) nowX += map[nowY][nowX].second;
            else if (dir == 2) nowX -= map[nowY][nowX].second;
            else if (dir == 3) nowY -= map[nowY][nowX].second;

            prev = dir;
        }
        cout << nowY << " " << nowX << endl;
    }
}
