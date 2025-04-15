target = main.cpp
output = main
flags = 
all:$(output)
	./$(output)

$(output): $(target)
	g++ $(flags) $(target) -o $(output)
clean:
	rm -f $(output)
