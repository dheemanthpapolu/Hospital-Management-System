#include "SegmentTree.h"

SegmentTree::SegmentTree(const std::vector<int>& data) {
    n = data.size();
    tree.resize(4 * n);
    build(data, 1, 0, n - 1);
}

void SegmentTree::build(const std::vector<int>& data, int node, int start, int end) {
    if (start == end) {
        tree[node] = data[start];
    } else {
        int mid = (start + end) / 2;
        build(data, 2 * node, start, mid);
        build(data, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

void SegmentTree::updateTree(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid)
            updateTree(2 * node, start, mid, idx, val);
        else
            updateTree(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

void SegmentTree::update(int idx, int val) {
    updateTree(1, 0, n - 1, idx, val);
}

int SegmentTree::queryTree(int node, int start, int end, int idx) const {
    if (start == end) {
        return tree[node];
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid)
            return queryTree(2 * node, start, mid, idx);
        else
            return queryTree(2 * node + 1, mid + 1, end, idx);
    }
}

int SegmentTree::query(int idx) const {
    return queryTree(1, 0, n - 1, idx);
}
