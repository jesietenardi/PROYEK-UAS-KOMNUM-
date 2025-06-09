#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Fungsi kecepatan default: v(t) = a*t + b (misal akselerasi konstan)
double v_default(double t) {
    // Contoh: a = 0.5 m/s^2, b = 10 m/s
    return 0.5 * t + 10;
}

// Fungsi kecepatan custom (user input via array)
typedef struct {
    double *t;
    double *v;
    int n;
} DataKecepatan;

// Deklarasi fungsi agar tidak error implicit declaration
void simulasi_default();
void simulasi_input();
void simulasi_default_csv();
void simulasi_input_csv();

double v_interpolasi(double t, DataKecepatan data) {
    // Linear interpolation
    if (t <= data.t[0]) return data.v[0];
    if (t >= data.t[data.n-1]) return data.v[data.n-1];
    for (int i = 0; i < data.n-1; i++) {
        if (t >= data.t[i] && t <= data.t[i+1]) {
            double dt = data.t[i+1] - data.t[i];
            double dv = data.v[i+1] - data.v[i];
            return data.v[i] + (t - data.t[i]) * dv / dt;
        }
    }
    return 0;
}

// Runge-Kutta Orde 4 untuk ODE ds/dt = v(t)
double runge_kutta(double (*v_func)(double), double t0, double s0, double t_end, double h) {
    double t = t0, s = s0;
    while (t < t_end) {
        double k1 = h * v_func(t);
        double k2 = h * v_func(t + h/2.0);
        double k3 = h * v_func(t + h/2.0);
        double k4 = h * v_func(t + h);
        s += (k1 + 2*k2 + 2*k3 + k4) / 6.0;
        t += h;
    }
    return s;
}

// Runge-Kutta Orde 4 untuk data kecepatan diskrit (interpolasi)
double runge_kutta_data(DataKecepatan data, double t0, double s0, double t_end, double h) {
    double t = t0, s = s0;
    while (t < t_end) {
        double k1 = h * v_interpolasi(t, data);
        double k2 = h * v_interpolasi(t + h/2.0, data);
        double k3 = h * v_interpolasi(t + h/2.0, data);
        double k4 = h * v_interpolasi(t + h, data);
        s += (k1 + 2*k2 + 2*k3 + k4) / 6.0;
        t += h;
    }
    return s;
}

// Fungsi untuk menyimpan hasil simulasi ke file CSV
void simpan_csv(const char *filename, double *waktu, double *kecepatan, double *jarak, int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }
    fprintf(fp, "waktu,kecepatan,jarak\n");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%lf,%lf,%lf\n", waktu[i], kecepatan[i], jarak[i]);
    }
    fclose(fp);
    printf("Hasil simulasi telah disimpan ke %s\n", filename);
}

// Simulasi default dengan penyimpanan CSV
void simulasi_default_csv() {
    double t0 = 0, s0 = 0, t_end, h;
    printf("=== Simulasi Data Default (dengan simpan CSV) ===\n");
    printf("Fungsi kecepatan: v(t) = 0.5*t + 10 (m/s)\n");
    printf("Masukkan waktu akhir simulasi (detik): ");
    scanf("%lf", &t_end);
    printf("Masukkan langkah waktu (h, detik): ");
    scanf("%lf", &h);
    int n = (int)((t_end-t0)/h)+1;
    double *waktu = (double*)malloc(n*sizeof(double));
    double *kecepatan = (double*)malloc(n*sizeof(double));
    double *jarak = (double*)malloc(n*sizeof(double));
    double t = t0, s = s0;
    for (int i = 0; i < n; i++) {
        waktu[i] = t;
        kecepatan[i] = v_default(t);
        jarak[i] = s;
        double k1 = h * v_default(t);
        double k2 = h * v_default(t + h/2.0);
        double k3 = h * v_default(t + h/2.0);
        double k4 = h * v_default(t + h);
        s += (k1 + 2*k2 + 2*k3 + k4) / 6.0;
        t += h;
    }
    printf("Estimasi jarak tempuh: %.4lf meter\n", jarak[n-1]);
    char filename[100];
    printf("Masukkan nama file untuk menyimpan hasil (misal: iterasi.csv): ");
    scanf("%s", filename);
    simpan_csv(filename, waktu, kecepatan, jarak, n);
    free(waktu); free(kecepatan); free(jarak);
}

