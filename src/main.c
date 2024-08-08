#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


int main(void)
{
	setbuf(stdout, NULL);

	LinkedList* l = ll_newLinkedList();



	int* a = (int*)malloc(sizeof(int));
	*a = 123;
	ll_add(l, a);


	int* retorno;
	retorno = (int*)ll_get(l, 0);

	if (retorno == NULL)
	{
		printf("NULO \n");
	}
	else
	{
		printf("%d \n", *retorno);
	}
	printf("------------------------------------------\n");


	int* b = (int*)malloc(sizeof(int));
	*b = 111;

	ll_push(l, 0, b);


	retorno = (int*)ll_get(l, 0);

	if (retorno == NULL)
	{
		printf("NULO \n");
	}
	else
	{
		printf("%d \n", *retorno);
	}
	printf("------------------------------------------\n");


	retorno = (int*)ll_get(l, 1);

	if (retorno == NULL)
	{
		printf("NULO \n");
	}
	else
	{
		printf("%d \n", *retorno);
	}
	printf("------------------------------------------\n");


	LinkedList* l2 = ll_subList(l, 0, l->size);

	retorno = (int*)ll_get(l2, 1);

	if (retorno == NULL)
	{
		printf("NULO \n");
	}
	else
	{
		printf("%d \n", *retorno);
	}
	printf("------------------------------------------\n");

	printf("%d", ll_containsAll(l,l2));
    return 0;
}

































