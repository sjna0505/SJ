all: search-shell

search-shell: search-shell.cpp combiners.o util.o searcheng.o searchui.o webpage.o txt_parser.o md_parser.o handler.o cmdhandler.o
	g++ -g -std=gnu++11 -Wall search-shell.cpp combiners.o util.o txt_parser.o searcheng.o searchui.o webpage.o md_parser.o handler.o cmdhandler.o -o search-shell

webpage.o: webpage.cpp webpage.h util.h
	g++ -g -Wall -std=gnu++11 -c webpage.cpp -o webpage.o

handler.o: searcheng.h handler.h handler.cpp
	g++ -g -Wall -std=gnu++11 -c handler.cpp -o handler.o

util.o: util.cpp util.h webpage.h
	g++ -g -Wall -std=gnu++11 -c util.cpp -o util.o

searchui.o: searchui.cpp searchui.h util.h searcheng.h handler.h
	g++ -g -Wall -std=gnu++11 -c searchui.cpp -o searchui.o

txt_parser.o: txt_parser.cpp txt_parser.h pageparser.h util.h
	g++ -g -Wall -std=gnu++11 -c txt_parser.cpp -o txt_parser.o

combiners.o: searcheng.h combiners.cpp
	g++ -g -Wall -std=gnu++11 -c combiners.cpp -o combiners.o

searcheng.o: searcheng.cpp searcheng.h webpage.h pageparser.h
	g++ -g -Wall -std=gnu++11 -c searcheng.cpp -o searcheng.o

cmdhandler.o: handler.h searcheng.h cmdhandler.h cmdhandler.cpp util.h
	g++ -g -Wall -std=gnu++11 -c cmdhandler.cpp -o cmdhandler.o

md_parser.o: md_parser.cpp md_parser.h pageparser.h util.h
	g++ -g -Wall -std=gnu++11 -c md_parser.cpp -o md_parser.o

clean:
	rm -f *.o search-shell

