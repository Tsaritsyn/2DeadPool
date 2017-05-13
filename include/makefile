EXE = main_Ivan
BALL = ball
TABLE = table
KEY = -lm -lsfml-graphics -lsfml-window -lsfml-system

$(EXE) : $(EXE).o $(BALL).o $(TABLE).o
	g++ -o $(EXE) $(EXE).o $(BALL).o $(TABLE).o $(KEY)
&(EXE).o : &(EXE).cpp
	g++ -c $(EXE).cpp
$(BALL).o : $(BALL).cpp
	g++ -c $(BALL).cpp
$(TABLE).o : $(TABLE).cpp
	g++ -c $(TABLE).cpp
clean :
	rm -f *.o *~ $(EXE)
