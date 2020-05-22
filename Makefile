CXX=g++
CXXFLAGS= -std=c++17 -Wall -pedantic -Wno-long-long -O2
EXECUTABLE=MatrixCalculator

.PHONY: all compile run clean doc

all: compile doc

compile: ${EXECUTABLE}

run: ${EXECUTABLE}
	./${EXECUTABLE}

clean:
	rm -f *.o
	rm -f ${EXECUTABLE}
	rm -rf doc/

doc: src/UI/CUIText.cpp src/UI/CUIText.h src/UI/CUserInterface.cpp src/UI/CUserInterface.h \
	src/Calculator/CCalculator.cpp src/Calculator/CCalculator.h \
	src/Matrix/CDenseMatrix.cpp src/Matrix/CDenseMatrix.h src/Matrix/CLinear.cpp src/Matrix/CLinear.h \
	src/Matrix/CMatrix.cpp src/Matrix/CMatrix.h src/Matrix/CSparseMatrix.cpp src/Matrix/CSparseMatrix.h \
	src/index.txt
	doxygen >/dev/null

${EXECUTABLE}: main.o \
               CUserInterface.o CUIText.o\
               CCalculator.o\
               CMatrix.o CDenseMatrix.o CSparseMatrix.o\
               CLinear.o
	${CXX} ${CXXFLAGS} $^ -o ${EXECUTABLE}

%.o:
	${CXX} ${CXXFLAGS} -c $< -o $@

main.o: src/main.cpp src/UI/CUserInterface.h \
 src/UI/../Calculator/CCalculator.h \
 src/UI/../Calculator/../Matrix/CMatrix.h \
 src/UI/../Calculator/../Matrix/CLinear.h \
 src/UI/../Calculator/../Matrix/../Exception/CExceptions.h

CExceptions.o: src/Exception/CExceptions.h

CCalculator.o: src/Calculator/CCalculator.cpp \
 src/Calculator/CCalculator.h src/Calculator/../Matrix/CMatrix.h \
 src/Calculator/../Matrix/CLinear.h \
 src/Calculator/../Matrix/../Exception/CExceptions.h

CDenseMatrix.o: src/Matrix/CDenseMatrix.cpp src/Matrix/CDenseMatrix.h \
 src/Matrix/CMatrix.h src/Matrix/../Exception/CExceptions.h

CLinear.o: src/Matrix/CLinear.cpp src/Matrix/CLinear.h \
 src/Matrix/../Exception/CExceptions.h src/Matrix/CMatrix.h

CMatrix.o: src/Matrix/CMatrix.cpp src/Matrix/CMatrix.h \
 src/Matrix/../Exception/CExceptions.h src/Matrix/CSparseMatrix.h \
 src/Matrix/CDenseMatrix.h

CSparseMatrix.o: src/Matrix/CSparseMatrix.cpp src/Matrix/CSparseMatrix.h \
 src/Matrix/CMatrix.h src/Matrix/../Exception/CExceptions.h

CUIText.o: src/UI/CUIText.cpp src/UI/CUIText.h

CUserInterface.o: src/UI/CUserInterface.cpp src/UI/CUserInterface.h \
 src/UI/../Calculator/CCalculator.h \
 src/UI/../Calculator/../Matrix/CMatrix.h \
 src/UI/../Calculator/../Matrix/CLinear.h \
 src/UI/../Calculator/../Matrix/../Exception/CExceptions.h \
 src/UI/CUIText.h
