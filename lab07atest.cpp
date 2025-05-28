// lab07atest.cpp

#include "WordCount.h"
#include "tddFuncs.h"
#include <sstream>
#include <string>

int main() {
  WordCount wc;

  wc.addAllWords("Sentence is a fun fun sentence");

  
  std::ostringstream out1;
  wc.dumpWordsSortedByWord(out1);
  std::string result1 = out1.str();
  std::string expected1 = "sentence,2\nis,1\nfun,2\na,1\n";
  assertEquals(expected1, result1, "dumpWordsSortedByWord()", __LINE__);

  std::ostringstream out2;
  wc.dumpWordsSortedByOccurence(out2);
  std::string result2 = out2.str();
  std::string expected2 = "a,1\nis,1\nfun,2\nsentence,2\n";
  assertEquals(expected2, result2, "dumpWordsSortedByOccurence()", __LINE__);

  return 0;
}
