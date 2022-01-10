#include "sortingmethods.h"

void SortingMethods::bubbleSort(int *l, int *r)
{
    int size = r - l;
    if (size <= 1) return;
    bool b = true;
    while (b) {
        b = false;
        for (int *i = l; i + 1 < r; i++) {
            if (*i > *(i + 1)) {
                std::swap(*i, *(i + 1));
                b = true;
            }
        }
        r--;
    }
}

void SortingMethods::shakerSort(int *l, int *r)
{
    int size = r - l;
    if (size <= 1) return;
    bool b = true;
    int *beg = l - 1;
    int *end = r - 1;
    while (b) {
        b = false;
        beg++;
        for (int *i = beg; i < end; i++) {
            if (*i > *(i + 1)) {
                std::swap(*i, *(i + 1));
                b = true;
            }
        }
        if (!b) break;
        end--;
        for (int *i = end; i > beg; i--) {
            if (*i < *(i - 1)) {
                std::swap(*i, *(i - 1));
                b = true;
            }
        }
    }
}

void SortingMethods::combSort(int *l, int *r)
{
    int size = r - l;
    if (size <= 1) return;
    double k = 1.2473309;
    int step = size - 1;
    while (step > 1) {
        for (int *i = l; i + step < r; i++) {
            if (*i > *(i + step))
                std::swap(*i, *(i + step));
        }
        step /= k;
    }
    bool b = true;
    while (b) {
        b = false;
        for (int *i = l; i + 1 < r; i++) {
            if (*i > *(i + 1)) {
                std::swap(*i, *(i + 1));
                b = true;
            }
        }
    }
}

void SortingMethods::insertionSort(int *l, int *r)
{
    for (int *i = l + 1; i < r; i++) {
            int *j = i;
            while (j > l && *(j - 1) > *j) {
                std::swap(*(j - 1), *j);
                j--;
            }
    }
}

void SortingMethods::shellsort(int *l, int *r)
{
    int size = r - l;
    int step = size / 2;
    while (step >= 1) {
        for (int *i = l + step; i < r; i++) {
            int *j = i;
            int *diff = j - step;
            while (diff >= l && *diff > *j) {
                std::swap(*diff, *j);
                j = diff;
                diff = j - step;
            }
        }
        step /= 2;
    }
}

void SortingMethods::treeSort(int *l, int *r)
{
    std::multiset<int> tree;
    for (int *i = l; i <= r; i++)
        tree.insert(*i);
    for (int q : tree)
        *l = q, l++;
}

void SortingMethods::gnomeSort(int *l, int *r)
{
    int *i = l;
    while (i < r) {
        if (i == l || *(i - 1) <= *i) i++;
        else std::swap(*(i - 1), *i), i--;
    }
}

void SortingMethods::selectionSort(int *l, int *r)
{
    for (int *i = l; i < r; i++) {
        int min = *i, *ind = i;
        for (int *j = i + 1; j < r; j++) {
            if (*j < min) min = *j, ind = j;
        }
        std::swap(*i, *ind);
    }
}

/* For the "heapSort" method */
template<typename T>
class SortingMethods::heap {
private:
    QVector <T> h;
    int n = 0;
    void SiftUp(int a) {
        while (a) {
            int p = (a - 1) / 2;
            if (h[p] > h[a]) std::swap(h[p], h[a]);
            else break;
            a--; a /= 2;
        }
    }
    void SiftDown(int a) {
            while (2 * a + 1 < n) {
                int l = 2 * a + 1, r = 2 * a + 2;
                if (r == n) {
                    if (h[l] < h[a]) std::swap(h[l], h[a]);
                    break;
                }
                else if (h[l] <= h[r]) {
                    if (h[l] < h[a]) {
                        std::swap(h[l], h[a]);
                        a = l;
                    }
                    else break;
                }
                else if (h[r] < h[a]) {
                    std::swap(h[r], h[a]);
                    a = r;
                }
                else break;
            }
        }
public:
    int size() {
        return n;
    }
    int top() {
        return h[0];
    }
    bool empty() {
        return n == 0;
    }
    void push(T a) {
        h.push_back(a);
        SiftUp(n);
        n++;
    }
    void pop() {
        n--;
        std::swap(h[n], h[0]);
        h.pop_back();
        SiftDown(0);
    }
    void clear() {
        h.clear();
        n = 0;
    }
    T operator [] (int a) {
        return h[a];
    }
};

void SortingMethods::heapsort(int *l, int *r)
{
    heap<int> h;
    for (int *i = l; i < r; i++) h.push(*i);
    for (int *i = l; i < r; i++) {
        *i = h.top();
        h.pop();
    }
}

