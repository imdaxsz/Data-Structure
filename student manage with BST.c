#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct element {
	int num;
	char name[20];
}element;

typedef struct TreeNode {
	element key;
	struct TreeNode *left, *right;
}TreeNode;


// 이진탐색트리 삽입함수
void insertNode(TreeNode **root, element x)
{
	TreeNode *n; // 새 노드
	TreeNode *p = *root; // 삽입할 노드의 부모 노드를 저장하기 위한 포인터 변수
	TreeNode *q = NULL; // 삽입할 노드를 찾기 위한 포인터 변수


	// 노드를 삽입할 위치 탐색
	while (p != NULL) {
		if (x.num == p->key.num) {
			printf("%d %s 이미 같은 정보가 존재합니다.\n", x.num, x.name);
			return;
		}
		q = p;
		if (x.num < p->key.num) {
			p = p->left;
		}
		else if (x.num > p->key.num) {
			p = p->right;
		}
	}
	// 노드 삽입
	n = (TreeNode*)malloc(sizeof(TreeNode));
	n->key = x;
	n->left = NULL;
	n->right = NULL;

	if (q != NULL) {
		if (x.num < q->key.num) {
			q->left = n;
		}
		else if (x.num > q->key.num) {
			q->right = n;
		}
	}
	else
		*root = n;
}


// 이진탐색트리 삭제함수
void deleteNode(TreeNode **root, element x) {
	TreeNode *parent = NULL;
	TreeNode *p = *root;
	TreeNode *child;
	TreeNode *succ, *succ_parent;

	while ((p != NULL) && (p->key.num != x.num)) {
		parent = p;
		if (x.num < p->key.num) {
			p = p->left;
		}
		else
			p = p->right;
	}

	if (p == NULL) {
		printf("찾으시는 학생이 없습니다.\n");
		return;
	}

	// 삭제할 노드가 단말 노드인 경우
	if ((p->left == NULL) && (p->right == NULL)) {
		if (parent != NULL) {
			if (parent->left == p)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else
			root = NULL;
	}

	// 삭제할 노드가 한 개의 자식 노드를 가진 경우
	else if ((p->left == NULL) || (p->right == NULL)) {
		if (p->left != NULL)
			child = p->left;
		else
			child = p->right;

		if (parent != NULL) {
			if (parent->left == p)
				parent->left = child;
			else
				parent->right = child;
		}
		else
			*root = child;
	}

	// 삭제할 노드가 두 개의 자식 노드를 가진 경우
	else {
		succ_parent = p;
		succ = p->right;
		while (succ->left != NULL) {
			succ_parent = succ;
			succ = succ->left;
		}
		if (succ_parent->left == succ)
			succ_parent->left = succ->right;
		else
			succ_parent->right = succ->right;
		p->key = succ->key;
		p = succ;
	}
	free(p);
}


// 이진탐색트리 검색 함수
TreeNode* SearchTree(TreeNode *root, element x) { 
	while (root != NULL) {
		if (x.num == root->key.num)
			return root;
		else if (x.num < root->key.num)
			root = root->left;
		else
			root = root->right;
	}
	return root;
}


// 파일 불러오기
void load_file(TreeNode **root, element x) { 
	FILE *fp;

	if ((fp = fopen("student.txt", "r")) == NULL) {
		fprintf(stderr, "파일 불러오기 실패");
		exit(1);
	}

	printf("\n*****************************\n");
	printf(" 파일로부터 불러온 학생 정보\n");
	while (fscanf(fp, "%d", &x.num) != EOF) {
		printf("\n\t%d ", x.num);
		fscanf(fp, "%s", x.name);
		printf(" %s", x.name);
		insertNode(root, x);
	}
	printf("\n\n*****************************\n");
	fclose(fp);
}

// 중위순회를 이용한 오름차순 출력
void inorder(TreeNode *root, FILE *fp) { 
	if (root) {
		inorder(root->left, fp);
		fprintf(fp, "%d ", root->key.num);
		fprintf(fp, "%s\n", root->key.name);
		inorder(root->right, fp);
	}
}

// 오름차순 저장
void save_inorder(TreeNode *root) {
	FILE *fp;
	if ((fp = fopen("student.txt", "w")) == NULL) {
		fprintf(stderr, "파일 열기 실패");
		exit(1);
	}
	inorder(root, fp);
	printf("\n저장이 완료되었습니다.\n\n");
	fclose(fp);
}

// 화면에 오름차순 출력
void displayinorder(TreeNode *root) { 
	if (root != NULL) {
		displayinorder(root->left);
		printf("\t%d %s\n",
			root->key.num, root->key.name);

		displayinorder(root->right);
	}
}


int main()
{
	element e = { "," }; // 초기화
	TreeNode* root = NULL;// 최초 root 노드 NULL 값으로 초기화
	TreeNode* foundedNode = NULL;// 탐색에 필요한 Node , NULL 값으로 초기화

	// 삽입
	load_file(&root, e); // 파일 불러오기

	printf("\n-----학생 정보를 추가합니다.-----\n\n");
	printf("\t 학번 : ");// 삽입함수 호출
	scanf("%d", &e.num);
	printf("\t 이름 : ");
	scanf("%s", e.name);
	insertNode(&root, e);
	printf("\n");
	save_inorder(root);

	// 정보 검색
	printf("\n\n-----학생 정보를 검색합니다.-----\n\n");
	printf("\t학번 : ");
	scanf("%d", &e.num);
	foundedNode = SearchTree(root, e);	// 검색한 결과를 foundedNode로 넣어줌
	if (foundedNode != NULL) {
		printf("\n\t [검색완료]\n");
		printf("\t 학번 : %d\n", foundedNode->key.num);
		printf("\t 이름 : %s\n", foundedNode->key.name);
	}
	else
		printf("\n\t 정보를 찾지 못했습니다.\n");

	// 오름차순 정렬
	printf("\n\n---------오름차순 정렬---------\n\n");
	save_inorder(root);
	displayinorder(root);
	printf("\n오름차순으로 정렬되었습니다.\n\n");

	// 삭제
	printf("\n삭제할 학생의 학번을 입력하세요 : ");
	scanf("%d", &e.num);
	deleteNode(&root, e);
	printf("\n\t [삭제완료]\n\n");
	displayinorder(root);
	save_inorder(root);
	
}