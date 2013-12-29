rsa: rsa.cpp
	@g++ -g -o $@ $^

rsaZZmain.o: rsaZZmain.cpp
	@g++ -g -c $^

rsaZZ: rsaZZ.cpp rsaZZmain.o
	@g++ -g -o $@ $^ -lntl