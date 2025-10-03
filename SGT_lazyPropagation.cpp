#include <bits/stdc++.h>
#define int long long
using namespace std;

class SGT {
public:
    void build(int idx, int low, int hi, int seg[], int arr[], int lazy[]) {
        if (low == hi) {
            seg[idx] = arr[low];
            return;
        }
        int mid = (low + hi) / 2;
        build(2 * idx + 1, low, mid, seg, arr, lazy);
        build(2 * idx + 2, mid + 1, hi, seg, arr, lazy);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    void update(int idx, int low, int hi, int l, int r, int val, int seg[], int lazy[]) {
        // resolve pending updates
        if (lazy[idx] != 0) {
            seg[idx] += (hi - low + 1) * lazy[idx];
            if (low != hi) {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }

        // no overlap
        if (hi < l || low > r) return;

        // complete overlap
        if (low >= l && hi <= r) {
            seg[idx] += (hi - low + 1) * val;
            if (low != hi) {
                lazy[2 * idx + 1] += val;
                lazy[2 * idx + 2] += val;
            }
            return;
        }

        // partial overlap
        int mid = (low + hi) / 2;
        update(2 * idx + 1, low, mid, l, r, val, seg, lazy);
        update(2 * idx + 2, mid + 1, hi, l, r, val, seg, lazy);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    int query(int idx, int low, int hi, int l, int r, int seg[], int lazy[]) {
        // resolve pending updates
        if (lazy[idx] != 0) {
            seg[idx] += (hi - low + 1) * lazy[idx];
            if (low != hi) {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }

        // no overlap
        if (hi < l || low > r) return 0;

        // complete overlap
        if (low >= l && hi <= r) return seg[idx];

        // partial overlap
        int mid = (low + hi) / 2;
        int left = query(2 * idx + 1, low, mid, l, r, seg, lazy);
        int right = query(2 * idx + 2, mid + 1, hi, l, r, seg, lazy);
        return left + right;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i];

    int seg[4 * n], lazy[4 * n];
    memset(seg, 0, sizeof(seg));
    memset(lazy, 0, sizeof(lazy));

    SGT tree;
    tree.build(0, 0, n - 1, seg, arr, lazy);

    int q;
    cin >> q; // number of queries
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            // range query
            int l, r;
            cin >> l >> r;
            cout << tree.query(0, 0, n - 1, l, r, seg, lazy) << "\n";
        } else {
            // range update
            int l, r, val;
            cin >> l >> r >> val;
            tree.update(0, 0, n - 1, l, r, val, seg, lazy);
        }
    }

    return 0;
}
