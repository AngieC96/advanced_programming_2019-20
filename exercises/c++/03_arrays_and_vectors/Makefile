CXX = c++
CXXFLAGS = -Wall -Wextra -g -std=c++11

SRC = 01_matrix_transpose.cc           \
      02_convert_argv_to_types.cc      \
      03_mean_and_median.cc            \
      04_01_avoid_repeated_words.cc       \
	  04_02_avoid_repeated_words.cc   \
#      05_use_std::map.cc               \
      Prova_template.cc
      

EXE = $(SRC:.cc=.x)

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cc .x

all: $(EXE)

.PHONY: all

%.x: %.cc 
	$(CXX) $< -o $@ $(CXXFLAGS)

format: $(SRC)
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this command"

.PHONY: format

clean:
	rm -f $(EXE) *~

.PHONY: clean
