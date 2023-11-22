#include <stdio.h>
#include <math.h>
#define N 5
#include <stdlib.h>

void reg_x(int *register_x){
	int tmp =  (register_x[2] + register_x[3]) % 2;
    for(int i = 0; i < N; i++){
        register_x[N-i-1] =  register_x[N-i-2];
    }
    register_x[0] = tmp;

}

void reg_y(int *register_y){
	int tmp = (register_y[1] + register_y[2]) % 2;
    for(int i = 0; i < N; i++){
        register_y[N-i-1] =  register_y[N-i-2];
    }
    register_y[0] = tmp;
}


void GoldSeq(int *register_x, int *register_y, int *seq, int len_pos){
    for (int i = 0; i < len_pos; i++) {
        seq[i] = (register_x[4] + register_y[4]) % 2;
        reg_x(register_x);
        reg_y(register_y);
    }
}

void shiftseQ(int *shiftSeq ,int len_pos){
    int tmp, i;
    tmp = shiftSeq[len_pos-1];
	for(i = 0;i< len_pos;i++){
        shiftSeq[len_pos-i-1] =  shiftSeq[len_pos-i-2];
    }
    shiftSeq[0] = tmp;
}
void autocorr(int *seq, int *shiftSeq, float *cor, int len_pos){
    float res = 0;
    for (int i = 0; i < len_pos; i++) {
        if (seq[i] == shiftSeq[i]){
            res += 1.0;
        } else{
            res -= 1.0;
        }
    }
    *cor = res;
}
void crosscorr(int *seq, int *seq2, float *cor, int len_pos) {
    float res = 0.0;
    for (int i = 0; i < len_pos; i++) {
        res += seq[i] * seq2[i];
    }
    *cor=res;
}
void print_shift_table(int shift, int *shiftSeq, int *seq, int len_pos){
    int i,j;
    float cor;
    printf("\nСдвиг");
    for(i = 1; i <= len_pos; i++){
        printf("|%2d", i);
    }
    printf("|корреляция|");
    for(i = 0; i <= shift; i++){
        //printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	/*printf("\n");
	for(j=0;j< 174; j++){
		printf("\E(0q\E(B");
	}*/
	printf("\n");
	printf("| %2d ", i);
        for(j=0; j < len_pos; j++){
            	printf("|%2d", shiftSeq[j]);
        }
	autocorr(seq, shiftSeq, &cor, len_pos);
	printf("|%5.1f     |", cor/len_pos);
	shiftseQ(shiftSeq, len_pos);
    }
    printf("\n--------------------------------------------------------------------------------------------------------------\n");
}
int main(){
    int i = 0;
    int len_pos = pow(2,N) - 1;
    int *seq = (int*)malloc(len_pos*sizeof(int));
	int *seq2 = (int*)malloc(len_pos*sizeof(int));
    int *shiftSeq  = (int*)malloc(len_pos*sizeof(int));;
    //(x = 11, y = 11+7=18)
    int register_x[N] = {0, 1, 0, 1, 1}; 
    int register_y[N] = {1, 0, 0, 1, 0};
    //(x = 12, y = 13)
    int register_x1[N] = {0, 1, 1, 0, 0};
    int register_y1[N] = {0, 1, 1, 0, 1};
    

    printf("\nFirst Gold's sequence :\n");
    GoldSeq(register_x, register_y, seq, len_pos);
	for(i = 0; i < len_pos; i++){
        shiftSeq[i]=seq[i];
    }

    for (i = 0; i < len_pos; i++) {
        printf("%d", seq[i]);
    }
    printf("\n\n");
	
    print_shift_table(len_pos, shiftSeq, seq, len_pos);

    printf("\nSecond Gold's sequence :\n");
    GoldSeq(register_x1, register_y1, seq2, len_pos);
     for (i = 0; i < len_pos; i++) {
        printf("%d", seq2[i]);
    }
    printf("\n\n");
    float cor;
	crosscorr(seq, seq2, &cor, len_pos);
	printf("\nКорреляция между начальной и новосформированнной последовательностью >> %.0f\n", cor);
}
