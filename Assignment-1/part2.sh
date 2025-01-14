echo "My Student Account is $USER"
echo "Today's Date is $(date)"
echo

echo "Command 1: ls"
ls
echo 

echo "Command 2: touch file.txt"
touch file.txt
echo "This is a sample file." > file.txt

echo "Command 3: cat file.txt"
cat file.txt
echo

echo "Command 4: df -h"
df -h
echo

echo "Command 5: who"
who
echo

echo "Command 6: grep -o 'zymome' words | wc -l"
grep -o 'zymome' words | wc -l
echo

echo "Command 7: sort words | uniq -c | sort -nr | head -n 10"
sort words | uniq -c | sort -nr | head -n 10
echo

echo "Command 8: grep '^a' words"
grep '^a' words| head -n 10
echo

echo "Command 9: awk '{print toupper($0)}' words | head -n 100"
awk '{print toupper($0)}' words | head -n 100
echo

echo "Command 10: sed -n '5,10p' words"
sed -n '5,10p' words
echo

