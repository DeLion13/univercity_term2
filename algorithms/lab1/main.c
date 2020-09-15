#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <progbase.h>
#include <progbase/console.h>
#include <progbase/canvas.h>

void ins_sort(int n, int array[]);
void swap(int * a, int * b);
int randomInt(int min, int max);
void print(int d);

int main() {
    srand(time(NULL));

    int q = 0;
    int m = 0;
    int min = 0;
    int max = 0;

    printf("Input max: ");
    scanf("%d", &max);
    printf("and min(<max): ");
    scanf("%d", &min);
    printf("Input dimension (>3): ");
    scanf("%d", &m);

    int a[m][m];
    int m_cap = 0;
    if (m % 2 == 1) {
        m_cap = m - 1;
    } else {
        m_cap = m;
    }
    int main[m_cap];
    int back[m_cap];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = randomInt(min, max);
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j) {
                if (i != m / 2) {
                    main[q] = a[i][j];
                    back[q] = a[i][m - j - 1];
                    q++;
                } else {
                    if (m % 2 == 0) {
                        main[q] = a[i][j];
                        back[q] = a[i][m - j - 1];
                        q++;
                    }
                }

            }
        }
    }

    q = 0;

    printf("Non sorted:\n");

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j || i == m - j - 1) {
                Console_setCursorAttribute(FG_INTENSITY_BLUE);
                print(a[i][j]);
                Console_reset();
            } else {
                print(a[i][j]);
            }
        }
        printf("\n");
    }

    ins_sort(m_cap, main);
    ins_sort(m_cap, back);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j) {
                if (i != m / 2) {
                    a[i][j] = main[q];
                    a[i][m - j - 1] = back[q];
                    q++;
                } else {
                    if (m % 2 == 0) {
                        a[i][j] = main[q];
                        a[i][m - j - 1] = back[q];
                        q++;
                    }
                }

            }
        }
    }

    assert(a[0][0] <= a[1][1]);
    assert(a[m - 2][m - 2] <= a[m - 1][m - 1]);
    assert(a[0][m - 1] <= a[1][m - 2]);
    assert(a[m - 2][1] <= a[m - 1][0]);

    printf("Sorted:\n");

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j || i == m - j - 1) {
                Console_setCursorAttribute(FG_INTENSITY_BLUE);
                print(a[i][j]);
                Console_reset();
            } else {
                print(a[i][j]);
            }
        }
        printf("\n");
    }
    
    return 0;
}

void swap(int * a, int * b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void ins_sort(int n, int array[]) {
    for (int i = 0; i < n; i++) {
        int j = i;
        while(array[j] < array[j - 1] && j > 0) {
            swap(&array[j], &array[j - 1]);
            j--;
        }
    }
}

int randomInt(int min, int max) {
    int r = 0;
    r = rand() % (max - min + 1) + min;
    return r;
}

void print(int d) {
    printf("%3d ", d);
}