{
 echo "test1 with no arguments"
 ./backup_manager.sh
 cat output.txt

 echo "test2 with no up to date files"
 ./backup_manager.sh important backup_important_3 bin
 cat output.txt

 echo "test3 with up to date files"
 ./backup_manager.sh important backup_important_3 bin
 cat output.txt
} > out.txt