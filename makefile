a.out:  My_Point2d.o My_Group2D.o My_Cluster.o My_Poisk.o My_Type1.o My_Type3.o My_Field.o My_Controller.o My_Interface.o main.o
	g++ My_Point2d.o My_Group2D.o My_Cluster.o My_Poisk.o My_Type1.o My_Type3.o My_Field.o My_Controller.o My_Interface.o main.o

My_Point2d.o: My_Point2d.cpp My_Classes.h
	g++ -c My_Point2d.cpp

My_Group2D.o: My_Group2D.cpp My_Classes.h
	g++ -c My_Group2D.cpp

My_Cluster.o: My_Cluster.cpp My_Classes.h
	g++ -c My_Cluster.cpp

My_Poisk.o: My_Poisk.cpp My_Classes.h
	g++ -c My_Poisk.cpp

My_Type1.o: My_Type1.cpp My_Classes.h
	g++ -c My_Type1.cpp

My_Type3.o: My_Type3.cpp My_Classes.h
	g++ -c My_Type3.cpp

My_Field.o: My_Field.cpp My_Field.h My_Classes.h
	g++ -c My_Field.cpp

My_Controller.o: My_Controller.cpp My_Controller.h
	g++ -c My_Controller.cpp

My_Interface.o: My_Interface.cpp My_Interface.h
	g++ -c My_Interface.cpp

main.o: main.cpp My_Interface.h
	g++ -c main.cpp