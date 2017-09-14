CC = icpc
CFLAGS = -O3 -std=c++11
LDFLAGS = -lcilkrts
LDFLAGS += -lmkl_blas95_ilp64 -lmkl_intel_ilp64 -lmkl_core -lmkl_intel_thread -lmkl_gf_ilp64 -openmp

O_cgd = cgDNA.o
X_cgd = cgDNA

all : cgd

cgd: $(O_cgd)
	$(CC) $(CFLAGS) $(O_cgd) -o $(X_cgd) $(LDFLAGS)

%.o : %.cc
	@echo " - Compiling $<..."
	$(CC) $(CFLAGS) -c $<

clean:
	@rm *.o $(EXE)

