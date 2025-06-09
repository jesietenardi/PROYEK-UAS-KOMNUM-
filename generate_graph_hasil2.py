import pandas as pd
import matplotlib.pyplot as plt

# Grafik untuk hasil2.csv
csv_file = 'hasil2.csv'

data = pd.read_csv(csv_file)
plt.figure(figsize=(10,6))
plt.plot(data['waktu'], data['jarak'], marker='o', label='Jarak')
plt.plot(data['waktu'], data['kecepatan'], '--', label='Kecepatan')
plt.xlabel('Waktu (detik)')
plt.ylabel('Nilai')
plt.title('Grafik Jarak & Kecepatan terhadap Waktu (hasil2.csv)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('grafik_hasil2.png')
plt.show()
