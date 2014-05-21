#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "horse.h"

void init_matrix(int (*matrix)[NUM_CELLS])
{
	int i, j;
	/* заполняем недиагональные элементы */
	for (i = 0; i < NUM_CELLS; i++)
		for (j = i + 1; j < NUM_CELLS; j++)
			if (is_connect(i, j) == 1){
				matrix[i][j] = 1;
				matrix[j][i] = 1;
			}
			else{
				matrix[i][j] = 0;
				matrix[j][i] = 0;
			}
	/* заполняем диагональ */
	for (i = 0; i < NUM_CELLS; i++)
		matrix[i][i] = 0;
}

int is_connect(int a, int b)
{
	int xa, ya, xb, yb; //координаты полей
	int l; //ширина доски
	l = (int)sqrt(NUM_CELLS);
	/* декодироване вершин графа в поля шахматной доски */
	xa = a % l;
	xb = b % l;
	ya = a / l;
	yb = b / l;
	if ((abs(xa-xb) == 1 && abs(ya-yb) == 2) || (abs(xa-xb) == 2 && abs(ya-yb) == 1))
		return 1; //поля соединяются
	else 
		return 0; //поля не соединяются
}

void init_mass_ver(struct Vertex *mass_ver, int start_vertex){
	int i;
	for (i = 0; i < NUM_CELLS; i++){
		mass_ver[i].weight = INT_MAX; //машинная бесконечность
		mass_ver[i].state = 0; //вершина не посещена по умолчанию
		mass_ver[i].flag = 0; //по умолчанию вершина не проверена 
	}
	mass_ver[start_vertex].weight = 0; //расстояние до начальной (стартовой) вершины равно 0
}

int U_is_empty(struct Vertex *mass_ver){
	int i;
	int flag = 1; //будем считать что множество U пустое
	for (i = 0; i < NUM_CELLS; i++){
		if (mass_ver[i].state == 0){
			flag = 0; //множество U не пустое
			break;		
		}
	}
	if (flag == 1) return 1;
	else return 0;
}


int find_min_vertex(struct Vertex *mass_ver){
	int i;
	int current_weight = INT_MAX; //текущая метка по умолчанию берется максимально большой, чтобы алгоритм работал
	int current_number = 0; //текущий номер вершины
	for (i = 0; i < NUM_CELLS; i++){
		if (mass_ver[i].state == 1) continue;
		else
			if (mass_ver[i].weight < current_weight){ 
				current_weight = mass_ver[i].weight;
				current_number = i;
			}
	}
	return current_number;
}

int G_is_empty(struct Vertex *mass_ver, int current_number, int (*matrix)[NUM_CELLS]){
	int j;
	int i = current_number;
	int flag = 1; //будем считать что множество G пустое (мы просмотрели всех непосещенных соседей)
	for (j = 0; j < NUM_CELLS; j++)
		if (matrix[i][j] == 1 && mass_ver[j].state == 0 && mass_ver[j].flag == 0){
				flag = 0; //множество G не пустое
				break;
		} 	
	if (flag == 1) return 1; //множество G пустое
	else return 0; //множество G не пустое
}

int find_neighbor(struct Vertex *mass_ver, int vertex_number, int (*matrix)[NUM_CELLS]){
	int j;
	for (j = 0; j < NUM_CELLS; j++)
		if (matrix[vertex_number][j] == 1 && mass_ver[j].state == 0 && mass_ver[j].flag == 0) return j;
}

void reset_flags(struct Vertex *mass_ver, int vertex_number, int (*matrix)[NUM_CELLS]){
	int j;
	for (j = 0; j < NUM_CELLS; j++)
		if(matrix[vertex_number][j] == 1) mass_ver[j].flag = 0;
}
