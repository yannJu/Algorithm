/*
n × n 크기의 이미지와 회전 각이 입력으로 주어질 때, 이미지를 입력된 각만큼 회전하는 프로그램을 작성하시오. 예를 들어, 입력으로 ‘그림 1’과 같은 이미지가 주어지고 회전각으로 90이 입력됐을 때 그 출력은 ‘그림
2’와 같이 될 것이다. 동일 이미지에 대해 –90이 회전각으로 입력됐다면, ‘그림 3’과 같이 출력될 것이다.
그림 1 그림 2 그림 3
입력
입력은 표준입력(standard input)을 사용한다. 첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤20)가 입력된다. 두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 각 테스트 케이스의 첫 번째 줄에는 사진의 크기를 나타내는 자연수 n 와 회전각 a (5 ≤ n ≤ 50, a ∈{-270, -180, -90, 0, 90, 180, 270}) 이 주어진다. 두 번째 줄부터는 n 개 줄에 걸쳐 이미지 각 픽셀의 값을 나타내는 0 에서 9 사이의 정수 n 개가 공백없이 주어진다. 출력
출력은 표준출력(standard output)을 사용한다. 입력 테스트 케이스의 순서대로 실행 결과를 출력한다. 출력은 이미지가 입력되는 형식과 같은 형식으로 출력한다.
입출력 예
입력 출력 2
5 90
01876
16521
46125
41628
52438
5 -90
01876
16521
46125
41628
52438
54410
21661
46158
32227
88516
61588
72223
85164
16612
01445
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int testC;

    cin >> testC;
    while(testC--) {
        int n, turn;
        vector<vector<int> > picture;

        cin >> n >> turn;
        for (int i = 0; i < n; i++) {
            vector<int> tmpV;
            string nums;

            cin >> nums;
            for (int i = 0; i < nums.length(); i++) tmpV.push_back(nums[i] - '0');
            picture.push_back(tmpV);
        }

        if (turn == 0) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) cout << picture[i][j];
                cout << endl;
            }
        }
        else if (turn == 90 || turn == -270) {
            for (int i = 0; i < n; i++) {
                for (int j = n - 1; j > -1; j--) cout << picture[j][i];
                cout << endl;
            }
        }
        else if (turn == -90 || turn == 270) {
            for (int i = n - 1; i > -1; i--) {
                for (int j = 0; j < n; j++) cout << picture[j][i];
                cout << endl;
            }
        }
        else if (turn == 180 || turn == -180) {
            for (int i = n - 1; i > -1; i--) {
                for (int j = n - 1; j > -1; j--) cout << picture[i][j];
                cout << endl;
            }
        }
    }
}