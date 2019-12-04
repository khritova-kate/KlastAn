INT_O = My_Interface.o
INT_CPP = My_Interface.cpp
INT_H = My_Interface.h

CON_O = My_Controller.o
CON_CPP = My_Controller.cpp
CON_H = My_Controller.h

F_O = My_Field.o
F_CPP = My_Field.cpp
F_H = My_Field.h

PNT_O = My_Point2D.o
PNT_CPP = My_Point2D.cpp

CL_O = My_Cluster.o
CL_CPP = My_Cluster.cpp

GR_O = My_Group2D.o
GR_CPP = My_Group2D.cpp

HEAD = My_Classes.h

a.out:  $(INT_O) $(CON_O) $(F_O) $(PNT_O) $(GR_O) $(CL_O) My_Poisk.o My_Type1.o My_Type2.o My_Type3.o My_Type4.o My_Type5.o main.o
	g++ $(INT_O) $(CON_O) $(F_O) $(PNT_O) $(GR_O) $(CL_O) My_Poisk.o My_Type1.o My_Type2.o My_Type3.o My_Type4.o My_Type5.o main.o

$(INT_O): $(INT_CPP) $(INT_H) $(CON_H) $(F_H) $(HEAD)
	g++ -c $(INT_CPP)

$(CON_O): $(CON_CPP) $(CON_H) $(F_H) $(HEAD)
	g++ -c $(CON_CPP)

$(F_O): $(F_CPP) $(F_H) $(HEAD)
	g++ -c $(F_CPP)

$(PNT_O): $(PNT_CPP) $(HEAD)
	g++ -c $(PNT_CPP)

$(GR_O): $(GR_CPP) $(HEAD)
	g++ -c $(GR_CPP)

$(CL_O): $(CL_CPP) $(HEAD)
	g++ -c $(CL_CPP)

My_Poisk.o: My_Poisk.cpp $(HEAD)
	g++ -c My_Poisk.cpp

My_Type1.o: My_Type1.cpp $(HEAD)
	g++ -c My_Type1.cpp

My_Type2.o: My_Type2.cpp $(HEAD)
	g++ -c My_Type2.cpp

My_Type3.o: My_Type3.cpp $(HEAD)
	g++ -c My_Type3.cpp

My_Type4.o: My_Type4.cpp $(HEAD)
	g++ -c My_Type4.cpp

My_Type5.o: My_Type5.cpp $(HEAD)
	g++ -c My_Type5.cpp