void SortingMethods::quickSort(int *l, int *r)
{
    if (r - l <= 1) return;
        int z = *(l + (r - l) / 2);
        int* ll = l, *rr = r - 1;
        while (ll <= rr) {
            while (*ll < z) ll++;
            while (*rr > z) rr--;
            if (ll <= rr) {
                std::swap(*ll, *rr);
                ll++;
                rr--;
            }
        }
        if (l < rr) quickSort(l, rr + 1);
        if (ll < r) quickSort(ll, r);
}

/* For the "mergeSort" method */
void SortingMethods::merge(int *l, int *m, int *r, int *temp)
{
    int *cl = l, *cr = m, cur = 0;
        while (cl < m && cr < r) {
            if (*cl < *cr) temp[cur++] = *cl, cl++;
            else temp[cur++] = *cr, cr++;
        }
        while (cl < m) temp[cur++] = *cl, cl++;
        while (cr < r) temp[cur++] = *cr, cr++;
        cur = 0;
        for (int* i = l; i < r; i++)
             *i = temp[cur++];
}

/* For the "mergeSort" method */
void SortingMethods::_mergeSort(int *l, int *r, int *temp)
{
    if (r - l <= 1) return;
    int *m = l + (r - l) / 2;
    _mergeSort(l, m, temp);
    _mergeSort(m, r, temp);
    merge(l, m, r, temp);
}

void SortingMethods::mergeSort(int *l, int *r)
{
    int *temp = new int[r - l];
    _mergeSort(l, r, temp);
    delete []temp;
}

/* For the "bucketSort" method */
void SortingMethods::_newBucketSort(int *l, int *r, int *temp) {
    if (r - l <= 64) {
        insertionSort(l, r);
        return;
    }
    int minz = *l, maxz = *l;
    bool is_sorted = true;
    for (int *i = l + 1; i < r; i++) {
        minz = std::min(minz, *i);
        maxz = std::max(maxz, *i);
        if (*i < *(i - 1)) is_sorted = false;
    }
    if (is_sorted) return;
    int diff = maxz - minz + 1;
    int numbuckets;
    if (r - l <= 1e7) numbuckets = 1500;
    else numbuckets = 3000;
    int range = (diff + numbuckets - 1) / numbuckets;
    int *cnt = new int[numbuckets + 1];
    for (int i = 0; i <= numbuckets; i++)
        cnt[i] = 0;
    int cur = 0;
    for (int* i = l; i < r; i++) {
        temp[cur++] = *i;
        int ind = (*i - minz) / range;
        cnt[ind + 1]++;
    }
    int sz = 0;
    for (int i = 1; i <= numbuckets; i++)
        if (cnt[i]) sz++;
    int *run = new int[sz];
    cur = 0;
    for (int i = 1; i <= numbuckets; i++)
        if (cnt[i]) run[cur++] = i - 1;
    for (int i = 1; i <= numbuckets; i++)
        cnt[i] += cnt[i - 1];
    cur = 0;
    for (int *i = l; i < r; i++) {
        int ind = (temp[cur] - minz) / range;
        *(l + cnt[ind]) = temp[cur];
        cur++;
        cnt[ind]++;
    }
    for (int i = 0; i < sz; i++) {
        int r = run[i];
        if (r != 0) _newBucketSort(l + cnt[r - 1], l + cnt[r], temp);
        else _newBucketSort(l, l + cnt[r], temp);
    }
    delete []run;
    delete []cnt;
}

void SortingMethods::bucketSort(int *l, int *r)
{
    int *temp = new int[r - l];
    _newBucketSort(l, r, temp);
    delete[] temp;
}

/* For the "_LSDSort" & "_MSDSort" methods */
int SortingMethods::digit(int n, int k, int N, int M) {
    return (n >> (N * k) & (M - 1));
}

/* For the "LSDSort" method */
void SortingMethods::_LSDSort(int *l, int *r, int N) {
    int k = (32 + N - 1) / N;
        int M = 1 << N;
        int sz = r - l;
        int *b = new int[sz];
        int *c = new int[M];
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < M; j++)
                c[j] = 0;
            for (int* j = l; j < r; j++)
                c[digit(*j, i, N, M)]++;
            for (int j = 1; j < M; j++)
                c[j] += c[j - 1];
            for (int *j = r - 1; j >= l; j--)
                b[--c[digit(*j, i, N, M)]] = *j;
            int cur = 0;
            for (int *j = l; j < r; j++)
                *j = b[cur++];
        }
        delete[] b;
        delete[] c;
}

void SortingMethods::LSDSort(int *l, int *r)
{
    _LSDSort(l, r, 8);
}

