#include <stdio.h>
#include <math.h>

long double F1(long double x)
{
    return logl(x) - x + 1.8;
}

long double F2(long double x)
{
    return x * tanl(x) - ((long double) 1.0) / 3.0;
}

long double f1a(long double x)
{
    return 1/x;
}

long double f2a(long double x)
{
    return tanl(x) + x / (cosl(x) * cosl(x));
}

long double f(long double (*F) (long double x),long double x)
{
    return F(x) + x;
}

long double absD(long double x)
{
    return x > 0 ? x : x * -1;
}

long double maxD(long double a, long double b)
{
    return a > b ? a : b;
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
}

void iter(long double (*fa) (long double x), long double (*F) (long double x), float start, float finish)
{
    if (absD(fa(start)) >= 1 || absD(fa(finish)) >= 1)
    {
        printf("Function error\n");
        return;
    }

    long double current = (2 + 3) / 2, next  = f(F, current), eps = fEps(next);
    int iter = 0;


    while (absD(next - current) >= eps)
    {
        current = next;
        next = f(F, current);
        iter++;
        eps = fEps(next);
    }

    printf("My result = %2.52LF | Iterations = %3d\n", next, iter);
}

void dichotomies(long double (*F) (long double x), long double a, long double b)
{
    long double eps = fEps(maxD(a, b));
    int iter = 0;

    while (absD(a - b) > eps)
    {
        if (F(a) * F((a + b) / 2) > 0)
            a = (a + b) / 2;
        else
            b = (a + b) / 2;

        iter++;
        eps = fEps(maxD(a, b));
    }

    printf("My result = %2.52LF | Iterations = %3d\n", (a + b) / 2, iter);

}

int main() {

    printf("\nThe equation: ln(x)-x+1.8=0; a = 2; b = 3; x ~= 2.8459\n");
    printf("Iteration method:    ");
    iter(&f1a, &F1, 2, 3);
    printf("Dichotomies method:  ");
    dichotomies(&F1, 2, 3);

    line();

    printf("\nThe equation: x*tg(x)-1/3=0; a = 0.2; b = 1; x ~= 0.5472\n");
    printf("Iteration method:    ");
    iter(&f2a, &F2, 0.2, 1);
    printf("Dichotomies method:  ");
    dichotomies(&F2, 0.2, 1);


    return 0;
}
