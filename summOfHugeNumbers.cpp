#include <iostream>
#include <stdint.h>

int main() {
  std::cout << "Enter a first huge number: ";
  std::string firstHugeNumber;
  std::cin >> firstHugeNumber;

  std::cout << "Enter a second huge number: ";
  std::string secondHugeNumber;
  std::cin >> secondHugeNumber;

  uint32_t lenOfFirstHugeNumber = firstHugeNumber.length();
  uint32_t lenOfSecondHugeNumber = secondHugeNumber.length();

  uint32_t lenOfLargeNumber;
  lenOfLargeNumber = (lenOfFirstHugeNumber > lenOfSecondHugeNumber) ? lenOfFirstHugeNumber : lenOfSecondHugeNumber;
  
  uint32_t sumOfSingleElement = 0;
  uint16_t nextBitDiget = 0;
  std::string resultStr;

  for (int iteratorToLeft = lenOfLargeNumber; iteratorToLeft > 0; --iteratorToLeft) {
    const uint16_t ASCII_DIGIT_SHIFT = 48;
    char elementFirst = (lenOfFirstHugeNumber > (lenOfLargeNumber - iteratorToLeft)) ? 
                        firstHugeNumber[lenOfFirstHugeNumber - 1 - (lenOfLargeNumber - iteratorToLeft)] : 
                        '0';
    char elementSecond = (lenOfSecondHugeNumber > (lenOfLargeNumber - iteratorToLeft)) ? 
                        secondHugeNumber[lenOfSecondHugeNumber - 1 - (lenOfLargeNumber - iteratorToLeft)] : 
                        '0';
    sumOfSingleElement = int(elementFirst - ASCII_DIGIT_SHIFT) + int(elementSecond - ASCII_DIGIT_SHIFT) + nextBitDiget;
    nextBitDiget = (sumOfSingleElement / 10) % 10;

    if (iteratorToLeft != 1) {
      resultStr = char((sumOfSingleElement % 10) + ASCII_DIGIT_SHIFT) + resultStr;
    } else {
      resultStr = char((sumOfSingleElement % 10) + ASCII_DIGIT_SHIFT) + resultStr;
      if ((sumOfSingleElement / 10) != 0) {
        resultStr = char((sumOfSingleElement / 10) + ASCII_DIGIT_SHIFT) + resultStr;
      }
    }
  }
  std::cout << std::endl << "Result: " << std::endl;
  std::cout << resultStr << std::endl;

  return 0;
}
