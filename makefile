a.out: My_Point2d.o My_Group2D.o My_Field.o My_Controller.o My_Interface.o main.o
	g++ My_Point2d.o My_Group2D.o My_Field.o My_Controller.o My_Interface.o main.o

My_Point2d.o: My_Point2d.cpp My_Point2d.h
	g++ -c My_Point2d.cpp

My_Group2D.o: My_Group2D.cpp My_Group2D.h
	g++ -c My_Group2D.cpp

My_Field.o: My_Field.cpp My_Field.h
	g++ -c My_Field.cpp

My_Controller.o: My_Controller.cpp My_Controller.h
	g++ -c My_Controller.cpp

My_Interface.o: My_Interface.cpp My_Interface.h
	g++ -c My_Interface.cpp

main.o: main.cpp My_Interface.h
	g++ -c main.cpp