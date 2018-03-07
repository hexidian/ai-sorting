#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int val;
	struct listNode* next;
} listNode;

typedef struct {
	listNode* top;
	listNode* bottom;
} list;

typedef struct {
	list* data;
	struct list2delem* next;
} list2delem;

typedef struct {
	list2delem* top;
	list2delem* bottom;
} list2d;

void append2delem(list2delem* start, listNode* new) {
	start->data->bottom->next = new;
	start->data->bottom = new;
}

//for arrays
void Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
	int i,j,k;

	// i - to mark the index of left aubarray (L)
	// j - to mark the index of right sub-raay (R)
	// k - to mark the index of merged subarray (A)
	i = 0; j = 0; k =0;

	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j])
    {
      A[k++] = L[i++];
    } else {
      A[k++] = R[j++];
    }
	}
	while(i < leftCount)  {A[k++] = L[i++];}
	while(j < rightCount) {A[k++] = R[j++];}
}

//merges two lists, L and R, into the O list
void listMerge(list* O, list* L, int leftLen, list* R, int rightLen){
	int i,j,k;
	i = 0; j = 0; k= 0;

	while(i<leftLen && j<rightLen) {
		if(L->top->val < R->top->val)
		{
			listNode* adding = L->top;//store it as a variable so that we don't have to keep accessing it.
			O->bottom->next = adding;
			O->bottom = adding;
			L->top = adding->next;
			O->bottom->next = NULL;
			k++; i++;
		} else {
			listNode* adding = R->top;
			O->bottom->next = adding;
			O->bottom = adding;
			R->top = adding->next;
			O->bottom->next = NULL;
			k++; j++;
		}
	}
	if (i<leftLen) {
		O->bottom->next = L->top;
		O->bottom = L->bottom;
		//this leave the L list trashed, but that is okay because we don't need to use it anymore
	} else {
		O->bottom->next = R->top;
		O->bottom = L->bottom;
	}
}

//basic mergesort function. I will be comparing my natural merge sort to this
void MergeSort(int *A,int n) {
	int mid,i, *L, *R;
	if(n < 2){return;} // base condition. If the array has less than two element, do nothing.

	mid = n/2;  // find the mid index.

	// create left and right subarrays
	// mid elements (from index 0 till mid-1) should be part of left sub-array
	// and (n-mid) elements (from mid to n-1) will be part of right sub-array
	L = (int*)malloc(mid*sizeof(int));
	R = (int*)malloc((n- mid)*sizeof(int));

	for(i = 0;i<mid;i++) L[i] = A[i]; // creating left subarray
	for(i = mid;i<n;i++) R[i-mid] = A[i]; // creating right subarray

	MergeSort(L,mid);  // sorting the left subarray
	MergeSort(R,n-mid);  // sorting the right subarray
	Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.

  free(L);//we no longer need to reserve the memory for L and R
  free(R);
}

void NaturalMergeSort(list* A, int len){

  bool run = true;
	int lastVal;
  for (int i = 0; i < len; i++){

  }

}

//TODO: implement linked lists and use those for the merges because I will only need to be accessing the first element of it or appending to the end which is O(1) just like with arrays. This I will have unlimited length runs. I can then merge the runs faster b/c joining two lists is easy (just changing one pointer)

int main(){
  list left;
}
