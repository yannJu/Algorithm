/*
K-택배 회사는 N개의 도시에 물류창고를 만들어 전국에 물건을 배송한다. 
물건을 배송하다 보면 A 물류창고에서 B 물류창고로 물건을 옮겨야 하는 일이 생기게 된다. 
각 도시 사이에는 도로가 건설돼 있어 배송 차량이 다닐 수 있지만, 도로 보존을 위해 각각의 도로마다 차량의 중량을 제안하고 있다. 
만약 중량 제한을 초과하는 차량이 도로를 이용하다 적발되는 경우 엄청난 벌금을 물게 된다. 
이때, 두 물류창고 사이에 한 번의 이동으로 옮길 수 있는 최대 중량을 계산하는 프로그램을 작성하시오. 
단, 차량의 무게는 무시하며, 도로는 양방향 이동이 가능하다. 

입력
첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤ 10)가 입력된다. 두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 
각 테스트 케이스의 첫 번째 줄에는 도시의 수 N (2 ≤ N ≤ 1,000)과 도시를 연결하는 도로의 수 M (1 ≤M ≤ 10,000), 
물류를 옮길 창고 A 와 창고 B 의 번호(2 ≤ A, B ≤ N )가 순서대로 주어진다. 
다음 M 개의 줄에는 도로의 정보를 나타내는 세 정수 O, D (1 ≤ O, D ≤ N ), C (1 ≤ C ≤ 10,000) 이 주어진다. 
이것은 두 도시 O 와 D 사이에 중량 제한 C 를 나타내는 것이다. 

출력
입력되는 테스트 케이스 순서대로 출력의 첫 줄에 입구에서 출구까지 최소이동 거리를 출력한다. 

입출력 예
입력 출력
2
3 3 1 3
1 2 2
3 1 3
2 3 2
5 10 3 1
2 4 4
5 3 3
2 4 7
3 2 4
2 1 6
5 1 2
2 4 6
3 1 7
3 2 6
5 4 3

3
7
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int delivery(vector<vector<pair<int, int> >>cityMap, int A, int B, int end, int city);
int isRoute(vector<vector<pair<int, int> >>cityMap, int mid, int A, int B, int city);
int main()  {
    int testC, city, road, A, B, maxNum = -1;

    cin >> testC;
    while(testC--) {
        cin >> city >> road >> A >> B;
        vector<vector<pair<int, int>>> cityMap;

        //create map
        for (int i = 0; i < city; i++) {
            vector<pair<int, int>> tmp;
            cityMap.push_back(tmp);
        }

        //set Cost
        for (int i = 0; i < road; i++) {
                int O, D, C;
                cin >> O >> D >> C;

                cityMap[O - 1].push_back(make_pair(D, C));
                cityMap[D - 1].push_back(make_pair(O, C));
                maxNum = max(C, maxNum);
        }

        cout << delivery(cityMap, A, B, maxNum, city) << endl;
    }
}

int delivery(vector<vector<pair<int, int> >> cityMap, int A, int B, int end, int city) {
    int result = -1, start = 0, mid = -1;

    while (start <= end) {
        mid = (start + end) / 2;
        if (isRoute(cityMap, mid, A, B, city)) start = mid + 1;
        else end = mid - 1;
    }

    result = end;
    return result;
}

int isRoute(vector<vector<pair<int, int> >> cityMap, int mid, int A, int B, int city) {
    queue<int> q;
    vector<int> ckCity;

    for (int j = 0; j < city; j++) ckCity.push_back(0);
    ckCity[A - 1] = 1;

    q.push(A);
    while(!q.empty()) {
        int node = q.front();
        q.pop();

        if (node == B) return 1;
        for (int i = 0; i < cityMap[node - 1].size(); i++) {
            if (cityMap[node - 1][i].second >= mid) {
                if (ckCity[cityMap[node - 1][i].first - 1] == 0){ 
                    q.push(cityMap[node - 1][i].first);
                    ckCity[cityMap[node - 1][i].first - 1] = 1;
                }
            }
        }
    }

    return 0;
}