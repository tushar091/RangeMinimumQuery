#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int getMid(int ss, int se) {
    return ss + (se - ss) / 2;
}

int getMin(int a, int b) {
    return a < b ? a : b;
}

int RMQUtil(int st[], int ss, int se, int qs, int qe, int index) {
    if (qs <= ss && qe >= se) {
        return st[index];
    }

    if (se < qs || ss > qe) {
        return INT_MAX;
    }
    int mid = getMid(ss, se);
    return getMin(RMQUtil(st, ss, mid, qs, qe, 2 * index + 1),
                  RMQUtil(st, mid + 1, se, qs, qe, 2 * index + 2));
}

int RMQ(int st[], int n, int qs, int qe) {
    return RMQUtil(st, 0, n - 1, qs, qe, 0);
}

int createSTUtil(int arr[], int st[], int ss, int se, int index) {
    if (se == ss) {
        st[index] = arr[se];
        return st[index];
    }
    int mid = getMid(ss, se);
    st[index] = getMin(createSTUtil(arr, st, ss, mid, 2 * index + 1),
                       createSTUtil(arr, st, mid + 1, se, 2 * index + 2));
    return st[index];
}


int *createST(int arr[], int n) {
    int a = (int) ceil(log2(n));
    int maxSize = 2 * (int) (pow(2, a)) - 1;
    int *st = (int *) malloc(maxSize * sizeof(int));
    createSTUtil(arr, st, 0, n - 1, 0);
    return st;
}

int updateST(int st[], int arr[], int ss, int se, int idx, int val, int index) {
    if (ss == se && se == idx) {
        arr[idx] = val;
        st[index] = val;
        return val;
    }
    int mid = getMid(ss, se);
    if (mid >= idx) {
        st[index] = getMin(updateST(st, arr, ss, mid, idx, val, 2 * index + 1), st[index]);
        return st[index];
    } else {
        st[index] = getMin(updateST(st, arr, mid + 1, se, idx, val, 2 * index + 2), st[index]);
        return st[index];
    }

}

int main() {
    int arr[] = {2, 45, 6, 7, 21, 54, 123, 545};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *st = createST(arr, n);
    for (int i = 0; i < 15; ++i) {
        printf("%d ", st[i]);
    }
    int result = RMQ(st, n, 1, 5);
    printf("\n%d\n", result);
    updateST(st,arr,0,n-1,2,1,0);
    for (int i = 0; i < 15; ++i) {
        printf("%d ", st[i]);
    }
    result = RMQ(st, n, 1, 5);
    printf("\n%d", result);
    updateST(st,arr,0,n-1,7,100,0);
    result = RMQ(st, n, 6, 7);
    printf("\n%d", result);
    return 0;
}
