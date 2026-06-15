CXX = clang++
CFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Werror -MMD
TARGET = shenzhen

SRCS = $(shell find src -name '*.cpp')
OBJS = $(SRCS:src/%.cpp=.build/%.o)
DEPS = $(SRCS:src/%.cpp=.build/%.d)
 
$(shell mkdir -p .build)

debug: CFLAGS += -O0 -ggdb3 -DDEBUG
debug: $(TARGET)

release: CFLAGS += -O3 -flto  -DNDEBUG
release: $(TARGET)

# Link target
$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $^ -o $@

# Compile sources
.build/%.o: src/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm .build/* 2>/dev/null

-include $(DEPS)
.SILENT:
.PHONY: debug release clean