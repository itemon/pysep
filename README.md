# parse pinyin sequence, separating them item by item

## how to use
```c
pinyin_col_t *pyc = parse_pinyin_col("baijuyi");

for (size_t i = 0; i < pyc->cap; ++i) {
  char *syl = pyc->seq[i];
  printf("syllable %s\n", syl);
}

debug_pinyin_col(pyc);
dispose_pinyin_col(pyc);

//[pinyin_parser]3 syllable(-1):
//[pinyin_parser]bai
//[pinyin_parser]ju
//[pinyin_parser]yi
```