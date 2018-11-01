#include "crossover.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

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

/*generar poblacion inicial*/
void generatePopulation(int p_lgth, int c_lgth, int population[p_lgth][c_lgth], int crsvrTpl[p_lgth][c_lgth]){
	int i, j, gen, p;
	for(i = 0;i<p_lgth;i++){
		/*generar cromosoma*/
		for(j = 0;j<c_lgth;j++){
			gen = (rand() % (1 - 0 + 1)) + 0;	//valor de gen generado aleatoriamente
			population[i][j] = gen;	//fijar valor de gen de individuo i
		}
		/*generar plantilla de cruza*/
		p = (rand() % ((int)(c_lgth*0.45) - 1 + 1)) + 1;
		for(j = 0;j<p;j++) crsvrTpl[i][j] = 1;
		for(j = p;j<c_lgth;j++) crsvrTpl[i][j] = 0;
		shuffle(c_lgth, crsvrTpl[i]);
	}
}

/*rellena tabla con padres, plantilla de cruza y descendencia*/
int toString(char *table, int c_lgth, const int p1[c_lgth], const int p2[c_lgth], const int ch1[c_lgth], const int ch2[c_lgth], 
	const int p1_tpl[c_lgth], const int p2_tpl[c_lgth], const int ch1_tpl[c_lgth], const int ch2_tpl[c_lgth]){
	int i, lgth = 0;
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", p1[i]);	//primer padre
	lgth += sprintf((table + lgth), ":");
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", p1_tpl[i]);	//plantilla de cruza de primer padre
	lgth += sprintf((table + lgth), "\t|\t");
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", ch1[i]);	//primer hijo
	lgth += sprintf((table + lgth), ":");
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", ch1_tpl[i]);	//plantilla de cruza de primer hijo
	lgth += sprintf((table + lgth), "\n");
	
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", p2[i]); //segundo padre
	lgth += sprintf((table + lgth), ":");
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", p2_tpl[i]);	//plantilla de cruza de segundo padre
	lgth += sprintf((table + lgth), "\t|\t");
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", ch2[i]);	//segundo hijo
	lgth += sprintf((table + lgth), ":");
	for(i = 0;i<c_lgth;i++) lgth += sprintf((table + lgth), "%d", ch2_tpl[i]);	//plantilla de cruza de segundo hijo
	lgth += sprintf((table + lgth), "\n");
	return lgth;
}

/*cruzar poblacion*/
void breeding(char *table, int p_lgth, int c_lgth, int child[p_lgth][c_lgth], int ch_tpl[p_lgth][c_lgth], const int parent[p_lgth][c_lgth], const int p_tpl[p_lgth][c_lgth]){
	int i = 0, j, k;
	int template[c_lgth];
	int lgth = 0;
	while(i<p_lgth){
		accentuated_crsvr(c_lgth, child[i], ch_tpl[i], parent[i], parent[i + 1], p_tpl[i], p_tpl[i + 1]);	//generar primer hijo
		accentuated_crsvr(c_lgth, child[i + 1], ch_tpl[i + 1], parent[i + 1], parent[i], p_tpl[i + 1], p_tpl[i]);	//invertir roles de padres y generar segundo hijo
		/*rellenar tabla con resultados*/
		lgth += toString((table + lgth), c_lgth, parent[i], parent[i + 1], child[i], child[i + 1], p_tpl[i], p_tpl[i + 1], ch_tpl[i], ch_tpl[i + 1]);
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
	int parent[p_lgth][c_lgth], p_tpl[p_lgth][c_lgth]; //padres y plantilla de cruza de padres
	int child[p_lgth][c_lgth], ch_tpl[p_lgth][c_lgth];	//hijos y plantilla de cruza de hijos
	char *table = malloc( sizeof(char)*((p_lgth*c_lgth*4) + ((2 + 2 + 1 + 1)*p_lgth) + 2) );	//tabla con resultados
	table[0] = '\0';
	/*generar poblacion inicial*/
	generatePopulation(p_lgth, c_lgth, parent, p_tpl);
	/*cruzar*/
	breeding(table, p_lgth, c_lgth, child, ch_tpl, parent, p_tpl);
	/*imprimir resultado en pantalla*/
	printf("%s\n", table);
	free(table);
	return 1;
}
