#include <iostream>
#include <vector>
using namespace std;

class SegTree {
    public:
        SegTree() {}
        SegTree(vector<int> array) {
            size = next_power_of_2(array.size());
            max_size = 2 * size;
            seg_tree_array.resize(max_size);
            for(int i=0;i<array.size();i++) {
                assign(i, array[i]);
            }
        }

        int next_power_of_2(int x) {
            x = x | (x >> 1);
            x = x | (x >> 2);
            x = x | (x >> 4);
            x = x | (x >> 8);
            x = x | (x >> 16);
            return x+1;
        }

        void assign(int idx, int val) {
            int i = idx + size;
            int diff = val - seg_tree_array[i];
            while(i > 0) {
                seg_tree_array[i] += diff;
                i = (i >> 1);
            }
        }

        int range_sum(int i, int j) {
            return range_sum_helper(1, 0, size-1, i, j);
        }

        int range_sum_helper(int v, int l, int r, int i, int j) {
            if (l == i && r == j)
                return seg_tree_array[v];
            int m = (l + r) / 2;
            int t1 = 0;
            int t2 = 0;
            if (i <= m) {
                t1 = range_sum_helper(2*v, l, m, i, min(m,j));
            }
            if (j > m) {
                t2 = range_sum_helper(2*v+1, m+1, r, max(i, m+1), j);
            }
            return t1 + t2;

        }

    private:
        vector<int> seg_tree_array;
        int size;
        int max_size;
};



int main() {
    vector<int> test_array = {1,2,3,4,5,6,7,8,9};
    SegTree seg_tree(test_array);
    cout << "Range sum 1:5 = " << seg_tree.range_sum(1, 5) << endl;
    seg_tree.assign(2,10);
    cout << "Range sum 1:5 = " << seg_tree.range_sum(1, 5) << endl;
}
