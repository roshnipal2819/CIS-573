echo "Student Count by Section:"
awk -F, '{sections[$2]++} END {for (sec in sections) print sec, sections[sec]; print "Total", NR}' gradeBook.csv
echo ""
echo "Average Scores:"
awk -F, '{sum1+=$3; sum2+=$4} END {print "Average Exam 1: " sum1/NR; print "Average Exam 2: " sum2/NR}' gradeBook.csv
echo ""
echo "Students with Exam 2 < Exam 1:"
awk -F, '$4 < $3 {print $1} END {print "Total students:", NR}' gradeBook.csv
