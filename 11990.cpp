#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")

        using namespace std;

        using ll  = long long;
        using vi  = vector<int>;

        #define pb push_back
        #define ff first
        #define ss second
        #define lb lower_bound
        #define all(x) (x).begin() , (x).end()

        int n, q, arr[200005], ps[200005], batch; ll st[4*200005]; vector<int>blocks[2000];
        void init() {
            for(int l = 0; l <= n / batch; l++) blocks[l].clear();
            for(int l = 0; l <= 4 * n; l++) st[l] = 0, arr[l] = 0;
        }
        void build() {
            for(int l = 0; l < n; l++) blocks[l / batch].pb(arr[l]);
            for(int l = 0; l <= n / batch; l++) sort(all(blocks[l]));
        }
        int upd(int v) {
            int pos = ps[v];
            auto it = lb(all(blocks[pos / batch]), v);
            blocks[pos / batch].erase(it);
            ll res = 0;
            for(auto u : blocks[pos / batch]) {
                int p = ps[u];
                if(p < pos) { if(u > v) res++; }
                if(p > pos) { if(u < v) res++; }
            }
            for(int l = 0; l <= n / batch; l++) {
                if(l == pos / batch) continue;
                if(l < pos / batch) {
                    int curr = (int)blocks[l].size();
                    res += curr - (lb(all(blocks[l]), v) - blocks[l].begin());
                }
                if(l > pos / batch) {
                    res += lb(all(blocks[l]), v) - blocks[l].begin();
                }
            }
            return res;
        }
        void update(int v, int l, int r, int pos) {
            if(l == r) {
                st[v] ++;
                return;
            }
            int md = (l+r)/2;
            if(pos <= md) update(v*2, l, md, pos);
            else update(v*2+1, md + 1, r, pos);
            st[v] = st[v*2] + st[v*2+1];
        }
        ll query(int v, int l, int r, int lo, int hi) {
            if(l>hi||r<lo) return 0;
            if(l>=lo&&r<=hi) return st[v];
            return query(v*2, l, (l+r)/2, lo, hi) + query(v*2+1, (l+r)/2+1, r, lo, hi);
        }

        int32_t main() {
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
            /// freopen("in.txt", "r", stdin);
            /// freopen("out.txt", "w", stdout);
            while(cin >> n >> q) {
                batch = sqrt(n); init(); ll res = 0;
                for(int l = 0; l < n; l++) {
                    cin >> arr[l]; ps[arr[l]] = l;
                    res += query(1, 1, n, arr[l], n);
                    update(1, 1, n, arr[l]);
                }
                build();
                while(q--) {
                    cout << res << "\n";
                    int a; cin >> a; res -= upd(a);
                }
            }
        }


