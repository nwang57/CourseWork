#include <string>
#include <iostream>
#include <vector>
using namespace std;

class KMP {
public:
    KMP(string pattern) {
        build_automa(pattern);
    }
    
    KMP() {

    }

    void build_automa(string str) {
        pattern = str;
        if (str.length() != 0) {
            memo.resize(str.length());
            int j = -1;
            memo[0] = -1;
            for (int i=1;i<str.length();i++) {
                while (j > -1 && str[i] != str[j+1]) j = memo[j];
                if (str[i] == str[j+1]) j++;
                memo[i] = j;
            }
        }
    }
    int match_from(string str, int k) {
        if (str.length() == 0 || k >= str.length()) {
            return -1;
        }
        int j = -1;
        for (int i=k;i<str.length();i++) {
            while(j > -1 && str[i] != pattern[j+1]) j = memo[j];
            if (str[i] == pattern[j+1]) j++;
            if (j == pattern.length()-1) {
                return i-pattern.length()+1;
            }
        }
        return -1;
    }

    int match_one(string str) {
        return match_from(str, 0);
    }

    vector<int> match_all(string str) {
        vector<int> ret;
        int i = 0;
        while (i < str.length()) {
            int start = match_from(str, i);
            if (start == -1) break;
            i = start + pattern.length();
            ret.push_back(start);
        }
        return ret;
    }

    void print_memo() {
        for(int i=0;i<pattern.length();i++) {
            printf("%c:%d\n", pattern[i], memo[i]);
        }
    }
private:
    vector<int> memo;
    string pattern;
};


int main() {
    string pat = "cool";
    string str = "coco and cool!";
    string str2 = "yes mat coolcoolbear";
    KMP kmp;
    KMP kmp1("mat");
    kmp.build_automa(pat);
    int mat = kmp.match_one(str);
    int m1 = kmp1.match_one(str2);
    printf("Match 'mat' at %d\n", m1);
    printf("Match at %d, %s\n", mat, str.substr(mat, pat.length()).c_str());
    vector<int> matches = kmp.match_all(str2);
    printf("There are %d matches %d and %d\n", matches.size(), matches[0], matches[1]);
    return 0;
}
