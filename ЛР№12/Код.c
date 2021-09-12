#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <string.h> 
#include <locale.h> 
#include <stdlib.h>
int global_node_count = 0;
#define N 256
typedef struct Node//структура дерева
{
	char word[N];
	int count;
	struct Node *left, *right, *parent;
	struct Node *next, *prev;
} Node;

typedef struct DblList//двусвязный список
{
	unsigned int size;
	Node *head, *tail;
} DList;



Node* getFreeNode(char *word, Node *parent) //создание узла дерева
{

	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->left = tmp->right = NULL;
	strcpy(tmp->word, word);
	tmp->parent = parent;
	tmp->count = 1;
	return tmp;
}
void addelem(Node **root, char *word) //добавление узла дерева
{

	Node *tmp = NULL;
	//если дерево пустое, то создаем новое 
	if (*root == NULL) {
		*root = getFreeNode(word, NULL);
		return;
	}
	tmp = *root;
	while (tmp) {
		//если добавляемое слово больше tmp->word
		if (strcmp(word, tmp->word) > 0) {
			//если есть правый узел, идем вправо
			if (tmp->right) {
				tmp = tmp->right;
				continue;
			}
			//если нет, то добавляем вправо
			else {
				tmp->right = getFreeNode(word, tmp);
				return;
			}
		}
		//если добавляемое слово меньше tmp->word
		else if (strcmp(word, tmp->word) < 0) {
			//если есть левый узел, идем влево
			if (tmp->left) {
				tmp = tmp->left;
				continue;
			}
			//если его нет, то добавляем влево
			else {
				tmp->left = getFreeNode(word, tmp);
				return;
			}
		}
		//если такое слово уже было, то увеличиваем счетчик кол-ва
		else if (strcmp(word, tmp->word) == 0) {
			tmp->count++;
			return;
		}
	}
}
void search_count(Node * ptr)//функция для вызова функции ниже для каждого из поддеревьев
{
	if (!ptr)
		return;
	global_node_count++;
	search_count(ptr->left);
	search_count(ptr->right);
}


void search(Node * root)//функция для нахождения количества узлов в поддереве
{
	int res;
	if (!root)
	{
		printf("Tree is empty!\n");
		return;
	}
	search_count(root->left);
	res = global_node_count;
	global_node_count = 0;
	search_count(root->right);
	if (res > global_node_count)
	{
		printf("Left tree is bigger\n");
	}
	else
	{
		if (res < global_node_count)
		{

			printf("Right tree is bigger\n");
		}
		else
		{
			printf("Right and left are equal\n");
		}
	}
	return;
}

void printTree1(Node *root)//прямой обход дерева
{
	if (!root)
	{
		return;
	}
	printf("%s(%d)\n", root->word, root->count);
	printTree1(root->left);
	printTree1(root->right);
}



void printTree2(Node *root)//симметричный обход дерева
{
	if (!root)
		return;
	printTree2(root->left);
	printf("%s(%d)\n", root->word, root->count);
	printTree2(root->right);
}



void printTree3(Node *root)//обратный обход дерева
{
	if (!root)
	{
		return;
	}
	printTree3(root->left);
	printTree3(root->right);
	printf("%s(%d)\n", root->word, root->count);
}
DList* createList()//создание двусвязного списка
{
	DList *tmp = (DList*)malloc(sizeof(DList));
	tmp->size = 0;
	tmp->head = NULL;
	tmp->tail = NULL;
	return tmp;
}

