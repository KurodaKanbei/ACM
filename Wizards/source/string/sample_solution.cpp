#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <time.h>
#include <cstring>
#include <iostream>
#include <algorithm>

#define  pi acos(-1.0)
#define  eps 1e-9
#define  fi first
#define  se second
#define  rtl   rt<<1
#define  rtr   rt<<1|1
#define  bug               printf("******\n")
#define  mem(a, b)         memset(a,b,sizeof(a))
#define  name2str(x)       #x
#define  fuck(x)           cout<<#x" = "<<x<<endl
#define  sf(n)             scanf("%d", &n)
#define  sff(a, b)         scanf("%d %d", &a, &b)
#define  sfff(a, b, c)     scanf("%d %d %d", &a, &b, &c)
#define  sffff(a, b, c, d) scanf("%d %d %d %d", &a, &b, &c, &d)
#define  pf                printf
#define  FIN               freopen("../date.txt","r",stdin)
#define  gcd(a, b)         __gcd(a,b)
#define  lowbit(x)         x&-x
#define  IO                iOS::sync_with_stdio(false)


using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = 1e6 + 7;
const int maxm = 8e6 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;

struct Matrix {
    int mat[110][110], n;

    Matrix() {}

    Matrix(int _n) {
        n = _n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = 0;
    }

    Matrix operator*(const Matrix &b) const {
        Matrix ret = Matrix(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) {
                    int tmp = (long long) mat[i][k] * b.mat[k][j] % mod;
                    ret.mat[i][j] = (ret.mat[i][j] + tmp) % mod;
                }
        return ret;
    }
};


char buf[1000010];
int n, m, p;
map<char, int> mp;

struct Aho_Corasick {
    int next[110][52], fail[110], End[110];
    int root, cnt;

    int newnode() {
        for (int i = 0; i < 52; i++) next[cnt][i] = -1;
        End[cnt++] = 0;
        return cnt - 1;
    }

    void init() {
        cnt = 0;
        root = newnode();
    }

    void insert(char buf[]) {
        int len = strlen(buf);
        int now = root;
        for (int i = 0; i < len; i++) {
            if (next[now][mp[buf[i]]] == -1) next[now][mp[buf[i]]] = newnode();
            now = next[now][mp[buf[i]]];
        }
        End[now]++;
    }

    void build() {
        queue<int> Q;
        fail[root] = root;
        for (int i = 0; i < 52; i++)
            if (next[root][i] == -1) next[root][i] = root;
            else {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            if (End[fail[now]]) End[now] = 1;
            for (int i = 0; i < 52; i++)
                if (next[now][i] == -1) next[now][i] = next[fail[now]][i];
                else {
                    fail[next[now][i]] = next[fail[now]][i];
                    Q.push(next[now][i]);
                }
        }
    }

    Matrix get_Matrix() {
        Matrix ret = Matrix(cnt);
        for (int i = 0; i < cnt; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!End[next[i][j]]) ret.mat[i][next[i][j]]++;
            }
        }
        return ret;
    }

    void debug() {
        for (int i = 0; i < cnt; i++) {
            printf("id = %3d,fail = %3d,end = %3d,chi = [", i, fail[i], End[i]);
            for (int j = 0; j < 26; j++) printf("%2d", next[i][j]);
            printf("]\n");
        }
    }
} ac;

const int MAXL = 2500;
const int MAXN = 9999;
const int DLEN = 4;

class Big {
public:
    int a[600], len;

    Big(const int b = 0) {
        int c, d = b;
        len = 0;
        memset(a, 0, sizeof(a));
        while (d > MAXN) {
            c = d - (d / (MAXN + 1)) * (MAXN + 1);
            d = d / (MAXN + 1);
            a[len++] = c;
        }
        a[len++] = d;
    }

    Big(const char *s) {
        int t, k, index, L;
        memset(a, 0, sizeof(a));
        L = strlen(s);
        len = L / DLEN;
        if (L % DLEN) len++;
        index = 0;
        for (int i = L - 1; i >= 0; i -= DLEN) {
            t = 0;
            k = i - DLEN + 1;
            if (k < 0) k = 0;
            for (int j = k; j <= i; j++) t = t * 10 + s[j] - '0';
            a[index++] = t;
        }
    }

