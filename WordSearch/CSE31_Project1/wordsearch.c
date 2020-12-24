#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);

// Main function, DO NOT MODIFY!!!	
int main(int argc, char **argv) { 
    int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

	// Read puzzle block into 2D arrays
    for(i=0; i<bSize; i++){
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
	fclose(fptr);

	// Open file for reading word list
	fptr = fopen("states.txt", "r");
	if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
	
	// Save words into arrays
	for(i=0; i<50; i++){
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);		
	}
	
	// Remove newline characters from each word (except for the last word)
	for(i=0; i<49; i++){
		*(*(words+i) + strlen(*(words+i))-2) = '\0';	
	}
	
	// Print out word list
	printf("Printing list of words:\n");
	for(i=0; i<50; i++){
		printf("%s\n", *(words + i));		
	}
	printf("\n");
	
	// Print out original puzzle grid
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
	printf("\n");

	// Call searchPuzzle to find all words in the puzzle
	searchPuzzle(block, bSize, words, 50);
	printf("\n");
	
	// Print out final puzzle grid with found words in lower case
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
	printf("\n");
	
    return 0;
}

void printPuzzle(char** arr, int n){
	// This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
	// Your implementation here
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			printf("%c ", *(*(arr+i)+j));
		}
		printf("\n");
	}
}

void searchPuzzle(char** arr, int n, char** list, int listSize){
	// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
	// Your implementation here

//loop
	for(int l=0; l<listSize; l++){
		for(int i=0; i<n; i++){ 
			for (int j=0; j<n; j++){
				if(*(*(arr+i)+j) == *(*(list+l)+0) || *(*(arr+i)+j) == *(*(list+l)+0)+('a'-'A')){

					// check RIGHT
					for(int k=1; (j+k)<n; k++){
						if(*(*(arr+i)+j+k)==*(*(list+l)+k)-('a'-'A') || *(*(arr+i)+j+k)==*(*(list+l)+k) ){
							if(*(*(list+l)+k+1) == '\0'){
								printf("Word found: %s\n",*(list+l));
								for(int a=0; a<=k; a++){
									if( *(*(arr+i)+j+a)>='A' && *(*(arr+i)+j+a)<='Z' ){
										*(*(arr+i)+j+a) = *(*(arr+i)+j+a)+('a'-'A');
									}
								}
								break;
							}
						}else{
							break;	
						}
					}

					// check Down
					for(int k=1; (i+k)<n; k++){
						if(*(*(arr+i+k)+j)==*(*(list+l)+k)-('a'-'A') || *(*(arr+i+k)+j)==*(*(list+l)+k) ){
							if(*(*(list+l)+k+1) == '\0'){
								printf("Word found: %s\n",*(list+l));
								for(int a=0; a<=k; a++){
									if( *(*(arr+i+a)+j)>='A' && *(*(arr+i+a)+j)<='Z' ){
										*(*(arr+i+a)+j) = *(*(arr+i+a)+j)+('a'-'A');
									}
								}
								break;
							}
						}else{
							break;	
						}

					}

					// check \Bottom
					for(int k=1; (i+k)<n && (j+k)<n; k++){
						if(*(*(arr+i+k)+j+k)==*(*(list+l)+k)-('a'-'A') || *(*(arr+i+k)+j+k)==*(*(list+l)+k) ){
							if(*(*(list+l)+k+1) == '\0'){
								printf("Word found: %s\n",*(list+l));
								for(int a=0; a<=k; a++){
									if(*(*(arr+i+a)+j+a)>='A' && *(*(arr+i+a)+j+a)<='Z'){
										*(*(arr+i+a)+j+a) = *(*(arr+i+a)+j+a)+('a'-'A');
									}
								}
								break;
							}
						}else{
							break;	
						}
					}

					// check UP
					for(int k=1; (i-k)>=0; k++){
						if(*(*(arr+i-k)+j)==*(*(list+l)+k)-('a'-'A') || *(*(arr+i-k)+j)==*(*(list+l)+k) ){
							if(*(*(list+l)+k+1) == '\0'){
								printf("Word found: %s\n",*(list+l));
								for(int a=0; a<=k; a++){
									if( *(*(arr+i-a)+j)>='A' && *(*(arr+i-a)+j)<='Z' ){
										*(*(arr+i-a)+j) = *(*(arr+i-a)+j)+('a'-'A');
									}
								}
								break;
							}
						}else{
							break;	
						}
					} 

					// check /TOP
					for(int k=1; (i-k)>=0 && (j+k)<n; k++){
						if(*(*(arr+i-k)+j+k)==*(*(list+l)+k)-('a'-'A') || *(*(arr+i-k)+j+k)==*(*(list+l)+k) ){
							if(*(*(list+l)+k+1) == '\0'){
								printf("Word found: %s\n",*(list+l));
								for(int a=0; a<=k; a++){
									if(*(*(arr+i-a)+j+a)>='A' && *(*(arr+i-a)+j+a)<='Z'){
										*(*(arr+i-a)+j+a) = *(*(arr+i-a)+j+a)+('a'-'A');
									}
								}
								break;
							}
						}else{
							break;	
						}
					}
            	}
			} 
        } 
    } 

}


