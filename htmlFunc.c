/*
 HTML Parser by Artur@Chudzik.net.pl
 License: GPL
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct htmlStackElement{
	char tag[16];
	struct htmlStackElement *next;
};

struct htmlStackElement *stackHead;
int closureWarningPrinted = 0;
int parseError = 0;

void setParseError(int pe){
	parseError = pe;
}

void htmlStackPrint(){
	struct htmlStackElement *temp;
	temp = stackHead;
	while(temp!=NULL){
		printf("%s, ",temp->tag);
		temp=temp->next;	
	}
	printf("\n");
}

void htmlStackPush(char *tag){
	struct htmlStackElement *temp, *temp2;

	temp2 = (struct htmlStackElement*)malloc(sizeof(struct htmlStackElement));
	sprintf(temp2->tag, "%s", tag);
	temp2->next = NULL; 
	
	temp = stackHead;
	while(temp->next!=NULL) temp=temp->next;
	temp->next = temp2;
}

void htmlStackPop(char *tag, int fullClosure, int lineNumber){
	char lastTag[16];
	struct htmlStackElement *temp;
	
	temp = stackHead;
	
	while((temp->next)->next!=NULL) temp=temp->next;
	if(temp->next == NULL) return;
	
	if (fullClosure && !closureWarningPrinted){
		sprintf(lastTag, "</%s>", temp->next->tag);
		if (strcmp(lastTag, tag) != 0) {
			printf("[!!]: wrong closure: '%s' (expected: '%s') on line %d \n", lastTag, tag, lineNumber);
			closureWarningPrinted = 1;
		}
	}
	
	temp->next = NULL;
}

void htmlStackInit(){
	stackHead = (struct htmlStackElement*)malloc(sizeof(struct htmlStackElement));
	sprintf(stackHead->tag, "%s", "ROOT");
	stackHead->next = NULL;
}

void htmlStackFinish(){
	free(stackHead);
	if(parseError){
		printf("[ii]: Parse status: ERROR\n");
	} else {
		printf("[ii]: Parse status: OK!\n");
	}
}

void removeFirstChar(char *s){
	if (*s == '\0') return;
	*s = *(s+1);
	removeFirstChar(s+1);
}