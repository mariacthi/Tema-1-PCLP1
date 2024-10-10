// Tudor Maria - Elena 311CA
#include <stdio.h>
#include <math.h>
#define N (unsigned long)(pow(2, 64) - 1)

int sum_array(int freq[26])
{
	// contorizeaza cate litere au fost citite in total
	int s = 0;
	for (int i = 0; i < 26; i++)
		s += freq[i];
	return s;
}

int verify(int freq[26])
{
	// verifica daca au fost citite cel putin doua litere diferite
	int contor = 0;
	for (int i = 0; i < 26; i++) {
		if (freq[i] != 0)
			contor++;
		if (contor > 1)
			return 1;
	}
	return 0;
}

int cmmdc(int a, int b)
{
	// a > b
	// determina cel mai mare divizor comun al numerelor a si b
	if (a % b == 0)
		return b;
	int div = 1;
	for (int i = 1; i <= b / 2; i++)
		if (b % i == 0 && a % i == 0)
			div = i;
	return div;
}

void fractie_ireductibila(int a, int b)
{
	// a > b
	// transforma in fractie ireductibila raportul b / a
	int div = cmmdc(a, b);
	a /= div;
	b /= div;
	printf("%d/%d\n", b, a);
}

void top(int freq[26], int K)
{
	// afiseaza cele mai importante k litere
	int v[26];
	for (int i = 0; i < 26; i++)
		v[i] = freq[i];
	for (int i = 0; i < 25; i++) {
		for (int j = i + 1; j < 26; j++) {
			if (v[i] < v[j]) {
				int aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	/* copiaza vectorul de frecventa intr-un alt vector, pe care,
	dupa aceea, il sorteaza in ordine descrescatoare */
	int valori_folosite[26] = {0};
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < 26; j++) {
			if (v[i] == freq[j] && valori_folosite[j] == 0) {
				printf("%c", (char)(j + 97));
				valori_folosite[j] = 1;
				break;
				/* va afisa in ordine lexicografica literele care au acelasi
				numar de aparitii datorita vectorului valori_folosite
				care ia valoarea 1 pentru fiecare litera afisata */
			}
		}
		if (i != K - 1)
			printf(" ");
		else
			printf("\n");
	}
}

int alerta(int freq[])
{
	// verifica daca este nevoie sa afiseze vreo alerta
	int s = sum_array(freq);
	for (int i = 0; i < 26; i++) {
		if ((s % 2 == 0) && freq[i] >= (s / 2) && verify(freq) == 1) {
			printf("%c ", (char)(i + 'a'));
			fractie_ireductibila(s, freq[i]);
			return 1;
		} else if ((s % 2 == 1) && freq[i] > (s / 2) && verify(freq) == 1) {
			printf("%c ", (char)(i + 'a'));
			fractie_ireductibila(s, freq[i]);
			return 1;
		}
		/* cand numarul total de aparitii (s) este par, numarul de aparitii
		al unei litere pentru a declansa alerta trebuie sa fie cel putin egala
		cu jumatate din s, iar cand este impar, numarul de aparitii al unei
		litere, trebuie sa fie mai mare de jumatate */
	}
	return 0;
}

int main(void)
{
	int freq[26] = {0};
	char c;
	int contor = 0;
	for (unsigned long i = 0; i < N; i++) {
		scanf("%c", &c);
		if ((c >= 'A' && c <= 'Z') && c != 'Q' && c != 'T' && c != 'E')
			break;
		if (c >= 'a' && c <= 'z') {
			contor++;
			freq[c - 97]++;
			if (contor >= 5) {
				int a = alerta(freq);
				if (a == 1)
					contor = 0;
				/* alerta poate fi declansata la cel putin 5 litere
				primite de la momentul declansarii ultimei alerte
				(prima alerta dupa ce au fost primite macar 5 litere),
				acest aspect fiind monitorizat prin variabila contor */
			}
		}
		if (c == 'Q') {
			char L;
			scanf(" %c", &L);
			printf("%c %d\n", L, freq[L - 97]);
		}
		if (c == 'T') {
			int K;
			scanf(" %d", &K);
			top(freq, K);
		}
		if (c == 'E') {
			char L;
			scanf(" %c", &L);
			freq[L - 97] = 0;
		}
	}
	return 0;
}
