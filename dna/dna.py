import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("OUTPUT: python dna.py database.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    rows = []
    with open(sys.argv[1]) as database:
        reader = csv.DictReader(database)
        header = reader.fieldnames
        for row in reader:
            rows.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as sequenceFile:
        sequence = sequenceFile.read()

    # Find longest match of each STR in DNA sequence
    STR = []
    for i in range(1, len(header)):
        STR.append(str(longest_match(sequence, header[i])))

    # Check database for matching profiles
    for i in range(len(rows)):
        STRCount = 0
        for j in range(1, len(header)):
            if rows[i][header[j]] == STR[j - 1]:
                STRCount += 1
        if STRCount == len(header) - 1:
            print(rows[i]["name"])
            return
    print("No match")
    return


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
