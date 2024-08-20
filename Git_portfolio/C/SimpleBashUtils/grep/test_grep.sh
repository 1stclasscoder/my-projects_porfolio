#!/bin/bash

for textfile in text1.txt text2.txt text3.txt
do
	for pattern in count mrt Age rH
    do
        echo "TEST file $textfile pattern $pattern:"
        ./s21_grep $pattern $textfile > s21_grep_output
        grep $pattern $textfile > grep_output
        echo -e "$(diff -s grep_output s21_grep_output)\n"
        if [[ $(diff -q ./grep_output ./s21_grep_output) ]]
        then
        echo "____________________________________________________________"
        echo -e "\nFAIL: test failed while testing $textfile pattern $pattern\n"
        fi
    done
done

for textfile in text1.txt text2.txt text3.txt
do
    for option in i v c l n h s o
    do
        for pattern in count mrt Age rH
        do
            echo "TEST file $textfile pattern $pattern option -$option:"
            ./s21_grep -$option $pattern $textfile > s21_grep_output
            grep -$option $pattern $textfile > grep_output
            echo -e "$(diff -s grep_output s21_grep_output)\n"
            if [[ $(diff -q ./grep_output ./s21_grep_output) ]]
            then
            echo "____________________________________________________________"
            echo -e "\nFAIL: test failed while testing $textfile pattern $pattern option -$option\n"
            fi
        done
    done
done

for option in i v c l n h s
    do
        for second_option in i v c l n h s
        do
            for pattern in count mrt Age rH
            do
                echo "TEST file text1.txt pattern $pattern option -$option -$second_option:"
                ./s21_grep -$option$second_option $pattern text1.txt > s21_grep_output
                grep -$option$second_option $pattern text1.txt > grep_output
                echo -e "$(diff -s grep_output s21_grep_output)\n"
                if [[ $(diff -q ./grep_output ./s21_grep_output) ]]
                then
                echo "____________________________________________________________"
                echo -e "\nFAIL: test failed while testing text1.txt pattern $pattern option -$option second_option $second_option\n"
                fi
            done
        done
done



for textfile in text1.txt text2.txt text3.txt
do
        echo "TEST file $textfile -ie R:"
        ./s21_grep -ie R $textfile > s21_grep_output
        grep -ie R $textfile > grep_output
        echo -e "$(diff -s grep_output s21_grep_output)\n"
        if [[ $(diff -q ./grep_output ./s21_grep_output) ]]
        then
        echo "____________________________________________________________"
        echo -e "\nFAIL: test failed while testing $textfile -ie R\n"
        fi
done

for textfile in text1.txt text2.txt text3.txt
do
        echo "TEST file $textfile -f patterns_tests.txt:"
        ./s21_grep -f patterns_tests.txt $textfile > s21_grep_output
        grep -f patterns_tests.txt $textfile > grep_output
        echo -e "$(diff -s grep_output s21_grep_output)\n"
        if [[ $(diff -q ./grep_output ./s21_grep_output) ]]
        then
        echo "____________________________________________________________"
        echo -e "\nFAIL: test failed while testing $textfile -f patterns_tests.txt\n"
        fi
done

echo "TEST files text1.txt text2.txt text3.txt:"
./s21_grep R text1.txt text2.txt text3.txt > s21_grep_output
grep R text1.txt text2.txt text3.txt > grep_output
echo -e "$(diff -s grep_output s21_grep_output)\n"
if [[ $(diff -q ./grep_output ./s21_grep_output) ]]
then
echo "____________________________________________________________"
echo -e "\nFAIL: test failed while testing multiple files\n"
fi

rm -rf s21_grep_output
rm -rf grep_output
