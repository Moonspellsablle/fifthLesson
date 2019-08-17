#include <iostream>
#include <cstdint>
 
bool isOperationNeedToProceed(char *userInput, const char *command) {
  for (size_t i = 0; command[i] != '\0'; ++i) {
    if ((command[i] != userInput[i])) {
      return false;
    }
  }
  return true;
}
 
uint16_t getArrayLen(char *arrayOfData) {
  uint16_t i = 0;
  while (arrayOfData[i] != '\0') {
    ++i;
  }
  return i;
}
 
void *clearArray(char *buffer, uint16_t value, uint16_t len) {
  char *p = buffer;
  for (; len > 0; ++p, --len) {
    *p = value;
  }
  return buffer;
}

void printLogic(char *mainBuffer, char *userValue, const uint16_t &BUFFER_SIZE, char *beginOfMainBuffer, char *endOfMainBuffer, int16_t &movePosition) {
  
  uint16_t lenOfBuffer = getArrayLen(mainBuffer);
  uint16_t lenOfUserData = getArrayLen(userValue);
 
  if ((beginOfMainBuffer == nullptr) || (endOfMainBuffer == nullptr)) {
    beginOfMainBuffer = (mainBuffer + lenOfBuffer);
    endOfMainBuffer = mainBuffer + lenOfBuffer + (lenOfUserData - 1);
  } else {
    beginOfMainBuffer = mainBuffer + movePosition;
  }

  char leftPartOfBuffer[BUFFER_SIZE];
  char rightPartOfBuffer[BUFFER_SIZE];

  uint8_t i = 0;
  clearArray(leftPartOfBuffer, 0, sizeof leftPartOfBuffer);
  for (char *leftPart = mainBuffer; leftPart < beginOfMainBuffer; ++leftPart, ++i) {
    leftPartOfBuffer[i] = *leftPart;
  }
  
  i = 0;
  clearArray(rightPartOfBuffer, 0, sizeof rightPartOfBuffer);
  for (char *rightPart = beginOfMainBuffer; rightPart < (mainBuffer + lenOfBuffer); ++rightPart, ++i) {
    rightPartOfBuffer[i] = *rightPart;
  }
  std::cout <<  "leftPart: " << leftPartOfBuffer << std::endl;
  std::cout <<  "rightPart: " << rightPartOfBuffer << std::endl;

  if (getArrayLen(rightPartOfBuffer) > 0) {
    clearArray(mainBuffer, 0, sizeof mainBuffer);
    char *mainBufferPtr = mainBuffer;
    for (char *leftPartPtr = leftPartOfBuffer; leftPartPtr < leftPartOfBuffer + getArrayLen(leftPartOfBuffer); ++leftPartPtr, ++mainBufferPtr) {
      *mainBufferPtr = *leftPartPtr;
    }
    for (char *userInputPtr = userValue; userInputPtr < userValue + getArrayLen(userValue); ++userInputPtr, ++mainBufferPtr) {
      *mainBufferPtr = *userInputPtr;
    }
    for (char *rightPartPtr = rightPartOfBuffer; rightPartPtr < rightPartOfBuffer + getArrayLen(rightPartOfBuffer); ++rightPartPtr, ++mainBufferPtr) {
      *mainBufferPtr = *rightPartPtr;
    }
    movePosition += getArrayLen(userValue);
  } else {
    for (char *beginUserValue = userValue; beginUserValue < (userValue + lenOfUserData); ++beginUserValue) {
      *beginOfMainBuffer = *beginUserValue;
      ++beginOfMainBuffer;
    }
    movePosition = getArrayLen(mainBuffer);
  }

  std::cout << mainBuffer << std::endl;
}

void clearLogic(char *mainBuffer, char *beginOfMainBuffer, char *endOfMainBuffer, int16_t &movePosition) {
  clearArray(mainBuffer, 0, sizeof mainBuffer);
  movePosition = 0;
  beginOfMainBuffer = nullptr;
  endOfMainBuffer = nullptr;
  std::cout << "***Cleared***" << std::endl;
}
    
void moveLogic(char *mainBuffer, const uint16_t &BUFFER_SIZE, char *beginOfMainBuffer, char *endOfMainBuffer, int16_t &movePosition) {
  char direction[BUFFER_SIZE];
  uint16_t userValue;
  uint16_t lenOfBuffer = getArrayLen(mainBuffer);  

  std::cin >> direction >> userValue;
  if (isOperationNeedToProceed(direction, "left")) {
    //std::cout << "move position: " << movePosition << std::endl;
    movePosition -= userValue;
    //std::cout << "move position: " << movePosition << std::endl;
    if (movePosition < 0) {
      movePosition = 0;
    }
  } else if (isOperationNeedToProceed(direction, "right")) {
    movePosition += userValue;
    if (movePosition > lenOfBuffer) {
      movePosition = lenOfBuffer;
    }
  }
}

void copyLogic(char *mainBuffer, char *bufferForCopyPaste, uint16_t &leftPosition, uint16_t &rightPosition) {
  clearArray(bufferForCopyPaste, 0, sizeof bufferForCopyPaste);
  if (leftPosition < rightPosition) {
    if (leftPosition < 1) {
      leftPosition = 1;
    }
    if (rightPosition > getArrayLen(mainBuffer)) {
      rightPosition = getArrayLen(mainBuffer);
    }
    for (char *charBufferPtr = (mainBuffer + (leftPosition - 1)), *copiedBufferPtr = bufferForCopyPaste; charBufferPtr <= (mainBuffer + (rightPosition - 1)); ++charBufferPtr, ++copiedBufferPtr) {
      *copiedBufferPtr = *charBufferPtr;
    }
    //std::cout <<"***SaveToBuffer***\t" << bufferForCopyPaste << std::endl;
  }
}

