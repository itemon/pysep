//
//  pinyin_parser.h
//  tang
//
//  Created by 黄伟 on 2022/8/7.
//

#ifndef pinyin_parser_h
#define pinyin_parser_h

#include <stdio.h>

typedef enum {
  no_token_error,
  illegal_token_error,
  illegal_suffix_token_error,
} syllable_token_error;

#define PINYIN_OFFSET_AFTER_TRAILLING -1

typedef struct {
  size_t cap;
  size_t offset;
  syllable_token_error error;
  char **seq;
} pinyin_col_t;

typedef enum {
  undefined_state,
  prefix_syllable_state,
  syllable_done_state,
} syllable_state;

const static char *prefix_syllable[] = {
  "zh",
  "ch",
  "sh",
  "r",
  "z",
  "c",
  "s",

  "b",
  "p",
  "m",
  "f",
  "d",
  "t",
  "n",
  "l",
  
  "g",
  "k",
  "h",
  "j",
  "q",
  "x",
};

const static size_t prefix_syllable_size = 21;

// normal col
const static char *suffix_syllable_nor_col[] = {
  "ang",
  "eng",
  "ong",
  "an",
  "en",

  "er",
  "ai",
  "ei",
  "ao",
  "ou",
  
  "a",
  "o",
  "e",
  "ê",
};
const static size_t suffix_syllable_nor_col_size = 14;

// i col
const static char *suffix_syllable_i_col[] = {
  "iang",
  "iong",
  
  "iao",
  "ian",
  "ing",

  "ia",
  "ie",
  "iu",//i(o)u -> iu
  
  "in",
  
  "i",
};

const static char *suffix_syllable_i_col_std[] = {
  "yang",
  "ying",
  "yong",
  
  "yao",
  "you",//iou -> you
  "yan",
  "yin",

  "yi",
  "ya",
  "ye",
};

const static size_t suffix_syllable_i_col_size = 10;

// u col
const static char *suffix_syllable_u_col[] = {
  "uang",
  "ueng",
  
  "uai",
  "uan",

  "ua",
  "uo",
  "ui",//u(e)i
  "un",//u(e)n
  
  "u",
};
const static char *suffix_syllable_u_col_std[] = {
  "wang",
  "weng",
  
  "wai",
  "wei",//uei -> wei
  "wan",
  "wen",//uen -> wen

  "wu",
  "wa",
  "wo",
};
const static size_t suffix_syllable_u_col_size = 9;

// yu col
const static char *suffix_syllable_yu_col[] = {
  "üan",
  
  "üe",
  "ün",
  "ü",
};
const static char *suffix_syllable_yu_col_std[] = {
  "yuan",
  
  "yue",
  "yun",
  
  "yu",
};
const static size_t suffix_syllable_yu_col_size = 4;


pinyin_col_t *parse_pinyin_col(const char *pinyin_seq);

void debug_pinyin_col(pinyin_col_t *pinyin_col);

void dispose_pinyin_col(pinyin_col_t *pinyin_col);

#endif /* pinyin_parser_h */