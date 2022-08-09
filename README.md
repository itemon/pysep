# pysep
拆分拼音字符串，按字拆开，例如libai拆分为li bai。方便计算名字的首写字母组合等。

## 如何使用
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