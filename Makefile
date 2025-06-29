default: all

prepare:
	g++ Algorithms/wu_multi_pass/main.cpp -std=c++23 -O3 -I Algorithms/includes -o wu_multi_pass.out
	g++ Algorithms/wu_single_pass/main.cpp -std=c++23 -O3 -I Algorithms/includes -o wu_single_pass.out
	g++ Algorithms/wu_transformation/main.cpp -std=c++23 -O3 -I Algorithms/includes -o wu_transformation.out
	g++ Algorithms/gheibi_transformation/main.cpp -std=c++23 -O3 -I Algorithms/includes -o gheibi_transformation.out

test: astroph dimacs9 linux notredame wikipedia

clean:
	rm *.out *.in

all: prepare test clean




astroph:
	@echo "Preparing test AstroPh"
	./generator.py 40 200 5 10 1 > astroph.in < Data/ca-AstroPh/out.ca-AstroPh
	@echo "Testing wu_multi_pass: "
	./wu_multi_pass.out < astroph.in > wu_multi_pass_astroph.out
	@echo "Testing wu_single_pass: "
	./wu_single_pass.out < astroph.in > wu_single_pass_astroph.out
	@echo "Testing wu_transformation: "
	./wu_transformation.out < astroph.in > wu_transformation_astroph.out
	@echo "Testing gheibi_transformation: "
	./gheibi_transformation.out < astroph.in > gheibi_transformation_astroph.out
	./checker.py wu_multi_pass_astroph.out wu_single_pass_astroph.out wu_transformation_astroph.out gheibi_transformation_astroph.out

dimacs9:
	@echo "Preparing test Dimacs9"
	./generator.py 40 200 5 10 0 > dimacs9.in < Data/dimacs9-COL/out.dimacs9-COL
	@echo "Testing wu_multi_pass: "
	./wu_multi_pass.out < dimacs9.in > wu_multi_pass_dimacs9.out
	@echo "Testing wu_single_pass: "
	./wu_single_pass.out < dimacs9.in > wu_single_pass_dimacs9.out
	@echo "Testing wu_transformation: "
	./wu_transformation.out < dimacs9.in > wu_transformation_dimacs9.out
	@echo "Testing gheibi_transformation: "
	./gheibi_transformation.out < dimacs9.in > gheibi_transformation_dimacs9.out
	./checker.py wu_multi_pass_dimacs9.out wu_single_pass_dimacs9.out wu_transformation_dimacs9.out gheibi_transformation_dimacs9.out

linux:
	@echo "Preparing test Linux"
	./generator.py 40 200 5 10 0 > linux.in < Data/linux/out.linux
	@echo "Testing wu_multi_pass: "
	./wu_multi_pass.out < linux.in > wu_multi_pass_linux.out
	@echo "Testing wu_single_pass: "
	./wu_single_pass.out < linux.in > wu_single_pass_linux.out
	@echo "Testing wu_transformation: "
	./wu_transformation.out < linux.in > wu_transformation_linux.out
	@echo "Testing gheibi_transformation: "
	./gheibi_transformation.out < linux.in > gheibi_transformation_linux.out
	./checker.py wu_multi_pass_linux.out wu_single_pass_linux.out wu_transformation_linux.out gheibi_transformation_linux.out

notredame:
	@echo "Preparing test NotreDame"
	./generator.py 40 200 5 10 0 > notredame.in < Data/web-NotreDame/out.web-NotreDame
	@echo "Testing wu_multi_pass: "
	./wu_multi_pass.out < notredame.in > wu_multi_pass_notredame.out
	@echo "Testing wu_single_pass: "
	./wu_single_pass.out < notredame.in > wu_single_pass_notredame.out
	@echo "Testing wu_transformation: "
	./wu_transformation.out < notredame.in > wu_transformation_notredame.out
	@echo "Testing gheibi_transformation: "
	./gheibi_transformation.out < notredame.in > gheibi_transformation_notredame.out
	./checker.py wu_multi_pass_notredame.out wu_single_pass_notredame.out wu_transformation_notredame.out gheibi_transformation_notredame.out

wikipedia:
	@echo "Preparing test Wikipedia"
	./generator.py 40 200 5 10 0 > wikipedia.in < Data/wikipedia_link_io/out.wikipedia_link_io
	@echo "Testing wu_multi_pass: "
	./wu_multi_pass.out < wikipedia.in > wu_multi_pass_wikipedia.out
	@echo "Testing wu_single_pass: "
	./wu_single_pass.out < wikipedia.in > wu_single_pass_wikipedia.out
	@echo "Testing wu_transformation: "
	./wu_transformation.out < wikipedia.in > wu_transformation_wikipedia.out
	@echo "Testing gheibi_transformation: "
	./gheibi_transformation.out < wikipedia.in > gheibi_transformation_wikipedia.out
	./checker.py wu_multi_pass_wikipedia.out wu_single_pass_wikipedia.out wu_transformation_wikipedia.out gheibi_transformation_wikipedia.out