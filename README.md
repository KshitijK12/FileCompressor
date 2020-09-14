				   HUFFMAN COMPRESSION

Problem Description :
	Huffman Compression is a technique of data compression using Huffman Coding. The use cases of this project would be lossless compression and decompression of data. The first use case compressing a file by using fewer bits without any loss. The second use case is decompressing the compressed file, ie, retrieving the original data from the compressed file.

For Example:in a file with the following data: 
XXXXXXYYYYZZ 
the frequency of "X" is 6, the frequency of "Y" is 4, and the frequency of "Z" is 2. If each character is represented using a fixed-length code of two bits, then the number of bits required to store this file would be 24, i.e., (2 x 6) + (2x 4) + (2x 2) = 24 bits. 
If the above data were compressed using Huffman compression, the more frequently occurring numbers would be represented by smaller bits, such as: 
X by the code 0 (1 bit)
Y by the code 10 (2 bits)
Z by the code 11 (2 bits)
therefore the size of the file becomes 18, i.e., (1x 6) + (2 x 4) + (2 x 2) = 18 bits. 

Proposed Solution :
	We use a huffman tree to compute variable length code for all the characters by implementing Prefix Rule, on the basis of their frequencies in the file. We use the concepts of Priority Queue and Huffman Algorithm (greedy approach).
	The code length of a character depends on how frequently it occurs in the given text.The character which occurs most frequently gets the smallest code. The character which occurs least frequently gets the largest code.
	Huffman Coding implements a rule known as a prefix rule.This is to prevent the ambiguities while decoding.It ensures that the code assigned to any character is not a prefix of the code assigned to any other character. Huffman tree is a full binary tree in which each leaf of the tree corresponds to a letter in the given alphabet with minimum external path weight, i.e., the one with the minimum sum of weighted path lengths for the given set of leaves.
	Using a heap to store the weight of each tree, each iteration requires O(logn) time to determine the cheapest weight and insert the new weight. There are O(n) iterations, one for each item. Hence the time complexity of the Huffman algorithm is O(nlogn).
	

Alternate Solution :

    • Lossy Compression : Lossy methods can provide high degrees of compression and result in smaller compressed files, but some amount of data may be lost in the process. Thus, after a compression/decompression cycle, the data set will be modified from the uncompressed original and information may be lost. Another disadvantage of lossy compression is that the process is irreversible,ie,once you compress the file, you can't go back. Lossy compression techniques are useful for pictures and music files that can be trimmed at the edges. Unlike text files and processing files, pictures and music do not require reconstruction to be identical to the original, especially if the data dropped is insignificant or undetectable.Hence lossless compression is better for text file compression.

