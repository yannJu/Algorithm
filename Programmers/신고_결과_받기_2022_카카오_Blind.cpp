#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    int **ckAry = new int*[id_list.size()];
    
    for (int i = 0; i < id_list.size(); i++) {
        int *tmp = new int[id_list.size()];
        answer.push_back(0);
        for (int j = 0; j < id_list.size(); j++) tmp[j] = 0;
        ckAry[i] = tmp;
    }
    
    for (int j = 0; j < report.size(); j++) {
        string tmp = report[j], reportUser = "", stoppedUser = "";
        int reportIdx = -1, stoppedIdx = -1, reportCk = 0;
        
        for (int k = 0; k < tmp.length(); k++) {
            if (tmp[k] == ' ') reportCk = 1;
            else {
                if (reportCk == 0) reportUser += tmp[k];
                else stoppedUser += tmp[k];
            }
        }
        for (int l = 0; l < id_list.size(); l++) {
            if (id_list[l].compare(reportUser) == 0) reportIdx = l;
            if (id_list[l].compare(stoppedUser) == 0) stoppedIdx = l;
            if (reportIdx > -1 && stoppedIdx > -1) break;
        }
        
        if (ckAry[reportIdx][stoppedIdx] == 0) {
            ckAry[reportIdx][stoppedIdx] += 1;
            ckAry[stoppedIdx][stoppedIdx] += 1;
        }
    }
    
    for (int i = 0; i < id_list.size(); i++) {
        if (ckAry[i][i] >= k) {
            for (int j = 0; j < id_list.size(); j++) {
                if (ckAry[j][i] == 1 && i != j) answer[j] += 1;
            }
        }
    }
    return answer;
}