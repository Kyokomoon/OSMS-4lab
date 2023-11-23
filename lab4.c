#include <stdio.h>
#include <math.h>
#define N 5
#include <stdlib.h>


//сдвиг Х регистров
void reg_x(int *register_x){
	int tmp =  (register_x[2] + register_x[3]) % 2; //сумматор по модулую 2
    //Сдвиг массива
    for(int i = 0; i < N; i++){
        register_x[N-i-1] =  register_x[N-i-2];
    }
    register_x[0] = tmp; //присваиваем первому элементу суммиованное ранее значение

}
//сдвиг Y регистров
void reg_y(int *register_y){
	int tmp = (register_y[1] + register_y[2]) % 2; //сумматор по модулую 2
    //Сдвиг массива
    for(int i = 0; i < N; i++){
        register_y[N-i-1] =  register_y[N-i-2];
    }
    register_y[0] = tmp; //присваиваем первому элементу суммиованное ранее значение
}


//Получение последовательности голда
void GoldSeq(int *register_x, int *register_y, int *seq, int len_pos){
    for (int i = 0; i < len_pos; i++) {
        seq[i] = (register_x[4] + register_y[4]) % 2; //сумматор по модулю 2
        reg_x(register_x); //сдвиг регистров
        reg_y(register_y); //сдвиг регистров
    }
}

//сдвиг последовательности циклично
void shiftseQ(int *shiftSeq ,int len_pos){
    int tmp, i;
    tmp = shiftSeq[len_pos-1]; //сохранение последнего элемента
	for(i = 0;i< len_pos;i++){
        shiftSeq[len_pos-i-1] =  shiftSeq[len_pos-i-2]; //сдвиг эементов массива
    }
    shiftSeq[0] = tmp; //присваиваем первому элементу ранее сохраненное значение
}
//расчет автокорреляции
void autocorr(int *seq, int *shiftSeq, float *cor, int len_pos){
    float res = 0;
    for (int i = 0; i < len_pos; i++) {
	//считаем количество совпадений
        if (seq[i] == shiftSeq[i]){ 
            res += 1.0;
        } else{
            res -= 1.0;
        }
    }
    *cor = res;//возвращаем значения
}
//Взаимная корреляция
void crosscorr(int *seq, int *seq2, float *cor, int len_pos) {
    float res = 0.0;
    for (int i = 0; i < len_pos; i++) {
        res += seq[i] * seq2[i];
    }
    *cor=res;
}
//Выввод таблицы с информацией
void print_shift_table(int shift, int *shiftSeq, int *seq, int len_pos){
    int i,j;
    float cor;
	//Выводим первую строку таблицы
    printf("\nSdvig");
    for(i = 1; i <= len_pos; i++){
        printf("|%2d", i);
    }
    printf("|Corelation|");
	//выводим все вариации сдвига последовательности
    for(i = 0; i <= shift; i++){
        //printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	/*printf("\n");
	for(j=0;j< 174; j++){
		printf("\E(0q\E(B");
	}*/
	printf("\n");
	printf("| %2d ", i);
	//выводим значения взаимной корреляции
        for(j=0; j < len_pos; j++){
            	printf("|%2d", shiftSeq[j]);
        }
	autocorr(seq, shiftSeq, &cor, len_pos);
	printf("|%5.1f     |", cor/len_pos);
	//циклический сдвиг последовательности
	shiftseQ(shiftSeq, len_pos);
    }
    printf("\n--------------------------------------------------------------------------------------------------------------\n");
}
int main(){
    int i = 0;
    int len_pos = pow(2,N) - 1; //длина последовательности
    	//динамическое выделение памяти
	int *seq = (int*)malloc(len_pos*sizeof(int)); //Массив для хранения первой последовательности
	int *seq2 = (int*)malloc(len_pos*sizeof(int)); //Массив для хранения второй последовательности
    	int *shiftSeq  = (int*)malloc(len_pos*sizeof(int)); //Массив для храниения сдвига первой последовательности
    
	//Массивы  регистров 
	//(x = 11, y = 11+7=18)
    int register_x[N] = {0, 1, 0, 1, 1};
    int register_y[N] = {1, 0, 0, 1, 0};
    //(x = 12, y = 13)
    int register_x1[N] = {0, 1, 1, 0, 0};
    int register_y1[N] = {0, 1, 1, 0, 1};
    
	// Генерируем первую последовательность голда и выводим
    printf("\nFirst Gold's sequence :\n");
    GoldSeq(register_x, register_y, seq, len_pos);
	//копируем 1 последовательность в массив для сдвигов
	for(i = 0; i < len_pos; i++){
        	shiftSeq[i]=seq[i];
    	}

    for (i = 0; i < len_pos; i++) {
        printf("%d", seq[i]);
    }
    printf("\n\n");
	//выводим таблицу с сдвигами
    print_shift_table(len_pos, shiftSeq, seq, len_pos);

	//Генерируем вторую последовательность
    printf("\nSecond Gold's sequence :\n");
    GoldSeq(register_x1, register_y1, seq2, len_pos);
     for (i = 0; i < len_pos; i++) {
        printf("%d", seq2[i]);
    }
    printf("\n\n");
    float cor;
	//Взаимная корреляция первой и второй последовательнсти
	crosscorr(seq, seq2, &cor, len_pos);
	//printf("\nКорреляция между начальной и новосформированнной последовательностью >> %.0f\n", cor);
    printf("\nCorrelation between begin and new sequnce's >> %.0f\n", cor);
}
