#include <iostream>
#include <stdint.h>
#include <cmath>

bool isOperationNeedToProceed(char *userInput, const char *command) {
  for (size_t i = 0; command[i] != '\0'; ++i) {
    if ((command[i] != userInput[i])) {
      return false;
    }
  }
  return true;
}

int main() {
  const char printCommand[] = "print";
  const char selectCommand[] = "select";
  const char copyCommand[] = "copy";
  const char pasteCommand[] = "paste";
  const char moveCommand[] = "move";
  const char cutCommand[] = "cut";
  const char showCommand[] = "show";
  const char clearCommand[] = "clear";

  while (1) {
    std::cout << "Enter an operation to proceed: ";
    char operationFromUser[100];
    //char valueFormUser[100];
    if (!(std::cin >> operationFromUser) 
    || (!(isOperationNeedToProceed(operationFromUser, printCommand))
    && !(isOperationNeedToProceed(operationFromUser, selectCommand))
    && !(isOperationNeedToProceed(operationFromUser, copyCommand))
    && !(isOperationNeedToProceed(operationFromUser, pasteCommand))
    && !(isOperationNeedToProceed(operationFromUser, moveCommand))
    && !(isOperationNeedToProceed(operationFromUser, cutCommand))
    && !(isOperationNeedToProceed(operationFromUser, showCommand))
    && !(isOperationNeedToProceed(operationFromUser, clearCommand)))) {
      std::cout << "\n[You can use only following commands]:" 
      << std::endl << "print" 
      << std::endl << "select" 
      << std::endl << "copy" 
      << std::endl << "paste" 
      << std::endl << "move left" 
      << std::endl << "move right" 
      << std::endl << "cut" 
      << std::endl << "show"
      << std::endl
      << std::endl << "Enter an operation again!: "
      << std::endl;
      std::cin.clear();
      //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
    }
    if (isOperationNeedToProceed(operationFromUser, printCommand) || 
        isOperationNeedToProceed(operationFromUser, selectCommand) || 
        isOperationNeedToProceed(operationFromUser, moveCommand)) {
      char valueFormUser[100];
      if (std::cin >> valueFormUser) {
        std::cout << "Need to implement Facking Logic! Facking shit!" << std::endl;
      }
    }   
  }
  
  return 0;
}
