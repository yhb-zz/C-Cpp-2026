#include <stdio.h>
#include <time.h>

int IsPrime(int num) {
    int i;

    if (num == 1){return 0;}
    else{
        for(i = 2; i < (num+1)/2; i++){
            if(num % i == 0){return 0;}
        }
        return 1;
    }
}

int main() {
    int num;
    int count;
    long long range;
    range = 1000;
    printf("%d ", range);
    clock_t start = clock();

    count = 1;  //先把2算上
    for(num = 3; num <= range; num += 2){
        if (IsPrime(num)){count++;}
        printf("%d ", num);
    }

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("the number of the primes under %d is %d.", range, count);
    printf("time consumption:%fs\n", seconds);
    return 0;
}
