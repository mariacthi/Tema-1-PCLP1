// Tudor Maria - Elena 311CA
#include <stdio.h>
#define NMAX 400

void read_matrix(int n, int a[][NMAX])
{
	// citeste matricea
	for (int i = 0; i < n * n; i++)
		for (int j = 0; j < n * n; j++)
			scanf("%d", &a[i][j]);
}

void op1(int n, int a[][NMAX], int linie[], int x)
{
	// rezolva operatia 1
	x--; // numerotarea liniilor incepe de la 0
	int vf[NMAX] = {0};
	for (int i = 0; i < n * n; i++)
		vf[a[x][i]]++;
		/* parcurge linia x si stocheaza intr-un vector de
		frecventa valorile matricei de pe linia respectiva */
	for (int i = 0; i < n * n; i++) {
		if (vf[i + 1] != 0)
			linie[i] = 0;
		else
			linie[i] = 1;
	}
}

void op2(int n, int a[][NMAX], int coloana[], int y)
{
	//rezolva operatia 2
	y--; // numerotarea coloanelor incepe de la 0
	int vf[NMAX] = {0};
	for (int i = 0; i < n * n; i++)
		vf[a[i][y]]++;
		/* parcurge coloana y si stocheaza intr-un vector de
		frecventa valorile matricei de pe coloana respectiva */
	for (int i = 0; i < n * n; i++) {
		if (vf[i + 1] != 0)
			coloana[i] = 0;
		else
			coloana[i] = 1;
	}
}

void op3(int n, int a[][NMAX], int careu[], int z)
{
	// rezolva operatia 3
	z--; // numerotarea careurilor incepe de la 0
	int vf[NMAX] = {0};
	int l1 = (z / n) * n ; // linia de unde incepe careul
	int c1 = (z % n) * n; // coloana de unde incepe careul
	for (int i = l1; i < l1 + n; i++)
		for (int j = c1; j < c1 + n; j++)
			vf[a[i][j]]++;
			/* parcurge careul z si stocheaza intr-un vector de
			frecventa valorile matricei din careul respectiv */
	for (int i = 0; i < n * n; i++) {
		if (vf[i + 1] != 0)
			careu[i] = 0;
		else
			careu[i] = 1;
	}
}

int det_careu(int x, int y, int n)
{
	// determina careul in care se afla celula de coordonate x si y
	x /= n;
	y /= n;
	if (x == 0)
		return y;
	else
		return x * n + y;
}

void op4(int n, int a[][NMAX], int v4[], int x, int y)
{
	// rezolva operatia 4
	x--;
	y--;
	if (a[x][y] != 0) {
		for (int i = 0; i <= n * n; i++)
			v4[i] = 0;
			/* daca exista deja o valoare in celula de coordonate x si y,
			elementele vectorului pentru afisare vor lua valoarea 0 */
	} else {
		int linie[10], coloana[10], careu[10];
		op1(n, a, linie, x + 1);
		op2(n, a, coloana, y + 1);
		int z = det_careu(x, y, n);
		op3(n, a, careu, z + 1);
		/* verifica ce valori exista deja pe linia, pe coloana
		si in careul celulei de coordonate x si y */
		for (int i = 0; i < n * n; i++) {
			if (linie[i] == 1 && coloana[i] == 1 && careu[i] == 1)
				v4[i] = 1;
			else
				v4[i] = 0;
		}
	}
}

void op5(int a[][NMAX], int x, int y, int c)
{
	// rezolva operatia 5
	x--;
	y--;
	if (a[x][y] == 0)
		a[x][y] = c;
		// daca celula de coordonate x si y este libera, va lua valoarea c
}

int verify_line(int n, int a[][NMAX], int x)
{
	// verifica daca pe linia x exista vreo valoare care se repeta
	int vf[NMAX] = {0};
	for (int i = 0; i < n * n; i++)
		vf[a[x][i]]++;
	for (int i = 0; i < n * n; i++) {
		if (vf[i + 1] > 1)
			return 1;
	}
	return 0;
}

int verify_column(int n, int a[][NMAX], int y)
{
	// verifica daca pe coloana y exista vreo valoare care se repeta
	int vf[NMAX] = {0};
	for (int i = 0; i < n * n; i++)
		vf[a[i][y]]++;
	for (int i = 0; i < n * n; i++) {
		if (vf[i + 1] > 1)
			return 1;
	}
	return 0;
}

int verify_careu(int n, int a[][NMAX], int z)
{
	// verifica daca in careul z exista vreo valoare care se repeta
	int vf[NMAX] = {0};
	int l1 = (z / n) * n ; //linia de unde incepe careul
	int c1 = (z % n) * n; //coloana de unde incepe careul
	for (int i = l1; i < l1 + n; i++) {
		for (int j = c1; j < c1 + n; j++)
			vf[a[i][j]]++;
	}
	for (int i = 0; i < n * n; i++)
		if (vf[i + 1] > 1)
			return 1;
	return 0;
}

int op6(int n, int a[][NMAX])
{
	// rezolva operatia 6
	/* verifica pe rand fiecare linie, coloana si careu, iar daca
	gaseste vreun element care se repeta, returneaza 1 */
	for (int i = 0; i < n * n; i++)
		if (verify_line(n, a, i) == 1)
			return 1;

	for (int i = 0; i < n * n; i++)
		if (verify_column(n, a, i) == 1)
			return 1;

	for (int i = 0; i < n * n; i++)
		if (verify_careu(n, a, i) == 1)
			return 1;

	int verif = 2;
	/* daca configuratia tablei este valida, verifica daca
	jocul a fost castigat sau inca se poate completa*/
	for (int i = 0; i < n * n; i++)
		for (int j = 0; j < n * n; j++)
			if (a[i][j] == 0)
				verif = 0;

	return verif;
}

int main(void)
{
	int n, m, a[NMAX][NMAX], nr_op;
	scanf("%d %d", &n, &m);
	read_matrix(n, a);
	int linie[NMAX], coloana[NMAX], careu[NMAX], v4[NMAX];
	int x, y, z, c, verif;
	for (int j = 0; j < m; j++) {
		scanf("%d", &nr_op);
		switch (nr_op) {
		case 1:
			scanf("%d", &x);
			op1(n, a, linie, x);
			for (int i = 0; i < n * n; i++)
				printf("%d ", linie[i]);
			printf("\n");
			break;
		case 2:
			scanf("%d", &y);
			op2(n, a, coloana, y);
			for (int i = 0; i < n * n; i++)
				printf("%d ", coloana[i]);
			printf("\n");
			break;
		case 3:
			scanf("%d", &z);
			op3(n, a, careu, z);
			for (int i = 0; i < n * n; i++)
				printf("%d ", careu[i]);
			printf("\n");
			break;
		case 4:
			scanf("%d %d", &x, &y);
			op4(n, a, v4, x, y);
			for (int i = 0; i < n * n; i++)
				printf("%d ", v4[i]);
			printf("\n");
			break;
		case 5:
			scanf("%d %d %d", &x, &y, &c);
			op5(a, x, y, c);
			break;
		case 6:
			verif = op6(n, a);
			printf("%d\n", verif);
			break;
		default:
			break;
		}
	}
	return 0;
}
