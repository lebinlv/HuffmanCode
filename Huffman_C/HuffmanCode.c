#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 20		//最大可处理的带权值叶子节点数

//树节点定义
typedef struct TREE_Node
{
	int weight;
	struct TREE_Node *L_Child, *R_Child;
}treeNode;

//从数组weight[]中的length个权值建立哈夫曼树，返回树根指针
treeNode *Huffman_Create(int *weight, int n)
{
	//由权值生成左右子树均为NULL的森林
	treeNode **weightForest = NULL, *temp = NULL;
	weightForest = (treeNode**)malloc(n * sizeof (treeNode));
	for (int i = 0; i < n; i++)
	{
		weightForest[i] = (treeNode *)malloc(sizeof (treeNode));
		weightForest[i]->weight = weight[i];
		weightForest[i]->L_Child = weightForest[i]->R_Child = NULL;
	}        
	//进行length-1次循环生成哈夫曼树
	for (int i = 0; i < n-1; i++)
	{
		int min, j = 0,k1,k2;

		//找出权值最小的所在位置，即数组下标
		while (!weightForest[j])j++;
		min = weightForest[j]->weight;
		k1 = j;
		j++;
		for (; j < n; j++)
			if (weightForest[j] && weightForest[j]->weight < min)
			{
				min = weightForest[j]->weight;
				k1 = j;
			}
		temp = (treeNode*)malloc(sizeof (treeNode));
		temp->L_Child = weightForest[k1];//将最小的作为新节点的左子树
		weightForest[k1] = NULL;

		//找出权值次小的所在位置
		j = 0;
		while (!weightForest[j])j++;
		min = weightForest[j]->weight;
		k2 = j;
		j++;
		for (; j < n; j++)
			if (weightForest[j] && weightForest[j]->weight < min)
			{
				min = weightForest[j]->weight;
				k2 = j;
			}
		temp->R_Child = weightForest[k2];//将次小的作为新节点的右子树

		//计算新节点的权值
		temp->weight = temp->L_Child->weight + temp->R_Child->weight;
		weightForest[k2] = temp;//将新节点放到数组中以参与下次比较
	}
	free(weightForest);
	return temp;
}

//输出每个权值相对应的哈夫曼编码
void Huffman_Code(treeNode *root, char *code, int i)
{
	if (root->L_Child == NULL&&root->R_Child == NULL)
	{
		printf("\n权值为 %-3d的元素的哈夫曼编码为: ", root->weight);
		for (int j = 0; j < i; j++)printf("%c", code[j]);
	}
	else
	{
		code[i] = '1';
		Huffman_Code(root->L_Child, code, i + 1);
		code[i] = '0';
		Huffman_Code(root->R_Child, code, i + 1);
	}
}

int main()
{
	int weight[MAXNUM];
	int length = -1;
	//从键盘读入权值
	printf("Please input weight(input \"q\" to quit): ");
	while (scanf("%d", &weight[++length]));
	//建立哈夫曼树
	treeNode *Huffman_root = Huffman_Create(weight,length);
	//创建临时数组存储哈夫曼编码
	char code[MAXNUM] = { '0','0','0','0','0','0','0','0' };
	//输出哈夫曼编码
	Huffman_Code(Huffman_root, code, 0);
	printf("\n\n\n");
	system("pause");
    return 0;
}