#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) (((a)>(b)) ? (a) : (b)) 

typedef struct{
	int degree;     //최고차수 저장 
	int *coef;      //각 항의 계수 저장
	int *expon;     //각 항의 차수 저장 
} poly; 

poly add(poly a, int a_length, poly b, int b_length){
	poly c;
	c.degree = MAX(a.degree, b.degree);   
	
	c.coef = (int *)malloc(sizeof(int)*(c.degree + 1)); 
	if (c.coef == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    c.expon = (int *)malloc(sizeof(int)*(c.degree + 1)); 
	if (c.expon == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
	
	int a_index = 0, b_index = 0, c_index = 0;
	while ((a_index < (a_length/2)) || (b_index < (b_length/2))){
		if ((a_index < (a.degree + 1)) && (b_index < (b.degree + 1))){
			if (a.expon[a_index] > b.expon[b_index]){
				c.coef[c_index] = a.coef[a_index];
				c.expon[c_index] = a.expon[a_index];
				a_index++;
				c_index++;
			}
			else if (a.expon[a_index] == b.expon[b_index]){
				c.coef[c_index] = a.coef[a_index] + b.coef[b_index];
				c.expon[c_index] = a.expon[a_index];
				a_index++;
				b_index++;
				c_index++;
			}
			else {
				c.coef[c_index] = b.coef[b_index];
				c.expon[c_index] = b.expon[b_index];
				b_index++;
				c_index++;
			}
		}
		
		else if ((a_index >= (a_length/2)) && (b_index < (b_length/2))){
			c.coef[c_index] = b.coef[b_index];
			c.expon[c_index] = b.expon[b_index];
			b_index++;
			c_index++;
		}
		
		else if ((a_index < (a_length/2)) && (b_index >= (b_length/2))){
			c.coef[c_index] = a.coef[a_index];
			c.expon[c_index] = a.expon[a_index];
			a_index++;
			c_index++;
		}
	}
	return c;
}

poly mul(poly a, int a_length, poly b, int b_length){
	poly d;
	d.degree = a.degree + b.degree;
	d.coef = (int*)malloc(sizeof(int)*(d.degree + 1));
	d.expon = (int*)malloc(sizeof(int)*(d.degree + 1));
	
	int *p_coef = (int*)malloc(sizeof(int)*((a_length/2)*(b_length/2)));
	int *p_expon = (int*)malloc(sizeof(int)*((a_length/2)*(b_length/2)));
	
	int index = 0;
	for(int i=0; i<(a_length/2); i++){
		for(int j=0; j<(b_length/2); j++){
			p_coef[index] = a.coef[i] * b.coef[j];
			p_expon[index] = a.expon[i] + b.expon[j];       
			index++;     
		}
	}  
	
	//index = (a_length/2)*(b_length/2)
	
	int d_degree = d.degree;
	int d_index = 0;
	
	for (int d_index = 0; d_index < (d.degree + 1); d_index++){
		int sum = 0; 
		for(int i=0; i<((a_length/2)*(b_length/2)); i++){
			if(p_expon[i] == d_degree){
				sum += p_coef[i];
			}
		}
		
		if (sum != 0){
			d.coef[d_index] = sum;
			d.expon[d_index] = d.degree - d_index;
			d_degree--;	
		}
		
		else {
			d.coef[d_index] = 0;
			d.expon[d_index] = 0;
			d_degree--;	
		}
	}

	return d;
}


int main(){
	//다항식 a 입력  
	char a_input[100];              //문자열로 다항식 입력 받음  
    int a_num[100];                 //정수형으로 저장  
    int i = 0;

	poly a;
    printf("다항식 a를 입력하세요: ");
    fgets(a_input, sizeof(a_input), stdin);

    char *a_token = strtok(a_input, " ");
    while(a_token != NULL) {
        a_num[i++] = atoi(a_token);           //계수와 차수가 1차원 배열로 저장  
		a_token = strtok(NULL, " ");
    }

	int a_length = i;           //다항식을 모두 입력했을 때의 길이  
	a.degree = a_num[1];        //차수  
	
	a.coef = (int *)malloc(sizeof(int)*(i/2)); 
	if (a.coef == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    a.expon = (int *)malloc(sizeof(int)*(i/2)); 
	if (a.expon == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for(int i=0; i<a_length; i++){
    	if (i%2 == 0){             //계수  
    		a.coef[i/2] = a_num[i];
		}
		else {                     //차수 
			int j = i-1; 
			a.expon[j/2] = a_num[i];
		}
	}
	
	//다항식 b 입력  
	char b_input[100];              //문자열로 다항식 입력 받음  
    int b_num[100];                 //정수형으로 저장  
    int j = 0;

	poly b;
    printf("다항식 b를 입력하세요: ");
    fgets(b_input, sizeof(b_input), stdin);

    char *b_token = strtok(b_input, " ");
    while(b_token != NULL) {
        b_num[j++] = atoi(b_token);           //계수와 차수가 1차원 배열로 저장  
		b_token = strtok(NULL, " ");
    }
	
	int b_length = j;           //다항식을 모두 입력했을 때의 길이  
	b.degree = b_num[1];        //차수  
	
	b.coef = (int *)malloc(sizeof(int)*(j/2)); 
	if (b.coef == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    b.expon = (int *)malloc(sizeof(int)*(j/2)); 
	if (b.expon == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for(int i=0; i<a_length; i++){
    	if (i%2 == 0){             //계수  
    		b.coef[i/2] = b_num[i];
		}
		else {                     //차수 
			int j = i-1; 
			b.expon[j/2] = b_num[i];
		}
	}
	
	// a + b 출력
	poly c = add(a, a_length, b, b_length);
	printf("a + b = ");
	for (int i=0; i<(c.degree + 1); i++){
		if (c.expon[i] != 0){
			printf("%dx^%d", c.coef[i], c.expon[i]);
		}
		else if (c.coef[i] != 0){
			printf("%d", c.coef[i]);
		}
		if (i < c.degree && (c.expon[i+1] != 0 || c.coef[i+1] != 0)){
			printf(" + ");	
		}
	}
	printf("\n");

	
	// a * b 출력  
	poly d = mul(a, a_length, b, b_length);
	printf("a * b = ");
	for (int i=0; i<(d.degree + 1); i++){
		if (d.expon[i] != 0){
			printf("%dx^%d", d.coef[i], d.expon[i]);
		}
		else if (d.coef[i] != 0){
			printf("%d\n", d.coef[i]);
		}
		if (i < d.degree && (d.expon[i+1] != 0 || d.coef[i+1] != 0)){
			printf(" + ");	
		}
	}
	
	free(a.coef);
	free(b.coef);
	free(c.coef);
	free(d.coef);
	free(a.expon);
	free(b.expon);
	free(c.expon);
	free(d.expon);
	free(p_coef);
	free(p_expon);
	
	return 0; 
}
