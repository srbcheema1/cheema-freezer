DIRECTORY = bin/

all:
	mkdir build
	mkdir bin
	g++ -std=c++11 freezer.cpp -o freezer
	g++ -o enc_dec enc_dec.cpp
	
	cp freezer bin/freezer
	cp .start.sh bin/
	cp .start.desktop bin/start.desktop
	cp list_gen.sh bin/.list_gen.sh
	mv enc_dec bin/
	echo "hello world \n\nhow are you\n\n\n\nbye" > bin/hello.txt

	mv freezer build/freezer
	cp list_gen.sh build/.list_gen.sh
	cp .start.sh build/
	cp .start.desktop build/start.desktop
clean:
	rm -r build
	rm -r bin
