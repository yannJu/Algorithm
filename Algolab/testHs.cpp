#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;
int dir[4][2] = {{-1,0}, {0,-1}, {0,1}, {1,0}};
int dir_r[4][2] = {{1,0}, {0,1}, {0,-1}, {-1,0}};
int is_market[16][16];
int is_house[16][16];
int is_block[16][16];
pair<int,int> bfs(pair<int,int> point, vector<pair<int,int>> house, int n){
    vector<vector<int>> visited(n, vector<int>(n,0));
    vector<vector<int>> distance(n, vector<int>(n,0));
    queue<pair<int,int>> q;
    q.push(point);
    visited[point.first][point.second] = 1;
    distance[point.first][point.second] = 1;
    while(!q.empty()){
        point = q.front(); q.pop();
        for(int i=0; i<4; i++){
            int x = point.first + dir[i][0];
            int y = point.second + dir[i][1];
            if(x >= 0 && x < n && y >= 0 && y < n
            && !visited[x][y] && !is_block[x][y]){
                q.push(make_pair(x,y));
                visited[x][y] = 1;
                distance[x][y] = distance[point.first][point.second] + 1;
            }
        }
    }
    int min_v = 9999;
    pair<int,int> destination;
    for(auto i : house){
        int x = i.first; int y = i.second;
        if(!is_block[x][y]){
            min_v = min(min_v, distance[x][y]);
        }
    }
    for(auto i : house){
        int x = i.first; int y = i.second;
        if(distance[x][y] == min_v && !is_block[x][y]){
            destination = make_pair(x, y);
            is_block[x][y] = 1;
            break;
        }
  }
  return destination;
}
pair<int,int> move_one(pair<int,int> person, pair<int,int> market, int n){
    vector<vector<int>> visited(n, vector<int>(n,0));
    vector<vector<int>> distance(n, vector<int>(n,9999));
    visited[market.first][market.second] = 1;
    distance[market.first][market.second] = 1;
    queue<pair<int,int>> q;
    q.push(market);
    pair<int,int> point;
    int x, y;
    bool escape = false;
    while(!q.empty()){
        point = q.front(); q.pop();
        for(int i=0; i<4; i++){
            x = point.first + dir_r[i][0];
            y = point.second + dir_r[i][1];
            if(x >= 0 && x < n && y >= 0 && y < 0
            && !visited[x][y] && !is_block[x][y]){
                q.push(make_pair(x,y));
                visited[x][y] = 1;
                distance[x][y] = distance[point.first][point.second] + 1;
                if(x == person.first && y == person.second){
                    escape = true;
                    break;
                }
            }
        }
        if(escape){
            break;
        }
    }
    int min_v = 9999;
    for(int i=0; i<4; i++){
        x = person.first + dir[i][0];
        y = person.second + dir[i][1];
        if(x >= 0 && x < n && y >= 0 && y < n && !is_block[x][y]){
            min_v = min(min_v, distance[x][y]);
        }
    }
    for(int i=0; i<4; i++){
        x = person.first + dir[i][0];
        y = person.second + dir[i][1];
        if(x >= 0 && x < n && y >= 0 && y < n
        && !is_block[x][y] && distance[x][y] == min_v){
            return make_pair(x,y);
        }
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        int n, m, data;
        cin >> n >> m;
        vector<pair<int,int>> house;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cin >> data;
                // is배열들 다시쓰기위해서 초기화 해주기
                is_market[i][j] = 0;
                is_house[i][j] = 0;
                is_block[i][j] = 0;
                if(data){
                    // house 위치 기록
                    is_house[i][j] = 1;
                    house.push_back(make_pair(i,j));
                }
            }
        }
        // market 위치 기록. 배열들 0행 기준으로 하기위해 좌표값 -1 해주기
        int x, y;
        vector<pair<int,int>> market;
        market.push_back(make_pair(0,0));
        for(int i=0; i<m; i++){
            cin >> x >> y;
            is_market[x-1][y-1] = 1;
            market.push_back(make_pair(x-1,y-1));
        }
        // 시간 돌리면서 시물레이션 구현하기!
        int minute = 1;
        vector<pair<int,int>> person;
        person.push_back(make_pair(0,0)); // index 0 안쓰기 위해서 아무거나 넣기
        // 도착한 사람 번호 집합
        set<int> s;
        while(s.size() < m){
            cout << "minute : " << minute << endl;
            for(int i=1; i<minute+1; i++){
                // 다 도착했으면 나가기
                if(s.size() == m){
                    break;
                }
                // 사람 추가하기
                if(person.size() < minute+1 && i == minute && person.size() < m + 1){
                    // 숙소 정해서 들어가면 바로 막힘
                    person.push_back(bfs(market[i], house, n));
                    continue;
                }
                // 도착하지 않은 사람 이동하기
                else if(!s.count(i)){
                    person[i] = move_one(person[i], market[i], n);
                    cout << i << "point : " << person[i].first << ", " << person[i].second << endl;
                }
                // 성심당 도착 표시
                if(person[i] == market[i]){
                    cout << "arr_person : " << i << endl;
                    s.insert(i);
                    cout << "s_size : " << s.size() << endl;
                }
            }
            // 사람들 위치 확인 전체적으로 하면서 가게 지나가면 막기
            // 사람없는 숙소 지나가도 막아야하나 ? 일단 안막고 해보자
            for(int i=1; i<minute+1; i++){
                x = person[i].first;
                y = person[i].second;
                if(is_market[x][y]){
                    is_block[x][y] = 1;
                }
            }
            minute++;
            cout << "---------------------------------------" << endl;
        }
        cout << minute - 1 << endl;
    }
}