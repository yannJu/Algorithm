/*
학생들에게 수학을 가르치고 있는 쿠민이는 곧 다가오는 중간고사에서 복잡한 계산이 필요한 문제를 내고
싶어 학생들이 계산기를 사용하는 것에 대해 고민하고 있다. 시험시간 내 문제를 풀기 위해선 계산기가 꼭
필요하지만, 사용을 허락하기에는 요즘 계산기엔 기능이 너무 많아 고민이다. 이런 쿠민이를 위해 +, -, *, () 만 사용할 수 있는 계산기를 만드시오. 계산기는 전체 수식을 한 번에 입력받는다. 
입력된 수식에 +, -, * 가 섞여 있는 경우 곱셈을 덧셈/뺄셈보다 먼저 계산하며, 덧셈과 뺄셈은 왼쪽부터 순서대로 계산한다. 
그리고 수식에 괄호‘()’가 있는 경우 괄호안에 수식을 먼저 계산한다. 
예를 들어, 입력된 수식이 2 + 2 * 2 인 경우 계산 결과는 6이 되며, ( 2 + 2 ) * 2 인 경우 계산 결과는 8이 된다. 
** Python으로 문제를 해결하는 경우 eval() 사용 절대 금지 ** 

입력
첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤ 100)가 입력된다. 
두 번째 줄부터는 각 테스트 케이스에 대한 입력이 주어진다. 
각 테스트 케이스의 첫 번째 줄에는 기호를 포함한 전체 수식의 길이 l (3 ≤ l ≤ 50)이 주어진다. 
두 번째 줄에는 자연수와 기호(+, -, ×, ( )) 로 구성된 수식이 공백을 기준으로 입력된다. 
이때, 숫자는 자릿수에 상관없이 수식에서 1의 길이를 가진다. 잘못된 수식이 입력되거나 계산 결과 ‘integer overflow’가 발생하는
경우는 없다. 

출력
입력되는 테스트 케이스 순서대로 출력의 첫 줄에 수식의 계산 결과를 출력한다. 

입출력 예
입력 출력
3
5
2 + 2 * 2
222*+
7
( 2 + 2 ) * 2
22+2*
3
2 - 3
23-
6
8
-1
*/

//곱셈, 나눗셈, 괄호는 먼저 계산하고 나머지 연산은 스택에 넣기?
//곱셈, 나눗셈 계산시 스택에서 마지막 숫자를 가져와야함

#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

int main() {
    int testC;

    cin >> testC;
    while(testC--) {
        int l;
        string tmp;
        stack<string> sOp;
        vector<string> result;

        cin >> l;
        while(l--) {
            cin >> tmp;
            if (tmp.compare("+") == 0) {
                if (!sOp.empty()) {
                    while(!sOp.empty()) {
                        if (sOp.top().compare("(") == 0) break;
                        result.push_back(sOp.top());
                        sOp.pop();
                    }
                }
                
                sOp.push("+");
            }
            else if (tmp.compare("-") == 0) {
                if (!sOp.empty()) {
                    while(!sOp.empty()) {
                        if (sOp.top().compare("(") == 0) break;
                        result.push_back(sOp.top());
                        sOp.pop();
                    }
                }
                
                sOp.push("-");
            }
            else if (tmp.compare("*") == 0) sOp.push("*");
            else if (tmp.compare("(") == 0) sOp.push("(");
            else if (tmp.compare(")") == 0) {
                while(sOp.top().compare("(") != 0) {
                    result.push_back(sOp.top());
                    sOp.pop();
                }
                sOp.pop();
            }
            else result.push_back(tmp);
        }
        while(!sOp.empty()) {
            result.push_back(sOp.top());
            sOp.pop();
        }

        for (int i = 0; i < result.size(); i++) cout << result[i] << " ";
        cout << endl;
        //Calculate
        stack<long long> calcS;
        long long answer = 0;
        for (int i = 0; i < result.size(); i++) {
            long long first, second;
            string ckResult = result[i];

            if (ckResult.compare("+") == 0) {
                first = calcS.top();
                calcS.pop();
                second = calcS.top();
                calcS.pop();
                answer = first + second;

                calcS.push(answer);
            }
            else if (ckResult.compare("-") == 0) {
                first = calcS.top();
                calcS.pop();
                second = calcS.top();
                calcS.pop();
                answer = second - first;

                calcS.push(answer);
            }
            else if (ckResult.compare("*") == 0) {
                first = calcS.top();
                calcS.pop();
                second = calcS.top();
                calcS.pop();
                answer = first * second;

                calcS.push(answer);
            }
            else calcS.push(stoll(ckResult));
        }
        cout << calcS.top() << endl;
    }
}
