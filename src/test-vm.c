/*
 * test-vm.c
 *
 * Test samples for the virtual machine
 *
 * Copyright (C) 2013-03-18 liutos <mat.liutos@gmail.com>
 */
#include <stdio.h>
#include <string.h>

#include "types.h"
#include "object.h"
#include "read.h"
#include "write.h"
#include "compiler.h"
#include "eval.h"
#include "vm.h"
#include "init.h"

extern sexp extract_labels(sexp, int *);

int main(int argc, char *argv[])
{
  init_impl();
  char *cases[] = {
    /* "1", */
    /* "+", */
    /* "'hello", */
    /* "(+ 1 2)", */
    /* "(if #t 1 2)", */
    /* "(begin (set! a 1) a)", */
    /* "(begin \"doc\" (write \"Hello, world\") 2)", */
    /* "(lambda (x) (+ x 1))", */
    /* "(+ 1 1)", */
    /* "((lambda (x . y) (set! x y)) 1 2 3 4)", */
    "(car '(1 2))",
    /* "(+ (* 1 2) (+ 3 (read)))", */
    /* "(eval (read) (repl-environment))", */
  };
  for (int i = 0; i < sizeof(cases) / sizeof(char *); i++) {
    FILE *fp = fmemopen(cases[i], strlen(cases[i]), "r");
    lisp_object_t in_port = make_file_in_port(fp);
    printf(">> %s\n", cases[i]);
    lisp_object_t compiled_code =
        compile_as_fn(read_object(in_port), repl_environment);
    /* printf("-- "); */
    /* write_object(compiled_code, scm_out_port); */
    /* compiled_code = assemble_code(compiled_code); */
    /* printf("\n-> "); */
    /* write_object(compiled_code, out_port); */
    /* printf("\n"); */
    lisp_object_t value =
        run_compiled_code(compiled_code, repl_environment, EOL);
    /* printf("=> "); */
    /* write_object(value, out_port); */
    /* putchar('\n'); */
    port_format(scm_out_port, "=> %*\n", value);
    fclose(fp);
  }
  return 0;
}