// Simulasi input user dengan penyimpanan CSV
void simulasi_input_csv() {
    int n;
    printf("=== Simulasi Data Input Pengguna (dengan simpan CSV) ===\n");
    printf("Masukkan jumlah data kecepatan (minimal 2): ");
    scanf("%d", &n);
    if (n < 2) {
        printf("Data kurang!\n");
        return;
    }
    DataKecepatan data;
    data.n = n;
    data.t = (double*)malloc(n * sizeof(double));
    data.v = (double*)malloc(n * sizeof(double));
    printf("Masukkan data waktu (detik) dan kecepatan (m/s):\n");
    for (int i = 0; i < n; i++) {
        printf("t[%d] = ", i); scanf("%lf", &data.t[i]);
        printf("v[%d] = ", i); scanf("%lf", &data.v[i]);
    }
    double t0 = data.t[0], s0 = 0, t_end, h;
    printf("Masukkan waktu akhir simulasi (detik, <= %.2lf): ", data.t[n-1]);
    scanf("%lf", &t_end);
    if (t_end > data.t[n-1]) t_end = data.t[n-1];
    printf("Masukkan langkah waktu (h, detik): ");
    scanf("%lf", &h);
    int nstep = (int)((t_end-t0)/h)+1;
    double *waktu = (double*)malloc(nstep*sizeof(double));
    double *kecepatan = (double*)malloc(nstep*sizeof(double));
    double *jarak = (double*)malloc(nstep*sizeof(double));
    double t = t0, s = s0;
    for (int i = 0; i < nstep; i++) {
        waktu[i] = t;
        kecepatan[i] = v_interpolasi(t, data);
        jarak[i] = s;
        double k1 = h * v_interpolasi(t, data);
        double k2 = h * v_interpolasi(t + h/2.0, data);
        double k3 = h * v_interpolasi(t + h/2.0, data);
        double k4 = h * v_interpolasi(t + h, data);
        s += (k1 + 2*k2 + 2*k3 + k4) / 6.0;
        t += h;
    }
    printf("Estimasi jarak tempuh: %.4lf meter\n", jarak[nstep-1]);
    char filename[100];
    printf("Masukkan nama file untuk menyimpan hasil (misal: iterasi.csv): ");
    scanf("%s", filename);
    simpan_csv(filename, waktu, kecepatan, jarak, nstep);
    free(waktu); free(kecepatan); free(jarak);
    free(data.t); free(data.v);
}

void simulasi_default() {
    double t0 = 0, s0 = 0, t_end, h;
    printf("=== Simulasi Data Default ===\n");
    printf("Fungsi kecepatan: v(t) = 0.5*t + 10 (m/s)\n");
    printf("Masukkan waktu akhir simulasi (detik): ");
    scanf("%lf", &t_end);
    printf("Masukkan langkah waktu (h, detik): ");
    scanf("%lf", &h);
    double s = runge_kutta(v_default, t0, s0, t_end, h);
    printf("Estimasi jarak tempuh: %.4lf meter\n", s);
}

void simulasi_input() {
    int n;
    printf("=== Simulasi Data Input Pengguna ===\n");
    printf("Masukkan jumlah data kecepatan (minimal 2): ");
    scanf("%d", &n);
    if (n < 2) {
        printf("Data kurang!\n");
        return;
    }
    DataKecepatan data;
    data.n = n;
    data.t = (double*)malloc(n * sizeof(double));
    data.v = (double*)malloc(n * sizeof(double));
    printf("Masukkan data waktu (detik) dan kecepatan (m/s):\n");
    for (int i = 0; i < n; i++) {
        printf("t[%d] = ", i); scanf("%lf", &data.t[i]);
        printf("v[%d] = ", i); scanf("%lf", &data.v[i]);
    }
    double t0 = data.t[0], s0 = 0, t_end, h;
    printf("Masukkan waktu akhir simulasi (detik, <= %.2lf): ", data.t[n-1]);
    scanf("%lf", &t_end);
    if (t_end > data.t[n-1]) t_end = data.t[n-1];
    printf("Masukkan langkah waktu (h, detik): ");
    scanf("%lf", &h);
    double s = runge_kutta_data(data, t0, s0, t_end, h);
    printf("Estimasi jarak tempuh: %.4lf meter\n", s);
    free(data.t); free(data.v);
}

void menu() {
    int pilihan;
    do {
        printf("\n==============================================================\n");
        printf("|                Proyek UAS Komnum Jesie Tenardi             |\n");
        printf("==============================================================\n");
        printf("|   MENU ESTIMASI JARAK TEMPUH MOBIL (RUNGE-KUTTA)           |\n");
        printf("--------------------------------------------------------------\n");
        printf("| 1. Simulasi dengan data kecepatan default                  |\n");
        printf("| 2. Simulasi dengan data kecepatan input pengguna           |\n");
        printf("| 3. Simulasi default + simpan ke CSV                        |\n");
        printf("| 4. Simulasi input pengguna + simpan ke CSV                 |\n");
        printf("| 5. Keluar                                                  |\n");
        printf("--------------------------------------------------------------\n");
        printf("Pilih menu [1-5]: ");
        scanf("%d", &pilihan);
        printf("\n");
        switch (pilihan) {
            case 1: simulasi_default(); break;
            case 2: simulasi_input(); break;
            case 3: simulasi_default_csv(); break;
            case 4: simulasi_input_csv(); break;
            case 5:
                printf("==============================================================\n");
                printf("Okayy selesai terima kasih pak\n");
                printf("==============================================================\n");
                break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 5);
}

int main() {
    menu();
    return 0;
}