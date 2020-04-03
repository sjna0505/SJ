#!/usr/bin/python

import random

a = []
random.seed()
#for i in range(0,100000):
for i in range(0,100):
	a.append(random.randrange(0,1000))
#a = [218, 970, 641, 692, 460, 177, 984, 591, 445, 347]
b = []
def swap_max(A,i,n):
	largest = i
	for j in ( (i+1)*2 - 1, (i+1)*2 ):
		if (j >= n): break
#		print "HAHA n:%d i:%d j:%d" % (n,i,j)
#		print "HAHA" 
		if( A[largest] < A[j]): 
			largest = j
	if(largest != i):
		A[largest], A[i] = A[i], A[largest]
		if(n >= 3): swap_max(A,largest,n)

def maxify(A,n):
	if(n < 2): return
	for i in range(0,int(n/2)):
		if i <= int(n/2) - 1:
			swap_max(A,int(n/2) -1 -i,n)
	
def get_max(A,B):
	n = len(A)
	if(n == 0): return 
	if(n == 1):
		B.append(A[0])
		return
	maxify(A,n)
#	print A
	for i in range(n-1,0,-1):
		max_value = A[0]
		B.append(max_value)
		A[0],A[i]  = A[i],A[0]
		A.pop()
		swap_max(A,0,i)
#		print A
		if(n == 2):
			B.append(A[0])
			return
	B.append(A[0])
	return

print a
get_max(a,b)
print b
