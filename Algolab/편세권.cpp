/*
편의점은 이제 단순히 물건을 사는 곳을 넘어 한 끼 식사를 해결하고, 택배, 금융, 세탁, 경비실 역할까지
해주는 생활 플랫폼이 되었다. 이러한 편의점의 기능으로 인해 주변에 얼마나 가까이 얼마나 많은 편의점이 있는가가 집을 평가하는 기준이 돼, 
편세권이란 신조어까지 생겼다. 쿠민이는 이런 트렌드에 맞춰 편세권을 점수화하고 이를 제공하는 서비스를 만들려고 한다. 
쿠민이가 생각하는 편세권 점수 산정 방식은 다음과 같다.
 1. 집으로부터 거리가 10 이하인 편의점의 수
 2. 집으로부터 거리가 3 이하인 편의점 × 2
 3. 거리는 맨하탄 거리로 계산
 4. 편의점이 있는 위치는 제외
위 규칙에 따라 아래 그림에서 ‘*’이 편의점 위치일 때, (2, 3)의 편세권 점수는 4 + (3 × 2) = 10점이 된다. 
전체 지도의 크기(n × n)와 편의점의 위치 정보가 입력으로 주어질 때, 가장 편세권 점수가 높은 곳의 좌표를 편세권 점수와 함께 출력하는 프로그램을 작성하시오. 
최고 점수인 지역이 2개 이상인 경우 행 번호가 작은 지역을, 행 번호도 같다면 열 번호가 작은 지역을 출력하시오. 

입력
첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (3 ≤ t ≤ 20)가 입력된다. 두 번째 줄부터는 각 테스트
케이스에 대한 입력이 주어진다. 각 테스트 케이스의 첫 번째 줄에는 지도의 크기 n (2 ≤ n ≤ 50)과 지도에 표시된 편의점의 수 c (3 ≤c
≤ 200)이 주어진다. 두 번째 줄부터 편의점의 행과 열 (0 ≤ r,c < n )가 n개의 줄에 걸쳐 입력된다. 

출력
입력되는 테스트 케이스 순서대로 출력의 첫 줄에 편세권 점수가 가장 높은 곳의 행과 열 그리고 그 점수를 공백을 기준으로 순서대로 출력한다.

입출력 예
입력 출력 
2
7 4
2 1
4 3
5 2
2 5
5 10
0 0
1 0
2 0
3 0
4 0
0 4
1 4
2 4
3 4
4 4

2 2 12
1 2 22
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int tCase;

    cin >> tCase;
    while(tCase--) {
        int n, c, resultX, resultY, score = -1;
        vector<int> *map;
        vector<pair<int, int> > C;

        cin >> n >> c;
        map = new vector<int>[n];
        
        // Create Map
        for (int i = 0; i < n; i++) {
            vector<int> tmp;
            for (int j = 0; j < n; j++) {
                tmp.push_back(0);
            }
            map[i] = tmp;
        }
        // Setting C
        for (int i = 0; i < c; i++) {
            int y, x;
            cin >> y >> x;

            C.push_back(make_pair(y, x));
            map[y][x] = -1;
        }

        for (int i = 0; i < c; i++) {
            for (int j = 0; j < n; j++){
                for (int k = 0; k < n; k++) {
                    if (map[j][k] > -1) {
                        if (abs(j - C[i].first) + abs(k - C[i].second) <= 3) map[j][k] += 3;
                        else if (abs(j - C[i].first) + abs(k - C[i].second) <= 10) map[j][k] += 1;

                        if (score < map[j][k]) {
                            resultX = k;
                            resultY = j;
                            score = map[j][k];
                        }
                    } 
                }
            }
        }

        cout << resultY << " " << resultX << " " << score << endl;
    }
}