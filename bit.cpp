#include <iostream>
#include <vector>
using namespace std;

class BIT {
public:
    BIT(int n) {
        slots.resize(n+1);
    }

    void incr(int idx, int v) {
        while(idx < slots.size()) {
            slots[idx] += v;
            idx = go_up(idx);
        }
    }

    int sum2left(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += slots[idx];
            idx = go_down(idx);
        }
        return sum;
    }

    int go_up(int i) {
        return i + (i & (-i));
    }

    int go_down(int i) {
        return i - (i & (-i));
    }

private:
    vector<int> slots;
};

int main() {
    BIT bt(10);
    bt.incr(2, 1);
    cout << bt.sum2left(2) << " and " << bt.sum2left(8) << endl;
    bt.incr(6, 1);
    cout << bt.sum2left(1) << " and " << bt.sum2left(8) << endl;
}
