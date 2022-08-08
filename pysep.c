#include <stdio.h>
#include "pinyin_parser.h"

int main(int argc, char **argv) {
  // test with some pinyin data
  pinyin_col_t *pyc = parse_pinyin_col("baijuyi");
  debug_pinyin_col(pyc);
  dispose_pinyin_col(pyc);


  char *names[] = {
    "luobinwang",
    "li bai",
    "lib",
    "hanyu",
    "erhua"
  };

  for (size_t i = 0; i < 5; ++i) {
    char *seq = names[i];
    pinyin_col_t *pyc = parse_pinyin_col(seq);
    debug_pinyin_col(pyc);
    dispose_pinyin_col(pyc);
  }

  return 0;
}
