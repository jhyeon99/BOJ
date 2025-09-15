#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000000;
int failFunc[MAX];        // KMP 실패 함수(Failure Function)
vector<int> ans;          // 패턴이 등장한 위치 저장 (1-based index)

// 실패 함수 계산
void CalcFailFunc(string s) {
    for (int i = 1, j = 0; i < s.length(); i++) {
        // 일치하지 않으면 실패 함수 값으로 되돌림
        while (j && s[i] != s[j]) {
            j = failFunc[j - 1];
        }
        if (s[i] == s[j]) j++;
        failFunc[i] = j; // 실패 함수 저장
    }
}

// KMP 알고리즘으로 패턴 검색
void KMP(string t, string p) {
    for (int i = 0, j = 0; i < t.length(); i++) {
        // 일치하지 않으면 실패 함수 값으로 되돌림
        while (j && t[i] != p[j]) {
            j = failFunc[j - 1];
        }
        if (t[i] == p[j]) {
            j++;
            if (j == p.length()) {
                ans.push_back(i - p.length() + 2); // 1-based index
                j = failFunc[j - 1]; // 다음 비교 위치
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string t, p;
    getline(cin, t);  // 검색 대상 문자열
    getline(cin, p);  // 패턴 문자열

    CalcFailFunc(p);  // 실패 함수 계산
    KMP(t, p);        // KMP 알고리즘 수행

    cout << ans.size() << '\n'; // 패턴 등장 횟수
    for (int a : ans) cout << a << ' '; // 등장 위치 출력
    return 0;
}