/* For the "MSDSort" method */
void SortingMethods::_MSDSort(int *l, int *r, int N, int d, int *temp) {
    if (d == -1) return;
    if (r - l <= 32) {
        insertionSort(l, r);
        return;
    }
    int M = 1 << N;
    int *cnt = new int[M + 1];
    for (int i = 0; i <= M; i++)
        cnt[i] = 0;
    int cur = 0;
    for (int *i = l; i < r; i++) {
        temp[cur++] = *i;
        cnt[digit(*i, d, N, M) + 1]++;
    }
    int sz = 0;
    for (int i = 1; i <= M; i++)
        if (cnt[i]) sz++;
    int *run = new int[sz];
    cur = 0;
    for (int i = 1; i <= M; i++)
        if (cnt[i]) run[cur++] = i - 1;
    for (int i = 1; i <= M; i++)
        cnt[i] += cnt[i - 1];
    cur = 0;
    for (int *i = l; i < r; i++) {
        int ind = digit(temp[cur], d, N, M);
        *(l + cnt[ind]) = temp[cur];
        cur++;
        cnt[ind]++;
    }
    for (int i = 0; i < sz; i++) {
        int r = run[i];
        if (r != 0) _MSDSort(l + cnt[r - 1], l + cnt[r], N, d - 1, temp);
        else _MSDSort(l, l + cnt[r], N, d - 1, temp);
    }
    delete[] run;
    delete[] cnt;
}

void SortingMethods::MSDSort(int *l, int *r)
{
    int* temp = new int[r - l];
    _MSDSort(l, r, 8, 3, temp);
    delete[] temp;
}

/* For the "bitonicSort" method */
void SortingMethods::bitseqsort(int *l, int *r, bool inv) {
    if (r - l <= 1) return;
    int *m = l + (r - l) / 2;
    for (int *i = l, *j = m; i < m && j < r; i++, j++) {
        if (inv ^ (*i > *j)) std::swap(*i, *j);
    }
    bitseqsort(l, m, inv);
    bitseqsort(m, r, inv);
}

/* For the "bitonicSort" method */
void SortingMethods::makebitonic(int *l, int *r) {
    if (r - l <= 1) return;
    int *m = l + (r - l) / 2;
    makebitonic(l, m);
    bitseqsort(l, m, 0);
    makebitonic(m, r);
    bitseqsort(m, r, 1);
}

void SortingMethods::bitonicSort(int *l, int *r)
{
    int n = 1;
        int inf = *std::max(l, r) + 1;
        while (n < r - l) n *= 2;
        int *a = new int[n];
        int cur = 0;
        for (int *i = l; i < r; i++)
            a[cur++] = *i;
        while (cur < n) a[cur++] = inf;
        makebitonic(a, a + n);
        bitseqsort(a, a + n, 0);
        cur = 0;
        for (int *i = l; i < r; i++)
            *i = a[cur++];
        delete[] a;
}

/* For the "timSort" method */
void SortingMethods::_timSort(int *l, int *r, int *temp)
{
    int sz = r - l;
        if (sz <= 64) {
            insertionSort(l, r);
            return;
        }
        int minrun = sz, f = 0;
        while (minrun >= 64) {
            f |= minrun & 1;
            minrun >>= 1;
        }
        minrun += f;
        int* cur = l;
        QStack<QPair<int, int*>> s;
        while (cur < r) {
            int* c1 = cur;
            while (c1 < r - 1 && *c1 <= *(c1 + 1)) c1++;
            int* c2 = cur;
            while (c2 < r - 1 && *c2 >= *(c2 + 1)) c2++;
            if (c1 >= c2) {
                c1 = std::max(c1, cur + minrun - 1);
                c1 = std::min(c1, r - 1);
                insertionSort(cur, c1 + 1);
                s.push({ c1 - cur + 1, cur });
                cur = c1 + 1;
            }
            else {
                c2 = std::max(c2, cur + minrun - 1);
                c2 = std::min(c2, r - 1);
                std::reverse(cur, c2 + 1);
                insertionSort(cur, c2 + 1);
                s.push({ c2 - cur + 1, cur });
                cur = c2 + 1;
            }
            while (s.size() >= 3) {
                QPair<int, int*> x = s.top();
                s.pop();
                QPair<int, int*> y = s.top();
                s.pop();
                QPair<int, int*> z = s.top();
                s.pop();
                if (z.first >= x.first + y.first && y.first >= x.first) {
                    s.push(z);
                    s.push(y);
                    s.push(x);
                    break;
                }
                else if (z.first >= x.first + y.first) {
                    merge(y.second, x.second, x.second + x.first, temp);
                    s.push(z);
                    s.push({ x.first + y.first, y.second });
                }
                else {
                    merge(z.second, y.second, y.second + y.first, temp);
                    s.push({ z.first + y.first, z.second });
                    s.push(x);
                }
            }
        }
        while (s.size() != 1) {
                QPair<int, int*> x = s.top();
                s.pop();
                QPair<int, int*> y = s.top();
                s.pop();
                if (x.second < y.second) swap(x, y);
                merge(y.second, x.second, x.second + x.first, temp);
                s.push({ y.first + x.first, y.second });
        }
}

void SortingMethods::timsort(int *l, int *r)
{
    int *temp = new int[r - l];
    _timSort(l, r, temp);
    delete []temp;
}
