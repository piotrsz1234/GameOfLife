#include <stdio.h>
#include <stdlib.h>

int GetFileSize(int s) {
    if(s == 0)
        return 300;

    if(s == 1)
        return 3000;

    if(s == 2)
        return 30000;

    return 0;
}

void WriteFile(FILE *fptr, int n, int c, int s, int index, char* fileName){
    fprintf(fptr, "#!/bin/bash\n");
    fprintf(fptr, "#SBATCH -n %d\n", n);
    fprintf(fptr, "#SBATCH -c %d\n", c);
    fprintf(fptr, "#SBATCH -o ./outputs/%s%d=%d.txt\n", fileName, GetFileSize(s), n*6);
    fprintf(fptr, "./%s %d 20 0 0\n", fileName, GetFileSize(s));

}

void writePure(int s, int n, int index, char* fileName) {
    FILE *fptr;
    char *temp = malloc(1024 * sizeof(char));
    sprintf(temp, "new_scripts/c%d.sh", index);
    fptr = fopen(temp, "w");

    WriteFile(fptr, n * 6, 1, s, index, fileName);
    
    fclose(fptr);
    free(temp);
}

void writeOpen(int s, int n, int index, char* fileName) {
    FILE *fptr;
    char *temp = malloc(1024 * sizeof(char));
    sprintf(temp, "new_scripts/c%d.sh", index);
    fptr = fopen(temp, "w");

    WriteFile(fptr, n, 6, s, index, fileName);

    fclose(fptr);
    free(temp);
}

int main()
{
    int index = 0;
    for(int s = 0; s < 3; s++)
    {
        for(int n = 0; n < 15; n++)
        {
            writePure(s, n+1, index, "cluster");
            index++;
            writeOpen(s, n+1, index, "clusterMp");
            index++;
            writePure(s, n+1, index, "ncluster");
            index++;
            writeOpen(s, n+1, index, "nclusterMp");
            index++;
        }
    }
}