/*Alunos:
Igor Neves de Souza - matrícula: 04151827
Pamela Laise Santos da Silva - matrícula: 04161465
Priscila Medeiros de Oliveira - matrícula: 04103836
Paulo Renan Santana de Almeida - matrícula: 04164332
*/
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main (int argc,char *argv[])
{
    if (argc<=1){
        fprintf(2, "Usage:sleep<number>\n");
        exit(1);
    }

    int ticks = atoi(argv[1]);
    sleep(ticks);
    exit(0);

}

