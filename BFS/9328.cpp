#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

const int MAX = 102;     // 최대 행/열 크기
const int ALPHA = 26;    // 알파벳 개수
const int DIR = 4;       // 상, 하, 좌, 우 4방향

char c[MAX][MAX];        // 맵 정보
bool vst[MAX][MAX];      // 방문 여부
pii dir[DIR] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // 이동 방향

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;  // 테스트 케이스 수
    while (t--)
    {
        int h, w; cin >> h >> w;
        
        // 맵 테두리를 '.'로 초기화 (경계 처리)
        for (int i = 0; i <= h + 1; i++) c[i][0] = c[i][w + 1] = '.';
        for (int j = 0; j <= w + 1; j++) c[0][j] = c[h + 1][j] = '.';
        
        // 맵 입력
        for (int i = 1; i <= h; i++)
        {
            cin.ignore();
            for (int j = 1; j <= w; j++)
            {
                c[i][j] = cin.get();
            }
        }

        // 초기 열쇠 입력
        string s;
        cin.ignore();
        getline(cin, s);
        bool key[ALPHA] = {};
        for (char t : s)
            if ('a' <= t && t <= 'z')
                key[t - 'a'] = true;

        // BFS 초기화
        queue<pii> q;
        q.push({0, 0});
        for (int i = 0; i <= h + 1; i++)
            for (int j = 0; j <= w + 1; j++)
                vst[i][j] = false;
        vst[0][0] = true;

        // 문이 잠겨 있을 때 열쇠를 기다리는 좌표 저장
        vector<pii> d[ALPHA];
        int ans = 0;  // 수집한 문서 개수

        // BFS 탐색
        while (!q.empty())
        {
            pii curr = q.front(); q.pop();
            for (int i = 0; i < DIR; i++)
            {
                pii next = {curr.first + dir[i].first, curr.second + dir[i].second};
                if (next.first < 0 || next.first > h + 1 || next.second < 0 || next.second > w + 1) continue;
                if (vst[next.first][next.second]) continue;

                char ch = c[next.first][next.second];
                // 이동 가능한 칸: 빈칸, 문서, 열쇠, 문
                if (ch == '.' || ch == '$' || ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
                {
                    // 문인데 열쇠가 없으면 대기
                    if ('A' <= ch && ch <= 'Z' && !key[ch - 'A'])
                    {
                        d[ch - 'A'].push_back(next);
                        continue;
                    }

                    // 이동 처리
                    vst[next.first][next.second] = true;
                    q.push(next);

                    // 문서 수집
                    if (ch == '$') ans++;

                    // 열쇠 발견 시 잠겨있는 문 열기
                    else if ('a' <= ch && ch <= 'z')
                    {
                        key[ch - 'a'] = true;
                        for (pii open : d[ch - 'a'])
                            q.push(open);
                    }
                }
            }
        }

        cout << ans << '\n';
    }
    return 0;
}
