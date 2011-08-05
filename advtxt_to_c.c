#include <stdio.h>
#include <string.h>

const char* files[] = {
  "advent1.txt",
  "advent2.txt",
  "advent3.txt",
  "advent4.txt",
  NULL
};

int main(int argc, char** argv) {
  const char** filename = files;
  while(*filename != NULL) {
    printf("Opening %s\n", *filename);
    FILE* in = fopen(*filename, "r");

    char out_name_c[128];
    char out_name_h[128];

    int period = strcspn(*filename, ".");
    strncpy(out_name_c, *filename, period);
    strncpy(out_name_h, *filename, period);

    out_name_c[period] = '\0';
    out_name_h[period] = '\0';

    strcat(out_name_c, ".c");
    strcat(out_name_h, ".h");

    int index = (*filename)[period-1] - '0';

    // Write the header.
    printf("Writing header %s\n", out_name_h);
    FILE* out_h = fopen(out_name_h, "w");
    fprintf(out_h, "extern const char* messages%d[];\n", index);
    fclose(out_h);

    // Write the c file.
    printf("Writing c file %s\n", out_name_c);
    FILE* out = fopen(out_name_c, "w");
    fprintf(out, "const char* messages%d[] = {\n", index);

    // Read in each message and output as a string in the array.
    char buffer[1024];
    int first = 1;
    int is_empty = 0;
    while(fgets(buffer, 1024, in)) {
      if (buffer[0] == '#') {
        if (is_empty)
          fprintf(out, "\"\"");
        is_empty = 1;
        if (!first)
          fprintf(out, ",\n");
        first = 0;
      } else {
        is_empty = 0;
        // Strip off the newline.
        buffer[strlen(buffer)-1] = '\0';
        // Convert " to '
        char* pch = strpbrk(buffer, "\"");
        while (pch != NULL) {
          *pch = '\'';
          pch = strpbrk(pch + 1, "\"");
        }
        fprintf(out, "\"%s\\n\"\n", buffer);
      }
    }

    fprintf(out, "};\n");
    fclose(out);
    fclose(in);
    ++filename;
  }
  return 0;
}
