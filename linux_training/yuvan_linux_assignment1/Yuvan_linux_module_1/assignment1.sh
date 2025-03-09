#problem1
touch file1
chmod 755 file1
ls -l file1 > out1.txt

#problem2
touch file2
chmod a+w file2
ls -l file2 > out2.txt
chmod g-w file2
ls -l file2 > out2.txt

#problem3
mkdir -p dir1/dir2
touch dir1/dir2/sample_file
cd dir1
ln -s dir2/sample_file sample_file_link
ls -l > out3.txt
cd ..

#problem4
ps -e > out4.txt

#problem5
cd dir1
touch file1 file2 file3
ls -ltr > files_info.txt
cd ..
ls -l dir1/files_info.txt > out5.txt
cat dir1/files_info.txt > out5.txt