all: life life_debug validate 

life_debug: life.cpp submit.cpp 
	g++ -DDEBUG=1  -o life_debug life.cpp submit.cpp 

life: life.cpp submit.cpp
	cilk++ -DDEBUG=0 -fcilkscreen -O3 -o life life.cpp submit.cpp 

validate: validate.cpp
	g++ -o validate validate.cpp	
clean: 
	rm life life_debug validate
