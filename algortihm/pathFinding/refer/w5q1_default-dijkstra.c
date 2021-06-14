#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 10
#define STACK_MAX SIZE*SIZE

#define WALL 1
#define ROAD 0
#define GOAL 2
#define TRACE 3

const int inf = SIZE*SIZE+1;

/*************************************************************
**************             heap block           **************
*************************************************************/


#define HEAP_MAX 1000

typedef struct{
	int element;
	int key;
}HeapNode;

void initHeapNode(HeapNode* h, int e, int k){
	h->element = e;
	h->key = k;
}

void swap_int(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void swap(HeapNode *a, HeapNode *b){
	swap_int(&a->element, &b->element);
	swap_int(&a->key, &b->key);
}

typedef struct {
	HeapNode h[HEAP_MAX];
	int size; // is the size of array (nodes = size-1)
}Heap;

int heap_isEmpty(Heap *heap){
	return heap->size <= 0;
}
void print_heap(Heap *h){
	if(heap_isEmpty(h)) return;
	printf("heap :  ");

	for(int i = 1; i != h->size; i++)
		printf("%d:%d ", h->h[i].element-1,h->h[i].key);
	printf("\n");
}


int heap_min(Heap *heap){
	return heap->h[1].key;
}
void minHeapify(Heap *heap, int i ){

	int l = 2*i;
	int r = 2*i + 1;
	int min = i;

	HeapNode *A = heap->h;

	if(l <= heap->size && A[l].key < A[r].key) min = l;
	if(r <= heap->size && A[r].key < A[min].key) min = r;

	if(min != i){
		swap(&A[i], &A[min]);
		minHeapify(heap,min);
	}
}


Heap *minHeap_build(int arr[SIZE], int n){
	Heap *tmp = (Heap*)malloc(sizeof(Heap));

	tmp->size = n+1;
	initHeapNode(&tmp->h[0], -1, -1);


	for(int i = 0; i != HEAP_MAX; i++) tmp->h[i].element = i;

	for(int i = (tmp->size-1)/2; i != 0; i--){
		minHeapify(tmp, i);
	}
	for(int i = 1; i != tmp->size; i++) tmp->h[i].key = arr[i-1];
	return tmp;
}

int minHeap_extractMin(Heap* heap){

	if(heap->size == 0) {
		printf("heap underflow, uncontroled error");
		return -1;
	}

	int min = heap->h[1].element;
	heap->size--;
	heap->h[1] = heap->h[heap->size];

	minHeapify(heap,1);
	return min;
}

/*
	Decraese key of a specific node in heap tree
	example:
		index is 5, and key value is 10
		decrease value from 10 to 3,
		and we should check move it or not.
		cause the min-heap tree might be change
*/
Heap* minHeap_decrease_key(Heap *heap, int element, int key){
	HeapNode *A = heap->h;

	int i = 0;
	for(int j = 1; j != heap->size; j++){
		if(heap->h[j].element == element) i = j;
	}
	if(key > A[i].key){
		printf("empty:%d i : %d key : %d  new key is bigger than current key\n",heap_isEmpty(heap),i, A[i].key);
		return NULL;
	}
	A[i].key = key;

	/* if parent node is bigger than current node*/
	while(i > 1 && A[i/2].key > A[i].key){
		swap(&A[i], &A[i/2]);
		i = i/2;
		/*move to parent node*/
	}
	return heap;
}
void minHeap_insert(Heap* heap, int key){
	heap->h[heap->size].key = key;
	minHeap_decrease_key(heap, heap->size, key);
	heap->size++;
}
/*************************************************************
**************             heap block           **************
*************************************************************/

typedef struct
{
	int row, col;
}Node;

typedef struct
{
	Node *data[SIZE * SIZE];
	int top;
}List;

int pos(int i , int j){
	return i*SIZE+j;
}

List* initList(){

    List *tmp = (List*)malloc(sizeof(List));

    tmp->top = -1;
    for(int i = 0; i != STACK_MAX; i++)
		tmp->data[i] = (Node*)malloc(sizeof(Node));

    return tmp;
}
/*
Insert an element from top
*/
void addElement(List *l, int r, int c)
{
	if(l->top == STACK_MAX)return;
	Node *tmp = l->data[++l->top];
	tmp->row = r;
	tmp->col = c;
}

/*
remove an element from top and return a pointer point to the element.
If list is empty, return NULL.
*/
Node *removeElement(List *l)
{
	if(l->top == -1) return NULL;
	Node *pop_out = l->data[l->top];

	l->top--;
	return pop_out;
}

void printPath(List *l)
{
	if(l == NULL)
		return;
	int j;
	for(j = 0;j < l->top+1;j ++)
	{
		printf("(%d, %d) ", l->data[j]->row, l->data[j]->col);
	}
}

void printMaze(int **m)
{
	int j, k;
	for(j = 0;j < SIZE;j ++)
	{
		for(k = 0;k < SIZE;k ++)
		{
			if(m[j][k] == ROAD)
				printf("  ");
			else if(m[j][k] == WALL)
				printf("O ");
			else if(m[j][k] == TRACE){
				printf(". ");
			}
		}
		printf("\n");
	}
	for(int i = 0; i != SIZE; i++) printf("--");
	printf("\n");
}


/*
function initMaze
Alocate a 2-D array with s * s sizes as the map of maze.
Inside the maze where 0 represent empty space and 1 represent wall.
[0][0] is start point and [s - 1][s - 1] is finish point.
Randomly generate 20% wall in the maze.
Make sure [0][0] and [s - 1][s - 1] are 0
*/
void initMaze(int ***m, int s)
{
	*m = (int**)calloc(s, sizeof(int*));
	int *array_start = (int*)calloc(s*s, sizeof(int));
	for(int i = 0; i != s; i++) (*m)[i] = array_start+ i*s;

	int default_grid[SIZE][SIZE] ={{0,0,0,0,1,1,0,1,1,1},
                                   {1,1,1,0,1,1,0,0,0,0},
                                   {1,1,0,0,0,0,0,1,1,0},
                                   {1,1,0,1,1,1,1,1,1,1},
                                   {0,0,0,0,0,0,0,0,0,0},
                                   {0,1,0,1,1,0,1,0,1,0},
                                   {0,1,0,0,1,0,1,0,1,1},
                                   {0,1,1,1,1,1,1,1,1,0},
                                   {0,0,0,0,0,0,0,0,0,0},
                                   {1,1,1,1,1,1,1,1,1,0}};
	for(int i = 0; i != SIZE; i++){
		for(int j = 0; j != SIZE; j++){
			(*m)[i][j] = default_grid[i][j];
		}
	}

	printMaze(*m);
}
/*************************************************************
**************           dijkstra block         **************
*************************************************************/

void print_line(int arr[STACK_MAX]){
	for(int i = 0; i != STACK_MAX; i++){
		printf("%d ", arr[i]);
	}printf("\n");
}

void print_line_to_2d(int arr[STACK_MAX]){
	for(int i = 0; i != STACK_MAX; i++){
		if(!(i%SIZE)) printf("\n");
		if(arr[i] == 101) printf("-- ");
		else printf("%.2d ", arr[i]);

	}printf("\n");
}
void relax(int distance[STACK_MAX], int predecessor[STACK_MAX],int from, int to, int weight){
	if(distance[from] == inf)return;
	if(distance[to] > weight + distance[from]){
		distance[to] = weight + distance[from];
		predecessor[to] = from;
	}
}

void dijkstra(int adj[STACK_MAX][STACK_MAX], int distance[STACK_MAX], int start){

	int predecessor[STACK_MAX];

	int visited[STACK_MAX];//bool

	for(int i = 0; i != STACK_MAX; i++){
		distance[i] = inf;
		predecessor[i] = -1;
		visited[i] = 0;
	}
	distance[start] = 0;//Start from 0
	//print_line(distance);

	Heap *minQueue = minHeap_build(distance,STACK_MAX);

	while(!heap_isEmpty(minQueue)){
		int u = minHeap_extractMin(minQueue)-1;

		for(int i = 0; i != STACK_MAX; i++){
			if(i == u) continue;
			if(visited[i]) continue;
			relax(distance, predecessor, u, i, adj[u][i]);
			minHeap_decrease_key(minQueue, i+1, distance[i]);
		}
		visited[u] = 1;
	}
}

/*************************************************************
**************           dijkstra block         **************
*************************************************************/

/*
function findPath
This function will find a path between start point and finish point.
Return a queue content the path information inside.
If there is no path between two point then the queue will be empty.
*/
List *findPath(int **m, int s)
{
	int adj[SIZE*SIZE][SIZE*SIZE];

	for(int i = 0; i != SIZE*SIZE; i++){
		for(int j = 0; j != SIZE*SIZE; j++){
			adj[i][j] = inf;
		}
	}
	for(int i = 0; i != SIZE; i++){
		for(int j = 0; j != SIZE; j++){
			if(m[i][j] == 0){
				adj[pos(i,j)][pos(i,j)] = 0;
				if(i != SIZE-1 && m[i+1][j] == 0)
					adj[pos(i+1,j)][pos(i,j)] = adj[pos(i,j)][pos(i+1,j)] = 1;
				if(j != SIZE-1 && m[i][j+1] == 0)
					adj[pos(i,j+1)][pos(i,j)] = adj[pos(i,j)][pos(i,j+1)] = 1;
			}
		}
	}//flatten

	int distance[STACK_MAX];
	dijkstra(adj, distance, pos(0,0));

	print_line_to_2d(distance);


	int goal_pos =pos(SIZE-1,SIZE-1);
	int goal_dis = distance[goal_pos];
	printf("goal_dis : %d\n\n", goal_dis);

	int i=SIZE-1,j =SIZE-1;
	List* shortest_path = initList();
	while(goal_dis-- >= -1){

		addElement(shortest_path, i, j);
		m[i][j] = TRACE;

		if(goal_dis == -1) break;
		if(j != SIZE-1 	&& (distance[pos(i,j+1)] == goal_dis)) j++;
		if(j != 0 		&& (distance[pos(i,j-1)] == goal_dis)) j--;
		if(i != SIZE-1 	&& (distance[pos(i+1,j)] == goal_dis)) i++;
		if(i != 0 		&& (distance[pos(i-1,j)] == goal_dis)) i--;
	}
	printMaze(m);
	return shortest_path;
	return NULL;
}



int main()
{
	int **maze;
	initMaze(&maze, SIZE);
	printPath(findPath(maze, SIZE));

	free(*maze);
	free(maze);
	return 0;
}
