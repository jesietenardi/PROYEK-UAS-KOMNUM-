# Estimasi Jarak Tempuh Mobil dengan Metode Runge-Kutta

**Nama:** Jesie Tenardi  
**NPM:** 2306162002

---

## Deskripsi Program (Bahasa Sederhana)

Program ini dibuat untuk menghitung jarak yang ditempuh oleh mobil jika kecepatannya berubah-ubah setiap waktu. Perhitungan dilakukan dengan metode Runge-Kutta orde 4, yaitu cara membagi waktu menjadi bagian-bagian kecil agar hasil perhitungan jarak menjadi lebih akurat.

### Fitur Program
- Simulasi dengan rumus kecepatan otomatis (v(t) = 0.5*t + 10)
- Simulasi dengan data kecepatan yang dimasukkan sendiri oleh pengguna
- Hasil simulasi bisa disimpan ke file CSV (bisa dibuka di Excel)
- Membuat grafik kecepatan dan jarak dengan Python

### Cara Kerja Program
1. Pilih menu simulasi (otomatis, input sendiri, atau simpan ke CSV)
2. Program akan menghitung jarak tempuh mobil dengan metode Runge-Kutta
3. Hasilnya bisa dilihat di layar atau disimpan ke file CSV
4. File CSV bisa dibuat grafiknya dengan program Python

### File Penting
- `program.c` : Program utama untuk menghitung jarak (bahasa C)
- `hasil1.csv`, `hasil2.csv` : Contoh hasil simulasi
- `generate_graph_hasil1.py`, `generate_graph_hasil2.py` : Program Python untuk membuat grafik dari file CSV

### Cara Menjalankan
1. **Kompilasi program C:**
   ```powershell
   gcc program.c -o program.exe
   ```
2. **Jalankan program:**
   ```powershell
   .\program.exe
   ```
3. **Grafik :**
   ```powershell
   pip install pandas matplotlib
   python generate_graph_hasil1.py
   python generate_graph_hasil2.py
   ```
![Image](https://github.com/user-attachments/assets/c48ebd02-219f-4b7c-aa27-62426f000bec)
![Image](https://github.com/user-attachments/assets/de7b2283-d27d-4fed-8bca-474e7b0f0b89)
### Contoh Hasil CSV
| waktu | kecepatan | jarak |
|-------|-----------|-------|
| 0.0   | 10.0      | 0.0   |
| 0.5   | 10.25     | 5.06  |
| ...   | ...       | ...   |

### Penjelasan Metode
Metode Runge-Kutta orde 4 adalah cara menghitung jarak dengan membagi waktu menjadi bagian-bagian kecil, lalu menghitung jarak sedikit demi sedikit sampai waktu yang diinginkan. Dengan cara ini, hasil perhitungan menjadi lebih akurat walaupun kecepatan mobil berubah-ubah.

---

**Jesie Tenardi - 2306162002**

