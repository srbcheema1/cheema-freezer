DIRECTORY = bin/

all:
	mkdir build
	mkdir bin
	g++ -std=c++11 freezer.cpp -o freezer
	g++ -o enc_dec enc_dec.cpp
	
	cp freezer bin/freezer
	cp start.sh bin/.start.sh
	cp start.desktop bin/start.desktop
	cp list_gen.sh bin/.list_gen.sh
	cp keybox.jar bin/.keybox.jar
	cp utilities.sh bin/.utilities.sh
	echo "helloworld" > bin/.freezerkey
	mv enc_dec bin/
	echo "hello world \n\nhow are you\n\n\n\nbye" > bin/hello.txt
	
	mv freezer build/freezer
	cp start.sh build/.start.sh
	cp start.desktop build/start.desktop
	cp list_gen.sh build/.list_gen.sh
	cp keybox.jar build/.keybox.jar
	cp utilities.sh build/.utilities.sh
	echo "helloworld" > build/.freezerkey
clean:
	rm -r build
	rm -r bin
