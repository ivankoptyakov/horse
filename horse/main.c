#include "horse.h"
#include <stdio.h>

int main()
{
	printf("GCC 4.4.3 (GNU C Compiler)\n");
	printf("+-----------------------------------------------------------------------------------------------------+\n");
	printf("|Программа находит минимальное расстояние коня от указанной клетки до остальных клеток шахматной доски|\n");
	printf("+-----------------------------------------------------------------------------------------------------+\n");
	printf("\nВведите координаты коня в шахматной нотации (например f5): ");
	char cell[3];
	scanf("%s", cell);
	cell[2] = '\0';
	int x, y;
	y = (int) cell[0] - 97;
	x = (int) cell[1] - 49;
	int start_cell = 8 * y + x;
	printf("\nВведите координаты конечного пункта (например h8): ");
	scanf("%s", cell);
	cell[2] = '\0';
	y = (int) cell[0] - 97;
	x = (int) cell[1] - 49;
	int end_cell = 8 * y + x;
	//вспомогательные переменные 
	int v = 0;
	int u = 0;
	int tmp = 0;

	struct Vertex mass_ver[NUM_CELLS];
	int matrix[NUM_CELLS][NUM_CELLS];
	init_matrix(matrix); //инициализация графа
	init_mass_ver(mass_ver, start_cell); //инициализация массива вершин
	while (!U_is_empty(mass_ver)){
		v = find_min_vertex(mass_ver);
		while (!G_is_empty(mass_ver, v, matrix)){
			u = find_neighbor(mass_ver, v, matrix);
			tmp = mass_ver[v].weight + 1;
			if (tmp < mass_ver[u].weight) mass_ver[u].weight = tmp;
			mass_ver[u].flag = 1; //вершина проверена
		}
		reset_flags(mass_ver, v, matrix); //сбрасываем флаги всех соседей вершины v в нуль
		mass_ver[v].state = 1; //вершина посещена
	}
	printf("\nколичество ходов коня = %i\n", mass_ver[end_cell].weight);
	
	return 0;
}
