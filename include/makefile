EXE = main_Ivan
BALL = ball
TABLE = table
BILLIARD = billiard
VECTOR = vector_operations
KEY = -lm -lsfml-graphics -lsfml-window -lsfml-system

$(EXE) : $(EXE).o $(BALL).o $(TABLE).o $(BILLIARD).o $(VECTOR).o
	g++ -o $(EXE) $(EXE).o $(BALL).o $(TABLE).o $(BILLIARD).o $(VECTOR).o $(KEY)
&(EXE).o : &(EXE).cpp
	g++ -c $(EXE).cpp
$(BALL).o : $(BALL).cpp
	g++ -c $(BALL).cpp
$(TABLE).o : $(TABLE).cpp
	g++ -c $(TABLE).cpp
$(BILLIARD).o : $(BILLIARD).cpp
	g++ -c $(BILLIARD).cpp
$(VECTOR).o : $(VECTOR).cpp
	g++ -c $(VECTOR).cpp
clean :
	rm -f *.o *~ $(EXE)
