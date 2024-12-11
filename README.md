# Minesweeper Kami Kroco
Deskripsi
Minesweeper adalah permainan logika di mana pemain harus membuka semua sel pada papan permainan tanpa mengaktifkan tambang. Setiap sel yang dibuka akan memberikan informasi apakah itu berisi tambang atau jumlah tambang di sekitar sel tersebut. Pemain dapat memberi tanda bendera pada sel yang dicurigai mengandung tambang.

Permainan ini menggunakan papan dengan ukuran tetap (WIDTH x HEIGHT), dan diisi dengan sejumlah tambang yang ditempatkan secara acak. Pemain dapat membuka sel atau memberi tanda bendera untuk menghindari tambang.

Cara Install
1. Pindah ke folder minesweeper dengan input "cd minesweeper" pada cmd/terminal
2. Input "gcc *.c *.h -o runMinesweeper" pada cmd/terminal
3. Setelahnya buka runMinesweeper.exe dengan input "./runMinesweeper.exe" pada cmd/terminal

Cara Bermain
1. **Tujuan Permainan**
Tujuan utama adalah untuk membuka semua sel yang tidak mengandung tambang, sementara menandai sel yang dicurigai mengandung tambang dengan memberi bendera.

2. **Perintah dalam Permainan**
Buka sel: Masukkan perintah o <x> <y> untuk membuka sel pada koordinat (x, y).
Berikan tanda bendera: Masukkan perintah f <x> <y> untuk memberi tanda bendera pada sel pada koordinat (x, y).
Contoh:
o 2 3: Membuka sel di baris 2 dan kolom 3.
f 5 5: Memberi tanda bendera pada sel di baris 5 dan kolom 5.

3. **Proses Permainan**
Setiap sel yang dibuka dapat memiliki beberapa kemungkinan:
Tambang (💣): Jika pemain membuka sel yang berisi tambang, permainan berakhir dan pemain kalah.
Angka (1-8): Jika sel tersebut tidak berisi tambang, sel akan menunjukkan angka yang mengindikasikan jumlah tambang yang ada di sekelilingnya.
Sel kosong: Jika tidak ada tambang di sekitar sel, sel tersebut akan terbuka dan akan otomatis membuka sel-sel kosong di sekitarnya (rekursif).
Pemain juga dapat memberi tanda bendera (🚩) pada sel yang dicurigai mengandung tambang untuk menghindarinya.

4. **Menghitung Bendera**
Setiap kali Anda memberi tanda bendera, jumlah bendera yang tersisa akan berkurang. Jika Anda memberikan terlalu banyak bendera, Anda akan kehabisan tanda dan tidak dapat memberi bendera lagi.

5. **Mengakhiri Permainan**
Permainan berakhir ketika salah satu dari kondisi berikut terjadi:
Kalah: Jika Anda membuka sel yang mengandung tambang.
Menang: Jika semua sel yang aman telah terbuka dan semua tambang telah diberi tanda bendera.

6. **Tampilan Papan Permainan**
Papan permainan akan ditampilkan dalam bentuk grid, di mana setiap sel akan memiliki status yang ditentukan oleh kondisi berikut:
., untuk sel yang belum dibuka.
F, untuk sel yang diberi tanda bendera.
Angka 1-8, untuk menunjukkan jumlah tambang di sekitar sel.
-, untuk sel kosong yang tidak mengandung tambang.

7. **Contoh Tampilan Papan**
```plaintext
   0  1  2  3  4  5  6  7  8  9
0  .  .  F  .  .  .  .  .  .  . 
1  .  .  .  .  .  .  .  .  .  . 
2  .  .  .  1  .  .  2  2  .  . 
3  .  .  .  .  .  .  .  3  .  . 
4  .  -  -  -  -  .  .  .  .  . 
5  .  -  -  -  -  -  .  .  .  . 
6  .  -  -  -  -  -  .  .  .  . 
7  .  .  .  .  .  .  .  .  .  . 
8  .  .  .  .  .  .  .  .  .  . 
9  .  .  .  .  .  .  .  .  .  .
```

8. **Contoh Alur Permainan**   
Misalkan papan permainan berukuran 5x5 dan memiliki 3 tambang.
Pemain memberi perintah o 1 1 untuk membuka sel di baris 1 dan kolom 1.
Jika sel tersebut tidak mengandung tambang, permainan akan melanjutkan, menampilkan informasi mengenai jumlah tambang di sekitar sel tersebut.
Pemain bisa memberi perintah f 2 2 untuk memberi bendera pada sel yang dicurigai mengandung tambang.
Struktur Data
cell
Setiap sel pada papan permainan diwakili oleh tipe data cell yang memiliki atribut-atribut berikut:

is_open: Menyatakan apakah sel sudah dibuka.
is_flag: Menyatakan apakah sel diberi tanda bendera.
is_mine: Menyatakan apakah sel berisi tambang.
neig_mines: Menyimpan jumlah tambang di sekitar sel.
