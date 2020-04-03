#!/usr/bin/python

import random

a = []
random.seed()
for i in range(0,10000):
	a.append(random.randrange(0,1000))
#	a.append(i)


def qs(A,low,high,iti):
	if(low < 0 or high >= len(A) or low >= high):
#		print "iti:%d low:%d high:%d" % (iti, low, high)
		return 
	pivot = A[high]
	i = low
	for j in range(low, high+1):
#		print "HAHA"
#		print "before iti:%d low:%d,high:%d, size:%d, pivot:%d i%d:%d j%d:%d " % (iti,low,high,high-low+1,pivot,i,A[i],j,A[j])
#		print A
		if (A[j] <= pivot):
			A[i],A[j] = A[j],A[i]
			i = i + 1
#		print "after iti:%d low:%d,high:%d pivot:%d i%d:%d j%d:%d" % (iti,low,high,pivot,i,A[i],j,A[j])
#		print A
	qs(A,low,i-2,iti+1) 
	qs(A,i,high,iti+1)
		

print a
qs(a,0,len(a) - 1,0)
print a
