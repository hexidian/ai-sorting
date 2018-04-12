#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct listNode{
	int val;
	struct listNode* next;
} listNode;

typedef struct list{
	listNode* top;
	listNode* bottom;
} list;

typedef struct list2delem{
	listNode* top;
	listNode* bottom;
	struct list2delem* next;
} list2delem;

typedef struct list2d{
	list2delem* top;
	list2delem* bottom;
} list2d;

void print_list2delem(list2delem* this){
	printf("\n");
	for(listNode* i = this->top; i != NULL; i = i->next){
		printf("%d,\n", i->val);
	}
	printf("\n");
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


//TODO: rewrite this function to work without the length inputs. Take use of some of the techniques used latter in the code
void list2delemMerge(list2delem* O, list2delem* L, int leftLen, list2delem* R, int rightLen){
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

	//first divide up the runs... this takes many lines

  bool run = false;
	int lastVal;

	list2d bigboi;
	list2delem molds[len];//this is just a bunch of stuff for holding
	int runs = 0;
	listNode* nextNode = A->top;
	list2delem* this;

  for (int i = 0; i < len; i++)
	{
		if (!run) {
			list2delem* this = &molds[runs];
			this->top = nextNode; this->bottom = nextNode;
			nextNode = nextNode->next;
			this->top->next = NULL;
			if (runs > 1) {
				bigboi.bottom->next = this;
				bigboi.bottom = this;
			} else if (runs == 0) {
				bigboi.bottom = this;
				bigboi.top = this;
			} else {
				bigboi.top->next = this;
				bigboi.bottom = this;
			}
			run = true;
			runs++;
		} else {
			this->bottom->next = nextNode;
			this->bottom = nextNode;
			nextNode = nextNode->next;
			this->bottom->next = NULL;
			if (this->bottom->val <= nextNode->val) {
				run = false;
			}
		}
  }

	//finally done finding all the runs.

	//now we need to merge em'

	while (bigboi.top != bigboi.bottom){
		for (list2delem* i = bigboi.top; i->next != NULL; i = i->next){
			list2delem holder;
			list2delemMerge(&holder, i, i->next);
			i->top = holder.top; i->bottom = holder.bottom;
			i->next = i->next->next;
			//now there should be no pointers to the element which comes after i. It will still be in the memory, but I might take it out later for the sake of freeing up memory
		}
	}

	print_list2delem(bigboi.top);

}

//TODO: implement linked lists and use those for the merges because I will only need to be accessing the first element of it or appending to the end which is O(1) just like with arrays. This I will have unlimited length runs. I can then merge the runs faster b/c joining two lists is easy (just changing one pointer)

int main(){
  list left;
}
