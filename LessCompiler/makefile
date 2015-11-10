CXXFLAGS= -std=c++11 
toCSS: Context.o SyntaxAnalysisor.o File.o expression.o LessCompiler.o
	g++ -o $@ $^ -std=c++11
clean:
	rm *.o

