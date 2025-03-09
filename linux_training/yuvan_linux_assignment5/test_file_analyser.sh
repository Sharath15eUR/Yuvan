{
echo "command: ./file_analyser.sh"
./file_analyser.sh
echo "errors.log"
cat errors.log
echo ""

echo "command: ./file_analyser.sh -d logs"
./file_analyser.sh -d logs
echo "errors.log:"
cat errors.log
echo ""

echo "command: ./file_analyser.sh --help"
./file_analyser.sh --help
echo ""

echo "error_log1"
cat logs/error_log1
echo "erroe_log_2:"
cat logs/error_log2
echo ""
echo "command: ./file_analyser.sh -d logs -k Error"
./file_analyser.sh -d logs -k Error
echo ""

echo "script.sh"
cat script.sh
echo "command: ./file_analyser.sh -f script.sh -k TODO"
./file_analyser.sh -f script.sh -k TODO

} > out.txt