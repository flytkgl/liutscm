/*
 * test.c
 *
 * Simple tests
 *
 * Copyright (C) 2013-03-14 liutos <mat.liutos@gmail.com>
 */
#include <stdio.h>
#include <string.h>
#include "write.h"
#include "eval.h"
#include "read.h"

int main(int argc, char *argv[])
{
  char *cases[] = {
    "123",
    "-123",
    "#t",
    "#f",
    "#\\a",
    "#\\A",
    "#\\\\n",
    "#\\ ",
    "\"Hello, world!\"",
    "( )",
    "(1)",
    "(1 . 2)",
    "(1 (2))",
    "hello",
    "'hello",
    "(quote hello)",
  };
  symbol_table = make_hash_table(hash_symbol_name, symbol_name_comparator, 11);
  for (int i = 0; i < sizeof(cases) / sizeof(char *); i++) {
    FILE *stream = fmemopen(cases[i], strlen(cases[i]), "r");
    printf(">> %s\n=> ", cases[i]);
    write_object(eval_object(read_object(stream)));
    putchar('\n');
    fclose(stream);
  }
  return 0;
}
