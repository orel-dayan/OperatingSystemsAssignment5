#!/bin/bash

# Clean and build the project
make clean
make all
if [ $? -ne 0 ]; then
    echo "Compilation failed =("
    exit 1
fi

# Function to check if a number is prime
function is_prime() {
    num=$1
    if [ "$num" -lt 2 ]; then
        return 1
    fi
    if [ "$num" -eq 2 ]; then
        return 0
    fi
    if [ $((num % 2)) -eq 0 ]; then
        return 1
    fi
    for ((i=3;i*i<=num;i+=2)); do
        if [ $((num % i)) -eq 0 ]; then
            return 1
        fi
    done
    return 0
}

# Flag to track if all checks passed
all_checks_passed=true

# Perform the checks 5 times
for iteration in {1..5}; do
    echo "Iteration $iteration"

    # Check if two executions of ./st_pipeline with different random numbers have the same output
    random_number1=$((RANDOM % 5 + 1))
    random_number2=$((RANDOM % 999999))
    echo "Running ./st_pipeline $random_number1 $random_number2 twice..."
    output1=$(./st_pipeline $random_number1 $random_number2)
    output2=$(./st_pipeline $random_number1 $random_number2)

    if [ "$output1" != "$output2" ]; then
        echo "Output is not the same! =("
        all_checks_passed=false
    else
	    echo "Output is the same, now checking all the numbers if prime or not like declered..."
	    # Check if the numbers labeled as 'true' are prime and the rest are not
	    prev_line=0
	    while read -r line; do
		if [[ "$line" == "true" ]]; then
		    is_prime $prev_line
		    if [ $? -ne 0 ]; then
		        echo "Number $line is not prime but labeled as true! =("
		        all_checks_passed=false
		    fi
		elif [[ "$line" == "false" ]]; then
		    is_prime $prev_line
		    if [ $? -eq 0 ]; then
		        echo "Number $line is prime but not labeled as true! =("
		        all_checks_passed=false
		    fi
		fi
		prev_line=$line
	    done <<< "$output1"
    fi
done

# Perform memory check separately after the above checks
echo "Running memory checks..."
valgrind_output=$(valgrind --leak-check=full ./st_pipeline $random_number1 $random_number2 2>&1)

# Check for memory leaks in the output of valgrind
if echo "$valgrind_output" | grep -q "no leaks are possible"; then
    echo "No memory leaks detected"
else
    echo "Memory leaks detected! =("
    all_checks_passed=false
fi


if [ "$all_checks_passed" = true ]; then
    echo "All checks passed =)"
else
    echo "Some checks failed! =("
fi
