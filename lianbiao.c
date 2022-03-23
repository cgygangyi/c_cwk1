#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"

#define CreateNode(p)  p=(Book *)malloc(sizeof(Book));
#define DeleteNode(p)   free((void *)p);

Book *Crt1() 
{ 
	int x; Book *h, *p, *last;
	CreateNode(h);
	last=h;   
	while(1)
	{ 
		scanf("%d",&x);
		if(!x) break;
		CreateNode(p);
		p->id=x;
		last->next=p;
		last=p;
	}
	last->next=NULL;
	return h;
} 

