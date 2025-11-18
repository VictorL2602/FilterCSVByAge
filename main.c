#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 100
#define DELIM "," // CSV delimiter

char *ifile = NULL, *ofile = NULL;
unsigned filter_age_max;
FILE *istream, *ostream;

// No raw string literals in C
const char USAGE[] =
    "Filters CSV rows, keeping only those with provided maximum age\n"
    "%s max-age [input-file] [output-file]\n"
    "\n"
    "Example:\n"
    "%s max-age 17 input.csv output.csv\n"
    "%s max-age 10 input.csv (outputs to stdout)\n"
    "%s max-age 54           (inputs from stdin, outputs to stdout)\n";

void filter_stream(FILE *istream, FILE *ostream) {
  char line[LINE_MAX];
  char *fgets_return;
  char *name, *age_str;
  size_t line_no = 0;

  while (
      // Read a line from `istream`
      // YOUR CODE HERE
      (fgets_return = fgets(line, LINE_MAX, istream)) != NULL) {
    // læs en linje fra input og gem returværdien i fgets_return
    ++line_no;

    if (fgets_return && *fgets_return != '\n') {
      if (strlen(line) > 1) {
        // Parse name and age
        // YOUR CODE HERE
        name = strtok(line, DELIM);
        age_str = strtok(NULL, DELIM);
        // del linjen med komma: først navn, derefter alder

        if (!age_str) {
          // Missing age error
          // YOUR CODE HERE
          fprintf(stderr, "Line %zu: missing age value.\n", line_no);
          continue;
          // print fejl hvis linjen mangler en alder
        }
      }
    } else {
      // Blank line error
      // YOUR CODE HERE
      fprintf(stderr, "Line %zu: blank line.\n", line_no);
      continue;
      // print fejl hvis linjen er tom eller kun indeholder en newline
    }

    // Age processing
    unsigned age;
    int recognized_count = sscanf(age_str, "%u", &age);
    if (recognized_count == 1) {
      if (age <= filter_age_max) {
        // Output filtered line
        // YOUR CODE HERE
        fprintf(ostream, "%s,%u\n", name, age);
        // skriv navnet og alderen til output hvis alderen er inden for grænsen
      }
    } else {
      // Invalid age error
      // YOUR CODE HERE
      fprintf(stderr, "Line %zu: invalid age '%s'.\n", line_no, age_str);
      // print fejl hvis alderen ikke er et tal
    }
  }
}

int main(int argc, char *argv[]) {
  switch (argc) {
  case 4:
    ofile = argv[3];
    // fallthrough
  case 3:
    ifile = argv[2];
    // fallthrough
  case 2:
    if (!sscanf(argv[1], "%u", &filter_age_max)) {
      puts("First argument is not an age.");
      exit(EXIT_FAILURE);
    }
    break;

  default:
    printf(USAGE, argv[0], argv[0], argv[0], argv[0]);
    return EXIT_SUCCESS;
  }

  if (ifile) {
    // Open input file
    // YOUR CODE HERE
    istream = fopen(ifile, "r");
    // brug fopen til at åbne inputfilen for læsning "r"

    // Handle open error
    // YOUR CODE HERE
    if (!istream) {
      fprintf(stderr, "Could not open input file '%s'\n", ifile);
      exit(EXIT_FAILURE);
      // tjek om fopen fejlede og afbryd programmet hvis filen ikke kunne åbnes
    }
  } else {
    // Default to stdin
    // YOUR CODE HERE
    istream = stdin;
    // brug standard input når der ikke er angivet en inputfil
  }

  if (ofile) {
    // Open output file
    // YOUR CODE HERE
    ostream = fopen(ofile, "w");
    // åbn outputfil i skrivetilstand "w"

    // Handle open error
    // YOUR CODE HERE
    if (!ostream) {
      fprintf(stderr, "Could not open output file '%s'\n", ofile);
      exit(EXIT_FAILURE);
      // tjek om fopen fejlede og stop programmet hvis outputfilen ikke kan åbnes
    }
  } else {
    // Default to stdout
    // YOUR CODE HERE
    ostream = stdout;
    // brug standard output når der ikke er angivet en outputfil
  }

  filter_stream(istream, ostream);

  return EXIT_SUCCESS;
}
