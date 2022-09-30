#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int testC;

    cin >> testC;
    while(testC--) {
        int N, result = -1;
        cin >> N;

        //create Map
        vector<int> *map = new vector<int>[N], *memo = new vector<int>[N];
        for (int i = 0; i < N; i++) {
            int tmp;
            vector<int> vtmp, ckTmp;
            for (int j = 0; j < 5; j++) {
                cin >> tmp;
                vtmp.push_back(tmp);
                ckTmp.push_back(0);
            }
            map[i] = vtmp;
            memo[i] = ckTmp;
        }

        for (int i = N-1; i > -1; i--) {
//"--------------------------------------------------------------------------------------------------------------------------------------------------------------"
            if (i == N-1){
              for(int j=1; j<4; j++){
                if(map[i][j] != 1){
                  int memorize = map[i][j];

                  if(j-1 >= 0 && map[i][j-1] == 1) memorize++;                  //양옆 장애물 탐색
                  if(j+1 < 5 && map[i][j+1] == 1) memorize++;

                  memo[i][j] = memorize;
                }
              }
            }
            else{
              for (int j = 0; j < 5; j++) {
                  //그냥 map[i][j] = 1이면 어차피 장애물칸이니깐 continue 해주면 좋을듯 for문 탐색 안하고
                  if(map[i][j] != 1){
                    int memorize = map[i][j];

                    if(j-1 >= 0 && map[i][j-1] == 1) memorize++;                  //양옆 장애물 탐색
                    if(j+1 < 5 && map[i][j+1] == 1) memorize++;

                    int l=0, s=memo[i+1][j], r=0;                                 // memo값중에서 이용가능한 최대값 구하기
                    if(j-1 >= 0) l = memo[i+1][j-1];
                    if(j+1 < 5) r = memo[i+1][j+1];
                    memorize += max({l,r,s});

                    memo[i][j] = memorize;
                  }
                }
              }
//"--------------------------------------------------------------------------------------------------------------------------------------------------------------"
        }

        for (int i = 0; i < 5; i++) result = max(result, memo[0][i]);
        cout << result << endl;

        // for (int i = 0; i < N; i++) {
        //     for (int j = 0; j < 5; j++) cout << memo[i][j] << " ";
        //     cout << endl;
        // }
    }
}