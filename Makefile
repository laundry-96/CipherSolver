EXE = proj2
OBJS = Proj2.o Date.o CipherMessage.o
CPPFLAGS = -ansi -Wall

# The variable CXX is the default C++ compiler, in this case it's g++
$(EXE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXE)

.PHONY : clean
clean:
	-rm -f $(OBJS) $(EXE)