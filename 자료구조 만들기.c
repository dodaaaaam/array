#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS


int main (){
 	int a, b, c;
 	
 	//a,b,c 숫자 입력 받기  
 	printf("a, b, c : ");
 	scanf("%d %d %d", &a, &b, &c);
 	
 	//동적할당 
 	void ***ptr = (void ***)malloc(sizeof(void**)*3);   
 	if (ptr == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        return 1;
    }
    
    ptr[0] = (void **)malloc(sizeof(int*)*a);
    if (ptr[0] == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        return 1;
    }
    
    for(int i=0; i<a; i++){
    	ptr[0][i] = (void *)malloc(sizeof(int)*b);
	}
    
    ptr[1] = (void **)malloc(sizeof(double*)*b);
    if (ptr[1] == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        return 1;
    }
    
    for(int i=0; i<b; i++){
    	ptr[1][i] = (void *)malloc(sizeof(double)*c);
	}
    
    ptr[2] = (void **)malloc(sizeof(char*)*c);
    if (ptr[2] == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        return 1;
    }
    
    for(int i=0; i<c; i++){
    	ptr[2][i] = (void *)malloc(sizeof(char[20])*a);
	}
	
	
	//ptr[][][]에 값 할당
	int i_count = 1;
	for(int i=0; i<a; i++){
		for(int j=0; j<b; j++){
			((int *)ptr[0][i])[j] = i_count++;
		}
	}
	
	double d_count = 1.0;
	for(int i=0; i<b; i++){
		for(int j=0; j<c; j++){
			((double *)ptr[1][i])[j] = d_count;
			d_count += 0.1;
		}
	}
	
	int c_count = 1;
	for(int i = 0; i < c; i++){
        for(int j=0; j < a; j++){
        	char temp[20];
			sprintf(temp, "Hi%d", c_count++);
        	strcpy((char *)ptr[2][i]+(j*20), temp);
        	strcpy(temp, "");
		}
    }
	
	//배열 저장 값 출력
	for(int i=0; i<a; i++){
		for(int j=0; j<b; j++){
			printf("%d  ", ((int *)ptr[0][i])[j]);
		}
		printf("\n");
	}
	
	for(int i=0; i<b; i++){
		for(int j=0; j<c; j++){
			printf("%.1f  ", ((double *)ptr[1][i])[j]);
		}
		printf("\n");
	}
	
	for(int i=0; i<c; i++){
		for(int j=0; j<a; j++){
			printf("%s  ", (char *)ptr[2][i] + (j*20));
		}
		printf("\n");
	}
	
	return 0; 
}
    
    
    
