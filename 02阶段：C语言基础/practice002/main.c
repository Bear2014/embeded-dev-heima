#include <stdio.h>

/**
 * reverse the number: numbers
 */
void main()
{
	int numbers = 12345;
    int revNumbers = 0;

	while(numbers) {
		revNumbers = revNumbers * 10 + numbers % 10;  //5 54 543 5432 54321
		numbers /= 10; //1234 123 12 1 0

		printf("revNumbers=%d,numbers=%d\n",revNumbers,numbers);
	}
}