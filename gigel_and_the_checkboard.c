// Tudor Maria - Elena 311CA
#include <stdio.h>
#define NMAX 1000

void read_matrix(int n, int a[][NMAX])
{
	// citeste matricea
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
}

int abs(int a)
{
	// returneaza modulul lui a
	if (a >= 0)
		return a;
	return (-1) * a;
}

int move(int a, int n, int num)
{
	// realizeaza mutarea in functie de valoarea a scrisa pe tabla
	num += a % n;
	if (a > 0) {
		if (num >= n)
			num -= n;
	} else {
		if (num < 0)
			num += n;
	}
	return num;
}

void transform_in_letters(int col)
{
	/* transforma in litere numarul coloanei
	din matricea asociata tablei de sah */
	if (col < 26) {
		printf("%c", (char)(col + 'A'));
		/* daca numarul de coloane este mai mic decat 26,
		atunci este nevoie sa afisam o singura litera*/
	} else {
		int rest = col % 26;
		while (col != 0) {
			int litera = col / 26;
			if (litera != 0)
				printf("%c", (char)(litera - 1 + 'A'));
			col = col / 26;
		}
		/* daca numarul de coloane, este mai mare decat 26,
		se respecta reprezentarea din Microsoft Excel
		(A pentru a doua parcurgere a alfabetului,
		B pentru a treia etc., adica catul impartirii
		numarului de coloane la 26, minus 1) */
		printf("%c", (char)(rest + 'A'));
	}
}

int main(void)
{
	int n;
	scanf("%d", &n);
	int a[NMAX][NMAX];
	read_matrix(n, a);
	long dist = 0;
	int lin = 0, col = 0;
	while (a[lin][col] != 0) {
		dist += abs(a[lin][col]);
		/* distanta parcursa este reprezentata
		de modulul valorii scrise pe tabla */
		int copie = a[lin][col];
		if ((lin + col) % 2 == 0) {
			a[lin][col] = 0;
			// biletul poate fi folosit o singura data
			col = move(copie, n, col);
			/* cand suma liniei si coloanei in care ne aflam este un numar par,
			inseamna ca patratul este alb, deci ne vom misca pe linie*/
		} else {
			a[lin][col] = 0;
			lin = move(copie, n, lin);
			// patratul este negru, deci ne vom misca pe coloana
		}
	}
	printf("%ld\n", dist);
	lin = n - lin;
	/* numerele liniilor in tabla de sah sunt
	complementare liniilor matricei asociate */
	printf("%d ", lin);
	transform_in_letters(col);
	printf("\n");
	return 0;
}
