import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as csvfile:
        reader = csv.DictReader(csvfile)
        csv_list = list(reader)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as txtfile:
        dna = txtfile.read()

    # TODO: Find longest match of each STR in DNA sequence
    matches = {}
    for i in csv_list[0]:
        matches[i] = longest_match(dna, i)

    # TODO: Check database for matching profiles
    # Setup a count variable to keep track of each matching str count
    count = 1
    # Base case if the name is not updated then no match will be printed by default
    name = "No match"
    # For each database entry
    for i in range(len(csv_list)):
        # For each str count
        for j in matches:
            # Check if they match
            if str(matches[j]) == csv_list[i][j]:
                # If yes then update the count
                count += 1
        # If all str counts are the same
        if count == len(matches):
            # Output the corresponding name
            name = csv_list[i]["name"]
            break
        # If there was no match then reset the count and start again
        else:
            count = 1

    print(name)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
