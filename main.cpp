#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

// returns the lines of a file in the form of a array
std::vector<std::string> toVect(std::fstream& file){
  std::vector<std::string> myStrings;
  std::string line;
  while (std::getline(file, line)) {
      // Process each line as a string
      //std::cout << "Read line: " << line << "\n";
      myStrings.push_back(line);
  }
  return myStrings;

}
void printArray(std::vector<std::string> fileRows){
  for (size_t i = 0; i < fileRows.size(); ++i) {
    std::cout << i << ": " << fileRows[i] << "\n";
}

}
std::ofstream createFile(const std::string& filename){
  std::ofstream MyFile(filename);

  // Write to the file
  MyFile << "{textEditor name} just created " << filename << "\n";
  return MyFile;
}

int main(int argc, char* argv[]) {
  if (argc < 2){
    std::cout << "usage" << argv[0] << "{File}";
    return -1;
  }
  std::string filename = argv[1];

  // If file doesn't exist, create it
  if (!std::filesystem::exists(filename)) {
      std::ofstream createFile(filename); // creates the file
      if (!createFile) {
          std::cerr << "Failed to create file.\n";
          return -1;
      }
      createFile << "{textEditor name} just created\t" << filename << "\n";
      createFile.close();
  } 
  // open up the files again
  std::fstream EditFile(filename, std::ios::in | std::ios::out | std::ios::app);
  if (!EditFile) {
      std::cerr << "Failed to open file.\n";
      return -1;
  }
  std::vector<std::string> lines = toVect(EditFile);
  printArray(lines);
  return 0;
  // Here we grab the file lines and parse it into an array

  std::string input;
  std::cout << "Enter something (type 'exit' to quit):\n";

  // This loop will keep running until the user types "exit"
  while (true) {
      std::cout << "> ";
      std::getline(std::cin, input);  // reads a full line including spaces

      if (input == "exit") {
          break;
      }

      std::cout << "You entered: " << input << "\n";
  }

  std::cout << "Goodbye!\n";
  return 0;
  /*std::ifstream inFile("text1.txt");
  if (!inFile) {
        std::cout << "Failed to open input.txt for reading.\n";
        return 1;
    }
  
  std::string line;
  std::vector<std::string> lines = toVect(inFile);
  printArray(lines);
  
  inFile.close(); */                     // close the file (also happens automatically at destruction)
  return 0;
}
