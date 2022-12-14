#include <stdio.h>
#include <math.h>

long double F(long double x)
{
    return logl(x) - x + 1.8;
}

long double f(long double x)
{
    return F(x) + x;
}

long double fa(long double x)
{
    return 1/x;
}

long double absD(long double x)
{
    return x > 0 ? x : x * -1;
}

long double fEps(long double x)
{
    long double eps = 1.0;
    for (; (x + (eps / 2)) > x; eps /= 2.0);
    return eps;
}

void line()
{
    for (int i = 0; i < 118; ++i)
    {
        printf("-");
    }
    printf("\n");
}

int main() {

    if (absD(fa(2)) >= 1 && absD(fa(3)) >= 1)
    {
        printf("Function error");
        return 1;
    }

    long double current = (2 + 3) / 2, next  = f(current), eps = fEps(next);
    int iter = 0;

    printf("\nThe equation: ln(x)-x+1.8=0; a = 2; b = 3\n\n");
    line();

    printf("|X^(k-1)                                     |X^k                                         |");
    printf("X^k - X^(k-1)       |Iter |\n");
    line();


    while (absD(next - current) >= eps)
    {
        current = next;
        next = f(current);
        iter++;
        eps = fEps(next);

        printf("|%2.41LF |%2.41LF |%1.17LF |%4d |\n", current, next, next - current, iter);
    }

    line();

    printf("My result: %2.52LF | X: 2.8459 | Iterations: %3d\n", next, iter);


    return 0;
}
