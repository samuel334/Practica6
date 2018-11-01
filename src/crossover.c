#include "crossover.h"
/*cruza de un punto*/
void singlePoint_crsvr(int c_lgth, int *ch, const int *p1, const int *p2, int cp){
	if(!(cp>0 && cp<c_lgth)) return;
	int i;
	for(i = 0;i<c_lgth;i++){
		if(i<cp){
			*(ch + i) = *(p1 + i);
		}else{
			*(ch + i) = *(p2 + i);
		}
	}
}
/*cruza de dos puntos*/
void twoPoint_crsvr(int c_lgth, int *ch, const int *p1, const int *p2, int cp1, int cp2){
	if(cp1==cp2 || cp1<=0 || cp1>=c_lgth || cp2<=0 || cp2>=c_lgth) return;
	int i;
	for(i = 0;i<c_lgth;i++){
		if(i<cp1 || i>=cp2){
			*(ch + i) = *(p1 + i);
		}else{
			*(ch + i) = *(p2 + i);
		}
	}
}
/*cruza uniforme*/
void uniform_crsvr(int c_lgth, int *ch, const int *p1, const int *p2, const int *mask){
	int i;
	for(i = 0;i<c_lgth;i++){
		if(*(mask + i)==1){
			*(ch + i) = *(p1 + i);
		}else{
			*(ch + i) = *(p2 + i);
		}
	}
}
/*cruza acentuada*/
void accentuated_crsvr(int c_lgth, int *ch, int *mask, const int *p1, const int *p2, const int *mask1, const int *mask2){
	int i;
	const int *temp;
	for(i = 0;i<c_lgth;i++){
		*(ch + i) = *(p1 + i);
		*(mask + i) = *(mask1 + i);
		if(*(mask1 + i)==1 || *(mask2 + i)==1){
			/*cambia el padre del cual hereda*/
			temp = p1;
			p1 = p2;
			p2 = temp;
			/*cambia los puntos de cruza a heredar*/
			temp = mask1;
			mask1 = mask2;
			mask2 = temp;
		}
	}
}
