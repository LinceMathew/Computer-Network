
#include <stdio.h>
int top = -1;
int ps[9999];
int d[9999];
void push(int n)
{
    ps[++top] = n;
}
int pop()
{
    int i, j, k;
    for (i = 0; i <= top; i++)
    {
        for (j = i + 1; j <= top; j++)
        {
            if (d[ps[i]] < d[ps[j]])
            {
                k = ps[i];
                ps[i] = ps[j];
                ps[j] = k;
            }
        }
    }
    top--;
    return ps[top + 1];
}
int main()
{
    int N, n, i, j;
    char v[3];
    printf("Enter no. of nodes :\n");
    scanf("%d", &n);
    int c[n][n], f[n];
    char s[n];
    printf("Enter -1 if router does not exist or enter cost\n");
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            printf("%c -- %c\n", i + 'A', j + 'A');
            scanf("%d", &c[i][j]);
            c[j][i] = c[i][j];
        }
        f[i] = 0;
        d[i] = 99999;
    }
    for (j = 0; j < n; j++)
    {
        for (i = 0; i < n; i++)
            d[i] = 99999;
        printf("Enter the node :\n");
        scanf("%s", v);
        N = v[0] - 'A';

        for (i = 0; i < n; i++)
        {
            if (i == N)
                s[i] = ' ';
            else if (c[N][i] == -1)
                s[i] = ' ';
            else
                s[i] = i + 'A';
        }
        d[N] = 0;
        push(N);

        while (1)
        {
            if (top == -1)
                break;
            N = pop();
            for (i = 0; i < n; i++)
            {
                if (N != i && c[N][i] > -1)
                {
                    if (d[N] + c[N][i] < d[i])
                    {
                        d[i] = d[N] + c[N][i];
                        if (s[i] - 'A' != i)
                            s[i] = s[N];
                        push(i);
                    }
                }
            }
        }
        printf("Table for %s :\n", v);
        for (i = 0; i < n; i++)
        {
            printf("%c %d ", i + 'A', d[i]);
            if (s[i] - 'A' != i)
                printf("%c", s[i]);
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}
