/*
쿠민이는 요즘 주식에 빠져있다. 그는 미래를 내다보는 눈이 뛰어나, 예측한 주식의 가격이 항상 맞아떨어진다. 
매일 그는 아래 세 가지 중 한 행동을 한다.
 1. 주식 하나를 산다.
 2. 원하는 만큼 가지고 있는 주식을 판다.
 3. 아무것도 하지 않는다. 쿠민이는 미래를 예상하는 뛰어난 안목을 가졌지만, 어떻게 해야 자신이 최대 이익을 얻을 수 있는지 모른다. 
 그래서 쿠민이는 당신에게 매일의 주가를 알려주는 대신 최대 이익이 얼마나 되는지 계산을 해달라고
부탁했다. 예를 들어 쿠민이가 3일 치 주가 9, 5, 4 을 알려줬다면, 주가가 계속 감소하기 때문에, 최대 이익은 0이
된다. 그러나 만약 주가가 2, 5, 10 일 때는 처음 두 날에 주식을 하나씩 사고, 마지막 날 다 팔아 버리면
최대 이익 13을 얻을 수 있다.

입력
첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤ 100)가 입력된다. 두 번째 줄부터는 각 테스트
케이스에 대한 입력이 주어진다. 각 테스트 케이스의 첫 번째 줄에는 주가를 알려줄 날 수 d (3 ≤ d ≤ 100,000)이 주어진다. 
두 번째 줄에는 주가를 나타내는 d 개의 자연수가 공백을 기준으로 순서대로 주어진다. 

출력
입력되는 테스트 케이스 순서대로 출력의 첫 줄에 얻을 수 있는 최대 수익을 출력한다. 

입출력 예
입력 출력
3
3
9 5 4
3
2 5 10
6
3 3 7 9 7 4

0
13
14
*/

#include <iostream>
using namespace std;

int main() {
    int testC;

    cin >> testC;
    while(testC--) {
        int d;
        long long *stocks, maxStock, prevResult = 0, result = 0;

        cin >> d;
        stocks = new long long[d];
        for (int i = 0; i < d; i++) cin >> stocks[i];
        maxStock = d - 1;

       for (int i = d - 1; i > -1; i--) {
        if (stocks[i] > stocks[maxStock]) maxStock = i;
        else result += (stocks[maxStock] - stocks[i]);
       }

       cout << result << endl;
       delete stocks;
    }
}