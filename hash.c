#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 0;
int m;

void insert_key(int key, int ht[]) {
	for (int n = 0; n < m; n++) {
		if (ht[(key + n) % m] == key) {
			//printf("중복된 키 값 입니다.\n");
			return;
		}
		if (ht[(key + n) % m] == 0) {
			ht[(key + n) % m] = key;
			return;
		}
		else
			count++;
	}
}

int main()
{
	int *ht;
	int key;

	srand(time(NULL));

	m = 13;

	ht = (int*)malloc(sizeof(int) * m);
	for (int i = 0; i < m; i++)
		ht[i] = 0;

	for (int i = 0; i < m; i++) {
		key = (rand() % 100) + 1;
		insert_key(key, ht);
		printf("%d번째 숫자 : %d\n", i + 1, key);
	}

	for (int k = 0; k < m; k++) {
		printf("ht[%d] : %d\n", k, ht[k]);
	}

	free(ht);

	printf("\n%d일 때 충돌 횟수 : %d\n", m, count);
	printf("---------------------------------------\n");

	for (m = 63; m < 1000; m = m + 50) {
		ht = (int*)malloc(sizeof(int) * m);
		for (int i = 0; i < m; i++)
			ht[i] = 0;

		for (int i = 0; i < m; i++) {
			key = rand() % 1200 + 1;
			insert_key(key, ht);
		}
		free(ht);

		printf("%d일 때 충돌 횟수 : %d\n", m, count);
		count = 0;
	}

	m = 999;

	ht = (int*)malloc(sizeof(int) * m);
	for (int i = 0; i < m; i++)
		ht[i] = 0;

	for (int i = 0; i < m; i++) {
		key = rand() % 1200 + 1;
		insert_key(key, ht);
	}
	free(ht);

	printf("%d일 때 충돌 횟수 : %d\n", m, count);
}