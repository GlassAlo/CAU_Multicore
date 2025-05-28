#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>
#include <time.h>

#define SPHERES 20
#define INF     2e10f
#define DIM     2048
#define rnd(x)  (x * rand() / RAND_MAX)

struct Sphere {
    float r, g, b;
    float radius;
    float x, y, z;

    __device__ float hit(float ox, float oy, float* n) const {
        float dx = ox - x;
        float dy = oy - y;
        float rr = radius * radius;
        float d2 = dx * dx + dy * dy;
        if (d2 < rr) {
            float dz = sqrtf(rr - d2);
            *n = dz / radius;
            return dz + z;
        }
        return -INF;
    }
};

// Move spheres to constant memory for faster cached access
__constant__ Sphere d_spheres[SPHERES];

__global__ void render_kernel(unsigned char* ptr) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    if (x >= DIM || y >= DIM) return;

    int offset = x + y * DIM;
    float ox = x - DIM * 0.5f;
    float oy = y - DIM * 0.5f;

    float r = 0, g = 0, b = 0;
    float maxz = -INF;

    for (int i = 0; i < SPHERES; i++) {
        float n;
        float t = d_spheres[i].hit(ox, oy, &n);
        if (t > maxz) {
            maxz = t;
            r = d_spheres[i].r * n;
            g = d_spheres[i].g * n;
            b = d_spheres[i].b * n;
        }
    }

    // Use __saturatef to clamp color values and avoid branching
    ptr[offset * 4 + 0] = (unsigned char)(__saturatef(r) * 255.0f);
    ptr[offset * 4 + 1] = (unsigned char)(__saturatef(g) * 255.0f);
    ptr[offset * 4 + 2] = (unsigned char)(__saturatef(b) * 255.0f);
    ptr[offset * 4 + 3] = 255;
}

void ppm_write(const unsigned char* bitmap, int xdim, int ydim, FILE* fp) {
    fprintf(fp, "P3\n%d %d\n255\n", xdim, ydim);
    for (int y = 0; y < ydim; y++) {
        for (int x = 0; x < xdim; x++) {
            int i = x + y * xdim;
            fprintf(fp, "%d %d %d ", bitmap[4 * i], bitmap[4 * i + 1], bitmap[4 * i + 2]);
        }
        fprintf(fp, "\n");
    }
}

int main(int argc, char* argv[]) {
    char *filename = "result.ppm";
    if (argc > 1) {
        filename = argv[1];
    }
    srand(time(NULL));

    Sphere spheres_h[SPHERES];
    for (int i = 0; i < SPHERES; i++) {
        spheres_h[i].r = rnd(1.0f);
        spheres_h[i].g = rnd(1.0f);
        spheres_h[i].b = rnd(1.0f);
        spheres_h[i].x = rnd(2000.0f) - 1000;
        spheres_h[i].y = rnd(2000.0f) - 1000;
        spheres_h[i].z = rnd(2000.0f) - 1000;
        spheres_h[i].radius = rnd(200.0f) + 40;
    }

    // Copy host spheres to device constant memory
    cudaMemcpyToSymbol(d_spheres, spheres_h, sizeof(Sphere) * SPHERES);

    unsigned char *bitmap_h = nullptr;
    unsigned char *bitmap_d = nullptr;
    // Allocate device memory for image buffer
    cudaMalloc((void**)&bitmap_d, DIM * DIM * 4);
    // Allocate pinned (page-locked) host memory for image buffer
    cudaMallocHost((void**)&bitmap_h, DIM * DIM * 4);

    // Use 16x16 threads per block (256 threads)
    dim3 threads(16, 16);
    // Compute grid size to cover entire image
    dim3 blocks((DIM + threads.x - 1) / threads.x, (DIM + threads.y - 1) / threads.y);

    clock_t start = clock();

    render_kernel<<<blocks, threads>>>(bitmap_d);

    clock_t stop = clock();
    double duration = ((double) (stop - start)) / CLOCKS_PER_SEC;

    // Ensure all threads are finished
    cudaDeviceSynchronize();

    // Copy rendered image from device to host
    cudaMemcpy(bitmap_h, bitmap_d, DIM * DIM * 4, cudaMemcpyDeviceToHost);

    FILE* fp = fopen(filename, "w");
    if (fp) {
        ppm_write(bitmap_h, DIM, DIM, fp);
        fclose(fp);
    }

    printf("CUDA ray tracing: %f sec\n", duration);
    printf("[%s] was generated.\n", filename);

    cudaFree(bitmap_d);
    cudaFreeHost(bitmap_h);
    return 0;
}