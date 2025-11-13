#include <stdio.h>

void deny(void);
void jolly(void);

int main(void)
{
	printf("He's a cheerful fellow!\n");
	printf("He's a cheerful fellow!\n");
	jolly();
	deny();

return 0;
}


void jolly(void)
{
	printf("He's a cheerful fellow!\n");
}

void deny(void)
{
	printf("No one can deny it!\n");
}