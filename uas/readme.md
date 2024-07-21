# c++ conn db
1. pada terminal silahkan ketikan : apt-get install libmysqlclient-dev
2. kita harus mengcompile code kita : g++ -o crud_simple crud.cc -lmysqlclient
3. running hasil compile nya : ./crud_simple

# tools db
navicat

https://shared.djncloud.my.id/tools_tempur

# perintah sederhana docker
1. masuk ke dalam suatu file yang terdapat docker-compose.yml
2. selanjutnya jika ingin membuild atau up si container tersebut silahkan ketikan 
```
docker compose up -d --build 
```

3. setelah itu silahkan cek container nya apakah sudah running apa belum, dengan lakukan perintah
```
docker ps 
```

4. setelah itu jika container nya sudah nyala dan ingin dibuat down silahkan ketikan 
```
docker compose down
```

# kenapa harus pake docker?
karena docker bagus buat production nantinya

# penjelasan sederhana docker 
1. Kontainer: Kontainer adalah unit kecil, ringan, dan terisolasi yang berisi aplikasi dan semua dependensinya. Kontainer memungkinkan aplikasi berjalan secara konsisten di berbagai lingkungan tanpa khawatir tentang perbedaan konfigurasi.

2. Gambar (Image): Gambar adalah cetak biru dari kontainer. Gambar berisi semua file sistem dan dependensi yang dibutuhkan oleh aplikasi. Kamu bisa membayangkan gambar sebagai resep yang digunakan untuk membuat kontainer.

3. Docker Engine: Ini adalah perangkat lunak yang menjalankan kontainer Docker. Docker Engine mengelola pembuatan dan eksekusi kontainer di mesin kamu.

4. Docker Hub: Ini adalah repositori online tempat kamu bisa menyimpan dan mendistribusikan gambar Docker. Kamu bisa mengunduh gambar yang sudah ada atau mengunggah gambar yang kamu buat.

5. Portabilitas: Karena kontainer berisi semua yang dibutuhkan aplikasi, mereka bisa berjalan di mana saja—di komputer lokal, server, atau cloud—tanpa perlu menyesuaikan lingkungan eksekusi.

6. Isolasi: Kontainer berjalan secara terpisah dari sistem utama dan kontainer lainnya. Ini membantu memastikan bahwa aplikasi di dalam kontainer tidak saling mengganggu.

7. Efisiensi: Kontainer lebih efisien dibandingkan mesin virtual (VM) karena mereka berbagi kernel sistem operasi yang sama dan hanya mengemas aplikasi dan dependensinya, bukan seluruh sistem operasi.
