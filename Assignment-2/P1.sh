#!/bin/bash
echo "Dates:"
grep -E '[0-9]{1,2}-[A-Za-z]{3}-[0-9]{4}' UMassWhois.txt
echo ""
echo "All Uppercase Words:"
grep -o -E ' [A-Z]+ ' UMassWhois.txt
echo ""
echo "Domain Extensions with Line Numbers:"
grep -n -o -E '\.[a-zA-Z]{2,4}' UMassWhois.txt
echo ""
echo "Numbers with At Least 2 Digits:"
grep -o -E ' [0-9]{2,} ' UMassWhois.txt
echo ""
echo "Root Domain Names:"
grep -o -E '\b[a-zA-Z0-9._%-]+(?=\.[a-zA-Z]{2,4})' UMassWhois.txt
