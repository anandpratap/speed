CFLAGS = -openmp -wd588 -c -I/usr/include/python2.6 -fPIC -lpthread
CXX = icpc
SRC = api_wrap.cxx api.cpp metric.cpp bc.cpp flux.cpp residual.cpp solver.cpp utils.cpp integrator.cpp io.cpp force.cpp recon.cpp
OBJ = $(SRC:.cpp = .o)

all: pre-build main-build
pre-build:
	swig -c++ -python api.i
main-build: $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ)
	icpc -shared *.o -o _api.so -openmp
clean:
	rm -f core *.o *~ *.so *.cxx
