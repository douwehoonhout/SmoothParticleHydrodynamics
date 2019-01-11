#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "particle-list.h"

#define MAXLINE 1024

particle_list alloc_particles(int size) {
    particle_list particles;
    particles.size = size;
    particles.particles = malloc(size * sizeof(particle));
    return particles;
}
int nr_of_lines() {
    FILE *fp;
    int lines=0;
    char ch;
    fp=fopen("../input/particles","r");
    while((ch=fgetc(fp))!=EOF)
    {
        if (ch=='\n') { lines++; }
    }
    fclose(fp);
    return lines;
}

particle_list read_from_file() {
    int lines = nr_of_lines();
    char buffer[MAXLINE];
    FILE *fp;
    particle_list particle_list1 = alloc_particles(lines);

    char file_name[26] = "../input/particles";
    fp = fopen(file_name, "r"); // read mode

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    particle* particles = particle_list1.particles;


    for (int i = 0; i < lines;) {


        if (fgets(buffer, MAXLINE, fp) == NULL) {
            fprintf(stderr, "Inputfile %s is too short !\n", file_name);
            exit(1);
        }
        if (strlen(buffer) > 5) // Kludge solution to skip possibly empty lines !
        {
            sscanf(buffer, "%lf%*[ ,:;]%lf%*[ ,:;]%lf%*[ ,:;]%lf", &particles[i].x, &particles[i].y, &particles[i].density, &particles[i].velocity);

            i++; // only increase counter if line is valid
        }

    }
    for (int i = 0; i < lines; i++){
        particles[i].density = 1. / (particles[i + 1].x - particles[i].x);
        if (particles[i].density < 0){
            particles[i].density = 0;
        }
        particles[i].vy = 0;
    }

    fclose(fp);
    return particle_list1;
}

void initial_write(particle_list particle_list1) {
    FILE *f = fopen("../output/result.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    particle* particles = particle_list1.particles;
    fprintf(f, "id:  x: y:  vi:  rhoi: where t = 0\n");

    for (int i = 0; i < particle_list1.size; i++) {
        fprintf(f, "%d, %lf, %lf, %lf, %lf \n", i, particles[i].x, particles[i].y, particles[i].velocity, particles[i].density);
    }

    fclose(f);
}

void write_to_file(particle_list particle_list1, double time) {
    FILE *f = fopen("../output/result.txt", "a");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    particle* particles = particle_list1.particles;
    fprintf(f, "id:  x:  y:  vi:   where t = %lf \n", time);

    for (int i = 0; i < particle_list1.size; i++) {
        fprintf(f, "%d, %lf, %lf, %lf, %lf \n", i, particles[i].x, particles[i].y, particles[i].velocity, particles[i].density);
    }

    fclose(f);
}
