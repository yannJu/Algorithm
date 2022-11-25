/*
어느 초등학교에서 학교 게시판에 백일장 입상작을 전시하기 위해 학교 홈페이지에서 학생들에게 작품 추천을 받고 있다. 게시판에 전시되는 입상작은 아래와 같은 규칙을 갖는다.
 1. 처음 게시판은 비워둔다.
 2. 새로운 학생 추천이 들어오면, 추천받은 작품은 반드시 게시판에 전시된다.
 3. 게시판에 공간이 없는 경우 추천 수가 가장 적은 작품이 빠지고 새로운 작품이 전시된다.
 이때, 가장 적은 추천 수를 갖는 작품이 2개 이상인 경우 더 오래된 작품이 게시판에서 빠진다.
 4. 새로운 학생 추천이 이미 전시된 작품인 경우 작품의 추천 수만 증가한다.
 5. 게시판에서 빠진 작품은 추천 횟수가 0으로 초기화되며, 추천이 있는 경우 다시 전시될 수 있다. 입력
입력은 표준입력(standard input)을 사용한다. 첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤50)가 입력된다. 두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 각 테스트 케이스의 첫 번째 줄에는 게시판에 전시될 수 있는 작품 수 n 과 학생 추천 수 m (1 ≤ n ≤ 20,
5 ≤ m ≤ 1,000) 이 공백을 기준으로 순서대로 주어진다. 두 번째 줄에는 학생이 추천한 m 개의 작품 번호가 공백을 기준으로 순서대로 주어지며, 이때 작품 번호는 1부터 100 사이의 값을 갖는다. 출력
출력은 표준출력(standard output)을 사용한다. 입력 테스트 케이스의 순서대로 결과를 출력한다. 각 테스트 케이스에 대해 마지막에 전시되는 작품의 번호를 오름차순으로 출력한다. 입출력 예
입력 출력
3
3 9
2 1 4 3 5 6 2 7 2
5 9
2 1 4 3 5 6 2 7 2
3 11
4 1 9 4 5 3 9 4 7 8 4
2 6 7
2 3 5 6 7
4 7 8
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(vector<int> a, vector<int> b) {
    if (a[1] < b[1]) return true;
    else if (a[1] == b[1]) {
        if (a[2] < b[2]) return true;
        else return false;
    }
    else return false;
}

int main() {
    int testC;

    cin >> testC;
    while(testC--) {
        int n, m; // 작품수, 추천 갯수

        cin >> n >> m;
        vector<vector<int> > masterpieces, leave;

        for (int i = 0; i < m; i++) {
            int tmp;
            vector<int> tmpV;

            cin >> tmp;
            tmpV.push_back(tmp); tmpV.push_back(1); tmpV.push_back(i);
            if (masterpieces.size() < n) {
                masterpieces.push_back(tmpV);
            }
            else {
                int isIn = 0;
                for (int j = 0; j < n; j++) {
                    if (masterpieces[j][0] == tmp) {
                        masterpieces[j][1] += 1;
                        isIn = 1;
                        break;
                    }
                }
                if (isIn == 0) {
                    leave.push_back(masterpieces[0]);
                    masterpieces.erase(masterpieces.begin());
                    for (int k = 0; k < leave.size(); k++) {
                        if (leave[k][0] == tmp) {
                            masterpieces.push_back(leave[k]);
                            leave.erase(leave.begin() + k);
                        }
                    }
                    if (masterpieces.size() < n) masterpieces.push_back(tmpV);
                }
            }

            sort(masterpieces.begin(), masterpieces.end(), compare);
        }
        sort(masterpieces.begin(), masterpieces.end());
        for (int i = 0; i < masterpieces.size(); i++) cout << masterpieces[i][0] << " ";
        cout << endl;
    }
}