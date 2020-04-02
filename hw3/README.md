SEARCH

	For MDParser, I followed the logic of the finite state machine that was give to us. In SearchEng, it was crucial to account outgoing links that weren't linking to anything. In search() of SearchEng, I had to make sure I copied the searchable terms of the first term that was entered to the WebPageSet that was going to be combined.

TODOLIST

	It was crucial to always to be aware of the index that was trying to be accessed and the current capacity of the dynamically allocated array. Resizing also causes a great risk of having memory leaks as you essentially transfer the data from one dynamically allocated array to another. It was also a little tricky to exactly land at loc.