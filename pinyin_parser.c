//
//  pinyin_parser.c
//  tang
//
//  Created by 黄伟 on 2022/8/7.
//

#include "pinyin_parser.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

pinyin_col_t *parse_pinyin_col(const char *pinyin_seq) {
  pinyin_col_t *rlt = (pinyin_col_t *)malloc(sizeof(pinyin_col_t));
  memset(rlt, 0, sizeof(pinyin_col_t));
  
  size_t init_size = 8;
  char **syllable = (char **)malloc(sizeof(char *) * init_size);
  memset(syllable, 0, sizeof(char *) * init_size);

  size_t oft = 0;
  
#define ensure_syllable(prefix)\
  char *syl = (char *)malloc(strlen(prefix) + 1);\
  strcpy(syl, prefix);\
  syl[strlen(prefix) + 1] = '\0';\
  syllable[syllable_parsed_count] = syl;\
  syllable_parsed_count++;\
  state = syllable_done_state;\
  oft += strlen(prefix);
  
  size_t syllable_parsed_count = 0;
  syllable_state state = undefined_state;
  
  char *seq_cursor = (char *)pinyin_seq;
  char *prefix = "";
  
  while (1) {
    if (*seq_cursor == '\0' || !*seq_cursor) {
      break;
    }
    switch (state) {
      default:
      case syllable_done_state:
      case undefined_state: {
        // remove leading whitespace
        while (isspace(*seq_cursor)) {
          seq_cursor++;
          oft++;
        }
        // prefix match with leading syllable
        bool match_prefix_syllable = false;
        for (size_t i = 0; i < prefix_syllable_size; ++i) {
          if (strncmp(prefix_syllable[i], seq_cursor, strlen(prefix_syllable[i])) == 0) {
            state = prefix_syllable_state;
            match_prefix_syllable = true;
            seq_cursor += strlen(prefix_syllable[i]);
            prefix = (char *)prefix_syllable[i];
            break;
          }
        }
        
        if (!match_prefix_syllable) {
          bool done = false;
          // normal col
          for (size_t i = 0; i < suffix_syllable_nor_col_size; ++i) {
            prefix = (char *)suffix_syllable_nor_col[i];
            if (strncmp(prefix, seq_cursor, strlen(prefix)) == 0) {
              seq_cursor += strlen(prefix);
              
              ensure_syllable(prefix)
              done = true;
              break;
            }
          }
          
          if (!done) {
            for (size_t i = 0; i < suffix_syllable_i_col_size; ++i) {
              prefix = (char *)suffix_syllable_i_col_std[i];
              if (strncmp(prefix, seq_cursor, strlen(prefix)) == 0) {
                seq_cursor += strlen(prefix);
                
                ensure_syllable(prefix)
                done = true;
                break;
              }
            }
          }
          
          if (!done) {
            for (size_t i = 0; i < suffix_syllable_u_col_size; ++i) {
              prefix = (char *)suffix_syllable_u_col_std[i];
              if (strncmp(prefix, seq_cursor, strlen(prefix)) == 0) {
                seq_cursor += strlen(prefix);
                
                ensure_syllable(prefix)
                done = true;
                break;
              }
            }
          }
          
          if (!done) {
            for (size_t i = 0; i < suffix_syllable_yu_col_size; ++i) {
              prefix = (char *)suffix_syllable_yu_col_std[i];
              if (strncmp(prefix, seq_cursor, strlen(prefix)) == 0) {
                seq_cursor += strlen(prefix);
                
                ensure_syllable(prefix)
                done = true;
                break;
              }
            }
          }
          
          if (!done) {
            // prefix not match, suffix not match just return
            rlt->error = illegal_token_error;
            goto prepare;
          }
        }
        break;
      }
        
#pragma mark - define uniform loop fn
        
      case prefix_syllable_state: {
        while (isspace(*seq_cursor)){
          seq_cursor++;
          oft++;
        }
        bool done = false;
        
        // normal col
        for (size_t i = 0; i < suffix_syllable_nor_col_size; ++i) {
          char *suffix = (char *)suffix_syllable_nor_col[i];
          if (strncmp(suffix, seq_cursor, strlen(suffix)) == 0) {
            seq_cursor += strlen(suffix);
            
            char syl_txt[strlen(prefix) + strlen(suffix)];
            strcpy(syl_txt, prefix);
            strcat(syl_txt, suffix);
            
            ensure_syllable(syl_txt)
            done = true;
            break;
          }
        }
        
        if (!done) {
          for (size_t i = 0; i < suffix_syllable_i_col_size; ++i) {
            char *suffix = (char *)suffix_syllable_i_col[i];
            if (strncmp(suffix, seq_cursor, strlen(suffix)) == 0) {
              seq_cursor += strlen(suffix);
              
              char syl_txt[strlen(prefix) + strlen(suffix)];
              strcpy(syl_txt, prefix);
              strcat(syl_txt, suffix);
              
              ensure_syllable(syl_txt)
              done = true;
              break;
            }
          }
        }
        
        if (!done) {
          for (size_t i = 0; i < suffix_syllable_u_col_size; ++i) {
            char *suffix = (char *)suffix_syllable_u_col[i];
            if (strncmp(suffix, seq_cursor, strlen(suffix)) == 0) {
              seq_cursor += strlen(suffix);
              
              char syl_txt[strlen(prefix) + strlen(suffix)];
              strcpy(syl_txt, prefix);
              strcat(syl_txt, suffix);
              
              ensure_syllable(syl_txt)
              done = true;
              break;
            }
          }
        }
        
        if (!done) {
          for (size_t i = 0; i < suffix_syllable_yu_col_size; ++i) {
            char *suffix = (char *)suffix_syllable_yu_col[i];
            
            if (*prefix == 'j' || *prefix == 'q' || *prefix == 'x') {
              char tmp[strlen(suffix) + 1];
              strcpy(tmp, suffix);
              tmp[strlen(suffix) + 1] = '\0';
              tmp[0] = 'u';
              suffix = tmp;
            }
            
            if (strncmp(suffix, seq_cursor, strlen(suffix)) == 0) {
              seq_cursor += strlen(suffix);
              
              char syl_txt[strlen(prefix) + strlen(suffix)];
              strcpy(syl_txt, prefix);
              strcat(syl_txt, suffix);
              
              ensure_syllable(syl_txt)
              done = true;
              break;
            }
          }
        }
        
        if (!done) {
          rlt->error = illegal_suffix_token_error;
          goto prepare;
        }
        
        break;
      }

    }
  }
  
prepare:
  rlt->cap = syllable_parsed_count;
  rlt->seq = syllable;

  if (oft > strlen(pinyin_seq) - 1) {
    oft = PINYIN_OFFSET_AFTER_TRAILLING;
  }
  rlt->offset = oft;
  
  return rlt;
}

void debug_pinyin_col(pinyin_col_t *pinyin_col) {
  printf("[pinyin_parser]%ld syllable(%ld):\n", pinyin_col->cap, pinyin_col->offset);
  if (pinyin_col->cap == 0) {
    return;
  }
  for (size_t i = 0; i < pinyin_col->cap; ++i) {
    char *syl = pinyin_col->seq[i];
    printf("[pinyin_parser]%s\n", syl);
  }
}

void dispose_pinyin_col(pinyin_col_t *pinyin_col) {
  assert(pinyin_col != NULL);
  if (pinyin_col->cap == 0) {
    free(pinyin_col);
    return;
  }
  for (size_t i = 0; i < pinyin_col->cap; ++i) {
    char *syl = pinyin_col->seq[i];
    free(syl);
  }
  free(pinyin_col->seq);
  free(pinyin_col);
}