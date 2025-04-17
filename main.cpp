#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdlib> // for system()

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
void clearScreen() {
    // For Linux/macOS
    std::system("clear");

    // For Windows (if needed)
    // std::system("cls");
}
// Used to display
void DisplayText(std::vector<std::string> lines,uint cursor){
  clearScreen();
  for (size_t i = 0; i < lines.size(); ++i) {
    if (i != cursor){
    std::cout << "\t" << i << ": " << lines[i] << "\n";
    }else{
    std::cout << ">" << "\t"  << i << ": " << lines[i] << "\n";
    }
  }
  if (cursor >= lines.size()){
    std::cout << ">" << "\t" << cursor << ":  \n";
  }


}
bool startsWith(const std::string& str, const std::string& prefix) {
    return str.rfind(prefix, 0) == 0;
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
  //printArray(lines);
  // Here we grab the file lines and parse it into an array

  std::string input;
  std::cout << "Enter something (type 'exit' to quit):\n";
  uint cursor = 0;
  // This loop will keep running until the user types "exit"
  while (true) {
    DisplayText(lines,cursor);
    std::cout << "> ";
    std::getline(std::cin, input);  // reads a full line including spaces

    if (input == "exit") {
        break;
    }else if (input == "j")
    {
      cursor++;
    }
    else if (input == "k"){
      cursor--;
    }else if(input == "H"){ // Top of file
      cursor = 0;
    }else if(input == "M"){ // Middle of file
      cursor = lines.size() / 2;
    }else if(input == "L"){ // Bottom of file
      cursor = lines.size()-1;
    }
    else if(startsWith(input,"e ")){
     std::cout << "Going into edit mode (Gotta implement This)\n" ; 
    }
    else{
    std::cout << "You entered: " << input << "\n";

    }

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
