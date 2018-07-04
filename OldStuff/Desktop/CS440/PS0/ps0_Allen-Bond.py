"""
	Michael Allen-Bond
	CS440 Artificial Intelligence
	Dr. Scott Wallace
"""

import os

def create_corpus(d):
	filelist=os.listdir(d)
	filelist.remove('.svn')
	dictionary={}
	for filename in filelist:
		f=open(os.path.join(d,filename),"r")
		dictionary[filename]=f.read()
		f.close()
	return dictionary
"""When I first made this function, I printed everything out, but I figured you probably don't want 
a buttload of text here, so you'll just have to assume this works, otherwise none of the following functions
would be working either. :|  Also, I had to remove .svn from the filelist because it was interfering with the 
rest of the function, hopefully that's what you intended for us to do."""

corpus=create_corpus("Liens-50")



def corpus_char_stats(corpus):
	tuplelist=()
	sortedtuple=()
	for i in corpus:
		f=(len(corpus[i]),)
		tuplelist=tuplelist+f
	tuplelist=(sorted(tuplelist,reverse=True))
	minnum=(min(tuplelist),)
	maxnum=(max(tuplelist),)
	maxtomin=maxnum+minnum
	for i in tuplelist:
		f=(i,)
		sortedtuple=sortedtuple+f
	print(sortedtuple)
	print(maxtomin)

"""I wasn't sure whether you wanted all of the lengths in order, or just the 2, so I did both. The sort functions turns the tuple into a list,
so I had to turn it back into a tuple.  Again, not sure if that's what you wanted, but I did it.
Output:
(9647, 7563, 4443, 4245, 3988, 3796, 3221, 2524, 2486, 2470, 2432, 2430, 2355, 2351, 2070, 2049, 2044, 2039, 2027, 1985, 1967, 1938, 1907, 1891, 1877, 1716, 1680, 1592, 1433, 1398, 1385, 1360, 1359, 1343, 1335, 1330, 1321, 1318, 1308, 1291, 1285, 1281, 1272, 1269, 1261, 1236, 1187, 1004, 997, 946)
(9647, 946)
"""
corpus_char_stats(corpus)




def words(data):
	data=data.lower()
	masterlist=data.split(" ")
	punctlist=[]
	wordlist=[]
	for i in masterlist:
		if i.isalpha():
			wordlist.append(i)
		else:
			punctlist.append(i)
	"""print (wordlist)"""
	return wordlist

"""Alot of the words that don't register as alphabetical simply have commas or periods at the end, I'm not sure if that's what you wanted, but 
stripping the commas and periods out of the strings didn't sound like what we were supposed to do, since we create a list especially for punctuation."""




def find_word_ratios(corpus):
	from fractions import Fraction
	lowestratio=1.0
	name='nothin'
	for i in corpus:
		wordlist=words(corpus[i])
		masterlist=corpus[i].split(" ")
		x=1.*len(wordlist)
		y=1.*len(masterlist)
		ratio=x/y
		if lowestratio > ratio:
			lowestratio=ratio
			name=i
	print (name,lowestratio)
	print Fraction(lowestratio)

"""The fraction function is apparently very precise, since it gave me some godawful fraction to represent the ratio.  So I included the float
representation of the lowest ratio as well.

Output:
('WA_Kitsap_2009-08-24__200908240211.txt', 0.3598326359832636)
6482168501319877/18014398509481984
"""
find_word_ratios(corpus)



def word_frequencies(corpus):
	wordcount={}
	for i in corpus:
		wordlist=words(corpus[i])
		for j in wordlist:
			if j in wordcount:
				wordcount[j]+=1
			else:
				wordcount[j]=1
	keylist=sorted(wordcount, key=wordcount.get, reverse=True)[:10]
	valuelist=sorted(wordcount.values(), reverse=True)[:10]
	for i in range(10):
		print(keylist[i], valuelist[i])
	topten={}
	for i in range(len(keylist)):
		topten[keylist[i]]=valuelist[i]	
	print topten

"""The sorting methods for dictionaries is strange.  That is all.

I wanted to try doing a sorted top ten dictionary output, but if I try to resort the dictionary by values, it makes lists.  Not sure
how to resolve that.

Output:
('of', 771)
('the', 592)
('and', 298)
('to', 173)
('or', 159)
('lien', 146)
('a', 123)
('in', 120)
('for', 112)
('is', 110)
{'and': 298, 'a': 123, 'for': 112, 'of': 771, 'is': 110, 'lien': 146, 'to': 173, 'in': 120, 'the': 592, 'or': 159}
"""

word_frequencies(corpus)
