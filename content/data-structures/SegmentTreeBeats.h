/**
 * Author: Cube219
 * Date: 2022-07-22
 * Description: Lazy segment tree with has min/max query
 * 
 */
#pragma once

template <int N>
struct SegTree
{
    struct Node {
        int mx1, mx2, mx1cnt;
        ll sum;
    };
    Node t[N * 3];
    int stLeaf, n;

    void init(int n) {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }
    void initv(int idx, int v) {
        t[stLeaf + idx] = { v, -1, 1, v };
    }
    void build() {
        for(int i = stLeaf - 1; i > 0; --i) merge(i);
    }

    void merge(int node) {
        if(node >= stLeaf) return;

        Node l = t[node * 2];
        Node r = t[node * 2 + 1];
        Node& cur = t[node];

        if(l.mx1 == r.mx1) {
            cur.mx1 = l.mx1;
            cur.mx1cnt = l.mx1cnt + r.mx1cnt;
            cur.mx2 = max(l.mx2, r.mx2);
        } else {
            if(l.mx1 < r.mx1) swap(l, r);
            cur.mx1 = l.mx1;
            cur.mx1cnt = l.mx1cnt;
            cur.mx2 = max(l.mx2, r.mx1);
        }
        cur.sum = l.sum + r.sum;
    }

    void propagate(int l, int r, int node) {
        if(node >= stLeaf) return;

        Node& cur = t[node];
        for(int i = 0; i < 2; ++i) {
            int cnode = node * 2 + i;
            Node& c = t[cnode];
            if(cur.mx1 >= c.mx1) continue;

            c.sum -= c.mx1cnt * (ll)(c.mx1 - cur.mx1);
            c.mx1 = cur.mx1;
        }
    }

    void updateImpl(int cl, int cr, int l, int r, int node, int v) {
        propagate(cl, cr, node);
        if(cr < l || r < cl || t[node].mx1 <= v) return;
        if(l <= cl && cr <= r && t[node].mx1 > v && v > t[node].mx2) {
            t[node].sum -= t[node].mx1cnt * (ll)(t[node].mx1 - v);
            t[node].mx1 = v;

            propagate(cl, cr, node);
            return;
        }
        int m = (cl + cr) / 2;
        updateImpl(cl, m, l, r, node * 2, v);
        updateImpl(m + 1, cr, l, r, node * 2 + 1, v);
        merge(node);
    }
    void minUpdate(int l, int r, int v) {
        updateImpl(0, stLeaf - 1, l, r, 1, v);
    }

    ll getmaxImpl(int cl, int cr, int l, int r, int node) {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node].mx1;
        int m = (cl + cr) / 2;
        ll res = getmaxImpl(cl, m, l, r, node * 2);
        res = max(res, getmaxImpl(m + 1, cr, l, r, node * 2 + 1));
        return res;
    }
    ll getmax(int l, int r) {
        return getmaxImpl(0, stLeaf - 1, l, r, 1);
    }

    ll getsumImpl(int cl, int cr, int l, int r, int node) {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node].sum;
        int m = (cl + cr) / 2;
        ll res = getsumImpl(cl, m, l, r, node * 2);
        res += getsumImpl(m + 1, cr, l, r, node * 2 + 1);
        return res;
    }
    ll getsum(int l, int r) {
        return getsumImpl(0, stLeaf - 1, l, r, 1);
    }
};
