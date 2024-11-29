#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 80

int cal(int op1,int op2,char op){
    if(op=='+'){
        return op1+op2;
    }
    else if(op=='-'){
        return op1-op2;
    }
    else if(op=='*'){
        return op1*op2;
    }
    else if(op=='/'){
        if(op2==0){
            printf("Division by Zero error");
            exit(1);
        }
        return op1/op2;
    }
    else{    
        printf("Error:Invalid Operator");
        exit(1);
    }
}


int evalvate(char* exp){
    int num_stack[MAX];
    char op_stack[MAX];
    int num_top = -1;int op_top = -1;
    int length = strlen(exp);
    int i=0;
    while(i<length){
        if(isspace(exp[i])){
            i++;
            
        }
        else if(exp[i] >= '0' && exp[i] <= '9'){
            int num = 0;
            while(i<length&&(exp[i] >= '0' && exp[i] <= '9')){
                num = num*10+(exp[i]-'0');
                i++;
            }
            num_stack[++num_top]=num;
        }
        else if(exp[i]=='+'||exp[i]=='-'||exp[i]=='*'||exp[i]=='/'){
            op_stack[++op_top]=exp[i++];
        }
        else{
            printf("Error: Invalid expression.\n");
            exit(1);
        }
    }
    
    
    char opt_prec[] = {'/','*','-','+'};
    int m = 0;
    while(m<4){
        int j=0;
        for(j=0;j<=op_top;j++){ if( op_stack[j]==opt_prec[m]){
        int op2 = num_stack[j+1];
        int op1 = num_stack[j];
        char op = op_stack[j];
        int ans = cal(op1,op2,op);
        for (int k = j; k < op_top; k++) {
            op_stack[k] = op_stack[k + 1];
            }
        op_top--; 
        num_stack[j] = ans;
        for (int k = j + 1; k < num_top; k++) {
            num_stack[k] = num_stack[k + 1];
            }
        num_top--;
        }}
        m++;
        }

    return num_stack[num_top];
}

void main(){
    char exp[MAX];
    fgets(exp,MAX,stdin);
    int result = evalvate(exp);
    printf("%d",result);
}
// we can use dynamic allocation also if needed -----
// exp = (char *)malloc(capacity * sizeof(char));
//     if (exp == NULL) {
//         printf("Memory allocation failed.\n");
//         return 1;
//     }

//  while ((ch = getchar()) != EOF && ch != '\n') {
//         if (size + 1 >= capacity) {
//             capacity *= 2; 
//             exp = (char *)realloc(exp, capacity * sizeof(char));
//             if (exp == NULL) {
//                 printf("Memory reallocation failed.\n");
//                 return 1;
//             }
//         }

//         exp[size++] = ch;
//     }
//     exp[size] = '\0';
//  just remove max and pass size for the function evalvate;