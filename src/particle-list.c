#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "particle-list.h"

#define MAXLINE 1024

particle_list alloc_particles(int size) {
    particle_list particles;
    particles.n = size;
    particles.particles = malloc(size * sizeof(particle));
    return particles;
}

particle_list read_from_file() {
    char buffer[MAXLINE];
    FILE *fp;
    particle_list particle_list1 = alloc_particles(10);

    char file_name[26] = "../input/particles";
    fp = fopen(file_name, "r"); // read mode

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    particle* particles = particle_list1.particles;


    for (int i = 0; i < 10;) {


        if (fgets(buffer, MAXLINE, fp) == NULL) {
            fprintf(stderr, "Inputfile %s is too short !\n", file_name);
            exit(1);
        }
        if (strlen(buffer) > 5) // Kludge solution to skip possibly empty lines !
        {
            sscanf(buffer, "%lf%*[ ,:;]%lf%*[ ,:;]%lf", &particles[i].x, &particles[i].density, &particles[i].velocity);
            i++; // only increase counter if line is valid
        }
    }

    fclose(fp);
    return particle_list1;
}

