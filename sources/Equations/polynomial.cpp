#include "numbers.hpp"
#include "polynomial.hpp"

typedef long long int ll;
const ll MAXN = 4e5 + 51, G = 3;
const ll MOD1 = 469762049, MOD2 = 998244353, MOD3 = 1004535809;
const ll MOD = 468937312667959297;

#include<bits/stdc++.h>
using namespace std;

Polynomial::Polynomial(long long c[], int d)
{
    deg = d;
    coefficient = new long long [deg + 1];
    for (int i = 0; i <= deg; i++)
    {
        coefficient[i] = c[i];
    }
}

Polynomial::Polynomial(const Polynomial &b)
{
    deg = b.deg;
    coefficient = new long long [deg + 1];
    for (int i = 0; i <= deg; i++)
    {
        coefficient[i] = b[i];
    }
}

Polynomial Polynomial::operator+(const Polynomial&b)const
{
    int l = max(deg, b.deg);
    long long a[l];
    for (int i = 0; i <= min(deg, b.deg); i++)
        a[i] = coefficient[i] + b.coefficient[i];
    if (deg < l)
    {
        for (int i = deg + 1; i <= l; i++)
            a[i] = b.coefficient[i];
    }
    else
        for (int i = b.deg + 1; i <= l; i++)
            a[i] = b.coefficient[i];
    return Polynomial(a,l);
}

void NTT(long long *cp,long long cnt,long long inv,long long mod)
{
    long long lim = 0, cur = 0, res = 0, omg = 0;
    while ((1 << lim) < cnt)
    {
        lim++;
    }
    for (int i = 0; i < cnt; i++)
    {
        cur = 0;
        for (int j = 0; j < lim; j++)
        {
            if ((i >> j) & 1)
            {
                cur |= (1 << (lim - j - 1));
            }
        }
        if (i < cur)
        {
            std::swap(cp[i], cp[cur]);
        }
    }
    for (int i = 2; i <= cnt; i <<= 1)
    {
        cur = i >> 1, res = power(G, (mod - 1) / i, mod);
        for (long long * p = cp; p != cp + cnt; p += i)
        {
            omg = 1;
            for (int j = 0; j < cur; j++)
            {
                long long t = omg * p[j + cur] % mod;
                p[j + cur] = min_with_mod(p[j], t, mod);
                p[j] = add_with_mod(p[j], t, mod);
                omg = omg * res % mod;
            }
        }
    }
}

ll CRT(ll r1,ll r2,ll r3,ll mod)
{
    ll inv1 = 208783132, inv2 = 395249030;
    ll r = add_with_mod(mul_with_mod(mul_with_mod(min_with_mod(r1,r2,MOD1),inv1,MOD1),MOD2,MOD),r2,MOD);
    ll k = mul_with_mod(min_with_mod(r3,r,MOD3),inv2,MOD3);
    return ((k % mod) * (MOD % mod) % mod + r) % mod;
}

Polynomial mul_with_mod_po(Polynomial x, Polynomial y, ll mod)
{
    ll cnt = 1, inv;
    static ll cpx[MAXN], cpy[MAXN];
    memset(cpx,0,sizeof(cpx)), memset(cpy,0,sizeof(cpy));
    for (int i = 0; i <= x.deg; i++)
    {
        cpx[i] = x.coefficient[i];
    }
    for (int i = 0; i <= y.deg; i++)
    {
        cpy[i] = y.coefficient[i];
    }
    while (cnt <= x.deg + y.deg)
    {
        cnt<<=1;
    }
    NTT(cpx, cnt, 1, mod), NTT(cpy, cnt, 1, mod);
    for (int i = 0; i <= cnt; i++)
    {
        cpx[i] = cpx[i] * cpy[i] % mod;
    }
    NTT(cpx, cnt, -1, mod);
    int deg = x.deg + y.deg;
    inv = power(cnt, mod - 2, mod);
    cpx[0] = cpx[0] * inv % mod;
    for (int i = 1; i <= cnt >> 1; i++)
    {
        cpx[i] = cpx[i] * inv % mod;
        if (i != cnt - i)
        {
            cpx[cnt - i] = cpx[cnt - i] * inv % mod;
        }
        std::swap(cpx[i], cpx[cnt - i]);
    }
    ll coeff[deg + 1];
    for(int i = 0; i <= deg; i++)
    {
        coeff[i] = min_with_mod(cpx[i], 0, mod);
    }
    return Polynomial(coeff, deg);
}

Polynomial mul_with_armod(Polynomial x, Polynomial y, long long mod)
{
    for (int i = 0; i <= x.deg; i++)
    {
        x.coefficient[i] %= mod;
    }
    for (int i = 0; i <= y.deg; i++)
    {
        y.coefficient[i] %= mod;
    }
    Polynomial res1(mul_with_mod_po(x, y, MOD1));
    Polynomial res2(mul_with_mod_po(x, y, MOD2));
    Polynomial res3(mul_with_mod_po(x, y, MOD3));
    ll coeff[res1.deg + 1];
    for (int i = 0; i <= res1.deg; i++)
    {
        coeff[i] = CRT(res1.coefficient[i], res2.coefficient[i], res3.coefficient[i], mod);
    }
    return Polynomial(coeff, res1.deg);
}

Polynomial linear_re(Polynomial a, Polynomial b, int k, long long f[], long long P)
{
    Polynomial res(20);
    std::cout<<a[1]<<" "<<b[1]<<" "<<a[0]<<" "<<b[0]<<std::endl;
//    res.print();
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
        {
            (res[i + j] += 1ll * a[i] * b[j] % P) %= P;
//            res.print();
        }
    for (int i = 2 * k - 2; i >= k; res[i--] = 0)
        for (int j = 1; j <= k; j++)
        {
            (res[i - j] += 1ll * res[i] * f[j] % P) %= P;
//            res.print();
        }
//
    res.print();
    return res;
}

Polynomial ksm(Polynomial a, long long f[],int k, long long P, int b)
{
    Polynomial res(20);
    res.coefficient[0] = 1;
    for (; b; b >>= 1)
    {
        if (b & 1)
        {
//            a.print();
            res = linear_re(res, a, k, f, P);
        }
        printf("1\n");
        a = linear_re(a, a, k, f, P);
        a.print();
        std::cout<<2<<std::endl;
    }
    return res;
}

long long linear_res(int n, int k, long long f[], long long h[], long long P)
{
    for (int i = 1; i <= k; i++)
        f[i] = f[i] > 0 ? f[i] : f[i] + P;
    for (int i = 0; i < k; i++)
        h[i] = h[i] > 0 ? h[i] : h[i] + P;
    if (n < k)
    {
        return h[n];
    }
    Polynomial res(20);
    res[1] = 1;
    long long ans = 0;
    res = ksm(res, f, k, P, n);
    for (int i = 0; i < k; i++)
        ans = (ans + 1ll * res[i] * h[i] % P) % P;
    return ans;
}

/*
Polynomial Polynomial::inverse()
{

}
*/
