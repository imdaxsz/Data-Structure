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


// ����Ž��Ʈ�� �����Լ�
void insertNode(TreeNode **root, element x)
{
	TreeNode *n; // �� ���
	TreeNode *p = *root; // ������ ����� �θ� ��带 �����ϱ� ���� ������ ����
	TreeNode *q = NULL; // ������ ��带 ã�� ���� ������ ����


	// ��带 ������ ��ġ Ž��
	while (p != NULL) {
		if (x.num == p->key.num) {
			printf("%d %s �̹� ���� ������ �����մϴ�.\n", x.num, x.name);
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
	// ��� ����
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


// ����Ž��Ʈ�� �����Լ�
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
		printf("ã���ô� �л��� �����ϴ�.\n");
		return;
	}

	// ������ ��尡 �ܸ� ����� ���
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

	// ������ ��尡 �� ���� �ڽ� ��带 ���� ���
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

	// ������ ��尡 �� ���� �ڽ� ��带 ���� ���
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


// ����Ž��Ʈ�� �˻� �Լ�
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


// ���� �ҷ�����
void load_file(TreeNode **root, element x) { 
	FILE *fp;

	if ((fp = fopen("student.txt", "r")) == NULL) {
		fprintf(stderr, "���� �ҷ����� ����");
		exit(1);
	}

	printf("\n*****************************\n");
	printf(" ���Ϸκ��� �ҷ��� �л� ����\n");
	while (fscanf(fp, "%d", &x.num) != EOF) {
		printf("\n\t%d ", x.num);
		fscanf(fp, "%s", x.name);
		printf(" %s", x.name);
		insertNode(root, x);
	}
	printf("\n\n*****************************\n");
	fclose(fp);
}

// ������ȸ�� �̿��� �������� ���
void inorder(TreeNode *root, FILE *fp) { 
	if (root) {
		inorder(root->left, fp);
		fprintf(fp, "%d ", root->key.num);
		fprintf(fp, "%s\n", root->key.name);
		inorder(root->right, fp);
	}
}

// �������� ����
void save_inorder(TreeNode *root) {
	FILE *fp;
	if ((fp = fopen("student.txt", "w")) == NULL) {
		fprintf(stderr, "���� ���� ����");
		exit(1);
	}
	inorder(root, fp);
	printf("\n������ �Ϸ�Ǿ����ϴ�.\n\n");
	fclose(fp);
}

// ȭ�鿡 �������� ���
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
	element e = { "," }; // �ʱ�ȭ
	TreeNode* root = NULL;// ���� root ��� NULL ������ �ʱ�ȭ
	TreeNode* foundedNode = NULL;// Ž���� �ʿ��� Node , NULL ������ �ʱ�ȭ

	// ����
	load_file(&root, e); // ���� �ҷ�����

	printf("\n-----�л� ������ �߰��մϴ�.-----\n\n");
	printf("\t �й� : ");// �����Լ� ȣ��
	scanf("%d", &e.num);
	printf("\t �̸� : ");
	scanf("%s", e.name);
	insertNode(&root, e);
	printf("\n");
	save_inorder(root);

	// ���� �˻�
	printf("\n\n-----�л� ������ �˻��մϴ�.-----\n\n");
	printf("\t�й� : ");
	scanf("%d", &e.num);
	foundedNode = SearchTree(root, e);	// �˻��� ����� foundedNode�� �־���
	if (foundedNode != NULL) {
		printf("\n\t [�˻��Ϸ�]\n");
		printf("\t �й� : %d\n", foundedNode->key.num);
		printf("\t �̸� : %s\n", foundedNode->key.name);
	}
	else
		printf("\n\t ������ ã�� ���߽��ϴ�.\n");

	// �������� ����
	printf("\n\n---------�������� ����---------\n\n");
	save_inorder(root);
	displayinorder(root);
	printf("\n������������ ���ĵǾ����ϴ�.\n\n");

	// ����
	printf("\n������ �л��� �й��� �Է��ϼ��� : ");
	scanf("%d", &e.num);
	deleteNode(&root, e);
	printf("\n\t [�����Ϸ�]\n\n");
	displayinorder(root);
	save_inorder(root);
	
}