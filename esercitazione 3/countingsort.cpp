// C++ Program for counting sort
#include <bits/stdc++.h>
#include <string.h>
using namespace std;
#define RANGE 255

// The main function that sort
// the given string arr[] in
// alphabetical order
void countSort(char arr[]){
	// The output character array
	// that will have sorted arr
	char output[strlen(arr)];

	// Create a count array to store count of individual
	// characters and initialize count array as 0
	int count[RANGE + 1], i;
	memset(count, 0, sizeof(count));

	// Store count of each character
	for (i = 0; arr[i]; ++i)
		++count[arr[i]];

	// Change count[i] so that count[i] now contains actual
	// position of this character in output array
	for (i = 1; i <= RANGE; ++i)
		count[i] += count[i - 1];

	// Build the output character array
	for (i = 0; arr[i]; ++i) {
		output[count[arr[i]] - 1] = arr[i];
		--count[arr[i]];
	}


	for (i=sizeof(arr)-1;i>=0;--i){
		output[count[arr[i]]-1] = arr[i];
		--count[arr[i]];
	}



	// Copy the output array to arr, so that arr now
	// contains sorted characters
	for (i = 0; arr[i]; ++i)
		arr[i] = output[i];
}

void countSort2(char arr[]){
	int count[RANGE + 1], i;
	memset(count, 0, sizeof(count));

	for (i=0;arr[i];++i)
		++count[arr[i]-'a'];
    int c=0;
	for (i=0;i<RANGE;i++){
        while(count[i]>0){
            arr[c++]=i+'a';
            count[i]--;
        }
	}

    cout << arr;
}


int main(){
	char arr[] = "geeksforgeeks";

	countSort2(arr);


	return 0;
}

