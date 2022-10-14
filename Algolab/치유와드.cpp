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
#define pii pair<int, int>
using namespace std;

int main() {
    int testC;

    cin >> testC;
    while (testC--) {
        int n, m, a, b;
        vector<int> *poison, *heal, *resultMap;
        vector<pii> poisonAry, healAry;

        cin >> n >> m;
        //Create Map =====
        poison = new vector<int>[n];
        heal = new vector<int>[n];
        resultMap = new vector<int>[n];
        
        for (int i = 0; i < n; i++) {
            vector<int> tmpP, tmpH, tmpR;
            for (int j = 0; j < n; j++) {
                tmpP.push_back(0);
                tmpH.push_back(0);
                tmpR.push_back(0);
            }

            poison[i] = tmpP;
            heal[i] = tmpH;
            resultMap[i] = tmpR;
        }
        // Posion & Heal Setting
        cin >> a >> b;

        for (int i = 0; i < a; i++) {
            int pX, pY;

            cin >> pY >> pX;
            poison[pY][pX] = -1;
            poisonAry.push_back(make_pair(pY, pX));
        }
        for (int j = 0; j < b; j++) {
            int hX, hY;

            cin >> hY >> hX;
            heal[hY][hX] = 1;
            healAry.push_back(make_pair(hY, hX));
        }

        // Calc pass _ Poison
        for (int p = 0; p < poisonAry.size(); p++) {
            int nowX, nowY;

            nowY = poisonAry[p].first; nowX = poisonAry[p].second;
            for (int mm = 1; mm <= m; mm++) {
                for (int i = -mm; i <= mm; i++) {
                    for (int j = -mm; j < mm; j++) {
                        if ((nowY + i >= 0 && nowY + i < n) && (nowX + j >= 0 && nowX + j < n)) poison[nowY + i][nowX + j] -= 1;
                    }
                }
            }
        }
        // Calc pass _ Heal
        for (int h = 0; h < healAry.size(); h++) {
            int nowX, nowY;

            nowY = healAry[h].first; nowX = healAry[h].second;
            for (int mm = 1; mm <= m; mm++) {
                for (int i = -mm; i <= mm; i++) { 
                    for (int j = -mm + (i * -1); j < mm - (i * -1); j++) {  
                        if ((nowY + i >= 0 && nowY + i < n) && (nowX + j >= 0 && nowX + j < n)) heal[nowY + i][nowX + j] += 1;
                    }
                }
            }
        }

// (y - 2) : x
// (y - 1) : x - 1 ~ x + 1
// (y) : x - 2 ~ x + 2
// y + 1 : x - 1 ~ x + 1
// y + 2  ; x

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << poison[i][j] << " ";
            }
            cout << endl;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << heal[i][j] << " ";
            }
            cout << endl;
        }
    }
}