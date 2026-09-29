#include <stdio.h>

int IsPrime(int num) {
    int i;

    if (num == 1){return 0;}
    else{
        for(i = 2; i < num; i++){
            if(num % i == 0){return 0;}
        }
        return 1;
    }
}

int main() {
    int num;

    while (1){
        printf("Please enter a positive integer:");
        scanf("%d", &num);
        if (IsPrime(num)){
            printf("This number is a prime.\n");
        }
        else{
            printf("This number is not a prime number.\n");
        }
    }
    return 0;
}
