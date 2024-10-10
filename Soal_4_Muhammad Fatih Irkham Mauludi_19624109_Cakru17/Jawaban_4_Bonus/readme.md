### Implementasis algoritma A* dalam bentuk aplikasi CLI

**Notes:**  
Untuk linux, download file "A_star.elf".  
Untuk Windows, download file "A_star.exe".  
Atau, file "A_star.cpp" dapat dikompilasi secara langsung menggunakan g++

**Deskripsi:**  

(Disclaimer: semua kode dalam proyek ini di tulis oleh saya dan 0% menggunakan bantuan AI)

Dalam aplikasi ini pengguna dapat memilih ukuran grid dari 2x2 hingga 30x30.  

Pengguna dapat bebas memilih lokasi titik awal (source) dan titik akhir (target) dari path yang ingin dicari.

Di dalam grid tersebut dapat dimasukkan halangan (obstacles), baik secara manual oleh user ataupun di randomize.  

Setelah itu, simulasi akan berjalan dengan implementasi A* menggunakan fungsi heuristik:
```
F(x,y) : jarak grid[x][y] ke titik awal (source)
G(x,y) : jarak grid[x][y] ke titik akhir (target)
```
Setiap langkah dari algoritma akan ditampilkan dan delay antara tampilan setiap langkah akan ditentukan berdasarkan ukuran grid, (semakin besar grid, semakin cepat delay tampilan).

Algoritma akan melaporkan apakah mungkin untuk mendapat shortest path dari source ke target,  
jika terdapat shortest path, program akan menampilkannya.

Terimakasih.
