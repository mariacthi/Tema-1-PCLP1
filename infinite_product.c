// Tudor Maria - Elena 311CA
#include <math.h>
#include <stdio.h>

double sqrt(double x);

unsigned long power_8(int x)
{
	// returneaza numarul reprezentat de 8 la puterea x
	if (x == 0)
		return 1;
	return 8 * power_8(x - 1);
}

unsigned long schimba_baza(unsigned long a)
{
	// returneaza valoarea in baza 10 a numarului a citit in baza 8
	int i = 0;
	unsigned long a_schimbat = 0;
	while (a != 0) {
		a_schimbat += (a % 10) * power_8(i);
		i++;
		a = a / 10;
	}
	return a_schimbat;
}

int main(void)
{
	unsigned long N, i;
	long long a_max = -1, b_max = -1, a_primulmax = -1, b_primulmax = -1, a, b;
	/* a_primulmax este primul maxim din primul vector,
	iar a_max este al doilea maxim din primul vector
	(analog b_primulmax si b_max pentru al doilea vector) */
	unsigned long long ps = 0;
	// cu ps este notat produsul scalar
	double n_a = 0, n_b = 0;
	/* cu n_a si n_b sunt notate normele primului vector,
	respectiv celui de-al doilea vector */
	scanf("%lu", &N);
	for (i = 1; i <= N; i++) {
		scanf("%lld%lld", &a, &b);
		a = schimba_baza(a);
		b = schimba_baza(b);
		ps = ps + a * b;
		if (a > a_primulmax) {
			a_max = a_primulmax;
			a_primulmax = a;
		} else if (a > a_max && a != a_primulmax) {
			a_max = a;
		}
		if (b > b_primulmax) {
			b_max = b_primulmax;
			b_primulmax = b;
		} else if (b > b_max && b != b_primulmax) {
			b_primulmax = b;
		}
		n_a = n_a + a * a;
		n_b = n_b + b * b;
	}
	printf("%llu\n", ps);
	printf("%lld %lld\n", a_max, b_max);
	n_a = sqrt(n_a);
	printf("%.7lf ", n_a);
	n_b = sqrt(n_b);
	printf("%.7lf\n", n_b);
	return 0;
}
