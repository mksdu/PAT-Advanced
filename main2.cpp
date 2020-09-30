#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;
const int N = 1010;
typedef pair<int, int> pii;

int n, m, k, q, cnt;
int per[N], T[N], pre[N];
queue<pii> que[30];

void push_q() {
    int u;
    for(cnt = 1; cnt <= min(n * m, k);) {
        for(int i = 1; i <= n; i++) {
            if(que[i].empty()) u = 0;
            else u = que[i].back().first;
            que[i].push({cnt, per[cnt]});
            pre[cnt] = u;
//            cout << cnt << " " << u << endl;
            cnt++;
        }
    }
}

void get_time(int x, int &h, int &f) {
    h = x / 60;
    f = x % 60;
    h += 8;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif // ONLINE_JUDGE
    cin >> n >> m >> k >> q;
    for(int i = 1; i <= k; i++) cin >> per[i];
    push_q();

//    for(int i = 1; i <= n; i++) {
//        while(!que[i].empty()) {
//            cout << que[i].front().first << " " << que[i].front().second << endl;
//            que[i].pop();
//        }
//        cout << endl;
//    }
    while(true) {
        int cur = -1, min1 = 1000, pre1, flag = 0;
        for(int i = 1; i <= n; i++) {
            if(!que[i].empty()) {
                flag = 1;
                int u = que[i].front().first;
                int v = que[i].back().first;
                T[u] = T[pre[u]] + per[u];
                if(T[u] < min1) {
                    cur = i;
                    pre1 = v;
                    min1 = T[u];
                }
            }
        }
        if(flag) {
            que[cur].pop();
            if(cnt <= k) {
                que[cur].push({cnt, per[cnt]});
                pre[cnt] = pre1;
                cnt++;
            }
        }
        else
            break;
    }

    for(int i = 0; i < q; i++) {
        int x, h = 0, f = 0;
        cin >> x;
        get_time(T[x], h, f);
        if(T[x] + 8 * 60 - per[x] < 17 *60) printf("%02d:%02d\n", h, f);
        else printf("Sorry\n");
    }

    return 0;
}

