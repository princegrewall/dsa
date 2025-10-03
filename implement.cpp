#include <bits/stdc++.h>
#define int long long
using namespace std;

class SGT {
public:
    void build(int idx, int low, int hi, int seg[], int arr[]) {
        if (low == hi) {
            seg[idx] = arr[low];
            return;
        }
        int mid = (low + hi) / 2;
        build(2 * idx + 1, low, mid, seg, arr);
        build(2 * idx + 2, mid + 1, hi, seg, arr);
        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    int query(int idx, int low, int hi, int seg[], int l, int r) {
        // no overlap
        if (hi < l || low > r) return LLONG_MAX;

        // complete overlap
        if (low >= l && hi <= r) return seg[idx];

        // partial overlap
        int mid = (low + hi) / 2;
        int left = query(2 * idx + 1, low, mid, seg, l, r);
        int right = query(2 * idx + 2, mid + 1, hi, seg, l, r);
        return min(left, right);
    }

    void update(int idx, int low, int hi, int seg[], int i, int val) {
        if (low == hi) {
            seg[idx] = val;
            return;
        }
        int mid = (low + hi) / 2;
        if (i <= mid) update(2 * idx + 1, low, mid, seg, i, val);
        else update(2 * idx + 2, mid + 1, hi, seg, i, val);

        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

   int n;
    cin >> n;
     int arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i];

    int seg[4 * n]; // segment tree size
    SGT tree;

    tree.build(0, 0, n - 1, seg, arr);

    int q;
    cin >> q; // number of queries
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            // query range minimum
            int l, r;
            cin >> l >> r;
            cout << tree.query(0, 0, n - 1, seg, l, r) << "\n";
        } else {
            // update index
            int idx, val;
            cin >> idx >> val;
            tree.update(0, 0, n - 1, seg, idx, val);
        }
    }

    return 0;
}