    Big operator/(const LL &b) const {
        Big ret;
        LL down = 0;
        for (int i = len - 1; i >= 0; i--) {
            ret.a[i] = (a[i] + down * (MAXN + 1)) / b;
            down = a[i] + down * (MAXN + 1) - ret.a[i] * b;
        }
        ret.len = len;
        while (ret.a[ret.len - 1] == 0 && ret.len > 1) ret.len--;
        return ret;
    }

    bool operator>(const Big &T) const {
        int ln;
        if (len > T.len) return true;
        else if (len == T.len) {
            ln = len - 1;
            while (a[ln] == T.a[ln] && ln >= 0) ln--;
            if (ln >= 0 && a[ln] > T.a[ln]) return true;
            else return false;
        } else return false;
    }

    Big operator+(const Big &T) const {
        Big t(*this);
        int big = T.len > len ? T.len : len;
        for (int i = 0; i < big; i++) {
            t.a[i] += T.a[i];
            if (t.a[i] > MAXN) {
                t.a[i + 1]++;
                t.a[i] -= MAXN + 1;
            }
        }
        if (t.a[big] != 0) t.len = big + 1;
        else t.len = big;
        return t;
    }

    Big operator-(const Big &T) const {
        int big;
        bool flag;
        Big t1, t2;
        if (*this > T) {
            t1 = *this;
            t2 = T;
            flag = 0;
        } else {
            t1 = T;
            t2 = *this;
            flag = 1;
        }
        big = t1.len;
        for (int i = 0; i < big; i++) {
            if (t1.a[i] < t2.a[i]) {
                int j = i + 1;
                while (t1.a[j] == 0) j++;
                t1.a[j--]--;
                while (j > i) t1.a[j--] += MAXN;
                t1.a[i] += MAXN + 1 - t2.a[i];
            } else t1.a[i] -= t2.a[i];
        }
        t1.len = big;
        while (t1.a[t1.len - 1] == 0 && t1.len > 1) {
            t1.len--;
            big--;
        }
        if (flag) t1.a[big - 1] = 0 - t1.a[big - 1];
        return t1;
    }

    LL operator%(const int &b) const {
        LL d = 0;
        for (int i = len - 1; i >= 0; i--) d = ((d * (MAXN + 1)) % b + a[i]) % b;
        return d;
    }

    Big operator*(const Big &T) const {
        Big ret;
        int i, j, up, temp, temp1;
        for (i = 0; i < len; i++) {
            up = 0;
            for (j = 0; j < T.len; j++) {
                temp = a[i] * T.a[j] + ret.a[i + j] + up;
                if (temp > MAXN) {
                    temp1 = temp - temp / (MAXN + 1) * (MAXN + 1);
                    up = temp / (MAXN + 1);
                    ret.a[i + j] = temp1;
                } else {
                    up = 0;
                    ret.a[i + j] = temp;
                }
            }
            if (up != 0) ret.a[i + j] = up;
        }
        ret.len = i + j;
        while (ret.a[ret.len - 1] == 0 && ret.len > 1) ret.len--;
        return ret;
    }

    void print() {
        printf("%d", a[len - 1]);
        for (int i = len - 2; i >= 0; i--) printf("%04d", a[i]);
    }
};

Big dp[2][105];

int main() {
       //FIN;
    while (~scanf("%d%d%d", &n, &m, &p)) {
        mp.clear();
        scanf("%s", buf);
        int len = strlen(buf);
        for (int i = 0; i < len; ++i) mp[buf[i]] = i;
        ac.init();
        for (int i = 0; i < p; ++i) {
            scanf("%s", buf);
            ac.insert(buf);
        }
        ac.build();
        Matrix mat = ac.get_Matrix();
//        for (int i = 0; i < mat.n; ++i) {
//            for (int j = 0; j < mat.n; ++j) {
//                printf("%d ",mat.mat[i][j]);
//            }
//            printf("\n");
//        }
        int now=0;
        dp[now][0] = 1;
        for (int i = 1; i < mat.n; ++i) dp[now][i] = 0;
        for (int i = 1; i <= m; ++i) {
            now^=1;
            for (int j = 0; j < mat.n; ++j) dp[now][j]=0;
            for (int j = 0; j < mat.n; ++j) {
                for (int k = 0; k < mat.n; ++k) {
                    if (mat.mat[j][k]) dp[now][k] = dp[now][k] + dp[now^1][j] * mat.mat[j][k];
                }
            }
        }
        Big ans = 0;
        for (int i = 0; i < mat.n; ++i) ans = ans + dp[now][i];
        ans.print();
        printf("\n");
    }
    return 0;
}
