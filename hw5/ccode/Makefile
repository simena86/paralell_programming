INC=/home/beta/cilk/include/cilk++

all: life validate

life: life.cpp submit.cpp 
	/home/beta/cilk/bin/cilk++ -fcilkscreen -o life life.cpp submit.cpp -I $(INC)

validate: validate.cpp
	g++ -o validate validate.cpp	
clean: 
	rm life validate
