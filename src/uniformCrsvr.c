#include "crossover.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

void generatePopulation(int p_lgth, int c_lgth, int population[p_lgth][c_lgth]){
	int i, j, gen;
	for(i = 0;i<p_lgth;i++){
		for(j = 0;j<c_lgth;j++){
			gen = (rand() % (1 - 0 + 1)) + 0;	//valor de gen generado aleatoriamente
			population[i][j] = gen;	//fijar valor de gen de individuo i
		}
	}
}

/*rellena tabla con padres, plantilla de cruza y descendencia*/
int toString(char *table, int c_lgth, int template[c_lgth], const int p1[c_lgth], const int p2[c_lgth], const int ch1[c_lgth], const int ch2[c_lgth]){
	int i, lgth = 0;
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", p1[i]);	//primer padre
	lgth += sprintf((table + lgth), "\t|\t");
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", template[i]);	//puntos de cruza
	lgth += sprintf((table + lgth), "\t|\t");
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", ch1[i]);	//primer hijo
	lgth += sprintf((table + lgth), "\n");
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", p2[i]); //segundo padre
	lgth += sprintf((table + lgth), "\t|\t");
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), " ", template[i]);	//puntos de cruza
	lgth += sprintf((table + lgth), "\t|\t");
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", ch2[i]);	//segundo hijo
	lgth += sprintf((table + lgth), "\n");
	return lgth;
}

/*algoritmo de barajeo Fisher–Yates*/
void shuffle(unsigned int size, int array[size]){
	int i, temp, r;
	for(i = 0;i<(size - 1);i++){
		r = rand()%(size - i);
		temp = array[size - 1 - i];
		array[size - 1 - i] = array[r];
		array[r] = temp;
	}
}

/*genera plantilla de cruza con valores binarios, donde p se utiliza para 
calcular el numero de 1's y 0's*/
void generateCrsvrTemplate(int size, int template[size], int p){
	int i;
	p = (p*size)/100;
	for(i = 0;i<p;i++) template[i] = 1;
	for(i = p;i<size;i++) template[i] = 0;
	shuffle(size, template);
}

/*cruzar poblacion*/
void breeding(char *table, int p_lgth, int c_lgth, int child[p_lgth][c_lgth], const int parent[p_lgth][c_lgth]){
	int i = 0, j;
	int template[c_lgth];
	int lgth = 0;
	generateCrsvrTemplate(c_lgth, template, 60);	//generar plantilla de cruza, el 60 porciento de bits seran 1
	while(i<p_lgth){
		uniform_crsvr(c_lgth, child[i], parent[i], parent[i + 1], template);	//generar primer hijo
		uniform_crsvr(c_lgth, child[i + 1], parent[i + 1], parent[i], template);	//invertir roles de padres y generar segundo hijo
		/*rellenar tabla con resultados*/
		lgth += toString((table + lgth), c_lgth, template, parent[i], parent[i + 1], child[i], child[i + 1]);
		shuffle(c_lgth, template);	//barajear plantilla de cruza para generar nueva plantilla
		i += 2;
	}
	strcat(table, "\0");
}

int main(int argc, char *argv[]){
	if(argc!=3) exit(1);
	int p_lgth = atoi(argv[1]); //numero de individuos por generacion
	int c_lgth = atoi(argv[2]);	//tamaño de la cadena binaria
	if(p_lgth<0 || p_lgth%2 || c_lgth<3) exit(1);
	srand(time(NULL));
	int parent[p_lgth][c_lgth], child[p_lgth][c_lgth];	//padres y descendencia
	char *table = malloc( sizeof(char)*((p_lgth*c_lgth*2) + ((4 + 2 + 1)*p_lgth) + (c_lgth*(int)(p_lgth/2)) + 2) );	//tabla con resultados
	table[0] = '\0';
	/*generar poblacion inicial*/
	generatePopulation(p_lgth, c_lgth, parent);
	/*cruzar*/
	breeding(table, p_lgth, c_lgth, child, parent);
	/*imprimir resultado en pantalla*/
	printf("%s\n", table);
	free(table);
	return 1;
}
