#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
srand(time(NULL));
//ASCII a = 97, z = 122
int min=97;
int max=122;
int i=0;
int r;
while(i<10){
r = rand()%(max-min)+min;

char c = r;
printf("%c", c);

i++;

}
printf("\n");
}

