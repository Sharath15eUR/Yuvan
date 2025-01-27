#problem1
{
echo "All files"
ls -lh
echo "Files larger than 1 Mb"
find . -type f -size +1M -exec ls -lh {} +
}> out1.txt


#problem2
sed 's/localhost/127.0.0.1/g' config.txt > updated_config.txt
{
  echo "config.txt"
  cat "config.txt"
  echo "updated_config.txt"
  cat "updated_config.txt"
} > out2.txt

#problem3
grep "ERROR" log.txt | grep -v "DEBUG" > filtered_log.txt
{
  echo "log.txt"
  cat "log.txt"
  echo "filtered_log.txt"
  cat "filtered_log.txt"
} > out3.txt

#problem4
ps aux | sort -nrk 4 | head -1 | awk '{system("kill -9 " $2)}' > out4.txt

#problem5
{
echo "unique gateways"
ip route | awk '/default/ {print $3}' | sort -u
} > out5.txt

