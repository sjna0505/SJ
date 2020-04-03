#!/usr/bin/python
import random

class A:
	def __init__(self,n = 0):
		random.seed()
		self.n = n
		self.arr = []
		for i in range (0, n):
			self.arr.append(random.randrange(0,100))
	def dup(self):
		self.arr2 = []
		for i in range (0,self.n):
			self.arr2.append(self.arr[i])

	def insert_sort(self):
		if(self.n <= 1):
			return
		for key in range(1,self.n): 
			i = key -1
			while( self.arr[i] > self.arr[i+1]):
				self.arr[i], self.arr[i+1] = self.arr[i+1], self.arr[i]
				i = i - 1
				if(i <0):
					break

	def merge_sort(self,i,j):
		b = []
		if(j == i):
			b.append(self.arr2[i])
			return b
		if(j == i+1):
			if(self.arr2[i] >= self.arr2[i+1]):
				b.append(self.arr2[i+1])
				b.append(self.arr2[i])
			else:
				b.append(self.arr2[i])
				b.append(self.arr2[i+1])
			return b
#		print "HAHA i:%d j/2:%d j/2+1:%d j:%d" % (i,int((i+j)/2),int((i+j)/2)+1,j)
#		aa = self.merge_sort(i,int((i+j)/2))
#		print "aa:%s" % ",".join(map (lambda x: "%d" %x,aa))
#		bb = self.merge_sort(int((i+j)/2)+1,j)
#		print "HOHO i:%d j/2:%d j/2+1:%d j:%d aa:%s bb:%s" % (i,int((i+j)/2),int((i+j)/2)+1,j,",".join(map (lambda x: "%d" %x,aa)),",".join(map (lambda x: "%d" %x,bb)))
		return merge_two_list(self.merge_sort(i,int((i+j)/2)),self.merge_sort(int((i+j)/2)+1,j))

def merge_two_list(a,b):
	c = []
	i , j = 0,0
	while( i < len(a) and j < len(b)):
		if(a[i] < b[j]):	
			c.append(a[i])
			i = i+1
		else:
			c.append(b[j])
			j = j+1
#		print "i:%d j:%d a:%s b:%s" % (i,j,",".join(map (lambda x: "%d" % x, a)),",".join(map (lambda x: "%d" % x,b)))

	if( i == len(a) and j < len(b)):
		for k in range(j, len(b)):
			c.append(b[k])
	if( j == len(b) and i < len(a)):
		for k in range(i, len(a)):
			c.append(a[k])
#	print c
	return c
	
		
def main():
	a = A(20)
	a.dup()
	print a.arr2
	a.insert_sort()
	print a.arr
	print a.merge_sort(0,len(a.arr)-1)
if __name__ == "__main__":
	main()
