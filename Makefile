DIRECTORY = bin/

all:
	mkdir build
	mkdir bin
	g++ -o freezer freezer.cpp
	g++ -o enc_dec enc_dec.cpp
	
	cp freezer bin/
	cp .start.sh bin/
	cp .start.desktop bin/start.desktop
	cp list_gen.sh bin/
	mv enc_dec bin/
	
	mv freezer build/
	cp .start.sh build/
	cp .start.desktop build/start.desktop
clean:
	rm -r build
	rm -r bin
