#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX_TERMS 100

typedef struct {
	int row;
	int col;
	int value;
	int length;
}term;

term* sparse_matrix_mult(term *a, int a_r, int a_c, term *b, int b_r, int b_c){
	term *c = (term *)malloc(sizeof(term)*MAX_TERMS);
	if (a == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    int c_r = a_r;
    int c_c = b_c;
    
    int c_index=0;
    
    
    for(int i=0; i<c_r; i++){
    	for(int j=0; j<c_c; j++){         
    		int sum = 0;
			for(int n=0; n<a[0].length; n++){
    			for(int m=0; m<b[0].length; m++){
    				if((a[n].row == i)&&(b[m].col == j)&&(a[n].col == b[m].row)){
    					sum += a[n].value * b[m].value;
					}
				}
			}
			c[c_index].row = i; 
			c[c_index].col = j;
			c[c_index++].value = sum;
		}
	}
	c[0].length = c_index;
    
	return c;
}

int main(){
	//행렬 a
	term *a = (term *)malloc(sizeof(term)*MAX_TERMS);
	if (a == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
	
	int i=0;
	char a_out;
	int a_r = 0, a_c = 0;
	int b_r = 0, b_c = 0;
		
	printf("저장 멈춤 : value 뒤 '.'\n");
	
	printf("matrix a\n");
	printf("가로, 세로의 크기 : ");
	scanf("%d %d", &a_r, &a_c);
	printf("0이 아닌 원소의 row column value\n");
	
	while (i<MAX_TERMS){
		printf("= ");
 		scanf("%d %d %d%c", &a[i].row, &a[i].col, &a[i].value, &a_out);
 		
 		if (a_out == '.'){
 			i++;
			break;
		}
		
		i++;
 	}
 	a[0].length = i;

 	
 	
	//행렬 b
	term *b = (term *)malloc(sizeof(term)*MAX_TERMS);
	if (b == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
	
	int j=0;
	char b_out;
	
	printf("matrix b\n");
	printf("가로, 세로의 크기 : ");
	scanf("%d %d", &b_r, &b_c);
	
	if (a_c != b_r){
		printf("error");
		exit(1);
	}
	
	printf("0이 아닌 원소의 row column value\n");
	
	while (j<MAX_TERMS){
		printf("= ");
 		scanf("%d %d %d%c", &b[j].row, &b[j].col, &b[j].value, &b_out);
 		
 		if (b_out == '.'){
 			j++;
			break;
		}
		
		j++;
 	}
 	b[0].length = j;


	//a * b 출력 
	printf("matrix c\n");

    term *c = sparse_matrix_mult(a, a_r, a_c, b, b_r, b_c);
	for(int i=0; i<c[0].length; i++){
		if (c[i].value != 0){
			printf(": (%d, %d, %d)\n", c[i].row, c[i].col, c[i].value);	
		}
	}
	
	free(a);
	free(b);
	free(c);
	
	return 0;
}
