#define NUM_CELLS 64   //колличество клеток доски

struct Vertex {
	int state; //состояние: посещена или непосещена
	int weight; //вес вершины (метка)
	int flag; //проверена или непроверена для текущей вершины
};

void init_matrix(int (*)[NUM_CELLS]); //инициализация графа
void init_mass_ver(struct Vertex *, int); //инициализация массива вершин с указанием начальной вершины
int is_connect(int, int); //соединяются ли две клетки
int U_is_empty(struct Vertex *); //является ли пустым множество U
int find_min_vertex(struct Vertex *); //найти среди непосещенных вершин вершину с минимальной меткой
int G_is_empty(struct Vertex *, int, int (*)[NUM_CELLS]); //является ли пустым м-во G всех непос-х соседей текущей вершины
int find_neighbor(struct Vertex *, int, int (*)[NUM_CELLS]); //найти соседа для указанной вершины
void reset_flags(struct Vertex *, int, int (*)[NUM_CELLS]); //сбросить флаги в нуль для всех соседей указанной вершины
