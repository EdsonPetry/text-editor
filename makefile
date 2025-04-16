target = main.cpp
output = main
flags = 

all: $(output)
	@echo "Build complete. Use \`make run ARGS=\"your args\"\` to run with arguments."

build: $(output)

$(output): $(target)
	g++ $(flags) $(target) -o $(output)

run: $(output)
	./$(output) $(ARGS)

clean:
	rm -f $(output)