void pushBack(DList *list, Node *push)//добавление элемента в конец двусвязного списка
{

	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->parent = push->parent;
	tmp->right = push->right;
	tmp->left = push->left;
	tmp->count = push->count;
	strcpy(tmp->word, push->word);
	tmp->next = NULL;
	tmp->prev = list->tail;

	if (list->tail)
	{
		list->tail->next = tmp;
	}

	list->tail = tmp;
	list->size++;

	if (!list->head)
	{
		list->head = tmp;
	}
}
void pushfront(DList *list, Node *push)//добавление элемента в начало двусвязного списка
{
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->parent = push->parent;
	tmp->right = push->right;
	tmp->left = push->left;
	tmp->count = push->count;
	strcpy(tmp->word, push->word);
	tmp->prev = NULL;
	tmp->next = list->head;

	if (list->head)
	{
		list->head->prev = tmp;
	}

	list->head = tmp;
	list->size++;

	if (!list->head)
	{
		list->head = tmp;
	}
}

Node* popFront(DList *list) //вынимаем первый элемент из двусвязного списка
{

	Node *tmp;
	if (list->head == NULL)
	{
		return NULL;
	}

	tmp = list->head;
	list->head = list->head->next;
	if (list->head)
	{
		list->head->prev = NULL;
	}
	if (tmp == list->tail) {
		list->tail = NULL;
	}
	list->size--;
	return tmp;
}



void deleteList(DList **list) //удаление двусвязного списка
{

	Node  *next;
	Node *tmp = (*list)->head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}



void printTree4(Node *root) //обход в ширину
{
	DList *list = createList(); //создание двусвязного списка
	pushBack(list, root); //помещаем в очередь корень

	while (list->size != 0)
	{
		Node *tmp = (Node*)popFront(list);
		if (tmp) {
			printf("%s(%d)\n", tmp->word, tmp->count);
			if (tmp->left) 	//если есть левый наследник, то помещаем в очередь его
			{
				pushBack(list, tmp->left);
			}
			if (tmp->right) //если есть правый наследник, то помещаем в очередь его
			{
				pushBack(list, tmp->right);
			}
		}
	}
	deleteList(&list);
}

void printTreeA(Node *root)//обход в глубиу другим способом
{
	DList *list = createList(); //создание двусвязного списка
	pushfront(list, root); //помещаем в очередь корень

	while (list->size != 0)
	{
		Node *tmp = (Node*)popFront(list);
		if (tmp) 
		{

			printf("%s(%d)\n", tmp->word, tmp->count);
			if (tmp->right) //если есть правый наследник, то помещаем в очередь его
			{
				pushfront(list, tmp->right);
			}
			if (tmp->left)//если есть левый наследник, то помещаем в очередь его
			{
				pushfront(list, tmp->left);
			}
		}
	}
	deleteList(&list);
}


void check(char *s) //проверка слова на корректную длину
{

	if ((s != NULL)&&(strlen(s) > 20))
	{
		printf("A word must be less than 20 letters %s\n", s);
		exit(1);
	}
}

void deletet(Node **root)//удаление дерева
{
	if (*root) {
		deletet(&((*root)->left));
		deletet(&((*root)->right));
		free(*root);
	}
}



int main()
{
	//объявление всех нужных переменных
	Node *root = NULL;
	FILE *f;
	char str[N];
	char *istr, *sep = " ";
	if ((f = fopen("tree.txt", "rt+")) == NULL)//открытие файла 
	{
		printf("File can't be opened!\n");
		exit(0);
	}
	fgets(str, N, f);
	fclose(f);//закрытие файла 
	istr = strtok(str, sep);//делим полученный из файла текст на слова
	check(istr);
	while (istr != NULL) 
	{
		addelem(&root, istr);
		istr = strtok(NULL, sep);
		check(istr);
	}
	search(root);//вызов функции для выполнения задания
	printf("\nTree in a straight order\n");//вывод дерева в прямом порядке
	printTree1(root);
	printf("\nTree in a straight order2\n");//вывод дерева в прямом порядке другим способом
	printTreeA(root);
	printf("\nTree in a symmetrical order\n");//вывод дерева симметрично
	printTree2(root);
	printf("\nTree backwards\n");//вывод дерева в обратном порядке
	printTree3(root);
	printf("\nTree in width\n");//вывод дерева в ширину
	printTree4(root);
	deletet(&root);//очистка дерева
	return 0;
}
