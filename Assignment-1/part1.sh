echo "My Student Account is $USER"
echo
echo "Today's Date is $(date)"
echo

echo "Command: pwd"
cd /Users/roshni/Documents/Fall24-Sem/Operating-Systems/Assignment-1/
pwd  
echo

echo "Command: head -n 1 words"
head -n 1 words
echo

echo "Command: tail -n 1 words"
tail -n 1 words
echo

echo "Command: read -p "Enter the word you want to search for:"  search_word"
read -p "Enter the word you want to search for:" search_word
grep "$search_word" words
echo

echo "Number of lines in the file:"
wc -l words
echo

echo "Appending the beginning and end of the file to 'combined_output.txt'"
{ head -n 5 words; tail -n 5 words; } > appended_output.txt
echo

echo "Sorting the beginning, end, and the search result into 'sorted_output.txt'"
{ head -n 5 words; tail -n 5 words; grep "$search_word" words; } | sort > sorted_output.txt
echo