void cutLogic(char *mainBuffer, const uint16_t &BUFFER_SIZE, uint16_t &leftPosition, uint16_t &rightPosition, int16_t &movePosition, uint16_t &lenOfBuffer, char *beginOfMainBuffer, char *endOfMainBuffer) {
  char tempNewBuffer[BUFFER_SIZE];
  uint16_t i = 1;
  for (char *bufferPtr = mainBuffer, *tempNewBufferPtr = tempNewBuffer; bufferPtr < mainBuffer + getArrayLen(mainBuffer); ++bufferPtr, ++i){
    if (((i > 0) && (i < leftPosition)) || ((i > rightPosition) && (i <= getArrayLen(mainBuffer)))) {
      *tempNewBufferPtr = *bufferPtr;
      ++tempNewBufferPtr;
    }
  }
  clearArray(mainBuffer, 0, sizeof mainBuffer);
  for (char *bufferPtr = mainBuffer, *tempNewBufferPtr = tempNewBuffer; tempNewBufferPtr < tempNewBuffer + getArrayLen(tempNewBuffer); ++bufferPtr, ++tempNewBufferPtr) {
    *bufferPtr = *tempNewBufferPtr;
  }
  std::cout << tempNewBuffer << std::endl;
  if (movePosition > rightPosition) {
    beginOfMainBuffer = mainBuffer + (movePosition - (rightPosition - leftPosition + 1));
    endOfMainBuffer = mainBuffer + (lenOfBuffer - (rightPosition - leftPosition + 1));
    movePosition -= (rightPosition - leftPosition + 1);
    std::cout << movePosition << std::endl;
  }
}
  
void dialogueWithUser(char *operationFromUser) {
  if (!(std::cin >> operationFromUser)
  || (!(isOperationNeedToProceed(operationFromUser, "print"))
  && !(isOperationNeedToProceed(operationFromUser, "select"))
  && !(isOperationNeedToProceed(operationFromUser, "copy"))
  && !(isOperationNeedToProceed(operationFromUser, "paste"))
  && !(isOperationNeedToProceed(operationFromUser, "move"))
  && !(isOperationNeedToProceed(operationFromUser, "cut"))
  && !(isOperationNeedToProceed(operationFromUser, "show"))
  && !(isOperationNeedToProceed(operationFromUser, "clear")))) {
    std::cout << "\n[You can use only following commands]:"
    << std::endl << "print"
    << std::endl << "select [startRangeValue] [endRangeValue]"
    << std::endl << "copy"
    << std::endl << "paste"
    << std::endl << "move left [value]"
    << std::endl << "move right [value]"
    << std::endl << "cut"
    << std::endl << "show"
    << std::endl
    << std::endl << "Enter an operation again!: "
    << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
    }
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
 
  int16_t movePosition = 0;
 
  const uint16_t BUFFER_SIZE = 100;
  char mainBuffer[BUFFER_SIZE]{};
  uint16_t lenOfBuffer;
  uint16_t lenOfUserData;
 
  char *beginOfMainBuffer = nullptr;
  char *endOfMainBuffer = nullptr;

  char bufferForCopyPaste[BUFFER_SIZE]{};

  uint16_t leftPosition = 0;
  uint16_t rightPosition = 0;
 
  while (1) {
    std::cout << "Enter an operation to proceed: ";
    char operationFromUser[BUFFER_SIZE];
    dialogueWithUser(operationFromUser);


    if (isOperationNeedToProceed(operationFromUser, printCommand)) {
      char userValue[BUFFER_SIZE]{};
      std::cin >> userValue;
      printLogic(mainBuffer, userValue, BUFFER_SIZE, beginOfMainBuffer, endOfMainBuffer, movePosition);
    }
   
    if (isOperationNeedToProceed(operationFromUser, clearCommand)) {
      clearLogic(mainBuffer, beginOfMainBuffer, endOfMainBuffer, movePosition);
    }
 
    if (isOperationNeedToProceed(operationFromUser, showCommand)) {
      std::cout << mainBuffer << std::endl;
    }

    if (isOperationNeedToProceed(operationFromUser, moveCommand)) {
      moveLogic(mainBuffer, BUFFER_SIZE, beginOfMainBuffer, endOfMainBuffer, movePosition);
      lenOfBuffer = getArrayLen(mainBuffer);  
      beginOfMainBuffer = mainBuffer + movePosition;
      endOfMainBuffer = mainBuffer + lenOfBuffer;
      std::cout << "movePosition: " << movePosition << std::endl;
      std::cout << "lenOfBuffer: " << lenOfBuffer << std::endl;
      std::cout << "begin: " << beginOfMainBuffer << " end: " << endOfMainBuffer << std::endl;  
    }

    if (isOperationNeedToProceed(operationFromUser, selectCommand)) {
      std::cin >> leftPosition >> rightPosition;
      //std::cout << leftPosition << std::endl;
      //std::cout << rightPosition << std::endl;
    }

    if (isOperationNeedToProceed(operationFromUser, copyCommand)) {
      copyLogic(mainBuffer, bufferForCopyPaste, leftPosition, rightPosition);
    }

    if (isOperationNeedToProceed(operationFromUser, cutCommand)) {
      copyLogic(mainBuffer, bufferForCopyPaste, leftPosition, rightPosition);
      cutLogic(mainBuffer, BUFFER_SIZE, leftPosition, rightPosition, movePosition, lenOfBuffer, beginOfMainBuffer, endOfMainBuffer);
    }

    if (isOperationNeedToProceed(operationFromUser, pasteCommand)) {
      printLogic(mainBuffer, bufferForCopyPaste, BUFFER_SIZE, beginOfMainBuffer, endOfMainBuffer, movePosition);
    }
  }
  return 0;
}
 
