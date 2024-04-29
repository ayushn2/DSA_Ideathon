#include <stdio.h>

// Function to generate a DOT file representing a graph
void generateDOTFile() {
    FILE *fp;
    fp = fopen("graph.dot", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    fprintf(fp, "graph {\n");
    fprintf(fp, "    A -- B;\n");
    fprintf(fp, "    B -- C;\n");
    fprintf(fp, "    C -- D;\n");
    fprintf(fp, "}\n");

    fclose(fp);
}

int main() {
    generateDOTFile();
    return 0;
}
