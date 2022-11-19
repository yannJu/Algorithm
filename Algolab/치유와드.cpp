/*
OO게임은 새로운 던전에 몬스터가 없는 정사각 형태의 안전지대를 만들려고 한다. 안전지대에는 몬스터는
없지만 지속 피해를 주는 독 효과를 넣고, 유저들은 치유와드를 사용하여 독 효과를 상쇄시킬 수 있도록
하려고 한다. 독 효과와 치유와드는 아래와 같은 특징을 갖는다.
 1. 독 효과
 - 독 효과는 시체에서 발생하며, 효과 범위는 매분 아래와 같은 방식으로 늘어난다.
 - 독 효과 영향권에 들어간 지역은 매분 피해 효과가 ‘1’씩 증가한다. (음수로 표현)
 2. 치유와드
 - 치유와드의 치유 효과 범위는 매분 아래 그림과 같은 방식으로 늘어난다.
 - 치유와드 영향권에 들어간 지역은 매분 회복 효과가 ‘1’씩 증가한다. (양수로 표현)
한 칸은 다수의 독 효과 또는 치유 효과가 중첩되어 적용될 수 있다. 예를 들어 독 효과 4개와 치유 효과
1개의 영향권에 있는 지역은 매분 3의 피해 효과를 준다. 처음 안전지대에 진입한 시점을 0분이라 하고 이때 모든 위치의 효과 값이 0일 때, m 분 후 안전지대 각
위치 효과 적용 상황을 출력하는 프로그램을 작성하시오. 

입력
입력은 표준입력(standard input)을 사용한다. 첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤20)가 입력된다. 
두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 각 테스트 케이스의 첫 번째 줄에는 안전지대의 크기 n과 시간 m (5 ≤ n ≤ 20, 1 ≤ m ≤ 100,000,000) 이 주어진다. 
두 번째 줄에는 시체의 수와 치유와드의 수 a와 b (1 ≤ a, b ≤ n) 가 공백을 기준으로 순서대로 주어진다. 
이후 a 개의 줄에 걸쳐 시체가 위치한 행과 열 (0 ≤ r, c < n) 이 공백을 기준으로 순서대로 주어지며, 
이후 다시 b 개의 줄에 걸쳐 와드가 위치한 행과 열의 정보가 공백을 기준으로 순서대로 주어진다. 

출력
출력은 표준출력(standard output)을 사용한다. 각 테스트 케이스가 출력되는 첫 줄부터 안전지대의 효과
상태를 n개의 줄에 걸쳐 출력한다. 

입출력 예
입력 
2
5 2
1 1
1 1
2 2
5 3
2 2
0 0
4 4
0 4
4 0

출력
-2 -2 -1 -1 0
-2 -1 0 0 0
-1 0 0 1 1
-1 0 1 0 0
0 0 1 0 0

-3 -2 0 2 3
-2 -4 -2 0 2
0 -2 -4 -2 0
2 0 -2 -4 -2
3 2 0 -2 -3
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define pii pair<int, int>
using namespace std;

int main() {
    int testC;

    cin >> testC;
    while(testC--) {
        int n, m, a, b; // n : 안전지대 크기, m : 시간, a : 시체 수, b : 치유와드 수
        int pMax = -1, cMax = -1;
        int mm, pcFlag = 1;
        vector<pii> poisonXY, careXY;
        vector<vector<int> > map;

        cin >> n >> m >> a >> b;
        // 안전지대 초기화
        for (int i = 0; i < n; i++) {
            vector<int> tmp;
            for (int j = 0; j < n; j++) tmp.push_back(0);
            map.push_back(tmp);
        }
        
        // 시체위치 담기 + setting
        for (int i = 0; i < a; i++) {
            int pX, pY;

            cin >> pY >> pX;
            poisonXY.push_back(make_pair(pY, pX));
            pMax = max({pMax, (n - pY), (n - pX), pY, pX});\
        }

        // 치유와드 위치 담기
        for (int j = 0; j < b; j++) {
            int cX, cY;

            cin >> cY >> cX;
            careXY.push_back(make_pair(cY, cX));
            cMax = max({cMax, ((n - cX) + (n - cY)), ((n - cX) + cY), (cX + (n - cY)), (cX + cY)});
            // cMax = max({cMax, (cX + cY), (n - cX + cY), (2*n - cX + cY)});
        }

<<<<<<< HEAD
        if (m > cMax || m > pMax) m = max(cMax, pMax);
        cout << "M : " << m << endl;
        cout << " cmax : " << cMax << " pMax : " << pMax << endl;
=======
        mm = m;
        if (m > cMax && m > pMax) mm = max(cMax, pMax);
        // cout << "M : " << m << endl;
        // cout << " cmax : " << cMax << " pMax : " << pMax << endl;
>>>>>>> f7dc6a3b99a8d80be9d9daf7a228196ae61b0730
        // 시체 setting
        for (int i = 0; i < poisonXY.size(); i++) {
            int tmpPX = poisonXY[i].second, tmpPY = poisonXY[i].first;
            for (int ll = 1; ll <= mm; ll++) {
                for (int j = -1 * ll; j < ll + 1; j++) { // Y
                    for (int k = -1 * ll; k < ll + 1; k++) { // X
                        if ((tmpPY + j >= 0 && tmpPY + j < n) && (tmpPX + k >= 0 && tmpPX + k < n)) map[tmpPY + j][tmpPX + k] -= 1;
                    }
                }
            }
        }

        // 치유와드 setting
        for (int i = 0; i < careXY.size(); i++) {
            int tmpCX = careXY[i].second, tmpCY = careXY[i].first;
            for (int ll = 1; ll <= mm; ll++) { // minute
                for (int j = -1 * ll; j < ll + 1; j++) { // Y
                    for (int k = -1 * ll + abs(j); k < ll - abs(j) + 1; k++) { //X
                        if ((tmpCY + j >= 0 && tmpCY + j < n) && (tmpCX + k >= 0 && tmpCX + k < n)) map[tmpCY + j][tmpCX + k] += 1;
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            //a == poison , b = heal  b - a
            for (int j = 0; j < n; j++) cout << map[i][j] + ((m - mm) * (b - a)) << " ";
            cout << endl;
        }
    }
}