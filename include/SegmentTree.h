#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <vector>

class SegmentTree {
private:
    std::vector<int> tree;
    int n;

    void build(const std::vector<int>& data, int node, int start, int end);
    void updateTree(int node, int start, int end, int idx, int val);
    int queryTree(int node, int start, int end, int idx) const;

public:
    SegmentTree(const std::vector<int>& data);
    void update(int idx, int val);
    int query(int idx) const;
};

#endif
