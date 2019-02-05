#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define IDSIZE 10
#define NAMESIZE 20
#define LINESIZE 1024

typedef struct { 			/* a name consists of */
	char last[NAMESIZE];	/* a last name (1 word) */
	char first[NAMESIZE];	/* a first name (1 word) */
} name;

typedef struct {			/* a record consists of */
	char id[IDSIZE];		/* an ID 'a' followed by 8 digits */
	name name;				/* a name e.g., {"simpson", "homer"}, */
	int score;				/* a score between 0 & 100 inclusive */
} record;


int cmp_score_desc_id_asc(const void *p, const void *q){
	const record *pp = p;
	const record *qq = q;
	int n = qq->score - pp->score; 
	if(n != 0) {
		return n; 
	}
	return strcmp(pp->id, qq->id); 
}

int cmp_score_desc_name_asc(const void *p, const void *q){
	const record *pp = p;
	const record *qq = q;
	int m;
	int n = qq->score - pp->score; 
	if(n != 0) {
		return n; 
	}
	m = strcmp(pp->name.last, qq->name.last); 
	if(m != 0){
		return m;	
	}
	return strcmp(pp->name.first, qq->name.first); 
}

int cmp_sort_score_desc_name_asc_id_asc(const void *p, const void *q){
	const record *pp = p;
	const record *qq = q;
	int n = cmp_score_desc_name_asc(pp, qq);
	if(n != 0){
		return n;
	}
	return strcmp(pp->id, qq->id);
}

void sort_score_desc_id_asc(record a[], size_t n){
	qsort(a, n, sizeof(a[0]), cmp_score_desc_id_asc);
}  

void sort_score_desc_name_asc(record a[], size_t n){
	qsort(a, n, sizeof(a[0]), cmp_score_desc_name_asc);
}

void sort_score_desc_name_asc_id_asc(record a[], size_t n){
	qsort(a, n, sizeof(a[0]), cmp_sort_score_desc_name_asc_id_asc);
}


int isValid(const char s[]){
	size_t i;
	if(strlen(s) != 9 || s[0]!= 'a'){
		return 0;
	} 
	for(i = 1; s[i]!='\0'; i++){
		if(!isdigit(s[i]))
		return 0;
	}
	
	return 2;
}

int parse_record(size_t *pcount, record reclist[]){  
	char tempId[IDSIZE];
	char tempFirst[NAMESIZE];
	char tempLast[NAMESIZE];
	char buffer[LINESIZE];
	int tempScore;
	size_t i;
	
	printf("Enter ID, Last Name, First Name, Score\n"); 
	while(fgets(buffer, LINESIZE, stdin)){
		printf("Enter ID, Last Name, First Name, Score\n"); 
		
		sscanf(buffer, "%s %s %s %d", tempId, tempLast, tempFirst, &tempScore);
		
		if(isValid(tempId) != 2 || tempScore > 100 || tempScore < 0){
			printf("ID or score invalid, try again\n");
			continue;
		}
		
		if(strlen(tempFirst) > NAMESIZE || strlen(tempLast) > NAMESIZE){
			printf("Name too long");
			continue;
		}
		
		for(i = 0; tempLast[i]!='\0'; i++){
			tempLast[i] = tolower(tempLast[i]);
		}
		
		for(i = 0; i < strlen(tempFirst); i++){
			tempFirst[i] = tolower(tempFirst[i]);
		}
		
		strcpy(reclist[*pcount].id, tempId);
		strcpy(reclist[*pcount].name.last, tempLast);
		strcpy(reclist[*pcount].name.first, tempFirst);
		reclist[*pcount].score = tempScore;
		*pcount += 1;
	}
	
	return 1;

}


void print_record(size_t *pcount, record reclist[]){
	size_t j;
	for(j = 0; j < *pcount; j++){
		printf("%d %s %s %s\n", reclist[j].score, reclist[j].name.last, reclist[j].name.first, reclist[j].id); 
	}
}


int main(){
	record records[100];
	size_t counter = 0;
	parse_record(&counter, records);
	sort_score_desc_name_asc_id_asc(records, counter);
	print_record(&counter, records);
	
	return 0;
}