#include <stdio.h>
#include <string.h>
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
    "erhua",
    "xi an"
  };

  for (size_t i = 0; i < 6; ++i) {
    char *seq = names[i];
    pinyin_col_t *pyc = parse_pinyin_col(seq);
    debug_pinyin_col(pyc);
    dispose_pinyin_col(pyc);
  }

  /*char *chr = "xi’an";
  size_t chr_len = strlen(chr);
  for (size_t i = 0; i < chr_len; ++i) {
    printf("=>%d", (int)chr[i]);
  }
  printf("chr size is %ld\n", strlen(chr));
  char buf[32];
  strncpy(buf, chr, 4);
  puts(buf);
  */

  return 0;
}
