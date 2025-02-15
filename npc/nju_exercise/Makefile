TOPNAME = top
#TOPNAME = mux41_2bit
#exercise 6 shift_reg BarrelShifter
#constain file dir
NXDC_FILES = constr/$(TOPNAME).nxdc
INC_PATH ?=

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)


VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert



#VSRCS = $(wildcard ./vsrc/**/*.v ./vsrc/*.v)
#CSRCS = $(wildcard ./csrc/**/*.c ./csrc/*.cpp ./csrc/**/*.cc)

$(shell mkdir -p $(BUILD_DIR)) #will be execute after make

# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@


# project source
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v") #abspath = absoute path
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
# # Project source excluding testbenches
# CSRCS = $(filter-out $(wildcard ./csrc/*_tb.cpp), $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp"))
# #CSRCS = $(filter-out $(wildcard ./csrc/*_tb.cpp), $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp"))
CSRCS += $(SRC_AUTO_BIND)

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
INCFLAGS = $(addprefix -I, $(INC_PATH))  #add prefix
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\"" 


#verilator
$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))
# -o specify the path to the output (executable)

all:$(BIN)	
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	#$(BIN) +trace  # turn on the wave
	$(VERILATOR)  --cc --exe --build --trace-fst -j 0 \
		--top-module $(TOPNAME)\
		$(VSRCS) $(abspath ./tb_csrc/$(TOPNAME)_tb.cpp)
	./obj_dir/V$(TOPNAME)
	gtkwave waveform.fst 



run: $(BIN)
	@$^


#$(VERILATOR) --cc --exe --build --trace-fst -j 0 -Wall top.v top_tb.cpp 

#verilator --cc --exe --build --trace-fst -j 0 -Wall top.v top_tb.cpp 

clean:
	rm -rf $(BUILD_DIR)
	rm -r ./obj_dir


include ../Makefile
