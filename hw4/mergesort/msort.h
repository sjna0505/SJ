#include <vector>

/**
 * Performs mergesort on the provided vector using
 * the Compare object, comp, to peform ALL comparisons
 *
 * Must run in O(n*log(n))
 */
using namespace std;

template <class T, class Compare >
void mergeSort(std::vector<T>& list, Compare comp )
{
	//check if the list is empty or only has one element
	if(list.size() <= 1)
		return;
	list = split(list, 0, list.size() -1, comp);
};

template <class T, class Compare>
std::vector<T> split(std::vector<T>& list, int i, int j, Compare comp)
{
	int newI, newJ;
	vector<T> rslt;
	vector<T> left;
	vector<T> right;

	//check if there is one element(base case)
	if(i == j)
		rslt.push_back(list[i]);

	else{
		//split the last in half
		newI = int((i+j+1)/2);
		newJ = newI - 1;
		left = split(list,i,newJ,comp);
		right = split(list,newI,j,comp);
		//merge
		rslt = merge(left,right,comp);
		left.clear();
		right.clear();
	}

	return rslt;
};

template <class T, class Compare>
std::vector<T> merge(std::vector<T>& left, std::vector<T>& right, Compare comp)
{
	vector<T> rslt;
	int i = 0;
	int j = 0;

	//loop to compare and add to new list
	while(i < (int)left.size() && j < (int)right.size())
	{
		if(comp(left[i], right[j])){
			rslt.push_back(left[i]);
			i++;
		}
		else{
			rslt.push_back(right[j]);
			j++;
		}
	}

	//if one is exhausted, then remaining elements are added
	if(i == (int)left.size() && j < (int)right.size())
	{
		for(int k = j; k < (int)right.size(); k++){
			rslt.push_back(right[k]);
		}
	}
	if(j == (int)right.size() && i < (int)left.size())
	{
		for(int k = i; k < (int)left.size(); k++){
			rslt.push_back(left[k]);
		}
	}
	return rslt;
};

